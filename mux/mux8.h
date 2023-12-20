#ifndef MUX8_H
#define MUX8_H

#include "module/base.h"
#include "iqmath/iq.h"


//! Число входов мультиплексора.
#define MUX8_INPUTS 8


//! Перечисление возможных бит управления.
enum _E_Mux8_Control {
    MUX8_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mux8_Status {
    MUX8_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mux8 M_mux8;

//! Структура модуля.
struct _S_Mux8 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value[MUX8_INPUTS]; //!< Входные значения.
    // Выходные данные.
    iql_t out_value; //!< Выходное значение.
    // Параметры.
    reg_u32_t p_sel; //!< Селектор значений.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mux8);
    METHOD_DEINIT(M_mux8);
    METHOD_CALC(M_mux8);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mux8);
EXTERN METHOD_DEINIT_PROTO(M_mux8);
EXTERN METHOD_CALC_PROTO(M_mux8);

#define MUX8_DEFAULTS {\
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
        METHOD_INIT_PTR(M_mux8), METHOD_DEINIT_PTR(M_mux8),\
        METHOD_CALC_PTR(M_mux8),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MUX8_H */
