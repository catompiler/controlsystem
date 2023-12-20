#ifndef LIMIT_H
#define LIMIT_H

#include "module/base.h"
#include "iqmath/iq.h"


//! Перечисление возможных бит управления.
enum _E_Limit_Control {
    LIMIT_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Limit_Status {
    LIMIT_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Limit M_limit;

//! Структура модуля.
struct _S_Limit {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value; //!< Входные данные.
    // Выходные данные.
    iql_t out_value; //!< Выходное значение.
    // Параметры.
    iql_t p_min_value; //!< Значение нижней границы.
    iql_t p_max_value; //!< Значение верхней границы.
    // Регистры.
    // Методы.
    METHOD_INIT(M_limit);
    METHOD_DEINIT(M_limit);
    METHOD_CALC(M_limit);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_limit);
EXTERN METHOD_DEINIT_PROTO(M_limit);
EXTERN METHOD_CALC_PROTO(M_limit);

#define LIMIT_DEFCFG(MIN_VAL, MAX_VAL) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        MIN_VAL, /* p_min_value */\
        MAX_VAL, /* p_max_value */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_limit), METHOD_DEINIT_PTR(M_limit),\
        METHOD_CALC_PTR(M_limit),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define LIMIT_DEFAULTS LIMIT_DEFCFG(0, INT32_MAX)

#endif /* LIMIT_H */
