#ifndef PID_H
#define PID_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Pid_Control {
    PID_CONTROL_NONE = CONTROL_NONE,
    PID_CONTROL_RESET = CONTROL_RESET,
    PID_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Pid_Status {
    PID_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Pid M_pid;

//! Структура модуля.
struct _S_Pid {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iq24_t in_ref; //!< Задание.
    iq24_t in_fbk; //!< Обратная связь.
    // Выходные данные.
    iq24_t out_value; //!< Воздействие.
    // Параметры.
    // Регистры.
    iq24_t r_kp; //!< Коэффициент пропорциональной составляющей.
    iq24_t r_ki; //!< Коэффициент интегральной составляющей.
    iq24_t r_kd; //!< Коэффициент дифференциальной составляющей.
    iq24_t r_kf; //!< Коэффициент фильтра дифференциальной составляющей.
    iq24_t r_min; //!< Минимальное значение выхода.
    iq24_t r_max; //!< Максимальное значение выхода.
    // Методы.
    METHOD_INIT(M_pid);
    METHOD_DEINIT(M_pid);
    METHOD_CALC(M_pid);
    METHOD_CONTROL(M_pid);
    // Коллбэки.
    // Внутренние данные.
    iq24_t m_I;
    iq24_t m_e_z1;
    iq24_t m_D_z1;
};

EXTERN METHOD_INIT_PROTO(M_pid);
EXTERN METHOD_DEINIT_PROTO(M_pid);
EXTERN METHOD_CALC_PROTO(M_pid);
EXTERN METHOD_CONTROL_PROTO(M_pid);

#define PID_DEFCFG(KP, KI, KD, KF, OUTMIN, OUTMAX) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, 0, /* in_ref, in_fbk */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        KP, /* r_kp */\
        KI, /* r_ki */\
        KD, /* r_kd */\
        KF, /* r_kf */\
        OUTMIN, /* r_min */\
        OUTMAX, /* r_max */\
        /* Методы */\
        METHOD_INIT_PTR(M_pid), METHOD_DEINIT_PTR(M_pid),\
        METHOD_CALC_PTR(M_pid),\
        METHOD_CONTROL_PTR(M_pid),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_I_z1 */\
        0, /* m_e_z1 */\
        0, /* m_D_z1 */\
    }

#define PID_DEFAULTS PID_DEFCFG(0, 0, 0, 0, 0, 0)

#endif /* PID_H */
