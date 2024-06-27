#ifndef OR2_MASK_H
#define OR2_MASK_H

#include "module/base.h"


//! Число входов логики.
#define OR2_MASK_INPUTS 3


//! Перечисление возможных бит управления.
enum _E_Or2_Mask_Control {
    OR2_MASK_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Or2_Mask_Status {
    OR2_MASK_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Or2_Mask M_or2_mask;

//! Структура модуля.
struct _S_Or2_Mask {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    flag_t in_value[OR2_MASK_INPUTS];
    // Выходные данные.
    flag_t out_value;
    // Параметры.
    // Регистры.
    flag_t r_mask[OR2_MASK_INPUTS];
    // Методы.
    METHOD_INIT(M_or2_mask);
    METHOD_DEINIT(M_or2_mask);
    METHOD_CALC(M_or2_mask);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_or2_mask);
EXTERN METHOD_DEINIT_PROTO(M_or2_mask);
EXTERN METHOD_CALC_PROTO(M_or2_mask);

#define OR2_MASK_DEFCFG(MASK) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        {((MASK) >> 0) & 0x1, ((MASK) >> 1) & 0x1}, /* r_mask */\
        /* Методы */\
        METHOD_INIT_PTR(M_or2_mask), METHOD_DEINIT_PTR(M_or2_mask),\
        METHOD_CALC_PTR(M_or2_mask),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define OR2_MASK_DEFAULTS OF2_MASK_DEFCFG(0)

#endif /* OR2_MASK_H */
