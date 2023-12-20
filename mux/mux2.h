#ifndef MUX2_H
#define MUX2_H

#include "module/base.h"
#include "iqmath/iq.h"


//! Число входов мультиплексора.
#define MUX2_INPUTS 2


//! Перечисление возможных бит управления.
enum _E_Mux2_Control {
    MUX2_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mux2_Status {
    MUX2_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mux2 M_mux2;

//! Структура модуля.
struct _S_Mux2 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value[MUX2_INPUTS]; //!< Входные значения.
    // Выходные данные.
    iql_t out_value; //!< Выходное значение.
    // Параметры.
    reg_u32_t p_sel; //!< Селектор значений.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mux2);
    METHOD_DEINIT(M_mux2);
    METHOD_CALC(M_mux2);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mux2);
EXTERN METHOD_DEINIT_PROTO(M_mux2);
EXTERN METHOD_CALC_PROTO(M_mux2);

#define MUX2_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        0, /* p_sel */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_mux2), METHOD_DEINIT_PTR(M_mux2),\
        METHOD_CALC_PTR(M_mux2),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MUX2_H */
