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

#if CAN_DRIVER & CAN_DRIVER_SLCAN

#include "CO_driver_slcan_slave.h"

#include "slcan/slcan_slave.h"
//#include <stdint.h>
//#include <stddef.h>
#include <stdbool.h>
#include <assert.h>




void
CO_CANsetConfigurationMode_slcan_slave(void* CANptr) {
    /* Put CAN module in configuration mode */
    if(CANptr == NULL) return;

    slcan_slave_t* slave = (slcan_slave_t*)CANptr;

    slcan_slave_flags_t flags = slcan_slave_flags(slave);
    flags &= ~(SLCAN_SLAVE_FLAG_OPENED | SLCAN_SLAVE_FLAG_CONFIGURED | SLCAN_SLAVE_FLAG_LISTEN_ONLY | SLCAN_SLAVE_FLAG_AUTO_POLL);
    slcan_slave_set_flags(slave, flags);

    slcan_slave_flush(slave, NULL);
    slcan_slave_reset(slave);
}

void
CO_CANsetNormalMode_slcan_slave(CO_CANmodule_t* CANmodule) {
    /* Put CAN module in normal mode */
    if(CANmodule == NULL) return;
    if(CANmodule->CANptr == NULL) return;

    slcan_slave_t* slave = (slcan_slave_t*)CANmodule->CANptr;

    slcan_slave_flags_t flags = slcan_slave_flags(slave);
    flags &= SLCAN_SLAVE_FLAG_LISTEN_ONLY;
    flags |= SLCAN_SLAVE_FLAG_OPENED | SLCAN_SLAVE_FLAG_CONFIGURED | SLCAN_SLAVE_FLAG_AUTO_POLL;
    slcan_slave_set_flags(slave, flags);

    CANmodule->CANnormal = true;
}

CO_ReturnError_t
CO_CANmodule_init_slcan_slave(CO_CANmodule_t* CANmodule, void* CANptr, CO_CANrx_t rxArray[], uint16_t rxSize, CO_CANtx_t txArray[],
                  uint16_t txSize, uint16_t CANbitRate) {
    uint16_t i;

    /* verify arguments */
    if (CANmodule == NULL || CANptr == NULL || rxArray == NULL || txArray == NULL) {
        return CO_ERROR_ILLEGAL_ARGUMENT;
    }

    /* Configure object variables */
    CANmodule->CANptr = CANptr;
    CANmodule->rxArray = rxArray;
    CANmodule->rxSize = rxSize;
    CANmodule->txArray = txArray;
    CANmodule->txSize = txSize;
    CANmodule->CANerrorStatus = 0;
    CANmodule->CANnormal = false;
    CANmodule->useCANrxFilters = false; //(rxSize <= 32U) ? true : false; /* microcontroller dependent */
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
    //slcan_slave_t* slave = (slcan_slave_t*)CANptr;

    /* Configure CAN timing */
    // slcan не нуждается в настройке битрейта CAN.

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
CO_CANmodule_disable_slcan_slave(CO_CANmodule_t* CANmodule) {
    if (CANmodule != NULL) {
        /* turn off the module */
    }
}

CO_ReturnError_t
CO_CANrxBufferInit_slcan_slave(CO_CANmodule_t* CANmodule, uint16_t index, uint16_t ident, uint16_t mask, bool_t rtr, void* object,
                   void (*CANrx_callback)(void* object, void* message)) {
    CO_ReturnError_t ret = CO_ERROR_NO;

    if ((CANmodule != NULL) && (object != NULL) && (CANrx_callback != NULL) && (index < CANmodule->rxSize)) {
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
        if (CANmodule->useCANrxFilters) {}
    } else {
        ret = CO_ERROR_ILLEGAL_ARGUMENT;
    }

    return ret;
}

CO_CANtx_t*
CO_CANtxBufferInit_slcan_slave(CO_CANmodule_t* CANmodule, uint16_t index, uint16_t ident, bool_t rtr, uint8_t noOfBytes,
                   bool_t syncFlag) {
    CO_CANtx_t* buffer = NULL;

    if ((CANmodule != NULL) && (index < CANmodule->txSize)) {
        /* get specific buffer */
        buffer = &CANmodule->txArray[index];

        /* CAN identifier, DLC and rtr, bit aligned with CAN module transmit buffer, microcontroller specific. */
        buffer->ident = ((uint32_t)ident & 0x07FFU)/* | ((uint32_t)(((uint32_t)noOfBytes & 0xFU) << 11U))*/
                        | ((uint32_t)(rtr ? 0x8000U : 0U));
        buffer->DLC = noOfBytes;
        buffer->bufferFull = false;
        buffer->syncFlag = syncFlag;
    }

    return buffer;
}


static bool can_send_msg(CO_CANmodule_t* CANmodule, CO_CANtx_t* buffer)
{
    if(CANmodule == NULL || CANmodule->CANptr == NULL || buffer == NULL) return false;

    slcan_slave_t* slave = CANmodule->CANptr;

    slcan_can_msg_t can_msg;

    can_msg.frame_type = ((buffer->ident & CO_CAN_ID_FLAG_RTR) == 0) ? SLCAN_CAN_FRAME_NORMAL : SLCAN_CAN_FRAME_RTR;
    can_msg.id_type = SLCAN_CAN_ID_NORMAL;
    can_msg.id = buffer->ident & CO_CAN_ID_MASK;
    can_msg.dlc = buffer->DLC;

    if(can_msg.frame_type == SLCAN_CAN_FRAME_NORMAL){
        int i;
        for(i = 0; i < can_msg.dlc; i ++){
            can_msg.data[i] = buffer->data[i];
        }
    }

    slcan_err_t err = slcan_slave_send_can_msg(slave, &can_msg, NULL);
    if(err != E_SLCAN_NO_ERROR) return false;

    return true;
}

static bool can_recv_msg(CO_CANmodule_t* CANmodule, CO_CANrxMsg_t* rxMsg)
{
    if(CANmodule == NULL || CANmodule->CANptr == NULL || rxMsg == NULL) return false;

    slcan_slave_t* slave = CANmodule->CANptr;

    slcan_can_msg_t can_msg;

    if(slcan_slave_recv_can_msg(slave, &can_msg) != E_SLCAN_NO_ERROR) return false;

    rxMsg->ident = (can_msg.id & CO_CAN_ID_MASK) | ((can_msg.frame_type == SLCAN_CAN_FRAME_NORMAL) ? 0x0 : CO_CAN_ID_FLAG_RTR);
    rxMsg->DLC = can_msg.dlc;

    if(can_msg.frame_type == SLCAN_CAN_FRAME_NORMAL){
        int i;
        for(i = 0; i < can_msg.dlc; i ++){
            rxMsg->data[i] = can_msg.data[i];
        }
    }

    return true;
}

static bool can_is_can_send_msg(CO_CANmodule_t* CANmodule)
{
    if(CANmodule == NULL || CANmodule->CANptr == NULL) return false;

    slcan_slave_t* slave = CANmodule->CANptr;

    return slcan_slave_send_can_msgs_avail(slave) != 0;
}


CO_ReturnError_t
CO_CANsend_slcan_slave(CO_CANmodule_t* CANmodule, CO_CANtx_t* buffer) {
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
    if (can_send_msg(CANmodule, buffer) && CANmodule->CANtxCount == 0) {
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
CO_CANclearPendingSyncPDOs_slcan_slave(CO_CANmodule_t* CANmodule) {
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
CO_CANmodule_process_slcan_slave(CO_CANmodule_t* CANmodule) {
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
CO_CANinterrupt_slcan_slave(CO_CANmodule_t* CANmodule) {

    CO_CANrxMsg_t rcvMsgData;

    /* receive interrupt */
    if (can_recv_msg(CANmodule, &rcvMsgData)) {
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
    else if (can_is_can_send_msg(CANmodule)) {
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
                    if(can_send_msg(CANmodule, buffer)){
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


static CO_driver_port_api_t port = {
        CO_CANsetConfigurationMode_slcan_slave,
        CO_CANsetNormalMode_slcan_slave,
        (CO_CANmodule_init_proc_t)CO_CANmodule_init_slcan_slave,
        CO_CANmodule_disable_slcan_slave,
        (CO_CANrxBufferInit_proc_t)CO_CANrxBufferInit_slcan_slave,
        CO_CANtxBufferInit_slcan_slave,
        (CO_CANsend_proc_t)CO_CANsend_slcan_slave,
        CO_CANclearPendingSyncPDOs_slcan_slave,
        CO_CANmodule_process_slcan_slave,
        CO_CANinterrupt_slcan_slave,
};

static CO_driver_id_t reg_drv_id = CO_DRIVER_ID_INVALID;

CO_driver_id_t CO_driver_init_slcan_slave(CO_driver_t* drv)
{
    assert(drv != NULL);

    if(reg_drv_id != CO_DRIVER_ID_INVALID) return reg_drv_id;

    reg_drv_id = CO_driver_add_port(drv, "slcan", &port);

    return reg_drv_id;
}

#endif
