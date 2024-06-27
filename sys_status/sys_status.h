#ifndef SYS_STATUS_H
#define SYS_STATUS_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Sys_Status_Control {
    SYS_STATUS_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Sys_Status_Status {
    SYS_STATUS_STATUS_NONE = STATUS_NONE,
};

//! Командное слово 0.
enum _E_Sys_Status_Command0 {
    SYS_STATUS_COMMAND_NONE       = 0x00,
    SYS_STATUS_COMMAND_R_START_ON = 0x01, //!< Включение пускового сопротивления.
};

//! Тип командного слова.
typedef reg_u32_t sys_status_in_command_t;

//! Предварительная декларация типа модуля.
typedef struct _S_Sys_Status M_sys_status;

//! Структура модуля.
struct _S_Sys_Status {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    sys_status_in_command_t in_command; //!< Входное командное слово.
    // Выходные данные.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_sys_status);
    METHOD_DEINIT(M_sys_status);
    METHOD_CALC(M_sys_status);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_sys_status);
EXTERN METHOD_DEINIT_PROTO(M_sys_status);
EXTERN METHOD_CALC_PROTO(M_sys_status);

#define SYS_STATUS_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_command */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_sys_status), METHOD_DEINIT_PTR(M_sys_status),\
        METHOD_CALC_PTR(M_sys_status),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* SYS_STATUS_H */
