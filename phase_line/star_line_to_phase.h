#ifndef STAR_LINE_TO_PHASE_H
#define STAR_LINE_TO_PHASE_H

#include "module/base.h"
#include "clarke/clarke.h"
#include "clarke/clarke_inv.h"
#include "park/park.h"


//! Перечисление возможных бит управления.
enum _E_Star_Line_To_Phase_Control {
    STAR_LINE_TO_PHASE_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Star_Line_To_Phase_Status {
    STAR_LINE_TO_PHASE_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Star_Line_To_Phase M_star_line_to_phase;

//! Структура модуля.
struct _S_Star_Line_To_Phase {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iq24_t in_A; //!< Входная величина по фазе A.
    iq24_t in_B; //!< Входная величина по фазе B.
    iq24_t in_C; //!< Входная величина по фазе C.
    // Выходные данные.
    iq24_t out_A; //!< Выходная величина по фазе A.
    iq24_t out_B; //!< Выходная величина по фазе B.
    iq24_t out_C; //!< Выходная величина по фазе C.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_star_line_to_phase);
    METHOD_DEINIT(M_star_line_to_phase);
    METHOD_CALC(M_star_line_to_phase);
    // Коллбэки.
    // Внутренние данные.
    // Внутренние модули.
    M_clarke m_clarke;
    M_park m_park;
    M_clarke_inv m_clarke_inv;
};

EXTERN METHOD_INIT_PROTO(M_star_line_to_phase);
EXTERN METHOD_DEINIT_PROTO(M_star_line_to_phase);
EXTERN METHOD_CALC_PROTO(M_star_line_to_phase);

#define STAR_LINE_TO_PHASE_DEFAULTS {\
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
        METHOD_INIT_PTR(M_star_line_to_phase), METHOD_DEINIT_PTR(M_star_line_to_phase),\
        METHOD_CALC_PTR(M_star_line_to_phase),\
        /* Коллбэки */\
        /* Внутренние данные */\
        /* Внутренние модули */\
        CLARKE_DEFAULTS, /* m_clarke */\
        PARK_DEFAULTS, /* m_park */\
        CLARKE_INV_DEFAULTS, /* m_clarke_inv */\
    }

#endif /* STAR_LINE_TO_PHASE_H */
