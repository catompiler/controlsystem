#ifndef MS_TIMER_H
#define MS_TIMER_H

#include "module/base.h"
#include "thread_timer/thread_timer.h"

//! Перечисление возможных бит управления.
enum _E_Ms_Timer_Control {
    MS_TIMER_CONTROL_NONE = CONTROL_NONE,
    MS_TIMER_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Ms_Timer_Status {
    MS_TIMER_STATUS_NONE = STATUS_NONE,
    MS_TIMER_STATUS_READY = STATUS_READY,
    MS_TIMER_STATUS_RUN = STATUS_RUN,
    MS_TIMER_STATUS_ERROR = STATUS_ERROR,
};


#define MS_TIMER_TICKS_FREQ 1000
#define MS_TIMER_TICKS_PERIOD_US (1000000 / MS_TIMER_TICKS_FREQ)


typedef struct _S_ms_timer M_ms_timer;

struct _S_ms_timer {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    reg_u32_t out_counter; //!< Счётчик тиков.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_ms_timer);
    METHOD_DEINIT(M_ms_timer);
    METHOD_CONTROL(M_ms_timer);
    // Коллбэки.
    CALLBACK(on_timeout);
    // Внутренние данные.
    thread_timer_t m_thr_tim; //!< Таймер.
};

EXTERN METHOD_INIT_PROTO(M_ms_timer);
EXTERN METHOD_DEINIT_PROTO(M_ms_timer);
EXTERN METHOD_CONTROL_PROTO(M_ms_timer);

#define MS_TIMER_DEFAULTS {\
        0, 0, /* control, status */\
        0, /* out_counter */\
        METHOD_INIT_PTR(M_ms_timer), METHOD_DEINIT_PTR(M_ms_timer),\
        METHOD_CONTROL_PTR(M_ms_timer),\
        CALLBACK_DEFAULTS /* on_timeout */,\
        {0} /* m_thr_tim */,\
    }

#endif /* MS_TIMER_H */
