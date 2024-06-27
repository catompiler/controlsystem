#ifndef THRESHOLD_LE_H
#define THRESHOLD_LE_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Threshold_Le_Control {
    THRESHOLD_LE_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Threshold_Le_Status {
    THRESHOLD_LE_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Threshold_Le M_threshold_le;

//! Структура модуля.
struct _S_Threshold_Le {
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
    METHOD_INIT(M_threshold_le);
    METHOD_DEINIT(M_threshold_le);
    METHOD_CALC(M_threshold_le);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_threshold_le);
EXTERN METHOD_DEINIT_PROTO(M_threshold_le);
EXTERN METHOD_CALC_PROTO(M_threshold_le);

#define THRESHOLD_LE_DEFCFG(TH_VAL) {\
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
        METHOD_INIT_PTR(M_threshold_le), METHOD_DEINIT_PTR(M_threshold_le),\
        METHOD_CALC_PTR(M_threshold_le),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define THRESHOLD_LE_DEFAULTS THRESHOLD_LE_DEFCFG(0)

#endif /* THRESHOLD_LE_H */
