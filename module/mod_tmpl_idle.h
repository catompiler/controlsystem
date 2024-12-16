#ifndef MOD_TMPL_H
#define MOD_TMPL_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Mod_Tmpl_Control {
    MOD_TMPL_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mod_Tmpl_Status {
    MOD_TMPL_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mod_Tmpl M_mod_tmpl;

//! Структура модуля.
struct _S_Mod_Tmpl {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mod_tmpl);
    METHOD_DEINIT(M_mod_tmpl);
    METHOD_CALC(M_mod_tmpl);
    METHOD_IDLE(M_mod_tmpl);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mod_tmpl);
EXTERN METHOD_DEINIT_PROTO(M_mod_tmpl);
EXTERN METHOD_CALC_PROTO(M_mod_tmpl);
EXTERN METHOD_IDLE_PROTO(M_mod_tmpl);

#define MOD_TMPL_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_mod_tmpl), METHOD_DEINIT_PTR(M_mod_tmpl),\
        METHOD_CALC_PTR(M_mod_tmpl), METHOD_IDLE_PTR(M_mod_tmpl),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MOD_TMPL_H */
