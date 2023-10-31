#ifndef SYS_TIME_H
#define SYS_TIME_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Sys_Time_Control {
    SYS_TIME_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Sys_Time_Status {
    SYS_TIME_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Sys_Time M_sys_time;

//! Структура модуля.
struct _S_Sys_Time {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Регистры.
    reg_u32_t r_counter_ms; //!< Счётчик времени после загрузки в мс.
    reg_u32_t r_counter_s; //!< Счётчик времени после загрузки в с.
    reg_u32_t r_run_counter_s; //!< Счётчик времени работы в с.
    // Методы.
    METHOD_INIT(M_sys_time);
    METHOD_DEINIT(M_sys_time);
    METHOD_CALC(M_sys_time); //!< Должно вызываться с частотой 1 кГц.
    // Коллбэки.
    // Внутренние данные.
    uint32_t m_counter_ms; //!< Счётчик времени после загрузки в мс.
    uint32_t m_run_counter_ms; //!< Счётчик времени работы в мс.
};

EXTERN METHOD_INIT_PROTO(M_sys_time);
EXTERN METHOD_DEINIT_PROTO(M_sys_time);
EXTERN METHOD_CALC_PROTO(M_sys_time);

#define SYS_TIME_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        0, /* r_counter_ms */\
        0, /* r_counter_s */\
        0, /* r_run_counter_s */\
        /* Методы */\
        METHOD_INIT_PTR(M_sys_time), METHOD_DEINIT_PTR(M_sys_time),\
        METHOD_CALC_PTR(M_sys_time),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_counter_ms */\
        0, /* m_run_counter_ms */\
    }

#endif /* SYS_TIME_H */
