#ifndef SLIP_H
#define SLIP_H

#include "module/base.h"


//! Перечисление возможных бит управления.
enum _E_Slip_Control {
    SLIP_CONTROL_NONE = CONTROL_NONE,
    SLIP_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Slip_Status {
    SLIP_STATUS_NONE = STATUS_NONE,
    SLIP_STATUS_VALID = STATUS_VALID,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Slip M_slip;

//! Структура модуля.
struct _S_Slip {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_value; //!< Измеренная частота для вычисления скольжения.
    // Выходные данные.
    reg_iq24_t out_value;
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_slip);
    METHOD_DEINIT(M_slip);
    METHOD_CALC(M_slip);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_slip);
EXTERN METHOD_DEINIT_PROTO(M_slip);
EXTERN METHOD_CALC_PROTO(M_slip);

#define SLIP_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_slip), METHOD_DEINIT_PTR(M_slip),\
        METHOD_CALC_PTR(M_slip),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* SLIP_H */
