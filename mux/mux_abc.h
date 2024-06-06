#ifndef MUX_ABC_H
#define MUX_ABC_H

#include "module/base.h"
#include "iqmath/iq.h"


//! Число входов мультиплексора.
#define MUX_ABC_INPUTS 3


//! Перечисление возможных бит управления.
enum _E_Mux_Abc_Control {
    MUX_ABC_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mux_Abc_Status {
    MUX_ABC_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mux_Abc M_mux_abc;

//! Структура модуля.
struct _S_Mux_Abc {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_A[MUX_ABC_INPUTS]; //!< Входные значения A.
    iql_t in_B[MUX_ABC_INPUTS]; //!< Входные значения B.
    iql_t in_C[MUX_ABC_INPUTS]; //!< Входные значения C.
    // Выходные данные.
    iql_t out_A; //!< Выходное значение A.
    iql_t out_B; //!< Выходное значение B.
    iql_t out_C; //!< Выходное значение C.
    // Параметры.
    reg_u32_t p_sel; //!< Селектор значений.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mux_abc);
    METHOD_DEINIT(M_mux_abc);
    METHOD_CALC(M_mux_abc);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mux_abc);
EXTERN METHOD_DEINIT_PROTO(M_mux_abc);
EXTERN METHOD_CALC_PROTO(M_mux_abc);

#define MUX_ABC_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_A */\
        {0}, /* in_B */\
        {0}, /* in_C */\
        /* Выходные данные */\
        0, /* out_A */\
        0, /* out_B */\
        0, /* out_C */\
        /* Параметры */\
        0, /* p_sel */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_mux_abc), METHOD_DEINIT_PTR(M_mux_abc),\
        METHOD_CALC_PTR(M_mux_abc),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MUX_ABC_H */
