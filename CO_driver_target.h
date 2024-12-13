#ifndef CO_DRIVER_TARGET_H_
#define CO_DRIVER_TARGET_H_


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


/*
 * User Configuration.
 */

// User static variables for allocation.
#define CO_USE_GLOBALS 1

// crc16.
#define CO_CONFIG_CRC16 CO_CONFIG_CRC16_ENABLE

// SDO srv buf.
#define CO_CONFIG_SDO_SRV_BUFFER_SIZE 1024

// Disable LEDs.
#define CO_CONFIG_LEDS 0

// Disable storage.
#define CO_CONFIG_STORAGE 0

// Disable emergency.
#define CO_CONFIG_EM 0

// Disable LSS.
#define CO_CONFIG_LSS 0

// Disable HB consumer.
#define CO_CONFIG_HB_CONS 0

// HB config.
#define FIRST_HB_TIME_MS 0

// NMT config.
#define CO_CONFIG_NMT (CO_NMT_STARTUP_TO_OPERATIONAL)

// Disable TIME prod/cons.
#define CO_CONFIG_TIME 0

// Disable SYNC.
#define CO_CONFIG_SYNC 0

// Disable PDO.
#define CO_CONFIG_PDO 0

// Enable SDO server.
#define CO_CONFIG_SDO_SRV (CO_CONFIG_SDO_SRV_SEGMENTED | CO_CONFIG_SDO_SRV_BLOCK |\
						   CO_CONFIG_FLAG_CALLBACK_PRE | CO_CONFIG_FLAG_TIMERNEXT)

// SDO server timeout.
#define SDO_SERVER_TIMEOUT_MS 500

// Disable SDO client.
#define CO_CONFIG_SDO_CLI 0

// SDO client timeout.
#define SDO_CLIENT_TIMEOUT_MS 500

// SDO client block transfer.
#define SDO_CLIENT_BLOCK_TRANSFER false

// Node Id.
#define NODE_ID 1



/**
 * @defgroup CO_dataTypes Basic definitions
 * @{
 *
 * Target specific basic definitions and data types.
 *
 * Must be defined in the **CO_driver_target.h** file.
 *
 * Depending on processor or compiler architecture, one of the two macros must be defined: CO_LITTLE_ENDIAN or
 * CO_BIG_ENDIAN. CANopen itself is little endian.
 *
 * Basic data types may be specified differently on different architectures. Usually `true` and `false` are defined in
 * `<stdbool.h>`, `NULL` is defined in `<stddef.h>`, `int8_t` to `uint64_t` are defined in `<stdint.h>`.
 */
#define CO_LITTLE_ENDIAN                 /**< CO_LITTLE_ENDIAN or CO_BIG_ENDIAN must be defined */
#define CO_SWAP_16(x)    x               /**< Macro must swap bytes, if CO_BIG_ENDIAN is defined */
#define CO_SWAP_32(x)    x               /**< Macro must swap bytes, if CO_BIG_ENDIAN is defined */
#define CO_SWAP_64(x)    x               /**< Macro must swap bytes, if CO_BIG_ENDIAN is defined */
//#define NULL             (0)             /**< NULL, for general usage */
//#define true             1               /**< Logical true, for general use */
//#define false            0               /**< Logical false, for general use */
typedef bool bool_t;             /**< Boolean data type for general use */
//typedef signed char int8_t;              /**< INTEGER8 in CANopen (0002h), 8-bit signed integer */
//typedef signed int int16_t;              /**< INTEGER16 in CANopen (0003h), 16-bit signed integer */
//typedef signed long int int32_t;         /**< INTEGER32 in CANopen (0004h), 32-bit signed integer */
//typedef signed long long int int64_t;    /**< INTEGER64 in CANopen (0015h), 64-bit signed integer */
//typedef unsigned char uint8_t;           /**< UNSIGNED8 in CANopen (0005h), 8-bit unsigned integer */
//typedef unsigned int uint16_t;           /**< UNSIGNED16 in CANopen (0006h), 16-bit unsigned integer */
//typedef unsigned long int uint32_t;      /**< UNSIGNED32 in CANopen (0007h), 32-bit unsigned integer */
//typedef unsigned long long int uint64_t; /**< UNSIGNED64 in CANopen (001Bh), 64-bit unsigned integer */
typedef float float32_t;  /**< REAL32 in CANopen (0008h), single precision floating point value, 32-bit */
typedef double float64_t; /**< REAL64 in CANopen (0011h), double precision floating point value, 64-bit */
/** @} */

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
 * CAN receive callback function which pre-processes received CAN message
 *
 * It is called by fast CAN receive thread. Each \ref CO_obj "CANopenNode Object" defines its own and registers it with
 * CO_CANrxBufferInit(), by passing function pointer.
 *
 * @param object pointer to specific \ref CO_obj "CANopenNode Object", registered with CO_CANrxBufferInit()
 * @param rxMsg pointer to received CAN message
 */
void CANrx_callback(void* object, void* rxMsg);


/**
 * CAN rx message structure.
 */
typedef struct {
    uint32_t ident;
    uint8_t DLC;
    uint8_t data[8];
} CO_CANrxMsg_t;


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
static inline __attribute__((always_inline)) uint16_t
CO_CANrxMsg_readIdent(void* rxMsg) {
    return ((CO_CANrxMsg_t*)rxMsg)->ident;
}

/**
 * CANrx_callback() can read Data Length Code from received CAN message
 *
 * See also CO_CANrxMsg_readIdent():
 *
 * @param rxMsg Pointer to received message
 * @return data length in bytes (0 to 8)
 */
static inline __attribute__((always_inline)) uint8_t
CO_CANrxMsg_readDLC(void* rxMsg) {
    return ((CO_CANrxMsg_t*)rxMsg)->DLC;
}

/**
 * CANrx_callback() can read pointer to data from received CAN message
 *
 * See also CO_CANrxMsg_readIdent():
 *
 * @param rxMsg Pointer to received message
 * @return pointer to data buffer
 */
static inline __attribute__((always_inline)) const uint8_t*
CO_CANrxMsg_readData(void* rxMsg) {
    return ((CO_CANrxMsg_t*)rxMsg)->data;
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
} CO_CANrx_t;

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
} CO_CANtx_t;

/** @} */

/**
 * Complete CAN module object.
 *
 * Must be defined in the **CO_driver_target.h** file.
 *
 * Usually it has the following data fields, but they may differ for different microcontrollers.
 */
typedef struct {
    void* CANptr;                    /**< From CO_CANmodule_init() */
    CO_CANrx_t* rxArray;             /**< From CO_CANmodule_init() */
    uint16_t rxSize;                 /**< From CO_CANmodule_init() */
    CO_CANtx_t* txArray;             /**< From CO_CANmodule_init() */
    uint16_t txSize;                 /**< From CO_CANmodule_init() */
    uint16_t CANerrorStatus;         /**< CAN error status bitfield, see @ref CO_CAN_ERR_status_t */
    volatile bool_t CANnormal;       /**< CAN module is in normal mode */
    volatile bool_t useCANrxFilters; /**< Value different than zero indicates, that CAN module hardware filters are used
                                        for CAN reception. If there is not enough hardware filters, they won't be used.
                                        In this case will be *all* received CAN messages processed by software. */
    volatile bool_t bufferInhibitFlag; /**< If flag is true, then message in transmit buffer is synchronous PDO message,
                                          which will be aborted, if CO_clearPendingSyncPDOs() function will be called by
                                          application. This may be necessary if Synchronous window time was expired. */
    volatile bool_t
        firstCANtxMessage; /**< Equal to 1, when the first transmitted message (bootup message) is in CAN TX buffers */
    volatile uint16_t
        CANtxCount;  /**< Number of messages in transmit buffer, which are waiting to be copied to the CAN module */
    uint32_t errOld; /**< Previous state of CAN errors */
} CO_CANmodule_t;


/*
 * Main events handler.
 */
void
CO_CANinterrupt(CO_CANmodule_t* CANmodule);


/**
 * Data storage object for one entry.
 *
 * Must be defined in the **CO_driver_target.h** file.
 *
 * For more information on Data storage see @ref CO_storage or **CO_storage.h** file. Structure members documented here
 * are always required or required with @ref CO_storage_eeprom. Target system may add own additional, hardware specific
 * variables.
 */
typedef struct {
    void* addr;         /**< Address of data to store, always required. */
    size_t len;         /**< Length of data to store, always required. */
    uint8_t subIndexOD; /**< Sub index in OD objects 1010 and 1011, from 2 to 127. Writing 0x65766173 to 1010,subIndexOD
                           will store data to non-volatile memory Writing 0x64616F6C to 1011,subIndexOD will restore
                           default data, always required. */
    uint8_t attr;       /**< Attribute from @ref CO_storage_attributes_t, always required. */
    void* storageModule; /**< Pointer to storage module, target system specific usage, required with @ref
                            CO_storage_eeprom. */
    uint16_t crc; /**< CRC checksum of the data stored in eeprom, set on store, required with @ref CO_storage_eeprom. */
    size_t eepromAddrSignature; /**< Address of entry signature inside eeprom, set by init, required with @ref
                                   CO_storage_eeprom. */
    size_t eepromAddr; /**< Address of data inside eeprom, set by init, required with @ref CO_storage_eeprom. */
    size_t offset; /**< Offset of next byte being updated by automatic storage, required with @ref CO_storage_eeprom. */
    void* additionalParameters; /**< Additional target specific parameters, optional. */
} CO_storage_entry_t;

/**
 * @defgroup CO_critical_sections Critical sections
 * @{
 *
 * Protection of critical sections in multi-threaded operation.
 *
 * CANopenNode is designed to run in different threads, as described in [README.md](index.html). Threads are implemented
 * differently in different systems. In microcontrollers threads are interrupts with different priorities, for example.
 * It is necessary to protect sections, where different threads access to the same resource. In simple systems
 * interrupts or scheduler may be temporary disabled between access to the shared resource. Otherwise mutexes or
 * semaphores can be used.
 *
 * #### Reentrant functions
 * Functions CO_CANsend() from C_driver.h, and CO_error() from CO_Emergency.h may be called from different threads.
 * Critical sections must be protected. Either by disabling scheduler or interrupts or by mutexes or semaphores.
 * Lock/unlock macro is called with pointer to CAN module, which may be used inside.
 *
 * #### Object Dictionary variables
 * In general, there are two threads, which accesses OD variables: mainline (initialization, storage, SDO access) and
 * timer (PDO access). CANopenNode uses locking mechanism, where SDO server (or other mainline code) prevents execution
 * of the real-time thread at the moment it reads or writes OD variable. CO_LOCK_OD(CAN_MODULE) and
 * CO_UNLOCK_OD(CAN_MODULE) macros are used to protect:
 * - Whole real-time thread,
 * - SDO server protects read/write access to OD variable.   Locking of long OD variables, not accessible from real-time
 *   thread, may   block RT thread.
 * - Any mainline code, which accesses PDO-mappable OD variable, must protect   read/write with locking macros. Use @ref
 *   OD_mappable() for check.
 * - Other cases, where non-PDO-mappable OD variable is used inside real-time   thread by some other part of the user
 *   application must be considered with   special care. Also when there are multiple threads accessing the OD
 *   (e.g. when using a RTOS), you should always lock the OD.
 *
 * #### Synchronization functions for CAN receive
 * After CAN message is received, it is pre-processed in CANrx_callback(), which copies some data into appropriate
 * object and at the end sets **new_message** flag. This flag is then pooled in another thread, which further processes
 * the message. The problem is, that compiler optimization may shuffle memory operations, so it is necessary to ensure,
 * that **new_message** flag is surely set at the end. It is necessary to use [Memory
 * barrier](https://en.wikipedia.org/wiki/Memory_barrier).
 *
 * If receive function runs inside IRQ, no further synchronization is needed. Otherwise, some kind of synchronization
 * has to be included. The following example uses GCC builtin memory barrier `__sync_synchronize()`. More information
 * can be found [here](https://stackoverflow.com/questions/982129/what-does-sync-synchronize-do#982179).
 */

#define CO_LOCK_CAN_SEND(CAN_MODULE)   /**< Lock critical section in CO_CANsend() */
#define CO_UNLOCK_CAN_SEND(CAN_MODULE) /**< Unlock critical section in CO_CANsend() */
#define CO_LOCK_EMCY(CAN_MODULE)       /**< Lock critical section in CO_errorReport() or CO_errorReset() */
#define CO_UNLOCK_EMCY(CAN_MODULE)     /**< Unlock critical section in CO_errorReport() or CO_errorReset() */
#define CO_LOCK_OD(CAN_MODULE)         /**< Lock critical section when accessing Object Dictionary */
#define CO_UNLOCK_OD(CAN_MODULE)       /**< Unock critical section when accessing Object Dictionary */

/** Check if new message has arrived */
#define CO_FLAG_READ(rxNew)            ((rxNew) != NULL)
/** Set new message flag */
#define CO_FLAG_SET(rxNew)                                                                                             \
    {                                                                                                                  \
        __sync_synchronize();                                                                                          \
        rxNew = (void*)1L;                                                                                             \
    }
/** Clear new message flag */
#define CO_FLAG_CLEAR(rxNew)                                                                                           \
    {                                                                                                                  \
        __sync_synchronize();                                                                                          \
        rxNew = NULL;                                                                                                  \
    }

/** @} */

#endif /* CO_DRIVER_TARGET_H_ */
