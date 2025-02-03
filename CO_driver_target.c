/*
 * CAN module object for generic microcontroller.
 *
 * This file is a template for other microcontrollers.
 *
 * @file        CO_driver.c
 * @ingroup     CO_driver
 * @author      Janez Paternoster
 * @copyright   2004 - 2020 Janez Paternoster
 *
 * This file is part of <https://github.com/CANopenNode/CANopenNode>, a CANopen Stack.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 */

#include "301/CO_driver.h"
#include <assert.h>
#include <string.h>


//! Общий драйвер.
static CO_driver_t CO_drv;


CO_driver_t* CO_driver_init()
{
    memset(&CO_drv, 0x0, sizeof(CO_drv));

    return &CO_drv;
}

void CO_driver_deinit(CO_driver_t* drv)
{
    (void) drv;
}

CO_driver_t* CO_driver()
{
    return &CO_drv;
}

CO_driver_id_t CO_driver_add_port(CO_driver_t* drv, const char* driver_name, const CO_driver_port_api_t* port_api)
{
    assert(drv != NULL);

    if(port_api == NULL) return CO_DRIVER_ID_INVALID;

    CO_driver_id_t finded_id = CO_driver_find_port(drv, driver_name);
    if(finded_id != CO_DRIVER_ID_INVALID) return CO_DRIVER_ID_INVALID;

    CO_driver_t* codrv = (CO_driver_t*)drv;

    size_t i;
    for(i = 0; i < CO_DRIVERS_COUNT; i ++){
        if(codrv->ports[i].port_api == NULL){
            codrv->ports[i].driver_name = driver_name;
            codrv->ports[i].port_api = port_api;
//            codrv->ports[i].CANptr = NULL;

            return i;
        }
    }

    return CO_DRIVER_ID_INVALID;
}

void CO_driver_del_port(CO_driver_t* drv, CO_driver_id_t drvid)
{
    assert(drv != NULL);

    if(drvid == CO_DRIVER_ID_INVALID || drvid >= CO_DRIVERS_COUNT) return;

    CO_driver_t* codrv = (CO_driver_t*)drv;

    codrv->ports[drvid].port_api = NULL;
//    codrv->ports[drvid].CANptr = NULL;
}

CO_driver_id_t CO_driver_find_port(CO_driver_t* drv, const char* driver_name)
{
    assert(drv != NULL);

    if(driver_name == NULL) return CO_DRIVER_ID_INVALID;

    size_t i;
    for(i = 0; i < CO_DRIVERS_COUNT; i ++){
        CO_driver_port_t* port = &drv->ports[i];

        if(strcmp(port->driver_name, driver_name) == 0) return i;
    }

    return CO_DRIVER_ID_INVALID;
}

void* CO_driver_calloc(size_t count, size_t size)
{
    CO_driver_t* codrv = &CO_drv;
    CO_driver_pool_t* pool = &codrv->pool;

    size_t needed = count * size;
    size_t avail = CO_DRIVER_POOL_SIZE - pool->empty_ptr;

    if(needed > avail) return NULL;

    void* ptr = &pool->data[pool->empty_ptr];

    memset(ptr, 0x0, needed);

    pool->empty_ptr += needed;

    return ptr;
}

void CO_driver_free(void* ptr)
{
    (void) ptr;
}


void
CO_CANsetConfigurationMode(void* CANptr) {
    /* Put CAN module in configuration mode */
    if(CANptr == NULL) return;

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_driver_CAN_t* drvcan = (CO_driver_CAN_t*)CANptr;
    CO_driver_id_t drvid = CO_driver_find_port(codrv, drvcan->driver_name);

    if(drvid == CO_DRIVER_ID_INVALID || drvid >= CO_DRIVERS_COUNT) return;

    const CO_driver_port_api_t* port_api = codrv->ports[drvid].port_api;

    if(port_api == NULL || port_api->CO_CANsetConfigurationMode) return;

    port_api->CO_CANsetConfigurationMode(drvcan->CANptr);
}

void
CO_CANsetNormalMode(CO_CANmodule_t* CANmodule) {
    /* Put CAN module in normal mode */
    if(CANmodule == NULL) return;

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_driver_id_t drvid = CANmodule->driver_id;

    if(drvid == CO_DRIVER_ID_INVALID || drvid >= CO_DRIVERS_COUNT) return;

    const CO_driver_port_api_t* port_api = codrv->ports[drvid].port_api;

    if(port_api == NULL || port_api->CO_CANsetNormalMode) return;

    port_api->CO_CANsetNormalMode(CANmodule);

    CANmodule->CANnormal = true;
}

CO_ReturnError_t
CO_CANmodule_init(CO_CANmodule_t* CANmodule, void* CANptr, CO_CANrx_t rxArray[], uint16_t rxSize, CO_CANtx_t txArray[],
                  uint16_t txSize, uint16_t CANbitRate) {

    /* verify arguments */
    if (CANmodule == NULL || CANptr == NULL || rxArray == NULL || txArray == NULL) {
        return CO_ERROR_ILLEGAL_ARGUMENT;
    }

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_driver_CAN_t* drvcan = (CO_driver_CAN_t*)CANptr;
    CO_driver_id_t drvid = CO_driver_find_port(codrv, drvcan->driver_name);

    if(drvid == CO_DRIVER_ID_INVALID || drvid >= CO_DRIVERS_COUNT) return CO_ERROR_INVALID_STATE;

    const CO_driver_port_api_t* port_api = codrv->ports[drvid].port_api;

    if(port_api == NULL || port_api->CO_CANmodule_init) return CO_ERROR_INVALID_STATE;

    CO_ReturnError_t ret = port_api->CO_CANmodule_init(CANmodule, drvcan->CANptr, rxArray, rxSize, txArray, txSize, CANbitRate);

    CANmodule->driver_id = drvid;

    return ret;
}

void
CO_CANmodule_disable(CO_CANmodule_t* CANmodule) {
    if (CANmodule == NULL || CANmodule->CANptr == NULL) return;

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_driver_id_t drvid = CANmodule->driver_id;

    if(drvid == CO_DRIVER_ID_INVALID || drvid >= CO_DRIVERS_COUNT) return;

    const CO_driver_port_api_t* port_api = codrv->ports[drvid].port_api;

    if(port_api == NULL || port_api->CO_CANmodule_disable) return;

    port_api->CO_CANmodule_disable(CANmodule);
}

CO_ReturnError_t
CO_CANrxBufferInit(CO_CANmodule_t* CANmodule, uint16_t index, uint16_t ident, uint16_t mask, bool_t rtr, void* object,
                   void (*CANrx_callback)(void* object, void* message)) {
    CO_ReturnError_t ret = CO_ERROR_NO;

    if ((CANmodule != NULL) && (CANmodule->CANptr != NULL) && (object != NULL) && (CANrx_callback != NULL) && (index < CANmodule->rxSize)) {

        CO_driver_t* codrv = (CO_driver_t*)CO_driver();
        CO_driver_id_t drvid = CANmodule->driver_id;

        if(drvid == CO_DRIVER_ID_INVALID || drvid >= CO_DRIVERS_COUNT) return CO_ERROR_INVALID_STATE;

        const CO_driver_port_api_t* port_api = codrv->ports[drvid].port_api;

        if(port_api == NULL || port_api->CO_CANrxBufferInit) return CO_ERROR_INVALID_STATE;

        ret = port_api->CO_CANrxBufferInit(CANmodule, index, ident, mask, rtr, object, CANrx_callback);

    } else {
        ret = CO_ERROR_ILLEGAL_ARGUMENT;
    }

    return ret;
}

CO_CANtx_t*
CO_CANtxBufferInit(CO_CANmodule_t* CANmodule, uint16_t index, uint16_t ident, bool_t rtr, uint8_t noOfBytes,
                   bool_t syncFlag) {
    CO_CANtx_t* buffer = NULL;

    if ((CANmodule != NULL) && (CANmodule->CANptr != NULL) && (index < CANmodule->txSize)) {

        CO_driver_t* codrv = (CO_driver_t*)CO_driver();
        CO_driver_id_t drvid = CANmodule->driver_id;

        if(drvid == CO_DRIVER_ID_INVALID || drvid >= CO_DRIVERS_COUNT) return NULL;

        const CO_driver_port_api_t* port_api = codrv->ports[drvid].port_api;

        if(port_api == NULL || port_api->CO_CANtxBufferInit) return NULL;

        buffer = port_api->CO_CANtxBufferInit(CANmodule, index, ident, rtr, noOfBytes, syncFlag);
    }

    return buffer;
}

CO_ReturnError_t
CO_CANsend(CO_CANmodule_t* CANmodule, CO_CANtx_t* buffer) {
    CO_ReturnError_t err = CO_ERROR_NO;

    /* verify arguments */
    if (CANmodule == NULL || CANmodule->CANptr == NULL || buffer == NULL) {
        return CO_ERROR_ILLEGAL_ARGUMENT;
    }

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_driver_id_t drvid = CANmodule->driver_id;

    if(drvid == CO_DRIVER_ID_INVALID || drvid >= CO_DRIVERS_COUNT) return CO_ERROR_INVALID_STATE;

    const CO_driver_port_api_t* port_api = codrv->ports[drvid].port_api;

    if(port_api == NULL || port_api->CO_CANsend) return CO_ERROR_INVALID_STATE;

    port_api->CO_CANsend(CANmodule, buffer);

    return CO_ERROR_NO;

    return err;
}


void
CO_CANclearPendingSyncPDOs(CO_CANmodule_t* CANmodule) {
    if (CANmodule == NULL || CANmodule->CANptr == NULL) return;

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_driver_id_t drvid = CANmodule->driver_id;

    if(drvid == CO_DRIVER_ID_INVALID || drvid >= CO_DRIVERS_COUNT) return;

    const CO_driver_port_api_t* port_api = codrv->ports[drvid].port_api;

    if(port_api == NULL || port_api->CO_CANclearPendingSyncPDOs) return;

    port_api->CO_CANclearPendingSyncPDOs(CANmodule);
}


void
CO_CANmodule_process(CO_CANmodule_t* CANmodule) {
    if (CANmodule == NULL || CANmodule->CANptr == NULL) return;

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_driver_id_t drvid = CANmodule->driver_id;

    if(drvid == CO_DRIVER_ID_INVALID || drvid >= CO_DRIVERS_COUNT) return;

    const CO_driver_port_api_t* port_api = codrv->ports[drvid].port_api;

    if(port_api == NULL || port_api->CO_CANmodule_process) return;

    port_api->CO_CANmodule_process(CANmodule);
}


void
CO_CANinterrupt(CO_CANmodule_t* CANmodule) {
    if (CANmodule == NULL || CANmodule->CANptr == NULL) return;

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_driver_id_t drvid = CANmodule->driver_id;

    if(drvid == CO_DRIVER_ID_INVALID || drvid >= CO_DRIVERS_COUNT) return;

    const CO_driver_port_api_t* port_api = codrv->ports[drvid].port_api;

    if(port_api == NULL || port_api->CO_CANinterrupt) return;

    port_api->CO_CANinterrupt(CANmodule);
}

