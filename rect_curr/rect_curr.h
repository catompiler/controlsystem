#ifndef RECT_CURR_H
#define RECT_CURR_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Rect_Curr_Control {
    RECT_CURR_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Rect_Curr_Status {
    RECT_CURR_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Rect_Curr M_rect_curr;

//! Структура модуля.
struct _S_Rect_Curr {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_Ia; //!< Ток фазы A относительно сети.
    reg_iq24_t in_Ib; //!< Ток фазы B относительно сети.
    reg_iq24_t in_Ic; //!< Ток фазы C относительно сети.
    // Выходные данные.
    reg_iq24_t out_I; //!< Выходной выпрямленный ток относительно двигателя.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_rect_curr);
    METHOD_DEINIT(M_rect_curr);
    METHOD_CALC(M_rect_curr);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_rect_curr);
EXTERN METHOD_DEINIT_PROTO(M_rect_curr);
EXTERN METHOD_CALC_PROTO(M_rect_curr);

#define RECT_CURR_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_Ia */\
        0, /* in_Ib */\
        0, /* in_Ic */\
        /* Выходные данные */\
        0, /* out_I */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_rect_curr), METHOD_DEINIT_PTR(M_rect_curr),\
        METHOD_CALC_PTR(M_rect_curr),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* RECT_CURR_H */
