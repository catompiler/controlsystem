#ifndef NET_TIMER_H
#define NET_TIMER_H

#include "module/base.h"
#include "thread_timer/thread_timer.h"

//! Перечисление возможных бит управления.
enum _E_Net_Timer_Control {
    NET_TIMER_CONTROL_NONE = CONTROL_NONE,
    NET_TIMER_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Net_Timer_Status {
    NET_TIMER_STATUS_NONE = STATUS_NONE,
    NET_TIMER_STATUS_READY = STATUS_READY,
    NET_TIMER_STATUS_RUN = STATUS_RUN,
    NET_TIMER_STATUS_ERROR = STATUS_ERROR,
};


#define NET_TIMER_TICKS_FREQ 1000
#define NET_TIMER_TICKS_PERIOD_US (1000000 / NET_TIMER_TICKS_FREQ)


typedef struct _S_net_timer M_net_timer;

struct _S_net_timer {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    reg_u32_t out_counter; //!< Счётчик тиков.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_net_timer);
    METHOD_DEINIT(M_net_timer);
    METHOD_CONTROL(M_net_timer);
    // Коллбэки.
    CALLBACK(on_timeout);
    // Внутренние данные.
    thread_timer_t m_thr_tim; //!< Таймер.
};

EXTERN METHOD_INIT_PROTO(M_net_timer);
EXTERN METHOD_DEINIT_PROTO(M_net_timer);
EXTERN METHOD_CONTROL_PROTO(M_net_timer);

#define NET_TIMER_DEFAULTS {\
        0, 0, /* control, status */\
        0, /* out_counter */\
        METHOD_INIT_PTR(M_net_timer), METHOD_DEINIT_PTR(M_net_timer),\
        METHOD_CONTROL_PTR(M_net_timer),\
        CALLBACK_DEFAULTS /* on_timeout */,\
        THREAD_TIMER_DEFAULTS /* m_thr_tim */,\
    }

#endif /* NET_TIMER_H */
