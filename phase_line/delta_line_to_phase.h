#ifndef DELTA_LINE_TO_PHASE_H
#define DELTA_LINE_TO_PHASE_H

#include "module/base.h"


//! Перечисление возможных бит управления.
enum _E_Delta_Line_To_Phase_Control {
    DELTA_LINE_TO_PHASE_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Delta_Line_To_Phase_Status {
    DELTA_LINE_TO_PHASE_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Delta_Line_To_Phase M_delta_line_to_phase;

//! Структура модуля.
struct _S_Delta_Line_To_Phase {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_A; //!< Входная величина по фазе A.
    iql_t in_B; //!< Входная величина по фазе B.
    iql_t in_C; //!< Входная величина по фазе C.
    // Выходные данные.
    iql_t out_A; //!< Выходная величина по фазе A.
    iql_t out_B; //!< Выходная величина по фазе B.
    iql_t out_C; //!< Выходная величина по фазе C.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_delta_line_to_phase);
    METHOD_DEINIT(M_delta_line_to_phase);
    METHOD_CALC(M_delta_line_to_phase);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_delta_line_to_phase);
EXTERN METHOD_DEINIT_PROTO(M_delta_line_to_phase);
EXTERN METHOD_CALC_PROTO(M_delta_line_to_phase);

#define DELTA_LINE_TO_PHASE_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_A */\
        0, /* in_B */\
        0, /* in_C */\
        /* Выходные данные */\
        0, /* out_A */\
        0, /* out_B */\
        0, /* out_C */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_delta_line_to_phase), METHOD_DEINIT_PTR(M_delta_line_to_phase),\
        METHOD_CALC_PTR(M_delta_line_to_phase),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* DELTA_LINE_TO_PHASE_H */
