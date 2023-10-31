#ifndef PHASE_CONTROL_H
#define PHASE_CONTROL_H

#include "module/base.h"
#include "conf/conf.h"
#include "iqmath/iqmath.h"
#include <stdint.h>



//! Окно для управления по-умолчанию.
#define PHASE_CONTROL_ANGLE_WIN_DEFAULT (IQ24_2PI_PU / CONF_PERIOD_SAMPLES)

//! Константы углов.
//! Угол всего цикла управления.
#define PHASE_CONTROL_CYCLE_ANGLE (IQ24_2PI_PU)
//! Маска угла всего цикла управления для нормализации.
#define PHASE_CONTROL_CYCLE_ANGLE_MASK (PHASE_CONTROL_CYCLE_ANGLE - 1)
//! Угол, означающий начало цикла управления.
#define PHASE_CONTROL_CYCLE_ANGLE_BEGIN (PHASE_CONTROL_CYCLE_ANGLE / 2)
//! Угол, означающий окончание цикла управления.
#define PHASE_CONTROL_CYCLE_ANGLE_END (PHASE_CONTROL_CYCLE_ANGLE - PHASE_CONTROL_CYCLE_ANGLE_BEGIN)



//! Перечисление возможных бит управления.
enum _E_Phase_Control_Control {
    PHASE_CONTROL_CONTROL_NONE = CONTROL_NONE,
    PHASE_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Phase_Control_Status {
    PHASE_CONTROL_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Phase_Control M_phase_control;

//! Структура модуля.
struct _S_Phase_Control {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_angle_pu; //!< Угол слежения, в периодических единицах - [0; 2*pi).
    reg_iq24_t in_control_angle_pu; //!< Угол начала управления, в периодических единицах.
    reg_iq24_t in_min_angle_to_control_pu; //!< Минимальный угол для управления, в периодических единицах.
    reg_iq24_t in_max_angle_to_control_pu; //!< Максимальный угол для управления, в периодических единицах.
    // Выходные данные.
    strobe_t out_cycle; //!< Строб начала цикла управления.
    strobe_t out_period; //!< Строб начала периода.
    strobe_t out_control; //!< Строб начала управления.
    reg_iq24_t out_control_angle_pu; //!< Угол начала управления, в периодических единицах - [0; 2*pi + da).
    flag_t out_control_late; //!< Флаг опоздания (угол текущего семпла больше чем угол начала управления).
    flag_t out_control_between; //!< Флаг нахождения начала управления между текущим и следующим семплом.
    // Параметры.
    reg_iq24_t p_angle_win_pu; //!< Угол, в периодических единицах, окно для управления от текущего угла.
    // Регистры.
    // Методы.
    METHOD_INIT(M_phase_control);
    METHOD_DEINIT(M_phase_control);
    METHOD_CALC(M_phase_control);
    // Коллбэки.
    // Внутренние данные.
    iq24_t m_angle; //!< Угол цикла управления.
    iq24_t m_angle_z1; //!< Предыдущий угол цикла управления.
    strobe_t m_out_control; //!< Строб управления.
    iq24_t m_control_angle; //!< Угол установки управления.
    flag_t m_control_state; //!< Флаг управления в текущем периоде.
};

EXTERN METHOD_INIT_PROTO(M_phase_control);
EXTERN METHOD_DEINIT_PROTO(M_phase_control);
EXTERN METHOD_CALC_PROTO(M_phase_control);

#define PHASE_CONTROL_DEFCFG(P_ANGLE_WIN) {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_angle */\
        0, /* in_control_angle */\
        0, /* in_min_angle_to_control */\
        0, /* in_max_angle_to_control */\
        /* Выходные данные */\
        0, /* out_cycle */\
        0, /* out_period */\
        0, /* out_control */\
        0, /* out_control_angle */\
        0, /* out_control_late */\
        0, /* out_control_between */\
        /* Параметры */\
        P_ANGLE_WIN, /* p_angle_win */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_phase_control), METHOD_DEINIT_PTR(M_phase_control),\
        METHOD_CALC_PTR(M_phase_control),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_angle */\
        0, /* m_angle_z1 */\
        0, /* m_control_angle */\
        0, /* m_control_state */\
    }

#define PHASE_CONTROL_DEFAULTS PHASE_CONTROL_DEFCFG(PHASE_CONTROL_ANGLE_WIN_DEFAULT)

#endif /* PHASE_CONTROL_H */
