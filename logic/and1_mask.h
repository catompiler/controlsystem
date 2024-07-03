#ifndef AND1_MASK_H
#define AND1_MASK_H

#include "module/base.h"


//! Число входов логики.
#define AND1_MASK_INPUTS 1


//! Перечисление возможных бит управления.
enum _E_And1_Mask_Control {
    AND1_MASK_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_And1_Mask_Status {
    AND1_MASK_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_And1_Mask M_and1_mask;

//! Структура модуля.
struct _S_And1_Mask {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    flag_t in_value[AND1_MASK_INPUTS];
    // Выходные данные.
    flag_t out_value;
    // Параметры.
    // Регистры.
    flag_t r_mask[AND1_MASK_INPUTS];
    // Методы.
    METHOD_INIT(M_and1_mask);
    METHOD_DEINIT(M_and1_mask);
    METHOD_CALC(M_and1_mask);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_and1_mask);
EXTERN METHOD_DEINIT_PROTO(M_and1_mask);
EXTERN METHOD_CALC_PROTO(M_and1_mask);

#define AND1_MASK_DEFCFG(MASK) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        {((MASK) >> 0) & 0x1}, /* r_mask */\
        /* Методы */\
        METHOD_INIT_PTR(M_and1_mask), METHOD_DEINIT_PTR(M_and1_mask),\
        METHOD_CALC_PTR(M_and1_mask),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define AND1_MASK_DEFAULTS AND1_MASK_DEFCFG(0)

#endif /* AND1_MASK_H */
