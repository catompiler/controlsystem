#ifndef MAINS_U_INST_MUX_H
#define MAINS_U_INST_MUX_H

#include "module/base.h"



//! Число входов мультиплексора.
#define MAINS_U_MUX_INPUTS 2


//! Перечисление возможных бит управления.
enum _E_Mains_U_Mux_Control {
    MAINS_U_MUX_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mains_U_Mux_Status {
    MAINS_U_MUX_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mains_U_Mux M_mains_u_mux;

//! Структура модуля.
struct _S_Mains_U_Mux {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iq24_t in_Ua[MAINS_U_MUX_INPUTS]; //!< Мгновенные напряжения фазы A.
    iq24_t in_Ub[MAINS_U_MUX_INPUTS]; //!< Мгновенные напряжения фазы B.
    iq24_t in_Uc[MAINS_U_MUX_INPUTS]; //!< Мгновенные напряжения фазы C.
    // Выходные данные.
    iq24_t out_Ua; //!< Мгновенное напряжение фазы A.
    iq24_t out_Ub; //!< Мгновенное напряжение фазы B.
    iq24_t out_Uc; //!< Мгновенное напряжение фазы C.
    // Параметры.
    reg_u32_t p_sel; //!< Селектор значений напряжений.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mains_u_mux);
    METHOD_DEINIT(M_mains_u_mux);
    METHOD_CALC(M_mains_u_mux);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mains_u_mux);
EXTERN METHOD_DEINIT_PROTO(M_mains_u_mux);
EXTERN METHOD_CALC_PROTO(M_mains_u_mux);

#define MAINS_U_MUX_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_Ua */\
        {0}, /* in_Ub */\
        {0}, /* in_Uc */\
        /* Выходные данные */\
        0, /* out_Ua */\
        0, /* out_Ub */\
        0, /* out_Uc */\
        /* Параметры */\
        1, /* p_sel */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_mains_u_mux), METHOD_DEINIT_PTR(M_mains_u_mux),\
        METHOD_CALC_PTR(M_mains_u_mux),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MAINS_MUX_H */
