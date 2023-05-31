#ifndef ADC_TIMER_H
#define ADC_TIMER_H

#include "module/base.h"
#include "conf/conf.h"
#include "thread_timer/thread_timer.h"

//! Перечисление возможных бит управления.
enum _E_Adc_Timer_Control {
    ADC_TIMER_CONTROL_NONE = CONTROL_NONE,
    ADC_TIMER_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Adc_Timer_Status {
    ADC_TIMER_STATUS_NONE = STATUS_NONE,
    ADC_TIMER_STATUS_READY = STATUS_READY,
    ADC_TIMER_STATUS_RUN = STATUS_RUN,
    ADC_TIMER_STATUS_ERROR = STATUS_ERROR,
};


#define ADC_TIMER_AC_FREQ (50)
#define ADC_TIMER_TICKS_PER_PERIOD (CONF_PERIOD_SAMPLES)
#define ADC_TIMER_TICKS_FREQ (ADC_TIMER_AC_FREQ * ADC_TIMER_TICKS_PER_PERIOD)
#define ADC_TIMER_TICKS_PERIOD_US (1000000 / ADC_TIMER_TICKS_FREQ)


typedef struct _S_adc_timer M_adc_timer;

struct _S_adc_timer {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    reg_u32_t out_counter; //!< Счётчик тиков.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_adc_timer);
    METHOD_DEINIT(M_adc_timer);
    METHOD_CONTROL(M_adc_timer);
    // Коллбэки.
    CALLBACK(on_timeout);
    // Внутренние данные.
    thread_timer_t m_thr_tim; //!< Таймер.
};

EXTERN METHOD_INIT_PROTO(M_adc_timer);
EXTERN METHOD_DEINIT_PROTO(M_adc_timer);
EXTERN METHOD_CONTROL_PROTO(M_adc_timer);

#define ADC_TIMER_DEFAULTS {\
        0, 0, /* control, status */\
        0, /* out_counter */\
        METHOD_INIT_PTR(M_adc_timer), METHOD_DEINIT_PTR(M_adc_timer),\
        METHOD_CONTROL_PTR(M_adc_timer),\
        CALLBACK_DEFAULTS /* on_timeout */,\
        {0} /* m_thr_tim */,\
    }

#endif /* ADC_TIMER_H */
