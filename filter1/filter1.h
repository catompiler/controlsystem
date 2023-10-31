#ifndef FILTER1_H
#define FILTER1_H

#include "module/base.h"
#include "adc_timer/adc_timer.h"

//! Период дискретизации по-умолчанию.
#define FILTER1_Ts_DEFAULT (IQ24(1.0/(ADC_TIMER_TICKS_FREQ)))

//! Постоянная времени фильтра по-умолчанию.
#define FILTER1_T_DEFAULT (IQ24(0.001))


//! Перечисление возможных бит управления.
enum _E_Filter1_Control {
    FILTER1_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Filter1_Status {
    FILTER1_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Filter1 M_filter1;

//! Структура модуля.
struct _S_Filter1 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iq24_t in_value; //!< Фильтруеый сигнал.
    // Выходные данные.
    iq24_t out_value; //!< Отфильтрованный сигнал.
    // Параметры.
    reg_iq24_t p_T; //!< Постоянная времени фильтра.
    // Регистры.
    reg_iq24_t r_Ts; //!< Период дискретизации.
    // Методы.
    METHOD_INIT(M_filter1);
    METHOD_DEINIT(M_filter1);
    METHOD_CALC(M_filter1);
    METHOD_IDLE(M_filter1);
    // Коллбэки.
    // Внутренние данные.
    iq24_t m_kx; //!< Коэффициент входного значения.
    iq24_t m_ky; //!< Коэффициент выходного значения.
};

EXTERN METHOD_INIT_PROTO(M_filter1);
EXTERN METHOD_DEINIT_PROTO(M_filter1);
EXTERN METHOD_CALC_PROTO(M_filter1);
EXTERN METHOD_IDLE_PROTO(M_filter1);

#define FILTER1_DEFCFG(T) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        T, /* p_T */\
        /* Регистры */\
        FILTER1_Ts_DEFAULT, /* r_Ts */\
        /* Методы */\
        METHOD_INIT_PTR(M_filter1), METHOD_DEINIT_PTR(M_filter1),\
        METHOD_CALC_PTR(M_filter1), METHOD_IDLE_PTR(M_filter1),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_kx */\
        0, /* m_ky */\
    }

#define FILTER1_DEFAULTS FILTER1_DEFCFG(FILTER1_T_DEFAULT)

#endif /* FILTER1_H */
