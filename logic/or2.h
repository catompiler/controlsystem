#ifndef OR2_H
#define OR2_H

#include "module/base.h"


//! Число входов логики.
#define OR2_INPUTS 2


//! Перечисление возможных бит управления.
enum _E_Or2_Control {
    OR2_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Or2_Status {
    OR2_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Or2 M_or2;

//! Структура модуля.
struct _S_Or2 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    flag_t in_value[OR2_INPUTS];
    // Выходные данные.
    flag_t out_value;
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_or2);
    METHOD_DEINIT(M_or2);
    METHOD_CALC(M_or2);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_or2);
EXTERN METHOD_DEINIT_PROTO(M_or2);
EXTERN METHOD_CALC_PROTO(M_or2);

#define OR2_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_or2), METHOD_DEINIT_PTR(M_or2),\
        METHOD_CALC_PTR(M_or2),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* OR2_H */
