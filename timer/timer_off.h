#ifndef TIMER_OFF_H
#define TIMER_OFF_H

#include "module/base.h"
#include "edge_detect/edge_detect.h"
#include "timer.h"


//! Перечисление возможных бит управления.
enum _E_Timer_Off_Control {
    TIMER_OFF_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Timer_Off_Status {
    TIMER_OFF_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Timer_Off M_timer_off;

//! Структура модуля.
struct _S_Timer_Off {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    flag_t in_value; //!< Входное значение сигнала.
    // Выходные данные.
    flag_t out_value; //!< Выходное значение сигнала.
    // Параметры.
    //reg_u32_t r_time_off_ms; //!< Время задержки в мс. // в m_tmr.
    // Регистры.
    M_timer r_tmr; //!< Таймер времени до срабатывания выхода.
    // Методы.
    METHOD_INIT(M_timer_off);
    METHOD_DEINIT(M_timer_off);
    METHOD_CALC(M_timer_off);
    // Коллбэки.
    // Внутренние данные.
    // Внутренние модули.
    M_edge_detect m_ed; //!< Детект фронта.
};

EXTERN METHOD_INIT_PROTO(M_timer_off);
EXTERN METHOD_DEINIT_PROTO(M_timer_off);
EXTERN METHOD_CALC_PROTO(M_timer_off);

#define TIMER_OFF_DEFCFG(TIME) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        TIMER_DEFCFG(TIME), /* r_tmr */\
        /* TIME,*/ /* r_time_off_ms */\
        /* Методы */\
        METHOD_INIT_PTR(M_timer_off), METHOD_DEINIT_PTR(M_timer_off),\
        METHOD_CALC_PTR(M_timer_off),\
        /* Коллбэки */\
        /* Внутренние данные */\
        /* Внутренние модули */\
        EDGE_DETECT_DEFAULTS, /* m_ed */\
    }

#define TIMER_OFF_DEFAULTS TIMER_OFF_DEFCFG(0)

#endif /* TIMER_OFF_H */
