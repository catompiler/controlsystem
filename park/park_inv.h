#ifndef PARK_INV_H
#define PARK_INV_H

#include "module/base.h"

/**
 * Модуль обратного преобразования Парка.
 */

//! Перечисление возможных бит управления.
enum _E_Park_Inv_Control {
    PARK_INV_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Park_Inv_Status {
    PARK_INV_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Park_Inv M_park_inv;

//! Структура модуля.
struct _S_Park_Inv {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_A; //!< Значение по фазе A.
    reg_iq24_t in_B; //!< Значение по фазе B.
    reg_iq24_t in_cos_angle; //!< Значение косинуса угла поворота.
    reg_iq24_t in_sin_angle; //!< Значение синуса угла поворота.
    // Выходные данные.
    reg_iq24_t out_A; //!< Значение по фазе A.
    reg_iq24_t out_B; //!< Значение по фазе B.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_park_inv);
    METHOD_DEINIT(M_park_inv);
    METHOD_CALC(M_park_inv);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_park_inv);
EXTERN METHOD_DEINIT_PROTO(M_park_inv);
EXTERN METHOD_CALC_PROTO(M_park_inv);

#define PARK_INV_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_A */\
        0, /* in_B */\
        0, /* in_cos_angle */\
        0, /* in_sin_angle */\
        /* Выходные данные */\
        0, /* out_A */\
        0, /* out_B */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_park_inv), METHOD_DEINIT_PTR(M_park_inv),\
        METHOD_CALC_PTR(M_park_inv),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* PARK_INV_H */
