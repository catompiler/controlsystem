#ifndef OSCOPE_H
#define OSCOPE_H

#include "module/base.h"
#include "reg/reg.h"
#include <stddef.h>
#include <stdbool.h>


//! Перечисление возможных бит управления.
enum _E_Oscope_Control {
    OSCOPE_CONTROL_NONE = CONTROL_NONE,
    OSCOPE_CONTROL_RESET = CONTROL_RESET,
    OSCOPE_CONTROL_ENABLE = CONTROL_ENABLE,
    OSCOPE_CONTROL_START = CONTROL_START,
};

//! Перечисление возможных бит статуса.
enum _E_Oscope_Status {
    OSCOPE_STATUS_NONE = STATUS_NONE,
    OSCOPE_STATUS_READY = STATUS_READY,
    OSCOPE_STATUS_VALID = STATUS_VALID,
    OSCOPE_STATUS_RUN = STATUS_RUN,
};


//! Число каналов.
#define OSCOPE_CHANNELS 8

//! Число семплов на канал.
#define OSCOPE_SAMPLES 256

//! Тип семпла.
typedef iql_t oscope_sample_t;



//! Типы триггера.
typedef enum _E_Oscope_Trig_Type {
    OSCOPE_TRIG_RISING = 0, //!< Передний фронт.
    OSCOPE_TRIG_FALLING = 1, //!< Задний фронт.
} oscope_trig_type_t;

//! Состояние триггера.
typedef enum _E_Oscope_Trig_State {
    OSCOPE_TRIG_STATE_NONE = 0,
    OSCOPE_TRIG_STATE_NOT_ACTIVE = 1,
    OSCOPE_TRIG_STATE_ACTIVE = 2
} oscope_trig_state_t;



//! Структура триггера.
typedef struct _S_Oscope_Trig {
    reg_u32_t enabled; //!< Включение триггера.
    reg_u32_t ch_n; //!< Номер канала.
    reg_u32_t type; //!< Тип триггера.
    iql_t value; //!< Значение триггера.
} oscope_trig_t;


//! Структура параметров канала.
typedef struct _S_Oscope_Ch_Param {
    reg_u32_t reg_id; //!< Идентификатор регистра для осциллографирования.
    reg_u32_t enabled; //!< Флаг разрешения осциллографирования.
} oscope_ch_param_t;

//! Структура данных канала.
typedef struct _S_Oscope_Ch_Data {
    oscope_sample_t samples[OSCOPE_SAMPLES];
} oscope_ch_data_t;

//! Структура приватных данных канала.
typedef struct _S_Oscope_Ch_Private {
    reg_t* reg; //!< Осциллографируемый регистр.
    reg_t* base_reg; //!< Базовый регистр.
} oscope_ch_private_t;


//! Предварительная декларация типа модуля.
typedef struct _S_Oscope M_oscope;

//! Структура модуля.
struct _S_Oscope {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Регистры.
    reg_u32_t r_samples; //!< Число семплов (длина буфера).
    reg_u32_t r_prescaler; //!< Предделитель.
    reg_u32_t r_hist_samples; //!< Семплы истории (0..SAMPLES-1)
    oscope_ch_param_t r_ch[OSCOPE_CHANNELS]; //!< Параметры каналов.
    oscope_ch_data_t r_ch_data[OSCOPE_CHANNELS]; //!< Данные каналов.
    reg_u32_t r_mode; //!< Режим работы осциллографа.
    oscope_trig_t r_trig; //!< Триггер.
    reg_u32_t r_start; //!< Начальный индекс записи (индекс сработки триггера).
    reg_u32_t r_index; //!< Индекс вставки.
    reg_u32_t r_count; //!< Текущее число семплов.
    // Методы.
    METHOD_INIT(M_oscope);
    METHOD_DEINIT(M_oscope);
    METHOD_CONTROL(M_oscope);
    METHOD_CALC(M_oscope);
    METHOD_IDLE(M_oscope);
    // Коллбэки.
    // Внутренние данные.
    oscope_trig_state_t m_trig_state_z1; //!< Предыдущее состояние триггера.
    bool m_triggered; //!< Флаг срабатывания триггера.
    size_t m_psc_cnt; //!< Счётчик предделителя.
    oscope_ch_private_t m_ch[OSCOPE_CHANNELS]; //!< Приватные данные каналов.
};

EXTERN METHOD_INIT_PROTO(M_oscope);
EXTERN METHOD_DEINIT_PROTO(M_oscope);
EXTERN METHOD_CONTROL_PROTO(M_oscope);
EXTERN METHOD_CALC_PROTO(M_oscope);
EXTERN METHOD_IDLE_PROTO(M_oscope);

#define OSCOPE_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        OSCOPE_SAMPLES, /* r_samples */\
        0, /* r_prescaler */\
        0, /* r_hist_samples */\
        {{0}}, /* r_ch */\
        {{{0}}}, /* r_ch_data */\
        0, /* r_mode */\
        {0}, /* r_trig */\
        0, /* r_start */\
        0, /* r_index */\
        0, /* r_count */\
        /* Методы */\
        METHOD_INIT_PTR(M_oscope), METHOD_DEINIT_PTR(M_oscope),\
        METHOD_CONTROL_PTR(M_oscope), METHOD_CALC_PTR(M_oscope),\
        METHOD_IDLE_PTR(M_oscope),\
        /* Коллбэки */\
        /* Внутренние данные */\
        OSCOPE_TRIG_STATE_NONE, /* m_trig_state_z1 */\
        false, /* m_triggered */\
        0, /* m_psc_cnt */\
        {{0}}, /* m_ch */\
    }

#endif /* OSCOPE_H */
