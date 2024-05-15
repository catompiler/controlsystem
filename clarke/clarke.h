#ifndef CLARKE_H
#define CLARKE_H

#include "module/base.h"

/**
 * Модуль прямого преобразования Кларк.
 */

//! Перечисление возможных бит управления.
enum _E_Clarke_Control {
    CLARKE_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Clarke_Status {
    CLARKE_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Clarke M_clarke;

//! Структура модуля.
struct _S_Clarke {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_A; //!< Значение по фазе A.
    reg_iq24_t in_B; //!< Значение по фазе B.
    reg_iq24_t in_C; //!< Значение по фазе C.
    // Выходные данные.
    reg_iq24_t out_A; //!< Значение по фазе Alpha.
    reg_iq24_t out_B; //!< Значение по фазе Beta.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_clarke);
    METHOD_DEINIT(M_clarke);
    METHOD_CALC(M_clarke);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_clarke);
EXTERN METHOD_DEINIT_PROTO(M_clarke);
EXTERN METHOD_CALC_PROTO(M_clarke);

#define CLARKE_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_A */\
        0, /* in_B */\
        0, /* in_C */\
        /* Выходные данные */\
        0, /* out_A */\
        0, /* out_B */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_clarke), METHOD_DEINIT_PTR(M_clarke),\
        METHOD_CALC_PTR(M_clarke),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* CLARKE_H */
