#ifndef SETTINGS_H
#define SETTINGS_H

#include "module/base.h"
#include "storage/storage.h"
#include "reg/reg.h"
#include "future/future.h"


//! Перечисление возможных бит управления.
enum _E_Settings_Control {
    SETTINGS_CONTROL_NONE = CONTROL_NONE,
    SETTINGS_CONTROL_LOAD = (CONTROL_USER << 0),
    SETTINGS_CONTROL_STORE = (CONTROL_USER << 1),
};

//! Перечисление возможных бит статуса.
enum _E_Settings_Status {
    SETTINGS_STATUS_NONE = STATUS_NONE,
    SETTINGS_STATUS_READY = STATUS_READY, //!< Запись завершена успешно.
    SETTINGS_STATUS_VALID = STATUS_VALID, //!< Чтение завершено успешно.
    SETTINGS_STATUS_RUN = STATUS_RUN, //!< Производится операция.
    SETTINGS_STATUS_ERROR = STATUS_ERROR, //!< Ошибка последней операции.
};

//! Перечисление возможных ошибок.
enum _E_Settings_Error {
    SETTINGS_ERROR_NONE = ERROR_NONE,
    SETTINGS_ERROR_BUSY = (ERROR_USER + 0),
    SETTINGS_ERROR_LOAD = (ERROR_USER + 1),
    SETTINGS_ERROR_STORE = (ERROR_USER + 2)
};

////! Структура пары id - value параметра.
//typedef struct _S_Settings_Parameter {
//    reg_id_t id; //!< Идентификатор.
//    union _U_Values{
//        reg_u32_t value_u32; //!< Значение u32.
//        reg_u16_t value_u16; //!< Значение u16.
//        reg_u8_t  value_u8; //!< Значение u8.
//        reg_i32_t value_i32; //!< Значение i32.
//        reg_i16_t value_i16; //!< Значение i16.
//        reg_i8_t  value_i8; //!< Значение i8.
//        reg_iq24_t value_iq24; //!< Значение iq24.
//        reg_iq15_t value_iq15; //!< Значение iq15.
//        reg_iq7_t  value_iq7; //!< Значение iq7.
//    };
//} settings_parameter_t;

//! Размер буфера.
#define SETTINGS_BUF_SIZE EEPROM_PAGE_SIZE
//! Размер заголовка.
#define SETTINGS_BUF_HEADER_SIZE 2
//! Размер области проверки.
#define SETTINGS_BUF_CHECK_SIZE 2
//! Размер данных.
#define SETTINGS_BUF_DATA_SIZE ((SETTINGS_BUF_SIZE)-(SETTINGS_BUF_HEADER_SIZE)-(SETTINGS_BUF_CHECK_SIZE))

//! Предварительная декларация типа модуля.
typedef struct _S_Settings M_settings;

//! Структура модуля.
struct _S_Settings {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    error_t errors; //!< Ошибки.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_settings);
    METHOD_DEINIT(M_settings);
    METHOD_CONTROL(M_settings);
    METHOD_IDLE(M_settings);
    // Коллбэки.
    // Внутренние данные.
    uint8_t m_buf[SETTINGS_BUF_SIZE]; //!< Буфер.
    size_t m_index; //!< Индекс буфера.
    size_t m_reg_n; //!< Номер текущего регистра.
    size_t m_offset; //!< Смещение для записи.
    future_t m_future; //!< Будущее.
};

EXTERN METHOD_INIT_PROTO(M_settings);
EXTERN METHOD_DEINIT_PROTO(M_settings);
EXTERN METHOD_CONTROL_PROTO(M_settings);
EXTERN METHOD_IDLE_PROTO(M_settings);

#define SETTINGS_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        0, /* errors */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_settings), METHOD_DEINIT_PTR(M_settings),\
        METHOD_CONTROL_PTR(M_settings), METHOD_IDLE_PTR(M_settings),\
        /* Коллбэки */\
        /* Внутренние данные */\
        {0}, /* m_buf */\
        0, /* m_index */\
        0, /* m_reg_n */\
        0, /* m_offset */\
        {0}, /* m_future */\
    }

#endif /* SETTINGS_H */
