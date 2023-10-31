#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "module/base.h"


//! Перечисление значений выхода порога.
enum _E_Threshold_Value {
    THRESHOLD_UNDER  = -1, //!< Входное значение меньше нижнего порога.
    THRESHOLD_WITHIN = 0,  //!< Входное значение в пределах [нижний порог; верхний порог].
    THRESHOLD_OVER   = +1, //!< Входное значение больше нижнего порога.
};

//! Перечисление возможных бит управления.
enum _E_Threshold_Control {
    THRESHOLD_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Threshold_Status {
    THRESHOLD_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Threshold M_threshold;

//! Структура модуля.
struct _S_Threshold {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_value; //!< Входные данные.
    // Выходные данные.
    reg_i32_t out_value; //!< Состояние порога.
    // Параметры.
    reg_iq24_t p_lower; //!< Значение нижней границы.
    reg_iq24_t p_upper; //!< Значение верхней границы.
    // Регистры.
    // Методы.
    METHOD_INIT(M_threshold);
    METHOD_DEINIT(M_threshold);
    METHOD_CALC(M_threshold);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_threshold);
EXTERN METHOD_DEINIT_PROTO(M_threshold);
EXTERN METHOD_CALC_PROTO(M_threshold);

#define THRESHOLD_DEFCFG(LOWER, UPPER) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        LOWER, /* p_lower */\
        UPPER, /* p_upper */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_threshold), METHOD_DEINIT_PTR(M_threshold),\
        METHOD_CALC_PTR(M_threshold),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define THRESHOLD_DEFAULTS THRESHOLD_DEFCFG(0, 1.0)

#endif /* THRESHOLD_H */
