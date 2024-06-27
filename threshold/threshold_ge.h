#ifndef THRESHOLD_GE_H
#define THRESHOLD_GE_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Threshold_Ge_Control {
    THRESHOLD_GE_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Threshold_Ge_Status {
    THRESHOLD_GE_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Threshold_Ge M_threshold_ge;

//! Структура модуля.
struct _S_Threshold_Ge {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value; //!< Значение для сравнения.
    // Выходные данные.
    flag_t out_value; //!< Результат сравнения значения с порогом.
    // Параметры.
    iql_t p_threshold; //!< Порог.
    // Регистры.
    // Методы.
    METHOD_INIT(M_threshold_ge);
    METHOD_DEINIT(M_threshold_ge);
    METHOD_CALC(M_threshold_ge);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_threshold_ge);
EXTERN METHOD_DEINIT_PROTO(M_threshold_ge);
EXTERN METHOD_CALC_PROTO(M_threshold_ge);

#define THRESHOLD_GE_DEFCFG(TH_VAL) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        TH_VAL, /* p_threshold */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_threshold_ge), METHOD_DEINIT_PTR(M_threshold_ge),\
        METHOD_CALC_PTR(M_threshold_ge),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define THRESHOLD_GE_DEFAULTS THRESHOLD_GE_DEFCFG(0)

#endif /* THRESHOLD_GE_H */
