#ifndef MUX6_H
#define MUX6_H

#include "module/base.h"
#include "iqmath/iq.h"


//! Число входов мультиплексора.
#define MUX6_INPUTS 6


//! Перечисление возможных бит управления.
enum _E_Mux6_Control {
    MUX6_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mux6_Status {
    MUX6_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mux6 M_mux6;

//! Структура модуля.
struct _S_Mux6 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value[MUX6_INPUTS]; //!< Входные значения.
    // Выходные данные.
    iql_t out_value; //!< Выходное значение.
    // Параметры.
    reg_u32_t p_sel; //!< Селектор значений.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mux6);
    METHOD_DEINIT(M_mux6);
    METHOD_CALC(M_mux6);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mux6);
EXTERN METHOD_DEINIT_PROTO(M_mux6);
EXTERN METHOD_CALC_PROTO(M_mux6);

#define MUX6_DEFAULTS {\
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
        METHOD_INIT_PTR(M_mux6), METHOD_DEINIT_PTR(M_mux6),\
        METHOD_CALC_PTR(M_mux6),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MUX6_H */
