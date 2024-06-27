#ifndef THRESHOLD_GT_H
#define THRESHOLD_GT_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Threshold_Gt_Control {
    THRESHOLD_GT_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Threshold_Gt_Status {
    THRESHOLD_GT_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Threshold_Gt M_threshold_gt;

//! Структура модуля.
struct _S_Threshold_Gt {
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
    METHOD_INIT(M_threshold_gt);
    METHOD_DEINIT(M_threshold_gt);
    METHOD_CALC(M_threshold_gt);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_threshold_gt);
EXTERN METHOD_DEINIT_PROTO(M_threshold_gt);
EXTERN METHOD_CALC_PROTO(M_threshold_gt);

#define THRESHOLD_GT_DEFCFG(TH_VAL) {\
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
        METHOD_INIT_PTR(M_threshold_gt), METHOD_DEINIT_PTR(M_threshold_gt),\
        METHOD_CALC_PTR(M_threshold_gt),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define THRESHOLD_GT_DEFAULTS THRESHOLD_GT_DEFCFG(0)

#endif /* THRESHOLD_GT_H */
