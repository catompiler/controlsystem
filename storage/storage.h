#ifndef STORAGE_H
#define STORAGE_H

#include "module/base.h"
#include "defs/defs.h"
#include "errors/errors.h"
#include "future/future.h"
#include <stddef.h>
#include <assert.h>
#include "eeprom/eeprom.h"


//! Перечисление возможных бит управления.
enum _E_Storage_Control {
    STORAGE_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Storage_Status {
    STORAGE_STATUS_NONE = STATUS_NONE,
    STORAGE_STATUS_READY = STATUS_READY,
    STORAGE_STATUS_RUN = STATUS_RUN,
    STORAGE_STATUS_ERROR = STATUS_ERROR,
};

//! Команда.
enum _E_Storage_Command {
    STORAGE_CMD_NONE = 0,
    STORAGE_CMD_ERASE = 1,
    STORAGE_CMD_WRITE = 2,
    STORAGE_CMD_READ = 3,
};

//! Перечисление регионов.
enum _E_Storage_Region {
    STORAGE_RGN_NONE = 0,                                        //!< STORAGE_NONE
    STORAGE_RGN_SETTINGS = 1,                                    //!< STORAGE_SETTINGS
    STORAGE_RGN_OSC0 = 2,                                        //!< STORAGE_OSC0
    STORAGE_RGN_OSCn = STORAGE_RGN_OSC0,                             //!< STORAGE_OSCn
    STORAGE_RGN_OSC1 = (STORAGE_RGN_OSCn + 1),                       //!< STORAGE_OSC1
    STORAGE_RGN_OSC2 = (STORAGE_RGN_OSCn + 2),                       //!< STORAGE_OSC2
    STORAGE_RGN_OSC3 = (STORAGE_RGN_OSCn + 3),                       //!< STORAGE_OSC3
    STORAGE_RGN_OSC_MAX = STORAGE_RGN_OSC3,                          //!< STORAGE_OSC_MAX
    STORAGE_RGN_OSCs_COUNT = (STORAGE_RGN_OSC_MAX - STORAGE_RGN_OSC0 + 1)//!< STORAGE_OSCs_COUNT
};

// Карта памяти.
// Размер страницы EEPROM.
//#define STORAGE_EEPROM_PAGE EEPROM_PAGE_SIZE
// Начало памяти.
#define STORAGE_MEM_BEG 0x0
// Регионы памяти.
#define STORAGE_MEM_RGN_SETTINGS_OFFSET 0x0
#define STORAGE_MEM_RGN_SETTINGS_SIZE 0x800
// Конец памяти.
#define STORAGE_MEM_END 0x400



//! Структура элемента очереди.
typedef struct _S_Storage_Cmd {
    unsigned int type;//!< Команда.
    size_t address; //!< Адрес.
    //size_t offset; //!< Смещение.
    void* data; //!< Адрес данных.
    size_t size; //!< Размер данных.
    future_t* future; //!< Будущее.
} storage_cmd_t;

//! Размер очереди.
#define STORAGE_QUEUE_LEN 8

// Метод err_t init(eeprom_t* eeprom).
#define STORAGE_METHOD_INIT_M_NAME init
#define STORAGE_METHOD_INIT_RET err_t
#define STORAGE_METHOD_INIT_ARGS eeprom_t* eeprom
#define STORAGE_METHOD_INIT(MOD_TYPE)                       METHOD(MOD_TYPE, STORAGE_METHOD_INIT_M_NAME, STORAGE_METHOD_INIT_RET, STORAGE_METHOD_INIT_ARGS)
#define STORAGE_METHOD_INIT_PTR(MOD_NAME)                   METHOD_PTR(MOD_NAME, STORAGE_METHOD_INIT_M_NAME)
#define STORAGE_METHOD_INIT_PROTO(MOD_NAME)                 METHOD_PROTO(MOD_NAME, STORAGE_METHOD_INIT_M_NAME, STORAGE_METHOD_INIT_RET, STORAGE_METHOD_INIT_ARGS)
#define STORAGE_METHOD_INIT_IMPL(MOD_NAME, THIS, EEP)       METHOD_IMPL(MOD_NAME, THIS, STORAGE_METHOD_INIT_M_NAME, STORAGE_METHOD_INIT_RET, EEP)
#define STORAGE_INIT(MOD, EEP)                              CALL(MOD, STORAGE_METHOD_INIT_M_NAME, EEP)

// Метод err_t read(unsigned int rgn, size_t offset, void* data, size_t size, future_t* future).
#define STORAGE_METHOD_READ_M_NAME read
#define STORAGE_METHOD_READ_RET err_t
#define STORAGE_METHOD_READ_ARGS unsigned int rgn, size_t offset, void* data, size_t size, future_t* future
#define STORAGE_METHOD_READ(MOD_TYPE)                       METHOD(MOD_TYPE, STORAGE_METHOD_READ_M_NAME, STORAGE_METHOD_READ_RET, STORAGE_METHOD_READ_ARGS)
#define STORAGE_METHOD_READ_PTR(MOD_NAME)                   METHOD_PTR(MOD_NAME, STORAGE_METHOD_READ_M_NAME)
#define STORAGE_METHOD_READ_PROTO(MOD_NAME)                 METHOD_PROTO(MOD_NAME, STORAGE_METHOD_READ_M_NAME, STORAGE_METHOD_READ_RET, STORAGE_METHOD_READ_ARGS)
#define STORAGE_METHOD_READ_IMPL(MOD_NAME, THIS, RGN,\
                                   OFF, DAT, SIZ, FUT)       METHOD_IMPL(MOD_NAME, THIS, STORAGE_METHOD_READ_M_NAME, STORAGE_METHOD_READ_RET, RGN, OFF, DAT, SIZ, FUT)
#define STORAGE_READ(MOD, RGN, OFF, DAT, SIZ, FUT)          CALL(MOD, STORAGE_METHOD_READ_M_NAME, RGN, OFF, DAT, SIZ, FUT)


// Метод err_t write(unsigned int rgn, size_t offset, const void* data, size_t size, future_t* future).
#define STORAGE_METHOD_WRITE_M_NAME write
#define STORAGE_METHOD_WRITE_RET err_t
#define STORAGE_METHOD_WRITE_ARGS unsigned int rgn, size_t offset, const void* data, size_t size, future_t* future
#define STORAGE_METHOD_WRITE(MOD_TYPE)                       METHOD(MOD_TYPE, STORAGE_METHOD_WRITE_M_NAME, STORAGE_METHOD_WRITE_RET, STORAGE_METHOD_WRITE_ARGS)
#define STORAGE_METHOD_WRITE_PTR(MOD_NAME)                   METHOD_PTR(MOD_NAME, STORAGE_METHOD_WRITE_M_NAME)
#define STORAGE_METHOD_WRITE_PROTO(MOD_NAME)                 METHOD_PROTO(MOD_NAME, STORAGE_METHOD_WRITE_M_NAME, STORAGE_METHOD_WRITE_RET, STORAGE_METHOD_WRITE_ARGS)
#define STORAGE_METHOD_WRITE_IMPL(MOD_NAME, THIS, RGN,\
                                   OFF, DAT, SIZ, FUT)       METHOD_IMPL(MOD_NAME, THIS, STORAGE_METHOD_WRITE_M_NAME, STORAGE_METHOD_WRITE_RET, RGN, OFF, DAT, SIZ, FUT)
#define STORAGE_WRITE(MOD, RGN, OFF, DAT, SIZ, FUT)          CALL(MOD, STORAGE_METHOD_WRITE_M_NAME, RGN, OFF, DAT, SIZ, FUT)


// Метод err_t erase(unsigned int rgn, future_t* future).
#define STORAGE_METHOD_ERASE_M_NAME erase
#define STORAGE_METHOD_ERASE_RET err_t
#define STORAGE_METHOD_ERASE_ARGS unsigned int rgn, future_t* future
#define STORAGE_METHOD_ERASE(MOD_TYPE)                       METHOD(MOD_TYPE, STORAGE_METHOD_ERASE_M_NAME, STORAGE_METHOD_ERASE_RET, STORAGE_METHOD_ERASE_ARGS)
#define STORAGE_METHOD_ERASE_PTR(MOD_NAME)                   METHOD_PTR(MOD_NAME, STORAGE_METHOD_ERASE_M_NAME)
#define STORAGE_METHOD_ERASE_PROTO(MOD_NAME)                 METHOD_PROTO(MOD_NAME, STORAGE_METHOD_ERASE_M_NAME, STORAGE_METHOD_ERASE_RET, STORAGE_METHOD_ERASE_ARGS)
#define STORAGE_METHOD_ERASE_IMPL(MOD_NAME, THIS, RGN, FUT)  METHOD_IMPL(MOD_NAME, THIS, STORAGE_METHOD_ERASE_M_NAME, STORAGE_METHOD_ERASE_RET, RGN, FUT)
#define STORAGE_ERASE(MOD, RGN, FUT)                         CALL(MOD, STORAGE_METHOD_ERASE_M_NAME, RGN, FUT)





//! Предварительная декларация типа модуля.
typedef struct _S_Storage M_storage;

//! Структура модуля.
struct _S_Storage {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Регистры.
    // Методы.
    STORAGE_METHOD_INIT(M_storage);
    METHOD_DEINIT(M_storage);
    METHOD_IDLE(M_storage);
    STORAGE_METHOD_ERASE(M_storage);
    STORAGE_METHOD_WRITE(M_storage);
    STORAGE_METHOD_READ(M_storage);
    // Коллбэки.
    // Внутренние данные.
    storage_cmd_t m_queue[STORAGE_QUEUE_LEN]; //!< Очередь команд.
    size_t m_q_head_index; //!< Голова очереди.
    size_t m_q_tail_index; //!< Хвост очереди.
    size_t m_q_count; //!< Число элементов в очереди.
    future_t m_future; //!< Будущее.
    eeprom_t* m_eeprom; //!< EEPROM.
};

EXTERN STORAGE_METHOD_INIT_PROTO(M_storage);
EXTERN METHOD_DEINIT_PROTO(M_storage);
EXTERN METHOD_IDLE_PROTO(M_storage);
EXTERN STORAGE_METHOD_ERASE_PROTO(M_storage);
EXTERN STORAGE_METHOD_WRITE_PROTO(M_storage);
EXTERN STORAGE_METHOD_READ_PROTO(M_storage);

#define STORAGE_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        STORAGE_METHOD_INIT_PTR(M_storage), METHOD_DEINIT_PTR(M_storage),\
        METHOD_IDLE_PTR(M_storage),\
        STORAGE_METHOD_ERASE_PTR(M_storage),\
        STORAGE_METHOD_WRITE_PTR(M_storage),\
        STORAGE_METHOD_READ_PTR(M_storage),\
        /* Коллбэки */\
        /* Внутренние данные */\
        {{0}}, /* m_queue */\
        0, /* m_q_head_index */\
        0, /* m_q_tail_index */\
        0, /* m_q_count */\
        {0}, /* m_future */\
        NULL, /* m_eeprom */\
    }

#endif /* STORAGE_H */
