#ifndef MAINS_I_INST_MUX_H
#define MAINS_I_INST_MUX_H

#include "module/base.h"



//! Число входов мультиплексора.
#define MAINS_I_MUX_INPUTS 2


//! Перечисление возможных бит управления.
enum _E_Mains_I_Mux_Control {
    MAINS_I_MUX_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mains_I_Mux_Status {
    MAINS_I_MUX_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mains_I_Mux M_mains_i_mux;

//! Структура модуля.
struct _S_Mains_I_Mux {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iq24_t in_Ia[MAINS_I_MUX_INPUTS]; //!< Мгновенные токи фазы A.
    iq24_t in_Ib[MAINS_I_MUX_INPUTS]; //!< Мгновенные токи фазы B.
    iq24_t in_Ic[MAINS_I_MUX_INPUTS]; //!< Мгновенные токи фазы C.
    // Выходные данные.
    iq24_t out_Ia; //!< Мгновенный ток фазы A.
    iq24_t out_Ib; //!< Мгновенный ток фазы B.
    iq24_t out_Ic; //!< Мгновенный ток фазы C.
    // Параметры.
    reg_u32_t p_sel; //!< Селектор значений токов.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mains_i_mux);
    METHOD_DEINIT(M_mains_i_mux);
    METHOD_CALC(M_mains_i_mux);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mains_i_mux);
EXTERN METHOD_DEINIT_PROTO(M_mains_i_mux);
EXTERN METHOD_CALC_PROTO(M_mains_i_mux);

#define MAINS_I_MUX_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_Ia */\
        {0}, /* in_Ib */\
        {0}, /* in_Ic */\
        /* Выходные данные */\
        0, /* out_Ia */\
        0, /* out_Ib */\
        0, /* out_Ic */\
        /* Параметры */\
        1, /* p_sel */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_mains_i_mux), METHOD_DEINIT_PTR(M_mains_i_mux),\
        METHOD_CALC_PTR(M_mains_i_mux),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MAINS_MUX_H */
