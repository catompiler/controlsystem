#ifndef MUX3_H
#define MUX3_H

#include "module/base.h"
#include "iqmath/iq.h"


//! Число входов мультиплексора.
#define MUX3_INPUTS 3


//! Перечисление возможных бит управления.
enum _E_Mux3_Control {
    MUX3_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mux3_Status {
    MUX3_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mux3 M_mux3;

//! Структура модуля.
struct _S_Mux3 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value[MUX3_INPUTS]; //!< Входные значения.
    // Выходные данные.
    iql_t out_value; //!< Выходное значение.
    // Параметры.
    reg_u32_t p_sel; //!< Селектор значений.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mux3);
    METHOD_DEINIT(M_mux3);
    METHOD_CALC(M_mux3);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mux3);
EXTERN METHOD_DEINIT_PROTO(M_mux3);
EXTERN METHOD_CALC_PROTO(M_mux3);

#define MUX3_DEFAULTS {\
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
        METHOD_INIT_PTR(M_mux3), METHOD_DEINIT_PTR(M_mux3),\
        METHOD_CALC_PTR(M_mux3),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MUX3_H */
