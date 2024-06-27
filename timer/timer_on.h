#ifndef TIMER_ON_H
#define TIMER_ON_H

#include "module/base.h"
#include "edge_detect/edge_detect.h"
#include "timer.h"


//! Перечисление возможных бит управления.
enum _E_Timer_On_Control {
    TIMER_ON_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Timer_On_Status {
    TIMER_ON_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Timer_On M_timer_on;

//! Структура модуля.
struct _S_Timer_On {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    flag_t in_value; //!< Входное значение сигнала.
    // Выходные данные.
    flag_t out_value; //!< Выходное значение сигнала.
    // Параметры.
    //reg_u32_t r_time_on_ms; //!< Время задержки в мс. // в m_tmr.
    // Регистры.
    M_timer r_tmr; //!< Таймер времени до срабатывания выхода.
    // Методы.
    METHOD_INIT(M_timer_on);
    METHOD_DEINIT(M_timer_on);
    METHOD_CALC(M_timer_on);
    // Коллбэки.
    // Внутренние данные.
    // Внутренние модули.
    M_edge_detect m_ed; //!< Детект фронта.
};

EXTERN METHOD_INIT_PROTO(M_timer_on);
EXTERN METHOD_DEINIT_PROTO(M_timer_on);
EXTERN METHOD_CALC_PROTO(M_timer_on);

#define TIMER_ON_DEFCFG(TIME) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        TIMER_DEFCFG(TIME), /* r_tmr */\
        /* TIME,*/ /* r_time_on_ms */\
        /* Методы */\
        METHOD_INIT_PTR(M_timer_on), METHOD_DEINIT_PTR(M_timer_on),\
        METHOD_CALC_PTR(M_timer_on),\
        /* Коллбэки */\
        /* Внутренние данные */\
        /* Внутренние модули */\
        EDGE_DETECT_DEFAULTS, /* m_ed */\
    }

#define TIMER_ON_DEFAULTS TIMER_ON_DEFCFG(0)

#endif /* TIMER_ON_H */
