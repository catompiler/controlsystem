#ifndef NOT_H
#define NOT_H

#include "module/base.h"


//! Перечисление возможных бит управления.
enum _E_Not_Control {
    NOT_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Not_Status {
    NOT_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Not M_not;

//! Структура модуля.
struct _S_Not {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    flag_t in_value;
    // Выходные данные.
    flag_t out_value;
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_not);
    METHOD_DEINIT(M_not);
    METHOD_CALC(M_not);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_not);
EXTERN METHOD_DEINIT_PROTO(M_not);
EXTERN METHOD_CALC_PROTO(M_not);

#define NOT_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_not), METHOD_DEINIT_PTR(M_not),\
        METHOD_CALC_PTR(M_not),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* NOT_H */
