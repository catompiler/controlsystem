#ifndef VALID_RANGE3_H
#define VALID_RANGE3_H

#include "module/base.h"


//! Число входных значений.
#define VALID_RANGE3_VALUES_COUNT 3

//! Перечисление значений выхода допустимого диапазона.
enum _E_Valid_Range3_Value {
    VALID_RANGE3_UNDER  = -1, //!< Входное значение меньше нижнего значения.
    VALID_RANGE3_WITHIN = 0,  //!< Входное значение в пределах [нижнее значение; верхнее значение].
    VALID_RANGE3_OVER   = +1, //!< Входное значение больше верхнего значения.
};

//! Перечисление значений общего выхода допустимого диапазона.
enum _E_Valid_Range3_All_Value {
    VALID_RANGE3_ALL_WITHIN       = 0x00, //!< Входные значения в допустимом диапазоне.
    VALID_RANGE3_ALL_1_NOT_WITHIN = 0x01, //!< Входное значение (№1) не в допустимом диапазоне.
    VALID_RANGE3_ALL_2_NOT_WITHIN = 0x02, //!< Входное значение (№2) не в допустимом диапазоне.
    VALID_RANGE3_ALL_3_NOT_WITHIN   = 0x04, //!< Входное значение (№3) не в допустимом диапазоне.
    VALID_RANGE3_ALL_NOT_WITHIN   = 0x07, //!< Входное значение (№3) не в допустимом диапазоне.
};

//! Перечисление возможных бит управления.
enum _E_Valid_Range3_Control {
    VALID_RANGE3_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Valid_Range3_Status {
    VALID_RANGE3_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Valid_Range3 M_valid_range3;

//! Структура модуля.
struct _S_Valid_Range3 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value[VALID_RANGE3_VALUES_COUNT]; //!< Входные данные.
    // Выходные данные.
    reg_i32_t out_value[VALID_RANGE3_VALUES_COUNT]; //!< Состояние допустимого диапазона.
    reg_u32_t out_value_all; //!< Состояние допустимого диапазона для всех значений.
    // Параметры.
    iql_t p_min_value; //!< Значение нижней границы.
    iql_t p_max_value; //!< Значение верхней границы.
    // Регистры.
    // Методы.
    METHOD_INIT(M_valid_range3);
    METHOD_DEINIT(M_valid_range3);
    METHOD_CALC(M_valid_range3);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_valid_range3);
EXTERN METHOD_DEINIT_PROTO(M_valid_range3);
EXTERN METHOD_CALC_PROTO(M_valid_range3);

#define VALID_RANGE3_DEFCFG(LOWER, UPPER) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_value[] */\
        /* Выходные данные */\
        {0}, /* out_value[] */\
        0, /* out_value_all */\
        /* Параметры */\
        LOWER, /* p_min_value */\
        UPPER, /* p_max_value */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_valid_range3), METHOD_DEINIT_PTR(M_valid_range3),\
        METHOD_CALC_PTR(M_valid_range3),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define VALID_RANGE3_DEFAULTS VALID_RANGE3_DEFCFG(0, 1.0)

#endif /* VALID_RANGE3_H */
