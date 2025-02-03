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

#if CAN_DRIVER & CAN_DRIVER_HW

#include "cpu.h"
#include "CO_driver_xmc4xxx.h"
#include "can/can_xmc4xxx.h"
#include "hardware/config.h"

//#include <stdint.h>
//#include <stddef.h>
#include <stdbool.h>
#include <assert.h>



void
CO_CANsetConfigurationMode_xmc4xxx(void* CANptr) {
    /* Put CAN module in configuration mode */
    if(CANptr == NULL) return;

    can_node_t* can_node = (can_node_t*)CANptr;

    can_node_set_configuration_mode(can_node);
}

void
CO_CANsetNormalMode_xmc4xxx(CO_CANmodule_t* CANmodule) {
    /* Put CAN module in normal mode */
    if(CANmodule == NULL) return;
    if(CANmodule->CANptr == NULL) return;

    can_node_t* can_node = (can_node_t*)CANmodule->CANptr;

    can_node_set_normal_mode(can_node);

    CANmodule->CANnormal = true;
}

CO_ReturnError_t
CO_CANmodule_init_xmc4xxx(CO_CANmodule_t* CANmodule, void* CANptr, CO_CANrx_t rxArray[], uint16_t rxSize, CO_CANtx_t txArray[],
                  uint16_t txSize, uint16_t CANbitRate) {
    uint16_t i;

    /* verify arguments */
    if (CANmodule == NULL || CANptr == NULL || rxArray == NULL || txArray == NULL) {
        return CO_ERROR_ILLEGAL_ARGUMENT;
    }

    can_node_t* can_node = (can_node_t*)CANmodule->CANptr;

    /* Configure object variables */
    CANmodule->CANptr = CANptr;
    CANmodule->rxArray = rxArray;
    CANmodule->rxSize = rxSize;
    CANmodule->txArray = txArray;
    CANmodule->txSize = txSize;
    CANmodule->CANerrorStatus = 0;
    CANmodule->CANnormal = false;
    CANmodule->useCANrxFilters = true;//(rxSize <= (CAN_RX_FILTERS_COUNT)) ? true : false; /* microcontroller dependent */
    CANmodule->bufferInhibitFlag = false;
    CANmodule->firstCANtxMessage = true;
    CANmodule->CANtxCount = 0U;
    CANmodule->errOld = 0U;

    for (i = 0U; i < rxSize; i++) {
        rxArray[i].ident = 0U;
        rxArray[i].mask = 0xFFFFU;
        rxArray[i].object = NULL;
        rxArray[i].pCANrx_callback = NULL;
    }
    for (i = 0U; i < txSize; i++) {
        txArray[i].bufferFull = false;
    }

    /* Configure CAN module registers */
#warning CAN node initialization!

    /* Configure CAN timing */
    can_bit_rate_t bit_rate = CAN_BIT_RATE_125kbit;
    switch(CANbitRate){
    default: break;
    case 10: bit_rate = CAN_BIT_RATE_10kbit; break;
    case 20: bit_rate = CAN_BIT_RATE_20kbit; break;
    case 50: bit_rate = CAN_BIT_RATE_50kbit; break;
    case 100: bit_rate = CAN_BIT_RATE_100kbit; break;
    case 125: bit_rate = CAN_BIT_RATE_125kbit; break;
    case 250: bit_rate = CAN_BIT_RATE_250kbit; break;
    case 500: bit_rate = CAN_BIT_RATE_500kbit; break;
    case 800: bit_rate = CAN_BIT_RATE_800kbit; break;
    case 1000: bit_rate = CAN_BIT_RATE_1000kbit; break;
    }
    can_node_set_bitrate(can_node, bit_rate);

    /* Configure CAN module hardware filters */
    if (CANmodule->useCANrxFilters) {
        /* CAN module filters are used, they will be configured with */
        /* CO_CANrxBufferInit() functions, called by separate CANopen */
        /* init functions. */
        /* Configure all masks so, that received message must match filter */
    } else {
        /* CAN module filters are not used, all messages with standard 11-bit */
        /* identifier will be received */
        /* Configure mask 0 so, that all messages with standard identifier are accepted */
    }

    /* configure CAN interrupt registers */

    return CO_ERROR_NO;
}

void
CO_CANmodule_disable_xmc4xxx(CO_CANmodule_t* CANmodule) {
    if (CANmodule != NULL && CANmodule->CANptr != NULL) {
        can_node_t* can_node = (can_node_t*)CANmodule->CANptr;
        /* turn off the module */
        can_disable(can_node->can);
    }
}

CO_ReturnError_t
CO_CANrxBufferInit_xmc4xxx(CO_CANmodule_t* CANmodule, uint16_t index, uint16_t ident, uint16_t mask, bool_t rtr, void* object,
                   void (*CANrx_callback)(void* object, void* message)) {
    CO_ReturnError_t ret = CO_ERROR_NO;

    if ((CANmodule != NULL) && (CANmodule->CANptr != NULL) && (object != NULL) && (CANrx_callback != NULL) && (index < CANmodule->rxSize)) {

        can_node_t* can_node = (can_node_t*)CANmodule->CANptr;

        /* buffer, which will be configured */
        CO_CANrx_t* buffer = &CANmodule->rxArray[index];

        /* Configure object variables */
        buffer->object = object;
        buffer->pCANrx_callback = CANrx_callback;

        /* CAN identifier and CAN mask, bit aligned with CAN module. Different on different microcontrollers. */
        buffer->ident = ident & 0x07FFU;
        if (rtr) {
            buffer->ident |= 0x0800U;
        }
        buffer->mask = (mask & 0x07FFU) | 0x0800U;

        /* Set CAN hardware module filter and mask. */
        if(CANmodule->useCANrxFilters){
            can_node_init_rx_buffer(can_node, index, ident, mask, rtr);
        }else{
            can_node_init_rx_buffer(can_node, index, ident, 0, rtr);
        }
    } else {
        ret = CO_ERROR_ILLEGAL_ARGUMENT;
    }

    return ret;
}

CO_CANtx_t*
CO_CANtxBufferInit_xmc4xxx(CO_CANmodule_t* CANmodule, uint16_t index, uint16_t ident, bool_t rtr, uint8_t noOfBytes,
                   bool_t syncFlag) {
    CO_CANtx_t* buffer = NULL;

    if ((CANmodule != NULL) && (CANmodule->CANptr != NULL) && (index < CANmodule->txSize)) {

        can_node_t* can_node = (can_node_t*)CANmodule->CANptr;

        /* get specific buffer */
        buffer = &CANmodule->txArray[index];

        /* CAN identifier, DLC and rtr, bit aligned with CAN module transmit buffer, microcontroller specific. */
        buffer->ident = ((uint32_t)ident & 0x07FFU)/* | ((uint32_t)(((uint32_t)noOfBytes & 0xFU) << 11U))*/
                        | ((uint32_t)(rtr ? 0x8000U : 0U));
        buffer->DLC = noOfBytes;
        buffer->bufferFull = false;
        buffer->syncFlag = syncFlag;

        can_node_init_tx_buffer(can_node, index, ident, rtr, noOfBytes);
    }

    return buffer;
}


static bool CO_driver_can_send_msg(CO_CANmodule_t* CANmodule, CO_CANtx_t* buffer)
{
    if(CANmodule == NULL || CANmodule->CANptr == NULL || buffer == NULL) return false;

    can_node_t* can_node = (can_node_t*)CANmodule->CANptr;

    can_msg_t can_msg;

    can_msg.rtr = ((buffer->ident & CO_CAN_ID_FLAG_RTR) == 0) ? 0 : 1;
    can_msg.ide = 0;
    can_msg.id = buffer->ident & CO_CAN_ID_MASK;
    can_msg.dlc = buffer->DLC;

    if(can_msg.rtr == 0){
        int i;
        for(i = 0; i < can_msg.dlc; i ++){
            can_msg.data[i] = buffer->data[i];
        }
    }

    ptrdiff_t buf_index = ((ptrdiff_t)buffer - (ptrdiff_t)CANmodule->txArray) / sizeof(CANmodule->txArray[0]);

    err_t err = can_node_send_msg(can_node, buf_index, &can_msg);
    if(err != E_NO_ERROR) return false;

    return true;
}

static bool CO_driver_can_recv_msg(CO_CANmodule_t* CANmodule, CO_CANrxMsg_t* rxMsg)
{
    if(CANmodule == NULL || CANmodule->CANptr == NULL || rxMsg == NULL) return false;

    can_node_t* can_node = (can_node_t*)CANmodule->CANptr;

    can_msg_t can_msg;

    ptrdiff_t buf_index = ((ptrdiff_t)rxMsg - (ptrdiff_t)CANmodule->rxArray) / sizeof(CANmodule->rxArray[0]);

    if(can_node_recv_msg(can_node, buf_index, &can_msg) != E_NO_ERROR) return false;

    rxMsg->ident = (can_msg.id & CO_CAN_ID_MASK) | ((can_msg.rtr == 0) ? 0x0 : CO_CAN_ID_FLAG_RTR);
    rxMsg->DLC = can_msg.dlc;

    if(can_msg.rtr == 0){
        int i;
        for(i = 0; i < can_msg.dlc; i ++){
            rxMsg->data[i] = can_msg.data[i];
        }
    }

    return true;
}

static bool CO_driver_can_is_can_send_msg(CO_CANmodule_t* CANmodule)
{
    if(CANmodule == NULL || CANmodule->CANptr == NULL) return false;

    can_node_t* can_node = (can_node_t*)CANmodule->CANptr;

    return false; //slcan_slave_send_can_msgs_avail(slave) != 0;
}


CO_ReturnError_t
CO_CANsend_xmc4xxx(CO_CANmodule_t* CANmodule, CO_CANtx_t* buffer) {
    CO_ReturnError_t err = CO_ERROR_NO;

    /* Verify overflow */
    if (buffer->bufferFull) {
        if (!CANmodule->firstCANtxMessage) {
            /* don't set error, if bootup message is still on buffers */
            CANmodule->CANerrorStatus |= CO_CAN_ERRTX_OVERFLOW;
        }
        err = CO_ERROR_TX_OVERFLOW;
    }

    CO_LOCK_CAN_SEND(CANmodule);
    /* if CAN TX buffer is free, copy message to it */
    if (CO_driver_can_send_msg(CANmodule, buffer) && CANmodule->CANtxCount == 0) {
        CANmodule->bufferInhibitFlag = buffer->syncFlag;
        /* copy message and txRequest */
        // copied in can_send_msg(...).
    }
    /* if no buffer is free, message will be sent by interrupt */
    else {
        buffer->bufferFull = true;
        CANmodule->CANtxCount++;
    }
    CO_UNLOCK_CAN_SEND(CANmodule);

    return err;
}

void
CO_CANclearPendingSyncPDOs_xmc4xxx(CO_CANmodule_t* CANmodule) {
    uint32_t tpdoDeleted = 0U;

    CO_LOCK_CAN_SEND(CANmodule);
    /* Abort message from CAN module, if there is synchronous TPDO.
     * Take special care with this functionality. */
    if (/* messageIsOnCanBuffer && */ CANmodule->bufferInhibitFlag) {
        /* clear TXREQ */
        CANmodule->bufferInhibitFlag = false;
        tpdoDeleted = 1U;
    }
    /* delete also pending synchronous TPDOs in TX buffers */
    if (CANmodule->CANtxCount != 0U) {
        uint16_t i;
        CO_CANtx_t* buffer = &CANmodule->txArray[0];
        for (i = CANmodule->txSize; i > 0U; i--) {
            if (buffer->bufferFull) {
                if (buffer->syncFlag) {
                    buffer->bufferFull = false;
                    CANmodule->CANtxCount--;
                    tpdoDeleted = 2U;
                }
            }
            buffer++;
        }
    }
    CO_UNLOCK_CAN_SEND(CANmodule);

    if (tpdoDeleted != 0U) {
        CANmodule->CANerrorStatus |= CO_CAN_ERRTX_PDO_LATE;
    }
}

/* Get error counters from the module. If necessary, function may use different way to determine errors. */
static uint16_t rxErrors = 0, txErrors = 0, overflow = 0;

void
CO_CANmodule_process_xmc4xxx(CO_CANmodule_t* CANmodule) {
    uint32_t err;

    err = ((uint32_t)txErrors << 16) | ((uint32_t)rxErrors << 8) | overflow;

    if (CANmodule->errOld != err) {
        uint16_t status = CANmodule->CANerrorStatus;

        CANmodule->errOld = err;

        if (txErrors >= 256U) {
            /* bus off */
            status |= CO_CAN_ERRTX_BUS_OFF;
        } else {
            /* recalculate CANerrorStatus, first clear some flags */
            status &= 0xFFFF
                      ^ (CO_CAN_ERRTX_BUS_OFF | CO_CAN_ERRRX_WARNING | CO_CAN_ERRRX_PASSIVE | CO_CAN_ERRTX_WARNING
                         | CO_CAN_ERRTX_PASSIVE);

            /* rx bus warning or passive */
            if (rxErrors >= 128) {
                status |= CO_CAN_ERRRX_WARNING | CO_CAN_ERRRX_PASSIVE;
            } else if (rxErrors >= 96) {
                status |= CO_CAN_ERRRX_WARNING;
            }

            /* tx bus warning or passive */
            if (txErrors >= 128) {
                status |= CO_CAN_ERRTX_WARNING | CO_CAN_ERRTX_PASSIVE;
            } else if (txErrors >= 96) {
                status |= CO_CAN_ERRTX_WARNING;
            }

            /* if not tx passive clear also overflow */
            if ((status & CO_CAN_ERRTX_PASSIVE) == 0) {
                status &= 0xFFFF ^ CO_CAN_ERRTX_OVERFLOW;
            }
        }

        if (overflow != 0) {
            /* CAN RX bus overflow */
            status |= CO_CAN_ERRRX_OVERFLOW;
        }

        CANmodule->CANerrorStatus = status;
    }
}


void
CO_CANinterrupt_xmc4xxx(CO_CANmodule_t* CANmodule) {

    CO_CANrxMsg_t rcvMsgData;

    /* receive interrupt */
    if (CO_driver_can_recv_msg(CANmodule, &rcvMsgData)) {
        CO_CANrxMsg_t* rcvMsg;     /* pointer to received message in CAN module */
        uint16_t index;            /* index of received message */
        uint32_t rcvMsgIdent;      /* identifier of the received message */
        CO_CANrx_t* buffer = NULL; /* receive message buffer from CO_CANmodule_t object. */
        bool_t msgMatched = false;

        rcvMsg = &rcvMsgData; /* get message from module here */
        rcvMsgIdent = rcvMsg->ident;
        if (CANmodule->useCANrxFilters) {
            /* CAN module filters are used. Message with known 11-bit identifier has been received */
            index = 0; /* get index of the received message here. Or something similar */
            if (index < CANmodule->rxSize) {
                buffer = &CANmodule->rxArray[index];
                /* verify also RTR */
                if (((rcvMsgIdent ^ buffer->ident) & buffer->mask) == 0U) {
                    msgMatched = true;
                }
            }
        } else {
            /* CAN module filters are not used, message with any standard 11-bit identifier */
            /* has been received. Search rxArray form CANmodule for the same CAN-ID. */
            buffer = &CANmodule->rxArray[0];
            for (index = CANmodule->rxSize; index > 0U; index--) {
                if (((rcvMsgIdent ^ buffer->ident) & buffer->mask) == 0U) {
                    msgMatched = true;
                    break;
                }
                buffer++;
            }
        }

        /* Call specific function, which will process the message */
        if (msgMatched && (buffer != NULL) && (buffer->pCANrx_callback != NULL)) {
            buffer->pCANrx_callback(buffer->object, (void*)rcvMsg);
        }

        /* Clear interrupt flag */
    }

    /* transmit interrupt */
    else if (CO_driver_can_is_can_send_msg(CANmodule)) {
        /* Clear interrupt flag */

        /* First CAN message (bootup) was sent successfully */
        CANmodule->firstCANtxMessage = false;
        /* clear flag from previous message */
        CANmodule->bufferInhibitFlag = false;
        /* Are there any new messages waiting to be send */
        if (CANmodule->CANtxCount > 0U) {
            uint16_t i; /* index of transmitting message */

            /* first buffer */
            CO_CANtx_t* buffer = &CANmodule->txArray[0];
            /* search through whole array of pointers to transmit message buffers. */
            for (i = CANmodule->txSize; i > 0U; i--) {
                /* if message buffer is full, send it. */
                if (buffer->bufferFull) {
                    if(CO_driver_can_send_msg(CANmodule, buffer)){
                        buffer->bufferFull = false;
                        CANmodule->CANtxCount--;

                        /* Copy message to CAN buffer */
                        CANmodule->bufferInhibitFlag = buffer->syncFlag;
                        /* canSend... */
                        //break; /* exit for loop */
                    }
                }
                buffer++;
            } /* end of for loop */

            /* Clear counter if no more messages */
            if (i == 0U) {
                CANmodule->CANtxCount = 0U;
            }
        }
    } else {
        /* some other interrupt reason */
    }
}


static const CO_driver_port_api_t port = {
        CO_CANsetConfigurationMode_xmc4xxx,
        CO_CANsetNormalMode_xmc4xxx,
        (CO_CANmodule_init_proc_t)CO_CANmodule_init_xmc4xxx,
        CO_CANmodule_disable_xmc4xxx,
        (CO_CANrxBufferInit_proc_t)CO_CANrxBufferInit_xmc4xxx,
        CO_CANtxBufferInit_xmc4xxx,
        (CO_CANsend_proc_t)CO_CANsend_xmc4xxx,
        CO_CANclearPendingSyncPDOs_xmc4xxx,
        CO_CANmodule_process_xmc4xxx,
        CO_CANinterrupt_xmc4xxx,
};

static CO_driver_id_t reg_drv_id = CO_DRIVER_ID_INVALID;

CO_driver_id_t CO_driver_init_xmc4xxx(CO_driver_t* drv)
{
    if(drv == NULL) return CO_DRIVER_ID_INVALID;

    if(reg_drv_id != CO_DRIVER_ID_INVALID) return reg_drv_id;

    reg_drv_id = CO_driver_add_port(drv, CO_DRIVER_XMC4XXX_NAME, &port);

    return reg_drv_id;
}

#endif
