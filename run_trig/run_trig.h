#ifndef RUN_TRIG_H
#define RUN_TRIG_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Run_Trig_Control {
    RUN_TRIG_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Run_Trig_Status {
    RUN_TRIG_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Run_Trig M_run_trig;

//! Структура модуля.
struct _S_Run_Trig {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    flag_t out_value; //! Состояние триггера включения.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_run_trig);
    METHOD_DEINIT(M_run_trig);
    METHOD_CALC(M_run_trig);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_run_trig);
EXTERN METHOD_DEINIT_PROTO(M_run_trig);
EXTERN METHOD_CALC_PROTO(M_run_trig);

#define RUN_TRIG_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_run_trig), METHOD_DEINIT_PTR(M_run_trig),\
        METHOD_CALC_PTR(M_run_trig),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* RUN_TRIG_H */
