#ifndef EDGE_DETECT_H
#define EDGE_DETECT_H

#include "module/base.h"


//! Перечисление возможных бит управления.
enum _E_Edge_Detect_Control {
    EDGE_DETECT_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Edge_Detect_Status {
    EDGE_DETECT_STATUS_NONE = STATUS_NONE,
};


//! Перечисление состояний сигнала.
enum _E_Edge_Detect_Signal_State {
    EDGE_DETECT_LOW = 0b00,
    EDGE_DETECT_LEADING = 0b01,
    EDGE_DETECT_FALLING = 0b10,
    EDGE_DETECT_HIGH = 0b11,
};

//! Тип состояний сигнала.
typedef enum _E_Edge_Detect_Signal_State edge_detect_signal_state_t;


//! Предварительная декларация типа модуля.
typedef struct _S_Edge_Detect M_edge_detect;

//! Структура модуля.
struct _S_Edge_Detect {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    flag_t in_value; //!< Значение сигнала.
    // Выходные данные.
    edge_detect_signal_state_t out_value; //!< Детектированный фронт(состояние) сигнала.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_edge_detect);
    METHOD_DEINIT(M_edge_detect);
    METHOD_CALC(M_edge_detect);
    // Коллбэки.
    // Внутренние данные.
    flag_t m_b0_z1; //!< Прошлое входное значение.
};

EXTERN METHOD_INIT_PROTO(M_edge_detect);
EXTERN METHOD_DEINIT_PROTO(M_edge_detect);
EXTERN METHOD_CALC_PROTO(M_edge_detect);

#define EDGE_DETECT_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_edge_detect), METHOD_DEINIT_PTR(M_edge_detect),\
        METHOD_CALC_PTR(M_edge_detect),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_b0_z1 */\
    }

#endif /* EDGE_DETECT_H */
