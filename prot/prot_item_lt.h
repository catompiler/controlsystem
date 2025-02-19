#ifndef PROT_ITEM_LT_H
#define PROT_ITEM_LT_H

#include "module/base.h"
#include "timer/timer_on.h"
#include "threshold/threshold_lt.h"



//! Перечисление возможных бит управления.
enum _E_Prot_Item_Lt_Control {
    PROT_ITEM_LT_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Prot_Item_Lt_Status {
    PROT_ITEM_LT_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Prot_Item_Lt M_prot_item_lt;

//! Структура модуля.
struct _S_Prot_Item_Lt {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value; //!< Значение величины.
    // Выходные данные.
    flag_t out_value; //!< Флаг срабатывания защиты.
    // Параметры.
    // Регистры.
    M_threshold_lt r_threshold;
    M_timer_on r_timer;
    // Методы.
    METHOD_INIT(M_prot_item_lt);
    METHOD_DEINIT(M_prot_item_lt);
    METHOD_CALC(M_prot_item_lt);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_prot_item_lt);
EXTERN METHOD_DEINIT_PROTO(M_prot_item_lt);
EXTERN METHOD_CALC_PROTO(M_prot_item_lt);

#define PROT_ITEM_LT_DEFCFG(VAL, T) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        THRESHOLD_LT_DEFCFG(VAL), /* r_threshold */\
        TIMER_ON_DEFCFG(T), /* r_timer */\
        /* Методы */\
        METHOD_INIT_PTR(M_prot_item_lt), METHOD_DEINIT_PTR(M_prot_item_lt),\
        METHOD_CALC_PTR(M_prot_item_lt),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define PROT_ITEM_LT_DEFAULTS PROT_ITEM_LT_DEFCFG(IQ24(1.0), 1)

#endif /* PROT_ITEM_LT_H */
