#ifndef PID_COEFS_H
#define PID_COEFS_H

#include "module/base.h"
#include "adc_timer/adc_timer.h"


//! Период дискретизации по-умолчанию.
#define PID_COEFS_Ts_DEFAULT (IQ24(1.0/(ADC_TIMER_TICKS_FREQ)))


//! Перечисление возможных бит управления.
enum _E_Pid_Coefs_Control {
    PID_COEFS_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Pid_Coefs_Status {
    PID_COEFS_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Pid_Coefs M_pid_coefs;

//! Структура модуля.
struct _S_Pid_Coefs {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    iq24_t out_kp;
    iq24_t out_ki;
    iq24_t out_kd;
    iq24_t out_kf;
    // Параметры.
    iq24_t p_kp; //!< Коэффициент пропорциональной составляющей.
    iq24_t p_Ti; //!< Постоянная времени интегрирования.
    iq24_t p_Td; //!< Постоянная времени дифференцирования.
    iq24_t p_Tf; //!< Постоянная времени фильтра дифференциальной составляющей.
    // Регистры.
    iq24_t r_Ts; //!< Время дискретизации регулятора.
    // Методы.
    METHOD_INIT(M_pid_coefs);
    METHOD_DEINIT(M_pid_coefs);
    METHOD_IDLE(M_pid_coefs);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_pid_coefs);
EXTERN METHOD_DEINIT_PROTO(M_pid_coefs);
EXTERN METHOD_IDLE_PROTO(M_pid_coefs);

#define PID_COEFS_DEFCFG(KP, TI, TD, TF) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        0, /* out_kp */\
        0, /* out_ki */\
        0, /* out_kd */\
        0, /* out_kf */\
        /* Параметры */\
        KP, /* p_kp */\
        TI, /* p_Ti */\
        TD, /* p_Td */\
        TF, /* p_Tf */\
        /* Регистры */\
        PID_COEFS_Ts_DEFAULT, /* r_Ts */\
        /* Методы */\
        METHOD_INIT_PTR(M_pid_coefs), METHOD_DEINIT_PTR(M_pid_coefs),\
        METHOD_IDLE_PTR(M_pid_coefs),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#define PID_COEFS_DEFAULTS PID_COEFS_DEFCFG(0, 0, 0, 0)

#endif /* PID_COEFS_H */
