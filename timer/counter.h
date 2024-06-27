#ifndef COUNTER_H
#define COUNTER_H

#include "module/base.h"


//! Перечисление возможных бит управления.
enum _E_Counter_Control {
    COUNTER_CONTROL_NONE = CONTROL_NONE,
    COUNTER_CONTROL_START = CONTROL_START,
    COUNTER_CONTROL_STOP = CONTROL_STOP,
};

//! Перечисление возможных бит статуса.
enum _E_Counter_Status {
    COUNTER_STATUS_NONE = STATUS_NONE,
    COUNTER_STATUS_RUN = STATUS_RUN,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Counter M_counter;

//! Структура модуля.
struct _S_Counter {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    reg_u32_t out_value; //!< Значение счётчика.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_counter);
    METHOD_DEINIT(M_counter);
    METHOD_CALC(M_counter);
    METHOD_CONTROL(M_counter);
    // Коллбэки.
    // Внутренние данные.
    uint32_t m_ref_counter; //!< Опорное значение счётчика.
};

EXTERN METHOD_INIT_PROTO(M_counter);
EXTERN METHOD_DEINIT_PROTO(M_counter);
EXTERN METHOD_CALC_PROTO(M_counter);
EXTERN METHOD_CONTROL_PROTO(M_counter);

#define COUNTER_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_counter), METHOD_DEINIT_PTR(M_counter),\
        METHOD_CALC_PTR(M_counter),\
        METHOD_CONTROL_PTR(M_counter),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_ref_counter */\
    }

#endif /* COUNTER_H */
