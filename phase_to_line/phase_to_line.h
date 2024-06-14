#ifndef PHASE_TO_LINE_H
#define PHASE_TO_LINE_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Phase_To_Line_Control {
    PHASE_TO_LINE_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Phase_To_Line_Status {
    PHASE_TO_LINE_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Phase_To_Line M_phase_to_line;

//! Структура модуля.
struct _S_Phase_To_Line {
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
    METHOD_INIT(M_phase_to_line);
    METHOD_DEINIT(M_phase_to_line);
    METHOD_CALC(M_phase_to_line);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_phase_to_line);
EXTERN METHOD_DEINIT_PROTO(M_phase_to_line);
EXTERN METHOD_CALC_PROTO(M_phase_to_line);

#define PHASE_TO_LINE_DEFAULTS {\
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
        METHOD_INIT_PTR(M_phase_to_line), METHOD_DEINIT_PTR(M_phase_to_line),\
        METHOD_CALC_PTR(M_phase_to_line),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* PHASE_TO_LINE_H */
