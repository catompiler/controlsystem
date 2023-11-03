#ifndef VALID_RANGE_H
#define VALID_RANGE_H

#include "module/base.h"


//! Перечисление значений выхода допустимого диапазона.
enum _E_Valid_Range_Value {
    VALID_RANGE_UNDER  = -1, //!< Входное значение меньше нижнего значения.
    VALID_RANGE_WITHIN = 0,  //!< Входное значение в пределах [нижнее значение; верхнее значение].
    VALID_RANGE_OVER   = +1, //!< Входное значение больше верхнего значения.
};

//! Перечисление возможных бит управления.
enum _E_Valid_Range_Control {
    VALID_RANGE_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Valid_Range_Status {
    VALID_RANGE_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Valid_Range M_valid_range;

//! Структура модуля.
struct _S_Valid_Range {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value; //!< Входные данные.
    // Выходные данные.
    reg_i32_t out_value; //!< Состояние допустимого диапазона.
    // Параметры.
    iql_t p_min_value; //!< Значение нижней границы.
    iql_t p_max_value; //!< Значение верхней границы.
    // Регистры.
    // Методы.
    METHOD_INIT(M_valid_range);
    METHOD_DEINIT(M_valid_range);
    METHOD_CALC(M_valid_range);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_valid_range);
EXTERN METHOD_DEINIT_PROTO(M_valid_range);
EXTERN METHOD_CALC_PROTO(M_valid_range);

#define VALID_RANGE_DEFCFG(LOWER, UPPER) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        LOWER, /* p_min_value */\
        UPPER, /* p_max_value */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_valid_range), METHOD_DEINIT_PTR(M_valid_range),\
        METHOD_CALC_PTR(M_valid_range),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define VALID_RANGE_DEFAULTS VALID_RANGE_DEFCFG(0, 1.0)

#endif /* VALID_RANGE_H */
