#ifndef ARMATURE_I_INST_MUX_H
#define ARMATURE_I_INST_MUX_H

#include "module/base.h"



//! Число входов мультиплексора.
#define ARMATURE_I_MUX_INPUTS 2


//! Перечисление возможных бит управления.
enum _E_Armature_I_Mux_Control {
    ARMATURE_I_MUX_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Armature_I_Mux_Status {
    ARMATURE_I_MUX_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Armature_I_Mux M_armature_i_mux;

//! Структура модуля.
struct _S_Armature_I_Mux {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iq24_t in_Iarm[ARMATURE_I_MUX_INPUTS]; //!< Мгновенное напряжение выхода.
    // Выходные данные.
    iq24_t out_Iarm; //!< Мгновенное напряжение выхода.
    // Параметры.
    reg_u32_t p_sel; //!< Селектор значений напряжений.
    // Регистры.
    // Методы.
    METHOD_INIT(M_armature_i_mux);
    METHOD_DEINIT(M_armature_i_mux);
    METHOD_CALC(M_armature_i_mux);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_armature_i_mux);
EXTERN METHOD_DEINIT_PROTO(M_armature_i_mux);
EXTERN METHOD_CALC_PROTO(M_armature_i_mux);

#define ARMATURE_I_MUX_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_Iarm */\
        /* Выходные данные */\
        0, /* out_Iarm */\
        /* Параметры */\
        1, /* p_sel */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_armature_i_mux), METHOD_DEINIT_PTR(M_armature_i_mux),\
        METHOD_CALC_PTR(M_armature_i_mux),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* ARMATURE_MUX_H */
