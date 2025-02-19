#ifndef PROT_ITEM_GT_H
#define PROT_ITEM_GT_H

#include "module/base.h"
#include "timer/timer_on.h"
#include "threshold/threshold_gt.h"



//! Перечисление возможных бит управления.
enum _E_Prot_Item_Gt_Control {
    PROT_ITEM_GT_CONTROL_NONE = CONTROL_NONE,
//    PROT_ITEM_GT_CONTROL_ENABLE = CONTROL_ENABLE,
//    PROT_ITEM_GT_CONTROL_RESET = CONTROL_RESET,
};

//! Перечисление возможных бит статуса.
enum _E_Prot_Item_Gt_Status {
    PROT_ITEM_GT_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Prot_Item_Gt M_prot_item_gt;

//! Структура модуля.
struct _S_Prot_Item_Gt {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value; //!< Значение величины.
    // Выходные данные.
    flag_t out_value; //!< Флаг срабатывания защиты.
    // Параметры.
    // Регистры.
    M_threshold_gt r_threshold;
    M_timer_on r_timer;
    // Методы.
    METHOD_INIT(M_prot_item_gt);
    METHOD_DEINIT(M_prot_item_gt);
    METHOD_CALC(M_prot_item_gt);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_prot_item_gt);
EXTERN METHOD_DEINIT_PROTO(M_prot_item_gt);
EXTERN METHOD_CALC_PROTO(M_prot_item_gt);

#define PROT_ITEM_GT_DEFCFG(VAL, T) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        THRESHOLD_GT_DEFCFG(VAL), /* r_threshold */\
        TIMER_ON_DEFCFG(T), /* r_timer */\
        /* Методы */\
        METHOD_INIT_PTR(M_prot_item_gt), METHOD_DEINIT_PTR(M_prot_item_gt),\
        METHOD_CALC_PTR(M_prot_item_gt),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define PROT_ITEM_GT_DEFAULTS PROT_ITEM_GT_DEFCFG(IQ24(1.0), 1)

#endif /* PROT_ITEM_GT_H */
