#ifndef AND2_H
#define AND2_H

#include "module/base.h"


//! Число входов логики.
#define AND2_INPUTS 2


//! Перечисление возможных бит управления.
enum _E_And2_Control {
    AND2_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_And2_Status {
    AND2_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_And2 M_and2;

//! Структура модуля.
struct _S_And2 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    flag_t in_value[AND2_INPUTS];
    // Выходные данные.
    flag_t out_value;
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_and2);
    METHOD_DEINIT(M_and2);
    METHOD_CALC(M_and2);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_and2);
EXTERN METHOD_DEINIT_PROTO(M_and2);
EXTERN METHOD_CALC_PROTO(M_and2);

#define AND2_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_and2), METHOD_DEINIT_PTR(M_and2),\
        METHOD_CALC_PTR(M_and2),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* AND2_H */
