#ifndef COMP_GE_H
#define COMP_GE_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Comp_Ge_Control {
    COMP_GE_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Comp_Ge_Status {
    COMP_GE_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Comp_Ge M_comp_ge;

//! Структура модуля.
struct _S_Comp_Ge {
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
    METHOD_INIT(M_comp_ge);
    METHOD_DEINIT(M_comp_ge);
    METHOD_CALC(M_comp_ge);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_comp_ge);
EXTERN METHOD_DEINIT_PROTO(M_comp_ge);
EXTERN METHOD_CALC_PROTO(M_comp_ge);

#define COMP_GE_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, 0, /* in_A, in_B */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_comp_ge), METHOD_DEINIT_PTR(M_comp_ge),\
        METHOD_CALC_PTR(M_comp_ge),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* COMP_GE_H */
