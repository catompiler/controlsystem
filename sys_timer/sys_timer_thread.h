#if defined(PORT_POSIX)

#ifndef SYS_TIMER_THREAD_H
#define SYS_TIMER_THREAD_H

#include "module/base.h"
#include "thread_timer/thread_timer.h"

//! Перечисление возможных бит управления.
enum _E_Sys_Timer_Control {
    SYS_TIMER_CONTROL_NONE = CONTROL_NONE,
    SYS_TIMER_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Sys_Timer_Status {
    SYS_TIMER_STATUS_NONE = STATUS_NONE,
    SYS_TIMER_STATUS_READY = STATUS_READY,
    SYS_TIMER_STATUS_RUN = STATUS_RUN,
    SYS_TIMER_STATUS_ERROR = STATUS_ERROR,
};


#define SYS_TIMER_ONE_SHOT 1
#define SYS_TIMER_TICKS_PERIOD_US (1)


typedef struct _S_sys_timer M_sys_timer;

struct _S_sys_timer {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    reg_u32_t out_counter; //!< Счётчик тиков.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_sys_timer);
    METHOD_DEINIT(M_sys_timer);
    METHOD_CONTROL(M_sys_timer);
    // Коллбэки.
    CALLBACK(on_timeout);
    // Внутренние данные.
    thread_timer_t m_thr_tim; //!< Таймер.
};

EXTERN METHOD_INIT_PROTO(M_sys_timer);
EXTERN METHOD_DEINIT_PROTO(M_sys_timer);
EXTERN METHOD_CONTROL_PROTO(M_sys_timer);

#define SYS_TIMER_DEFAULTS {\
        0, 0, /* control, status */\
        0, /* out_counter */\
        METHOD_INIT_PTR(M_sys_timer), METHOD_DEINIT_PTR(M_sys_timer),\
        METHOD_CONTROL_PTR(M_sys_timer),\
        CALLBACK_DEFAULTS /* on_timeout */,\
        THREAD_TIMER_DEFAULTS /* m_thr_tim */,\
    }

#endif /* SYS_TIMER_THREAD_H */

#endif
