#ifndef MUX5_H
#define MUX5_H

#include "module/base.h"
#include "iqmath/iq.h"


//! Число входов мультиплексора.
#define MUX5_INPUTS 5


//! Перечисление возможных бит управления.
enum _E_Mux5_Control {
    MUX5_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mux5_Status {
    MUX5_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mux5 M_mux5;

//! Структура модуля.
struct _S_Mux5 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value[MUX5_INPUTS]; //!< Входные значения.
    // Выходные данные.
    iql_t out_value; //!< Выходное значение.
    // Параметры.
    reg_u32_t p_sel; //!< Селектор значений.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mux5);
    METHOD_DEINIT(M_mux5);
    METHOD_CALC(M_mux5);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mux5);
EXTERN METHOD_DEINIT_PROTO(M_mux5);
EXTERN METHOD_CALC_PROTO(M_mux5);

#define MUX5_DEFAULTS {\
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
        METHOD_INIT_PTR(M_mux5), METHOD_DEINIT_PTR(M_mux5),\
        METHOD_CALC_PTR(M_mux5),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MUX5_H */
