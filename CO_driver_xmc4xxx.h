#ifndef CO_DRIVER_XMC4XXX_H_
#define CO_DRIVER_XMC4XXX_H_

#include "cpu.h"


/*
 * CO_driver_target.h definitions.
 */

/**
 * @defgroup CO_CAN_Message_reception Reception of CAN messages
 * @{
 *
 * Target specific definitions and description of CAN message reception
 *
 * CAN messages in CANopenNode are usually received by its own thread or higher priority interrupt. Received CAN
 * messages are first filtered by hardware or by software. Thread then examines its 11-bit CAN-id and mask and
 * determines, to which \ref CO_obj "CANopenNode Object" it belongs to. After that it calls predefined CANrx_callback()
 * function, which quickly pre-processes the message and fetches the relevant data. CANrx_callback() function is defined
 * by each \ref CO_obj "CANopenNode Object" separately. Pre-processed fetched data are later processed in another
 * thread.
 *
 * If \ref CO_obj "CANopenNode Object" reception of specific CAN message, it must first configure its own CO_CANrx_t
 * object with the CO_CANrxBufferInit() function.
 */

/**
 * CAN rx message structure.
 */
typedef struct {
    uint32_t ident;
    uint8_t DLC;
    uint8_t data[8];
} CO_CANrxMsg_xmc4xxx_t;

/**
 * CANrx_callback() can read CAN identifier from received CAN message
 *
 * Must be defined in the **CO_driver_target.h** file.
 *
 * This is target specific function and is specific for specific microcontroller. It is best to implement it by using
 * inline function or macro. `rxMsg` parameter should cast to a pointer to structure. For best efficiency structure may
 * have the same alignment as CAN registers inside CAN module.
 *
 * @param rxMsg Pointer to received message
 * @return 11-bit CAN standard identifier.
 */
static uint16_t
CO_CANrxMsg_readIdent_xmc4xxx(void* rxMsg) {
    return ((CO_CANrxMsg_xmc4xxx_t*)rxMsg)->ident;
}

/**
 * CANrx_callback() can read Data Length Code from received CAN message
 *
 * See also CO_CANrxMsg_readIdent():
 *
 * @param rxMsg Pointer to received message
 * @return data length in bytes (0 to 8)
 */
static uint8_t
CO_CANrxMsg_readDLC_xmc4xxx(void* rxMsg) {
    return ((CO_CANrxMsg_xmc4xxx_t*)rxMsg)->DLC;
}

/**
 * CANrx_callback() can read pointer to data from received CAN message
 *
 * See also CO_CANrxMsg_readIdent():
 *
 * @param rxMsg Pointer to received message
 * @return pointer to data buffer
 */
static const uint8_t*
CO_CANrxMsg_readData_xmc4xxx(void* rxMsg) {
    return ((CO_CANrxMsg_xmc4xxx_t*)rxMsg)->data;
}
/**
 * Configuration object for CAN received message for specific \ref CO_obj "CANopenNode Object".
 *
 * Must be defined in the **CO_driver_target.h** file.
 *
 * Data fields of this structure are used exclusively by the driver. Usually it has the following data fields, but they
 * may differ for different microcontrollers. Array of multiple CO_CANrx_t objects is included inside CO_CANmodule_t.
 */
typedef struct {
    uint16_t ident; /**< Standard CAN Identifier (bits 0..10) + RTR (bit 11) */
    uint16_t mask;  /**< Standard CAN Identifier mask with the same alignment as ident */
    void* object;   /**< \ref CO_obj "CANopenNode Object" initialized in from CO_CANrxBufferInit() */
    void (*pCANrx_callback)(void* object,
                            void* message); /**< Pointer to CANrx_callback() initialized in CO_CANrxBufferInit() */
} CO_CANrx_xmc4xxx_t;

/** @} */


/**
 * @defgroup CO_CAN_Message_transmission Transmission of CAN messages
 * @{
 *
 * Target specific definitions and description of CAN message transmission
 *
 * If \ref CO_obj "CANopenNode Object" needs transmitting CAN message, it must first configure its own CO_CANtx_t object
 * with the CO_CANtxBufferInit() function. CAN message can then be sent with CO_CANsend() function. If at that moment
 * CAN transmit buffer inside microcontroller's CAN module is free, message is copied directly to the CAN module.
 * Otherwise CO_CANsend() function sets _bufferFull_ flag to true. Message will be then sent by CAN TX interrupt as soon
 * as CAN module is freed. Until message is not copied to CAN module, its contents must not change. If there are
 * multiple CO_CANtx_t objects with _bufferFull_ flag set to true, then CO_CANtx_t with lower index will be sent first.
 */

/**
 * Configuration object for CAN transmit message for specific \ref CO_obj "CANopenNode Object".
 *
 * Must be defined in the **CO_driver_target.h** file.
 *
 * Data fields of this structure are used exclusively by the driver. Usually it has the following data fields, but they
 * may differ for different microcontrollers. Array of multiple CO_CANtx_t objects is included inside CO_CANmodule_t.
 */
typedef struct {
    uint32_t ident;             /**< CAN identifier as aligned in CAN module */
    uint8_t DLC;                /**< Length of CAN message */
    uint8_t data[8];            /**< 8 data bytes */
    volatile bool_t bufferFull; /**< True if previous message is still in the buffer */
    volatile bool_t syncFlag;   /**< Synchronous PDO messages has this flag set. It prevents them to be sent outside the
                                     synchronous window */
} CO_CANtx_xmc4xxx_t;

/** @} */


#endif /* CO_DRIVER_XMC4XXX_H_ */

