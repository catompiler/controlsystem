#ifndef LARIONOV_MODEL_H
#define LARIONOV_MODEL_H

#include "module/base.h"
#include "iqmath/iqmath.h"
#include "conf/conf.h"
#include <stdint.h>



//! Число фаз для управления.
#define LARIONOV_MODEL_PHASES_COUNT 3

//! Число ключей для управления.
#define LARIONOV_MODEL_KEYS_COUNT (LARIONOV_MODEL_PHASES_COUNT * 2)

//! Индексы управлений и ключей.
//! Управления.
//! Управление AB.
#define LARIONOV_MODEL_AB 0
//! Управление BC.
#define LARIONOV_MODEL_BC 2
//! Управление CA.
#define LARIONOV_MODEL_CA 4
//! Управление BA.
#define LARIONOV_MODEL_BA 3
//! Управление CB.
#define LARIONOV_MODEL_CB 5
//! Управление AC.
#define LARIONOV_MODEL_AC 1
//! Ключи.
//! Ключ верхний фазы A.
#define LARIONOV_MODEL_A_HI 0
//! Ключ верхний фазы B.
#define LARIONOV_MODEL_B_HI 2
//! Ключ верхний фазы C.
#define LARIONOV_MODEL_C_HI 4
//! Ключ нижний фазы A.
#define LARIONOV_MODEL_A_LO 3
//! Ключ нижний фазы B.
#define LARIONOV_MODEL_B_LO 5
//! Ключ нижний фазы C.
#define LARIONOV_MODEL_C_LO 1


//! Продолжительность угла управления по-умолчанию.
#define LARIONOV_MODEL_CONTROL_DURATION_ANGLE_DEFAULT (IQ24_PI_PU / 18)

//! Интервал времени для вычисления модели по-умолчанию.
#define LARIONOV_MODEL_DT_DEFAULT (IQ24(0.02 / CONF_PERIOD_SAMPLES))


//! Перечисление возможных бит управления.
enum _E_Larionov_Model_Control {
    LARIONOV_MODEL_CONTROL_NONE = CONTROL_NONE,
    LARIONOV_MODEL_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Larionov_Model_Status {
    LARIONOV_MODEL_STATUS_NONE = STATUS_NONE,
    LARIONOV_MODEL_STATUS_WARNING = STATUS_WARNING,
};

//! Перечисление возможных бит предупреждений.
enum _E_Larionov_Model_Warnings {
    LARIONOV_MODEL_WARNING_NONE = WARNING_NONE,
    // TODO: Larionov model warning handle.
    LARIONOV_MODEL_WARNING_INVALID_PARAMS = (WARNING_USER << 0),
};

//! Предварительная декларация типа модуля.
typedef struct _S_Larionov_Model M_larionov_model;

//! Структура модуля.
struct _S_Larionov_Model {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    warning_t warnings; //!< Слово предупреждений.
    // Входные данные.
    reg_iq24_t in_Uab; //!< Напряжение фазы AB.
    reg_iq24_t in_Ubc; //!< Напряжение фазы BC.
    reg_iq24_t in_Uca; //!< Напряжение фазы CA.
    reg_iq24_t in_Uref_angle_pu; //!< Угол опорной фазы, в периодических единицах, [0; 2*pi).
    strobe_t in_control[LARIONOV_MODEL_KEYS_COUNT]; //!< Управление.
    reg_iq24_t in_control_delay_angle_pu; //!< Угол до импульса управления, в периодических единицах.
    reg_iq24_t in_control_duration_angle_pu; //!< Продолжительность (угол) управления, в периодических единицах.
    reg_iq24_t in_dt; //!< Интервал времени между вычислениями для вычисления модели, с.
    // Выходные данные.
    reg_iq24_t out_Iab; //!< Ток фазы AB.
    reg_iq24_t out_Ibc; //!< Ток фазы BC.
    reg_iq24_t out_Ica; //!< Ток фазы CA.
    reg_iq24_t out_U; //!< Выходное напряжение.
    reg_iq24_t out_I; //!< Выходной ток.
    // Параметры.
    // Общие.
    reg_iq15_t p_I_hold; //!< Ток удержания, А.
    // Нагрузка.
    reg_u32_t p_load_type; //!< Тип нагрузки.
    // Сопротивление [0].
    reg_iq15_t p_load_r_R; //!< Сопротивление, Ом.
    // RL цепь [1].
    reg_iq15_t p_load_rl_R; //!< Сопротивление, Ом.
    reg_iq15_t p_load_rl_L; //!< Индуктивность, Гн.
    // ДПТ [2].
    reg_iq15_t p_load_dcm_Unom; //!< Номинальное напряжение, В.
    reg_iq15_t p_load_dcm_Inom; //!< Номинальный ток, А.
    reg_iq15_t p_load_dcm_Nnom; //!< Номинальные обороты, об/мин.
    reg_iq15_t p_load_dcm_J; //!< Момент инерции, кг * м2.
    reg_iq15_t p_load_dcm_Mr; //!< Момент сопротивления на валу, Н * м.
    reg_iq15_t p_load_dcm_R; //!< Сопротивление, Ом.
    reg_iq15_t p_load_dcm_L; //!< Индуктивность, Гн.
    // Регистры.
    // Методы.
    METHOD_INIT(M_larionov_model);
    METHOD_DEINIT(M_larionov_model);
    METHOD_CALC(M_larionov_model);
    METHOD_IDLE(M_larionov_model);
    // Коллбэки.
    // Внутренние данные.
    flag_t m_need_control; //!< Флаг необходимости управления.
    flag_t m_control[LARIONOV_MODEL_KEYS_COUNT]; //!< Сохранённое управление.
    iq24_t m_control_ref_angle; //!< Угол, с которого отсчитывается управление.
    iq24_t m_control_delay_angle; //!< Угол до начала управления.
    iq24_t m_control_ref_Uab; //!< Напряжение фазы AB до управления.
    iq24_t m_control_ref_Ubc; //!< Напряжение фазы BC до управления.
    iq24_t m_control_ref_Uca; //!< Напряжение фазы CA до управления.
    iq24_t m_cur_Uref_angle; //!< Используемый опорный угол.
    iq24_t m_cur_dt; //!< Используемый интервал времени.
    iq24_t m_cur_Uab; //!< Используемое напряжение фазы AB.
    iq24_t m_cur_Ubc; //!< Используемое напряжение фазы BC.
    iq24_t m_cur_Uca; //!< Используемое напряжение фазы CA.
    iq24_t m_gates_ref_angle; //!< Угол начала управления.
    flag_t m_gates_state[LARIONOV_MODEL_KEYS_COUNT]; //!< Состояния управляющих.
    flag_t m_scrs_state[LARIONOV_MODEL_KEYS_COUNT]; //!< Состояния тиристоров.
    iq24_t m_scrs_I[LARIONOV_MODEL_KEYS_COUNT]; //!< Токи тиристоров.
    iq24_t m_U_rect; //!< Напряжение на выходе выпрямителя.
    // Данные нагрузки.
    // Общие.
    iq24_t m_U_load; //!< Напряжение нагрузки.
    iq24_t m_I_load; //!< Ток нагрузки.
    iq24_t m_I_hold; //!< Ток удержания.
    // R цепь.
    iq24_t m_load_r_U; //!< Напряжение нагрузки.
    iq24_t m_load_r_I; //!< Ток нагрузки.
    iq24_t m_load_r_R; //!< Сопротивление.
    // RL цепь.
    iq24_t m_load_rl_U; //!< Напряжение нагрузки.
    iq24_t m_load_rl_I; //!< Ток нагрузки.
    iq24_t m_load_rl_R; //!< Сопротивление.
    iq24_t m_load_rl_L; //!< Индуктивность.
    // ДПТ.
    iq24_t m_load_dcm_U; //!< Напряжение нагрузки.
    iq24_t m_load_dcm_I; //!< Ток нагрузки.
    iq24_t m_load_dcm_Unom; //!< Номинальное напряжение.
    iq24_t m_load_dcm_Inom; //!< Номинальный ток.
    iq15_t m_load_dcm_Tj; //!< Механическая инерционная постоянная.
    iq24_t m_load_dcm_Mr; //!< Момент сопротивления на валу.
    iq24_t m_load_dcm_R; //!< Сопротивление.
    iq24_t m_load_dcm_L; //!< Индуктивность.
    iq24_t m_load_dcm_W; //!< Угловая частота двигателя.
    iq24_t m_load_dcm_kF; //!< Коэффициент связи двигателя.
};

EXTERN METHOD_INIT_PROTO(M_larionov_model);
EXTERN METHOD_DEINIT_PROTO(M_larionov_model);
EXTERN METHOD_CALC_PROTO(M_larionov_model);
EXTERN METHOD_IDLE_PROTO(M_larionov_model);

#define LARIONOV_MODEL_DEFAULTS {\
        /* Базовые поля */\
        CONTROL_ENABLE, 0, /* control, status */\
        0, /* warnings*/\
        /* Входные данные */\
        0, /* in_Uab */\
        0, /* in_Ubc */\
        0, /* in_Uca */\
        0, /* in_Uref_angle_pu */\
        {0}, /* in_control */\
        0, /* in_control_delay_angle_pu */\
        0, /* in_control_duration_angle_pu */\
        LARIONOV_MODEL_DT_DEFAULT, /* in_dt */\
        /* Выходные данные */\
        0, /* out_Iab */\
        0, /* out_Ibc */\
        0, /* out_Ica */\
        0, /* out_U */\
        0, /* out_I */\
        /* Параметры */\
        IQ15(0.05), /* p_I_hold */\
        2, /* p_load_type */\
        /* Сопротивление [0] */\
        IQ15(10.0), /* p_load_r_R */\
        /* RL цепь [1] */\
        IQ15(0.1), /* p_load_rl_R */\
        IQ15(0.01), /* p_load_rl_L */\
        /* ДПТ [2] */\
        IQ15(440), /* p_load_dcm_Unom */\
        IQ15(361), /* p_load_dcm_Inom */\
        IQ15(1475), /* p_load_dcm_Nnom */\
        IQ15(4.5), /* p_load_dcm_J */\
        IQ15(5.0), /* p_load_dcm_Mr */\
        IQ15(0.2), /* p_load_dcm_R */\
        IQ15(0.01), /* p_load_dcm_L */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_larionov_model), METHOD_DEINIT_PTR(M_larionov_model),\
        METHOD_CALC_PTR(M_larionov_model), METHOD_IDLE_PTR(M_larionov_model),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_need_control */\
        {0}, /* m_control */\
        0, /* m_control_ref_angle */\
        0, /* m_control_delay_angle */\
        0, /* m_control_ref_Uab */\
        0, /* m_control_ref_Ubc */\
        0, /* m_control_ref_Uca */\
        0, /* m_cur_Uref_angle */\
        0, /* m_cur_dt */\
        0, /* m_cur_Uab */\
        0, /* m_cur_Ubc */\
        0, /* m_cur_Uca */\
        0, /* m_gates_ref_angle */\
        {0}, /* m_gates_state */\
        {0}, /* m_scrs_state */\
        {0}, /* m_scrs_I */\
        0, /* m_U_rect */\
        /* Данные нагрузки */\
        /* Общие */\
        0, /* m_U_load */\
        0, /* m_I_load */\
        0, /* m_I_hold */\
        /* R цепь */\
        0, /* m_load_r_U */\
        0, /* m_load_r_I */\
        0, /* m_load_r_R */\
        /* RL цепь */\
        0, /* m_load_rl_U */\
        0, /* m_load_rl_I */\
        0, /* m_load_rl_R */\
        0, /* m_load_rl_L */\
        /* ДПТ */\
        0, /* m_load_dcm_U */\
        0, /* m_load_dcm_I */\
        0, /* m_load_dcm_Unom */\
        0, /* m_load_dcm_Inom */\
        0, /* m_load_dcm_Tj */\
        0, /* m_load_dcm_Mr */\
        0, /* m_load_dcm_R */\
        0, /* m_load_dcm_L */\
        0, /* m_load_dcm_W */\
        0, /* m_load_dcm_kF */\
    }

#endif /* LARIONOV_MODEL_H */
