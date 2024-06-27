#ifndef SYS_COMMAND_H
#define SYS_COMMAND_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Sys_Command_Control {
    SYS_COMMAND_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Sys_Command_Status {
    SYS_COMMAND_STATUS_NONE = STATUS_NONE,
};

//! Командное слово 0.
enum _E_Sys_Command_Command0 {
    SYS_COMMAND_COMMAND_NONE   = 0x00,
    SYS_COMMAND_COMMAND_CB_ON  = 0x01,
    SYS_COMMAND_COMMAND_CB_OFF = 0x02,
    SYS_COMMAND_COMMAND_PROT   = 0x04,
    SYS_COMMAND_COMMAND_TEST   = 0x08,
};

//! Тип командного слова.
typedef reg_u32_t sys_command_out_command_t;

//! Предварительная декларация типа модуля.
typedef struct _S_Sys_Command M_sys_command;

//! Структура модуля.
struct _S_Sys_Command {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    sys_command_out_command_t out_command; //!< Выходное командное слово.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_sys_command);
    METHOD_DEINIT(M_sys_command);
    METHOD_CALC(M_sys_command);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_sys_command);
EXTERN METHOD_DEINIT_PROTO(M_sys_command);
EXTERN METHOD_CALC_PROTO(M_sys_command);

#define SYS_COMMAND_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        0, /* out_command */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_sys_command), METHOD_DEINIT_PTR(M_sys_command),\
        METHOD_CALC_PTR(M_sys_command),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* SYS_COMMAND_H */
