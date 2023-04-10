#ifndef DATA_LOG_H
#define DATA_LOG_H

#include "module/base.h"


//! Перечисление возможных бит управления.
enum _E_Data_Log_Control {
    DATA_LOG_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Data_Log_Status {
    DATA_LOG_STATUS_NONE = STATUS_NONE,
    DATA_LOG_STATUS_READY = STATUS_READY,
};

//! Число каналов.
#define DATA_LOG_CH_COUNT 16
//! Длина записи данных каждого канала.
#define DATA_LOG_CH_LEN 1024

//! Тип значения данных лога.
typedef int32_t data_log_value_t;

//! Структура параметров канала.
typedef struct _S_Data_Log_Ch_Param {
    reg_u32_t p_enabled; //!< Разрешение логгирования канала.
    reg_u32_t p_reg_id; //!< Идентификатор логгируемого регистра.
    //reg_u32_t p_base_reg_id; //!< Идентификатор регистра с базовым значением.
} data_log_ch_param_t;

//! Структура данных канала.
typedef struct _S_Data_Log_Ch_Data {
    void* ptr; //!< Указатель на логгируемые данные.
    data_log_value_t data[DATA_LOG_CH_LEN]; //!< Данные.
} data_log_ch_data_t;

typedef struct _S_Data_Log M_data_log;

struct _S_Data_Log {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    data_log_ch_param_t ch[DATA_LOG_CH_COUNT]; //!< Настройки каналов.
    // Регистры.
    // Методы.
    METHOD_INIT(M_data_log);
    METHOD_DEINIT(M_data_log);
    METHOD_CALC(M_data_log);
    METHOD_IDLE(M_data_log);
    // Коллбэки.
    // Внутренние данные.
    uint32_t m_count; //!< Число записанных данных.
    uint32_t m_get_index; //!< Индекс чтения данных.
    uint32_t m_put_index; //!< Индекс записи данных.
    data_log_ch_data_t m_ch[DATA_LOG_CH_COUNT]; //!< Данные каналов.
};

EXTERN METHOD_INIT_PROTO(M_data_log);
EXTERN METHOD_DEINIT_PROTO(M_data_log);
EXTERN METHOD_CALC_PROTO(M_data_log);
EXTERN METHOD_IDLE_PROTO(M_data_log);

#define DATA_LOG_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        {{0}}, /* Массив параметров каналов */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_data_log), METHOD_DEINIT_PTR(M_data_log),\
        METHOD_CALC_PTR(M_data_log), METHOD_IDLE_PTR(M_data_log),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, 0, 0, /* Количество данных, нндексы чтения и записи */\
        {{0}} /* Данные каналов */\
    }

#endif /* DATA_LOG_H */
