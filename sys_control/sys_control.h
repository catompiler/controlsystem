#ifndef SYS_CONTROL_H
#define SYS_CONTROL_H

#include "module/base.h"
#include "fsm/fsm.h"

//! Перечисление возможных бит управления.
enum _E_Sys_Control_Control {
    SYS_CONTROL_CONTROL_NONE    = CONTROL_NONE,
    SYS_CONTROL_CONTROL_ENABLE  = 0x01,
    SYS_CONTROL_CONTROL_ON      = 0x02,
    SYS_CONTROL_CONTROL_CONT_ON = 0x04,
    SYS_CONTROL_CONTROL_RUN     = 0x08,
};

//! Перечисление возможных бит статуса.
enum _E_Sys_Control_Status {
    SYS_CONTROL_STATUS_NONE = STATUS_NONE,
    SYS_CONTROL_STATUS_ERROR = STATUS_ERROR,
};

//! Перечисление возможных бит ошибок.
enum _E_Sys_Control_Errors {
    SYS_CONTROL_ERROR_NONE = ERROR_NONE, //!< Нет ошибок.
    //SYS_CONTROL_ERROR_INTERNAL = 0x01, //!< Внутренняя ошибка.
    SYS_CONTROL_ERROR_HARDWARE = 0x02, //!< Ошибка аппаратной части.
    SYS_CONTROL_ERROR_SOFTWARE = 0x04, //!< Ошибка программной части.
    //SYS_CONTROL_ERROR_ = 0x00, //!< .
};

//! Перечисление возможных бит предупреждений.
enum _E_Sys_Control_Warnings {
    SYS_CONTROL_WARNING_NONE = WARNING_NONE, //!< Нет предупреждений.
    //SYS_CONTROL_WARNING_ = 0x00, //!<
};

//! Перечисление возможных бит состояния.
enum _E_Sys_Control_State {
    SYS_CONTROL_STATE_NONE = 0x00,
    SYS_CONTROL_STATE_INIT,
    SYS_CONTROL_STATE_OFF,
    SYS_CONTROL_STATE_READY_ON,
    SYS_CONTROL_STATE_READY_RUN,
    SYS_CONTROL_STATE_RUN,
    SYS_CONTROL_STATE_ERROR,
};

//! Перечисление состояний включения.
enum _E_Sys_Control_Ready_On_State {
    SYS_CONTROL_READY_ON_NONE = 0x00,
    SYS_CONTROL_READY_ON_WAIT_ON,
    SYS_CONTROL_READY_ON_WAIT_MAINS,
    SYS_CONTROL_READY_ON_WAIT_MAINS_FREQ,
    SYS_CONTROL_READY_ON_WAIT_CONT_ON,
    SYS_CONTROL_READY_ON_DONE
};

//! Предварительная декларация типа модуля.
typedef struct _S_Sys_Control M_sys_control;

//! Структура модуля.
struct _S_Sys_Control {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    error_t errors; //!< Ошибки.
    warning_t warnings; //!< Предупреждения.
    fsm_t fsm_state; //!< Основной КА.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_sys_control);
    METHOD_DEINIT(M_sys_control);
    METHOD_CALC(M_sys_control);
    // Коллбэки.
    // Внутренние данные.
    fsm_t fsm_ready_on; //!< Конечный автомат включения.
};

EXTERN METHOD_INIT_PROTO(M_sys_control);
EXTERN METHOD_DEINIT_PROTO(M_sys_control);
EXTERN METHOD_CALC_PROTO(M_sys_control);

#define SYS_CONTROL_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        0, 0, /* errors, warnings */\
        FSM_DEFAULTS, /* fsm_state */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_sys_control), METHOD_DEINIT_PTR(M_sys_control),\
        METHOD_CALC_PTR(M_sys_control),\
        /* Коллбэки */\
        /* Внутренние данные */\
        FSM_DEFAULTS, /* fsm_ready_on */\
    }

#endif /* SYS_CONTROL_H */
