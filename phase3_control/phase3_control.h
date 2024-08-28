#ifndef PHASE3_CONTROL_H
#define PHASE3_CONTROL_H

#include "module/base.h"
#include "iqmath/iqmath.h"
#include "conf/conf.h"
#include <stdint.h>
#include "phase_control/phase_control.h"


//RECTIF_3PH_
//! Число фаз для управления.
#define PHASE3_CONTROL_PHASES_COUNT 3

//! Число ключей для управления.
#define PHASE3_CONTROL_KEYS_COUNT (PHASE3_CONTROL_PHASES_COUNT * 2)

//! Индексы управлений и ключей.
//! Управления.
//! Управление AB.
#define PHASE3_CONTROL_AB 0
//! Управление BC.
#define PHASE3_CONTROL_BC 2
//! Управление CA.
#define PHASE3_CONTROL_CA 4
//! Управление BA.
#define PHASE3_CONTROL_BA 3
//! Управление CB.
#define PHASE3_CONTROL_CB 5
//! Управление AC.
#define PHASE3_CONTROL_AC 1
//! Ключи.
//! Ключ верхний фазы A.
#define PHASE3_CONTROL_A_HI 0
//! Ключ верхний фазы B.
#define PHASE3_CONTROL_B_HI 2
//! Ключ верхний фазы C.
#define PHASE3_CONTROL_C_HI 4
//! Ключ нижний фазы A.
#define PHASE3_CONTROL_A_LO 3
//! Ключ нижний фазы B.
#define PHASE3_CONTROL_B_LO 5
//! Ключ нижний фазы C.
#define PHASE3_CONTROL_C_LO 1


//! Минимальный угол управления, PU.
//#define PHASE3_CONTROL_MIN_CONTROL_ANGLE (IQ24_PI_PU / 3)

//! Максимальный угол управления, PU.
//#define PHASE3_CONTROL_MAX_CONTROL_ANGLE (IQ24_PI_PU + 2 * IQ24_PI_PU / 3)


//! Окно для управления по-умолчанию.
#define PHASE3_CONTROL_ANGLE_WIN_DEFAULT IQ24(1.5 / CONF_PERIOD_SAMPLES)

//! Минимальный разрешённый угол для управления по-умолчанию, для 1-фазных PHC.
#define PHASE3_CONTROL_MIN_ANGLE_TO_CONTROL_DEFAULT (0)

//! Максимальный разрешённый угол для управления по-умолчанию, для 1-фазных PHC.
#define PHASE3_CONTROL_MAX_ANGLE_TO_CONTROL_DEFAULT (IQ24_2PI_PU)


//! Минимальный угол управления по-умолчанию.
#define PHASE3_CONTROL_MIN_CONTROL_ANGLE_DEFAULT (IQ15(60))

//! Максимальный угол управления по-умолчанию.
#define PHASE3_CONTROL_MAX_CONTROL_ANGLE_DEFAULT (IQ15(300))


//! Перечисление возможных бит управления.
enum _E_Phase3_Control_Control {
    PHASE3_CONTROL_CONTROL_NONE = CONTROL_NONE,
    PHASE3_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Phase3_Control_Status {
    PHASE3_CONTROL_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Phase3_Control M_phase3_control;

//! Структура модуля.
struct _S_Phase3_Control {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_Ua_angle; //!< Угол фазы AB, в периодических единицах, [0; 2*pi).
    reg_iq24_t in_Ub_angle; //!< Угол фазы BC, в периодических единицах, [0; 2*pi).
    reg_iq24_t in_Uc_angle; //!< Угол фазы CA, в периодических единицах, [0; 2*pi).
    reg_iq24_t in_control_value; //!< Величина управления, 0 - 0%, 1 - 100% от максимума (до ограничения).
    // Выходные данные.
    strobe_t out_control[PHASE3_CONTROL_KEYS_COUNT]; //!< Управление.
    reg_iq24_t out_control_delay_angle; //!< Угол до импульса управления, в периодических единицах.
    reg_iq24_t out_control_max_duration_angle; //!< Максимальная продолжительность (угол) управления, в периодических единицах.
    // Границы значения величины управления.
    reg_iq24_t out_min_control_value; //!< Минимальная величина управления (максимальный электрический угол коммутации).
    reg_iq24_t out_max_control_value; //!< Максимальная величина управления (минимальный электрический угол коммутации).
    // Параметры.
    reg_iq15_t p_min_control_angle; //!< Минимальный угол управления, в электрических градусах.
    reg_iq15_t p_max_control_angle; //!< Максимальный угол управления, в электрических градусах.
    // Регистры.
    // Внутренние модули.
    M_phase_control phc[PHASE3_CONTROL_KEYS_COUNT];
    // Методы.
    METHOD_INIT(M_phase3_control);
    METHOD_DEINIT(M_phase3_control);
    METHOD_CALC(M_phase3_control);
    METHOD_IDLE(M_phase3_control);
    // Коллбэки.
    // Внутренние данные.
    reg_iq24_t m_min_control_angle_pu; //!< Минимальный угол управления, в периодических единицах.
    reg_iq24_t m_max_control_angle_pu; //!< Максимальный угол управления, в периодических единицах.
};


EXTERN METHOD_INIT_PROTO(M_phase3_control);
EXTERN METHOD_DEINIT_PROTO(M_phase3_control);
EXTERN METHOD_CALC_PROTO(M_phase3_control);
EXTERN METHOD_IDLE_PROTO(M_phase3_control);


#define PHASE3_CONTROL_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_Uab_angle */\
        0, /* in_Ubc_angle */\
        0, /* in_Uca_angle */\
        0, /* in_control_value */\
        /* Выходные данные */\
        {0}, /* out_control */\
        0, /* out_control_delay_angle */\
        0, /* out_control_max_duration_angle */\
        /* Границы значения величины управления */\
        0, /* out_min_control_value */\
        0, /* out_max_control_value */\
        /* Параметры */\
        PHASE3_CONTROL_MIN_CONTROL_ANGLE_DEFAULT, /* p_min_angle_to_control */\
        PHASE3_CONTROL_MAX_CONTROL_ANGLE_DEFAULT, /* p_max_angle_to_control */\
        /* Регистры */\
        /* Внутренние модули */\
        {PHASE_CONTROL_DEFCFG(PHASE3_CONTROL_ANGLE_WIN_DEFAULT,\
                              PHASE3_CONTROL_MIN_ANGLE_TO_CONTROL_DEFAULT,\
                              PHASE3_CONTROL_MAX_ANGLE_TO_CONTROL_DEFAULT),\
         PHASE_CONTROL_DEFCFG(PHASE3_CONTROL_ANGLE_WIN_DEFAULT,\
                              PHASE3_CONTROL_MIN_ANGLE_TO_CONTROL_DEFAULT,\
                              PHASE3_CONTROL_MAX_ANGLE_TO_CONTROL_DEFAULT),\
         PHASE_CONTROL_DEFCFG(PHASE3_CONTROL_ANGLE_WIN_DEFAULT,\
                              PHASE3_CONTROL_MIN_ANGLE_TO_CONTROL_DEFAULT,\
                              PHASE3_CONTROL_MAX_ANGLE_TO_CONTROL_DEFAULT),\
         PHASE_CONTROL_DEFCFG(PHASE3_CONTROL_ANGLE_WIN_DEFAULT,\
                              PHASE3_CONTROL_MIN_ANGLE_TO_CONTROL_DEFAULT,\
                              PHASE3_CONTROL_MAX_ANGLE_TO_CONTROL_DEFAULT),\
         PHASE_CONTROL_DEFCFG(PHASE3_CONTROL_ANGLE_WIN_DEFAULT,\
                              PHASE3_CONTROL_MIN_ANGLE_TO_CONTROL_DEFAULT,\
                              PHASE3_CONTROL_MAX_ANGLE_TO_CONTROL_DEFAULT),\
         PHASE_CONTROL_DEFCFG(PHASE3_CONTROL_ANGLE_WIN_DEFAULT,\
                              PHASE3_CONTROL_MIN_ANGLE_TO_CONTROL_DEFAULT,\
                              PHASE3_CONTROL_MAX_ANGLE_TO_CONTROL_DEFAULT)}, /* phc */\
        /* Методы */\
        METHOD_INIT_PTR(M_phase3_control), METHOD_DEINIT_PTR(M_phase3_control),\
        METHOD_CALC_PTR(M_phase3_control), METHOD_IDLE_PTR(M_phase3_control),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_min_control_angle_pu */\
        0, /* m_max_control_angle_pu */\
    }

#endif /* PHASE3_CONTROL_H */
