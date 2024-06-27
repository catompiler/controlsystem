#ifndef AND3_MASK_H
#define AND3_MASK_H

#include "module/base.h"


//! Число входов логики.
#define AND3_MASK_INPUTS 3


//! Перечисление возможных бит управления.
enum _E_And3_Mask_Control {
    AND3_MASK_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_And3_Mask_Status {
    AND3_MASK_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_And3_Mask M_and3_mask;

//! Структура модуля.
struct _S_And3_Mask {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    flag_t in_value[AND3_MASK_INPUTS];
    // Выходные данные.
    flag_t out_value;
    // Параметры.
    // Регистры.
    flag_t r_mask[AND3_MASK_INPUTS];
    // Методы.
    METHOD_INIT(M_and3_mask);
    METHOD_DEINIT(M_and3_mask);
    METHOD_CALC(M_and3_mask);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_and3_mask);
EXTERN METHOD_DEINIT_PROTO(M_and3_mask);
EXTERN METHOD_CALC_PROTO(M_and3_mask);

#define AND3_MASK_DEFCFG(MASK) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        {((MASK) >> 0) & 0x1, ((MASK) >> 1) & 0x1, ((MASK) >> 2) & 0x1}, /* r_mask */\
        /* Методы */\
        METHOD_INIT_PTR(M_and3_mask), METHOD_DEINIT_PTR(M_and3_mask),\
        METHOD_CALC_PTR(M_and3_mask),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define AND3_MASK_DEFAULTS AND3_MASK_DEFCFG(0)

#endif /* AND3_MASK_H */
