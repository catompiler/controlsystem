#ifndef CLARKE_INV_H
#define CLARKE_INV_H

#include "module/base.h"

/**
 * Модуль обратного преобразования Кларк.
 */

//! Перечисление возможных бит управления.
enum _E_Clarke_Inv_Control {
    CLARKE_INV_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Clarke_Inv_Status {
    CLARKE_INV_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Clarke_Inv M_clarke_inv;

//! Структура модуля.
struct _S_Clarke_Inv {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_A; //!< Значение по фазе Alpha.
    reg_iq24_t in_B; //!< Значение по фазе Beta.
    // Выходные данные.
    reg_iq24_t out_A; //!< Значение по фазе A.
    reg_iq24_t out_B; //!< Значение по фазе B.
    reg_iq24_t out_C; //!< Значение по фазе C.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_clarke_inv);
    METHOD_DEINIT(M_clarke_inv);
    METHOD_CALC(M_clarke_inv);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_clarke_inv);
EXTERN METHOD_DEINIT_PROTO(M_clarke_inv);
EXTERN METHOD_CALC_PROTO(M_clarke_inv);

#define CLARKE_INV_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_A */\
        0, /* in_B */\
        /* Выходные данные */\
        0, /* out_A */\
        0, /* out_B */\
        0, /* out_C */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_clarke_inv), METHOD_DEINIT_PTR(M_clarke_inv),\
        METHOD_CALC_PTR(M_clarke_inv),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* CLARKE_INV_H */
