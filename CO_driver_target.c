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


//! Тип общего драйвера.
typedef struct _S_CO_driver {
    CO_driver_port_api_t* port[CO_DRIVERS_COUNT];
} CO_driver_t;

//! Общий драйвер.
static CO_driver_t CO_drv;


//! Размер пула драйвера.
#define CO_DRIVER_POOL_SIZE 1024

//! Тип пула драйвера.
typedef struct _S_CO_Driver_Pool {
    uint8_t data[CO_DRIVER_POOL_SIZE]; //!< Данные.
    size_t empty_ptr; //!< Индекс свободных данных.
} CO_driver_pool_t;

//! Пул драйвера.
static CO_driver_pool_t CO_pool;


void* CO_driver_init(void* arg)
{
    (void) arg;

    memset(&CO_drv, 0x0, sizeof(CO_drv));
    memset(&CO_pool, 0x0, sizeof(CO_pool));

    return &CO_drv;
}

void CO_driver_deinit(void* drv)
{
    (void) drv;
}

void* CO_driver()
{
    return &CO_drv;
}

CO_driver_id_t CO_driver_add_port(void* drv, CO_driver_port_api_t* port)
{
    assert(drv != NULL);

    CO_driver_t* codrv = (CO_driver_t*)drv;

    size_t i;
    for(i = 0; i < CO_DRIVERS_COUNT; i ++){
        if(codrv->port[i] == NULL){
            codrv->port[i] = port;
            return i;
        }
    }

    return CO_DRIVER_ID_INVALID;
}

void CO_driver_del_port(void* drv, CO_driver_id_t drvid)
{
    assert(drv != NULL);

    if(drvid >= CO_DRIVERS_COUNT) return;

    CO_driver_t* codrv = (CO_driver_t*)drv;

    codrv->port[drvid] = NULL;
}

void* CO_driver_calloc(size_t count, size_t size)
{
    size_t needed = count * size;
    size_t avail = CO_DRIVER_POOL_SIZE - CO_pool.empty_ptr;

    if(needed > avail) return NULL;

    void* ptr = &CO_pool.data[CO_pool.empty_ptr];

    memset(ptr, 0x0, needed);

    CO_pool.empty_ptr += needed;

    return ptr;
}

void CO_driver_free(void* ptr)
{
    (void) ptr;
}


uint16_t
CO_CANrxMsg_readIdent(void* rxMsg) {
    assert(rxMsg != NULL);

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_CANrxMsg_t* msg = (CO_CANrxMsg_t*)rxMsg;

    return codrv->port[msg->driver_id]->CO_CANrxMsg_readIdent((void*)&msg->data);
}

uint8_t
CO_CANrxMsg_readDLC(void* rxMsg) {
    assert(rxMsg != NULL);

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_CANrxMsg_t* msg = (CO_CANrxMsg_t*)rxMsg;

    return codrv->port[msg->driver_id]->CO_CANrxMsg_readDLC((void*)&msg->data);
}

const uint8_t*
CO_CANrxMsg_readData(void* rxMsg) {
    assert(rxMsg != NULL);

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_CANrxMsg_t* msg = (CO_CANrxMsg_t*)rxMsg;

    return codrv->port[msg->driver_id]->CO_CANrxMsg_readData((void*)&msg->data);
}


void
CO_CANsetConfigurationMode(void* CANptr) {
    /* Put CAN module in configuration mode */
    if(CANptr == NULL) return;

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_driver_CAN_t* drvcan = (CO_driver_CAN_t*)CANptr;

    return codrv->port[drvcan->driver_id]->CO_CANsetConfigurationMode(drvcan->CANptr);
}

void
CO_CANsetNormalMode(CO_CANmodule_t* CANmodule) {
    /* Put CAN module in normal mode */
    if(CANmodule == NULL) return;

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_driver_CAN_t* drvcan = (CO_driver_CAN_t*)CANptr;

    codrv->port[drvcan->driver_id]->CO_CANsetNormalMode(drvcan->CANptr);

    CANmodule->CANnormal = true;
}

CO_ReturnError_t
CO_CANmodule_init(CO_CANmodule_t* CANmodule, void* CANptr, CO_CANrx_t rxArray[], uint16_t rxSize, CO_CANtx_t txArray[],
                  uint16_t txSize, uint16_t CANbitRate) {
    uint16_t i;

    /* verify arguments */
    if (CANmodule == NULL || CANptr == NULL || rxArray == NULL || txArray == NULL) {
        return CO_ERROR_ILLEGAL_ARGUMENT;
    }

    CO_driver_t* codrv = (CO_driver_t*)CO_driver();
    CO_driver_CAN_t* drvcan = (CO_driver_CAN_t*)CANptr;

    codrv->port[drvcan->driver_id]->CO_CANsetNormalMode(drvcan->CANptr);


    return CO_ERROR_NO;
}

void
CO_CANmodule_disable(CO_CANmodule_t* CANmodule) {
    if (CANmodule != NULL && CANmodule->CANptr != NULL) {
    }
}

CO_ReturnError_t
CO_CANrxBufferInit(CO_CANmodule_t* CANmodule, uint16_t index, uint16_t ident, uint16_t mask, bool_t rtr, void* object,
                   void (*CANrx_callback)(void* object, void* message)) {
    CO_ReturnError_t ret = CO_ERROR_NO;

    if ((CANmodule != NULL) && (CANmodule->CANptr != NULL) && (object != NULL) && (CANrx_callback != NULL) && (index < CANmodule->rxSize)) {

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

    }

    return buffer;
}

CO_ReturnError_t
CO_CANsend(CO_CANmodule_t* CANmodule, CO_CANtx_t* buffer) {
    CO_ReturnError_t err = CO_ERROR_NO;



    return err;
}

void
CO_CANclearPendingSyncPDOs(CO_CANmodule_t* CANmodule) {

}

void
CO_CANmodule_process(CO_CANmodule_t* CANmodule) {

}


void
CO_CANinterrupt(CO_CANmodule_t* CANmodule) {

}

