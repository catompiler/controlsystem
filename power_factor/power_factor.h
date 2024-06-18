#ifndef POWER_FACTOR_H
#define POWER_FACTOR_H

#include "module/base.h"



//! Перечисление возможных бит управления.
enum _E_Power_Factor_Control {
    POWER_FACTOR_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Power_Factor_Status {
    POWER_FACTOR_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Power_Factor M_power_factor;

//! Структура модуля.
struct _S_Power_Factor {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_S; //!< Полная мощность.
    reg_iq24_t in_P; //!< Активная мощность.
    reg_iq24_t in_Q; //!< Реактивная мощность.
    // Выходные данные.
    reg_iq24_t out_cos_phi; //!< cos(phi).
    reg_iq24_t out_sin_phi; //!< sin(phi).
    reg_iq24_t out_tan_phi; //!< tan(phi).
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_power_factor);
    METHOD_DEINIT(M_power_factor);
    METHOD_CALC(M_power_factor);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_power_factor);
EXTERN METHOD_DEINIT_PROTO(M_power_factor);
EXTERN METHOD_CALC_PROTO(M_power_factor);

#define POWER_FACTOR_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, 0, 0, /* in S, P, Q */\
        /* Выходные данные */\
        0, 0, 0, /* out cos, sin, tan */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_power_factor), METHOD_DEINIT_PTR(M_power_factor),\
        METHOD_CALC_PTR(M_power_factor),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* POWER_FACTOR_H */
