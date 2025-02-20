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
    SYS_STATUS_COMMAND_NONE         = 0x0, //!<
    SYS_STATUS_COMMAND_READY        = 0x1, //!< Готовность.
    SYS_STATUS_COMMAND_RUN          = 0x2, //!< Работа.
    SYS_STATUS_COMMAND_ERROR        = 0x4, //!< Ошибка.
    SYS_STATUS_COMMAND_WARNING      = 0x8, //!< Предупреждение.
    SYS_STATUS_COMMAND_LIMIT        = 0x10, //!< Ограничители.
    SYS_STATUS_COMMAND_CELL_CB      = 0x20, //!< ВВ Вкл.
    SYS_STATUS_COMMAND_MANUAL_AUTO  = 0x40, //!< Ручной/Автомат.
    SYS_STATUS_COMMAND_LOCAL_REMOTE = 0x80, //!< Мест/Дист.
    SYS_STATUS_COMMAND_FORW_BACKW   = 0x100, //!< Вперёд/Назад.
    SYS_STATUS_COMMAND_FAN          = 0x200, //!< Вентилятор.
    SYS_STATUS_COMMAND_MAINS_CB     = 0x400, //!< Контактор.
    SYS_STATUS_COMMAND_MAINS_TRIP   = 0x800, //!< Расцепитель.
    SYS_STATUS_COMMAND_EXT_BRAKE    = 0x1000, //!< Внешний тормоз.
    SYS_STATUS_COMMAND_EXC_INV      = 0x2000, //!< Инвертирование возбуждения.
    SYS_STATUS_COMMAND_EXT_EXCITER  = 0x4000, //!< Внешний возбудитель вкл.
    SYS_STATUS_COMMAND_R_START_ON   = 0x8000, //!< Включение пускового сопротивления.
    SYS_STATUS_COMMAND_USER_0       = 0x10000, //!< Пользовательский выход 0.
    SYS_STATUS_COMMAND_USER_1       = 0x20000, //!< Пользовательский выход 1.
//    SYS_STATUS_COMMAND_             = 0x0,

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
