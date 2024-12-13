#ifndef SYS_MAIN_H
#define SYS_MAIN_H

#include "module/base.h"
#include "fsm/fsm.h"

// Константы.
//!
//#define SYS_MAIN_INIT_

//! Перечисление возможных бит управления.
enum _E_Sys_Main_Control {
    SYS_MAIN_CONTROL_NONE = CONTROL_NONE,//!< SYS_MAIN_CONTROL_NONE
    SYS_MAIN_CONTROL_STOP = CONTROL_STOP//!< SYS_MAIN_CONTROL_NONE
};

//! Перечисление возможных бит статуса.
enum _E_Sys_Main_Status {
    SYS_MAIN_STATUS_NONE = STATUS_NONE,
    SYS_MAIN_STATUS_ERROR = STATUS_ERROR,
    //SYS_MAIN_STATUS_INIT = (STATUS_USER << 0),
};

//! Перечисление возможных бит ошибок.
enum _E_Sys_Main_Errors {
    SYS_MAIN_ERROR_NONE = ERROR_NONE, //!< Нет ошибок.
    //SYS_MAIN_ERROR_INTERNAL = 0x01, //!< Внутренняя ошибка.
    SYS_MAIN_ERROR_HARDWARE = 0x02, //!< Ошибка аппаратной части.
    SYS_MAIN_ERROR_SOFTWARE = 0x04, //!< Ошибка программной части.
    //SYS_MAIN_ERROR_ = 0x00, //!< .
};

//! Перечисление возможных бит предупреждений.
enum _E_Sys_Main_Warnings {
    SYS_MAIN_WARNING_NONE = WARNING_NONE, //!< Нет предупреждений.
    //SYS_MAIN_WARNING_ = 0x00, //!<
};

//! Перечисление возможных бит состояния.
enum _E_Sys_Main_State {
    SYS_MAIN_STATE_NONE = STATE_NONE,
    SYS_MAIN_STATE_INIT = STATE_INIT,
    SYS_MAIN_STATE_RUN = STATE_RUN,
};


typedef struct _S_Sys_Main M_sys_main;

struct _S_Sys_Main {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    error_t errors; //!< Ошибки.
    warning_t warnings; //!< Предупреждения.
    fsm_t fsm_state; //!< КА состояния..
    // Входные данные.
    // Выходные данные.
    // Параметры.
    //reg_u32_t p_ready_on_wait_mains_time; //!< Время ожидания сетевого напряжения, мс.
    //reg_u32_t p_ready_on_wait_freq_time; //!< Время ожидания частоты сети, мс.
    // Регистры.
    // Методы.
    METHOD_INIT(M_sys_main);
    METHOD_DEINIT(M_sys_main);
    METHOD_CALC(M_sys_main);
    METHOD_IDLE(M_sys_main);
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_sys_main);
EXTERN METHOD_DEINIT_PROTO(M_sys_main);
EXTERN METHOD_CALC_PROTO(M_sys_main);
EXTERN METHOD_IDLE_PROTO(M_sys_main);

#define SYS_MAIN_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        0, 0, /* errors, warnings */\
        FSM_DEFAULTS, /* fsm_state */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_sys_main), METHOD_DEINIT_PTR(M_sys_main),\
        METHOD_CALC_PTR(M_sys_main), METHOD_IDLE_PTR(M_sys_main),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* SYS_MAIN_H */
