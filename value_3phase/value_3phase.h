#ifndef VALUE_3PHASE_H
#define VALUE_3PHASE_H

#include "module/base.h"


// Константы для p_sel.
//! Ничего не вычислять.
#define VALUE_3PHASE_CALC_NONE 0
//! Вычислять фазу A.
#define VALUE_3PHASE_CALC_A 1
//! Вычислять фазу B.
#define VALUE_3PHASE_CALC_B 2
//! Вычислять фазу C.
#define VALUE_3PHASE_CALC_C 3


//! Перечисление возможных бит управления.
enum _E_Value_3phase_Control {
    VALUE_3PHASE_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Value_3phase_Status {
    VALUE_3PHASE_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Value_3phase M_value_3phase;

//! Структура модуля.
struct _S_Value_3phase {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_A;
    reg_iq24_t in_B;
    reg_iq24_t in_C;
    // Выходные данные.
    reg_iq24_t out_A;
    reg_iq24_t out_B;
    reg_iq24_t out_C;
    // Параметры.
    reg_u32_t p_sel; //!< Селектор для вычисления. 0 - не вычислять; 1-3 - номер фазы.
    // Регистры.
    // Методы.
    METHOD_INIT(M_value_3phase);
    METHOD_DEINIT(M_value_3phase);
    METHOD_CALC(M_value_3phase);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_value_3phase);
EXTERN METHOD_DEINIT_PROTO(M_value_3phase);
EXTERN METHOD_CALC_PROTO(M_value_3phase);

#define VALUE_3PHASE_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, 0, 0, /* in_values */\
        /* Выходные данные */\
        0, 0, 0, /* out_values */\
        /* Параметры */\
        0, /* p_sel */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_value_3phase), METHOD_DEINIT_PTR(M_value_3phase),\
        METHOD_CALC_PTR(M_value_3phase),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* VALUE_3PHASE_H */
