#ifndef TIMER_H
#define TIMER_H

#include "module/base.h"


//! Интервал по-умолчанию.
#define TIMER_INTERVAL_DEFAULT 0


//! Перечисление возможных бит управления.
enum _E_Timer_Control {
    TIMER_CONTROL_NONE = CONTROL_NONE,
//    TIMER_CONTROL_RESET = CONTROL_RESET,
    TIMER_CONTROL_START = CONTROL_START,
    TIMER_CONTROL_STOP = CONTROL_STOP,
};

//! Перечисление возможных бит статуса.
enum _E_Timer_Status {
    TIMER_STATUS_NONE = STATUS_NONE,
    TIMER_STATUS_RUN = STATUS_RUN,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Timer M_timer;

//! Структура модуля.
struct _S_Timer {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    //reg_u32_t in_counter; //!< Значение опорного счётчика.
    // Выходные данные.
    flag_t out_expired; //!< Флаг истечения времени.
    strobe_t out_timeout; //!< Строб тайм-аута.
    // Параметры.
    // Регистры.
    reg_u32_t p_interval; //!< Интервал таймера, мс.
    // Методы.
    METHOD_INIT(M_timer);
    METHOD_DEINIT(M_timer);
    METHOD_CALC(M_timer);
    METHOD_CONTROL(M_timer);
    // Коллбэки.
    // Внутренние данные.
    uint32_t m_ref_counter; //!< Опорное значение счётчика.
};

EXTERN METHOD_INIT_PROTO(M_timer);
EXTERN METHOD_DEINIT_PROTO(M_timer);
EXTERN METHOD_CALC_PROTO(M_timer);
EXTERN METHOD_CONTROL_PROTO(M_timer);

#define TIMER_DEFCFG(INTERVAL) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /*0,*/ /* in_counter */\
        /* Выходные данные */\
        0, /* out_expired */\
        0, /* out_timeout */\
        /* Параметры */\
        /* Регистры */\
        INTERVAL, /* r_interval */\
        /* Методы */\
        METHOD_INIT_PTR(M_timer), METHOD_DEINIT_PTR(M_timer),\
        METHOD_CALC_PTR(M_timer),\
        METHOD_CONTROL_PTR(M_timer),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_ref_counter */\
    }

#define TIMER_DEFAULTS TIMER_DEFCFG(TIMER_INTERVAL_DEFAULT)

#endif /* TIMER_H */
