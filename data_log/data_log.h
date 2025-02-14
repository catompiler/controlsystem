#ifndef DATA_LOG_H
#define DATA_LOG_H

#include "module/base.h"
#include "reg/reg.h"
#include "conf/conf.h"

#include "port.h"


//! Перечисление возможных бит управления.
enum _E_Data_Log_Control {
    DATA_LOG_CONTROL_NONE = CONTROL_NONE,
    DATA_LOG_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Data_Log_Status {
    DATA_LOG_STATUS_NONE = STATUS_NONE,
};

#if defined(PORT_POSIX)
//! Число каналов.
#define DATA_LOG_CH_COUNT 32
//! Длина записи данных каждого канала.
#define DATA_LOG_CH_LEN 32768
#endif
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
//! Число каналов.
#define DATA_LOG_CH_COUNT 16
//! Длина записи данных каждого канала.
#define DATA_LOG_CH_LEN 256
#endif


// Получение осциллограммы.
// Следующий индекс.
#define DATA_LOG_NEXT_INDEX(INDEX)\
    do{\
        (INDEX) = (INDEX) + 1;\
        if((INDEX) >= DATA_LOG_CH_LEN){\
            (INDEX) = 0;\
        }\
    }while(0)
// Предыдущий индекс.
#define DATA_LOG_PREV_INDEX(INDEX)\
    do{\
        if((INDEX) == 0){\
            (INDEX) = DATA_LOG_CH_LEN;\
        }\
        (INDEX) = (INDEX) - 1;\
    }while(0)


//! Тип значения данных лога.
typedef int32_t data_log_value_t;

//! Структура параметров канала.
typedef struct _S_Data_Log_Ch_Param {
    reg_u32_t enabled; //!< Разрешение логгирования канала.
    reg_u32_t reg_id; //!< Идентификатор логгируемого регистра.
} data_log_ch_param_t;

//! Структура данных канала.
typedef struct _S_Data_Log_Ch_Data {
    reg_t* reg; //!< Указатель на логгируемый регистр.
    reg_t* base_reg; //!< Указатель на регистр базовой величины.
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
    data_log_ch_param_t p_ch[DATA_LOG_CH_COUNT]; //!< Параметры каналов.
    // Регистры.
    uint32_t r_count; //!< Число записанных данных.
    uint32_t r_get_index; //!< Индекс чтения данных.
    uint32_t r_put_index; //!< Индекс записи данных.
    data_log_ch_data_t r_ch[DATA_LOG_CH_COUNT]; //!< Данные каналов.
    // Методы.
    METHOD_INIT(M_data_log);
    METHOD_DEINIT(M_data_log);
    METHOD_CALC(M_data_log);
    METHOD_IDLE(M_data_log);
    // Коллбэки.
    // Внутренние данные.
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
        0, 0, 0, /* Количество данных, нндексы чтения и записи */\
        {{0}}, /* Данные каналов */\
        /* Методы */\
        METHOD_INIT_PTR(M_data_log), METHOD_DEINIT_PTR(M_data_log),\
        METHOD_CALC_PTR(M_data_log), METHOD_IDLE_PTR(M_data_log),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* DATA_LOG_H */
