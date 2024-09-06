#ifndef RAMP_H
#define RAMP_H

#include "module/base.h"
#include "adc_timer/adc_timer.h"



//! Период дискретизации для частоты F Гц.
#define RAMP_Ts_FREQ(F) (IQ24(1.0/(F)))

//! Период дискретизации по-умолчанию.
#define RAMP_Ts_DEFAULT (RAMP_Ts_FREQ(ADC_TIMER_TICKS_FREQ))

//! Период дискретизации для частоты 1000 Гц.
#define RAMP_Ts_1000Hz (RAMP_Ts_FREQ(1000))

//! Время изменения величины.
#define RAMP_T(T) (IQ15(T))

//! Время изменения величины по-умолчанию.
#define RAMP_T_DEFAULT (RAMP_T(1))


//! Минимум по-умолчанию.
#define RAMP_MIN_DEFAULT (0)

//! Максимум по-умолчанию.
#define RAMP_MAX_DEFAULT (IQ24(1))



//! Перечисление возможных бит управления.
enum _E_Ramp_Control {
    RAMP_CONTROL_NONE = CONTROL_NONE,
    RAMP_CONTROL_RESET = CONTROL_RESET, //!< Сброс значения на 0.
};

//! Перечисление возможных бит статуса.
enum _E_Ramp_Status {
    RAMP_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Ramp M_ramp;

//! Структура модуля.
struct _S_Ramp {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_value; //!< Входная величина.
    // Выходные данные.
    reg_iq24_t out_value; //!< Выходная величина.
    // Параметры.
    reg_iq15_t p_time; //!< Время изменения величины от 0 до 100%.
    reg_iq24_t p_min; //!< Минимальное значение.
    reg_iq24_t p_max; //!< Максимальное значение.
    // Регистры.
    reg_iq24_t r_Ts; //!< Период дискретизации.
    // Методы.
    METHOD_INIT(M_ramp);
    METHOD_DEINIT(M_ramp);
    METHOD_CALC(M_ramp);
    METHOD_IDLE(M_ramp);
    // Коллбэки.
    // Внутренние данные.
    iq24_t m_dv_Ts; //!< Изменение величины за период дискретизации.
};

EXTERN METHOD_INIT_PROTO(M_ramp);
EXTERN METHOD_DEINIT_PROTO(M_ramp);
EXTERN METHOD_CALC_PROTO(M_ramp);
EXTERN METHOD_IDLE_PROTO(M_ramp);

#define RAMP_DEFCFG(MIN, MAX, TIME, TS) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        TIME, /* p_time */\
        MIN, /* p_min */\
        MAX, /* p_max */\
        /* Регистры */\
        TS, /* r_Ts */\
        /* Методы */\
        METHOD_INIT_PTR(M_ramp), METHOD_DEINIT_PTR(M_ramp),\
        METHOD_CALC_PTR(M_ramp), METHOD_IDLE_PTR(M_ramp),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_dv_Ts */\
    }

#define RAMP_DEFAULTS RAMP_DEFCFG(RAMP_MIN_DEFAULT, RAMP_MAX_DEFAULT, RAMP_T_DEFAULT, RAMP_Ts_DEFAULT)

#endif /* RAMP_H */
