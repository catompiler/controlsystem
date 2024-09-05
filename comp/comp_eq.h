#ifndef COMP_EQ_H
#define COMP_EQ_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Comp_Eq_Control {
    COMP_EQ_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Comp_Eq_Status {
    COMP_EQ_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Comp_Eq M_comp_eq;

//! Структура модуля.
struct _S_Comp_Eq {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_A; //!< Значение A.
    iql_t in_B; //!< Значение B.
    // Выходные данные.
    flag_t out_value; //!< Результат сравнения значений A и B.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_comp_eq);
    METHOD_DEINIT(M_comp_eq);
    METHOD_CALC(M_comp_eq);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_comp_eq);
EXTERN METHOD_DEINIT_PROTO(M_comp_eq);
EXTERN METHOD_CALC_PROTO(M_comp_eq);

#define COMP_EQ_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, 0, /* in_A, in_B */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_comp_eq), METHOD_DEINIT_PTR(M_comp_eq),\
        METHOD_CALC_PTR(M_comp_eq),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* COMP_EQ_H */
