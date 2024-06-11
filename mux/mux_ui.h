#ifndef MUX_UI_H
#define MUX_UI_H

#include "module/base.h"
#include "iqmath/iq.h"


//! Число входов мультиплексора.
#define MUX_UI_INPUTS 3


//! Перечисление возможных бит управления.
enum _E_Mux_Ui_Control {
    MUX_UI_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mux_Ui_Status {
    MUX_UI_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mux_Ui M_mux_ui;

//! Структура модуля.
struct _S_Mux_Ui {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_U[MUX_UI_INPUTS]; //!< Входные значения U.
    iql_t in_I[MUX_UI_INPUTS]; //!< Входные значения I.
    // Выходные данные.
    iql_t out_U; //!< Выходное значение U.
    iql_t out_I; //!< Выходное значение I.
    // Параметры.
    reg_u32_t p_sel; //!< Селектор значений.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mux_ui);
    METHOD_DEINIT(M_mux_ui);
    METHOD_CALC(M_mux_ui);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mux_ui);
EXTERN METHOD_DEINIT_PROTO(M_mux_ui);
EXTERN METHOD_CALC_PROTO(M_mux_ui);

#define MUX_UI_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_U */\
        {0}, /* in_I */\
        /* Выходные данные */\
        0, /* out_U */\
        0, /* out_I */\
        /* Параметры */\
        0, /* p_sel */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_mux_ui), METHOD_DEINIT_PTR(M_mux_ui),\
        METHOD_CALC_PTR(M_mux_ui),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MUX_UI_H */
