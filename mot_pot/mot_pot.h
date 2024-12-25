#ifndef MOT_POT_H
#define MOT_POT_H

#include "module/base.h"
#include "conf/consts.h"



//! Период дискретизации для частоты F Гц.
#define MOT_POT_Ts_FREQ(F) (IQ24(1.0/(F)))

//! Период дискретизации по-умолчанию.
#define MOT_POT_Ts_DEFAULT (MOT_POT_Ts_FREQ(CONF_SAMPLE_RATE))

//! Период дискретизации для частоты 1000 Гц.
#define MOT_POT_Ts_1000Hz (MOT_POT_Ts_FREQ(1000))

//! Время изменения величины.
#define MOT_POT_T(T) (IQ15(T))

//! Время изменения величины по-умолчанию.
#define MOT_POT_T_DEFAULT (MOT_POT_T(1))


//! Минимум по-умолчанию.
#define MOT_POT_MIN_DEFAULT (0)

//! Максимум по-умолчанию.
#define MOT_POT_MAX_DEFAULT (IQ24(1))



//! Перечисление возможных бит управления.
enum _E_Mot_Pot_Control {
    MOT_POT_CONTROL_NONE = CONTROL_NONE,//!< MOT_POT_CONTROL_NONE
    MOT_POT_CONTROL_RESET = CONTROL_RESET, //!< Сброс значения на 0.
};

//! Перечисление возможных бит статуса.
enum _E_Mot_Pot_Status {
    MOT_POT_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mot_Pot M_mot_pot;

//! Структура модуля.
struct _S_Mot_Pot {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    flag_t in_dec; //!< Флаг декремента.
    flag_t in_inc; //!< Флаг инкремента.
    // Выходные данные.
    // Параметры.
    reg_iq15_t p_time; //!< Время изменения величины от 0 до 100%.
    reg_iq24_t p_min; //!< Минимальное значение.
    reg_iq24_t p_max; //!< Максимальное значение.
    // Регистры.
    reg_iq24_t r_value; //!< Значение.
    reg_iq24_t r_Ts; //!< Период дискретизации.
    // Методы.
    METHOD_INIT(M_mot_pot);
    METHOD_DEINIT(M_mot_pot);
    METHOD_CALC(M_mot_pot);
    METHOD_IDLE(M_mot_pot);
    // Коллбэки.
    // Внутренние данные.
    iq24_t m_dv_Ts; //!< Изменение величины за период дискретизации.
};

EXTERN METHOD_INIT_PROTO(M_mot_pot);
EXTERN METHOD_DEINIT_PROTO(M_mot_pot);
EXTERN METHOD_CALC_PROTO(M_mot_pot);
EXTERN METHOD_IDLE_PROTO(M_mot_pot);

#define MOT_POT_DEFCFG(MIN, MAX, TIME, TS) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_dec */\
        0, /* in_inc */\
        /* Выходные данные */\
        /* Параметры */\
        TIME, /* p_time */\
        MIN, /* p_min */\
        MAX, /* p_max */\
        /* Регистры */\
        0, /* r_value */\
        TS, /* r_Ts */\
        /* Методы */\
        METHOD_INIT_PTR(M_mot_pot), METHOD_DEINIT_PTR(M_mot_pot),\
        METHOD_CALC_PTR(M_mot_pot), METHOD_IDLE_PTR(M_mot_pot),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_dv_Ts */\
    }

#define MOT_POT_DEFAULTS MOT_POT_DEFCFG(MOT_POT_MIN_DEFAULT, MOT_POT_MAX_DEFAULT, MOT_POT_T_DEFAULT, MOT_POT_Ts_DEFAULT)

#endif /* MOT_POT_H */
