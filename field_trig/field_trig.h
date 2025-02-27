#ifndef FIELD_TRIG_H
#define FIELD_TRIG_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Field_Trig_Control {
    FIELD_TRIG_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Field_Trig_Status {
    FIELD_TRIG_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Field_Trig M_field_trig;

//! Структура модуля.
struct _S_Field_Trig {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    flag_t out_run; //! Состояние триггера включения двигателя.
    flag_t out_field_on; //! Состояние триггера включения возбуждения.
    flag_t out_rstart_on; //!< Триггер управления пусковым сопротивлением.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_field_trig);
    METHOD_DEINIT(M_field_trig);
    METHOD_CALC(M_field_trig);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_field_trig);
EXTERN METHOD_DEINIT_PROTO(M_field_trig);
EXTERN METHOD_CALC_PROTO(M_field_trig);

#define FIELD_TRIG_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        0, /* out_run */\
        0, /* out_field_on */\
        0, /* out_rstart_on */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_field_trig), METHOD_DEINIT_PTR(M_field_trig),\
        METHOD_CALC_PTR(M_field_trig),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* FIELD_TRIG_H */
