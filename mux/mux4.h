#ifndef MUX4_H
#define MUX4_H

#include "module/base.h"
#include "iqmath/iq.h"


//! Число входов мультиплексора.
#define MUX4_INPUTS 4


//! Перечисление возможных бит управления.
enum _E_Mux4_Control {
    MUX4_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mux4_Status {
    MUX4_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mux4 M_mux4;

//! Структура модуля.
struct _S_Mux4 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value[MUX4_INPUTS]; //!< Входные значения.
    // Выходные данные.
    iql_t out_value; //!< Выходное значение.
    // Параметры.
    reg_u32_t p_sel; //!< Селектор значений.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mux4);
    METHOD_DEINIT(M_mux4);
    METHOD_CALC(M_mux4);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mux4);
EXTERN METHOD_DEINIT_PROTO(M_mux4);
EXTERN METHOD_CALC_PROTO(M_mux4);

#define MUX4_DEFAULTS {\
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
        METHOD_INIT_PTR(M_mux4), METHOD_DEINIT_PTR(M_mux4),\
        METHOD_CALC_PTR(M_mux4),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MUX4_H */
