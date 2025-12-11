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
    SYS_COMMAND_COMMAND_NONE           = 0x00,
    SYS_COMMAND_COMMAND_CELL_CB_NO     = 0x01, //!< Ячейка NO.
    SYS_COMMAND_COMMAND_CELL_CB_NC     = 0x02, //!< Ячейка NC.
    SYS_COMMAND_COMMAND_CELL_PROT      = 0x04, //!< Ячейка Защита.
    SYS_COMMAND_COMMAND_TEST           = 0x08, //!< Опробование.
    SYS_COMMAND_COMMAND_ENABLE         = 0x10, //!< Разрешение работы.
    SYS_COMMAND_COMMAND_INC            = 0x20, //!< Больше.
    SYS_COMMAND_COMMAND_DEC            = 0x40, //!< Меньше.
    SYS_COMMAND_COMMAND_MANUAL_AUTO    = 0x80, //!< Ручной/Автомат.
    SYS_COMMAND_COMMAND_LOCAL_REMOTE   = 0x100, //!< Мест/Дист.
    SYS_COMMAND_COMMAND_FORW_BACKW     = 0x200, //!< Вперёд/Назад.
    SYS_COMMAND_COMMAND_RESET_ERR      = 0x400, //!< Сброс ошибки.
    SYS_COMMAND_COMMAND_EXTERNAL_FAULT = 0x800, //!< Грибок.
    SYS_COMMAND_COMMAND_MAINS_SWITCH   = 0x1000, //!< Контактор.
    SYS_COMMAND_COMMAND_MAINS_TRIP     = 0x2000, //!< Расцепитель.
    SYS_COMMAND_COMMAND_EXT_EXCITER    = 0x4000, //!< Внешний возбудитель вкл.
    //SYS_COMMAND_COMMAND_ = 0x0,
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
    sys_command_out_command_t out_command; //!< Выходное командное слово. @{"id": 3, "rpdo": true}
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
