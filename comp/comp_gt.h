#ifndef COMP_GT_H
#define COMP_GT_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Comp_Gt_Control {
    COMP_GT_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Comp_Gt_Status {
    COMP_GT_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Comp_Gt M_comp_gt;

//! Структура модуля.
struct _S_Comp_Gt {
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
    METHOD_INIT(M_comp_gt);
    METHOD_DEINIT(M_comp_gt);
    METHOD_CALC(M_comp_gt);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_comp_gt);
EXTERN METHOD_DEINIT_PROTO(M_comp_gt);
EXTERN METHOD_CALC_PROTO(M_comp_gt);

#define COMP_GT_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, 0, /* in_A, in_B */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_comp_gt), METHOD_DEINIT_PTR(M_comp_gt),\
        METHOD_CALC_PTR(M_comp_gt),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* COMP_GT_H */
