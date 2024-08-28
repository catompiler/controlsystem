#ifndef SMOTOR_LARIONOV_H
#define SMOTOR_LARIONOV_H

#include "module/base.h"
#include <stdint.h>
#include "iqmath/iqmath.h"
#include "conf/conf.h"
#include "filter1/filter1.h"
#include "clarke/clarke.h"
#include "clarke/clarke_inv.h"
#include "park/park.h"
#include "park/park_inv.h"



//! Число фаз для управления.
#define SMOTOR_LARIONOV_PHASES_COUNT 3

//! Число ключей для управления.
#define SMOTOR_LARIONOV_KEYS_COUNT (SMOTOR_LARIONOV_PHASES_COUNT * 2)

//! Число ключей для цепи пускового сопротивления.
#define SMOTOR_LARIONOV_R_START_KEYS_COUNT (2)

//! Индексы управлений и ключей.
//! Управления.
//! Управление AB.
#define SMOTOR_LARIONOV_AB 0
//! Управление BC.
#define SMOTOR_LARIONOV_BC 2
//! Управление CA.
#define SMOTOR_LARIONOV_CA 4
//! Управление BA.
#define SMOTOR_LARIONOV_BA 3
//! Управление CB.
#define SMOTOR_LARIONOV_CB 5
//! Управление AC.
#define SMOTOR_LARIONOV_AC 1
//! Ключи.
//! Ключ верхний фазы A.
#define SMOTOR_LARIONOV_A_HI 0
//! Ключ верхний фазы B.
#define SMOTOR_LARIONOV_B_HI 2
//! Ключ верхний фазы C.
#define SMOTOR_LARIONOV_C_HI 4
//! Ключ нижний фазы A.
#define SMOTOR_LARIONOV_A_LO 3
//! Ключ нижний фазы B.
#define SMOTOR_LARIONOV_B_LO 5
//! Ключ нижний фазы C.
#define SMOTOR_LARIONOV_C_LO 1


//! Продолжительность угла управления по-умолчанию.
#define SMOTOR_LARIONOV_CONTROL_DURATION_ANGLE_DEFAULT (IQ24_PI_PU / 18)

//! Интервал времени для вычисления модели по-умолчанию.
#define SMOTOR_LARIONOV_DT_DEFAULT (IQ24(0.02 / CONF_PERIOD_SAMPLES))

//! Постоянная времени фильтра ЭДС по-умолчанию.
#define SMOTOR_LARIONOV_FILTER_EDS_T_DEFAULT (IQ24(0.25 / (50 * CONF_PERIOD_SAMPLES)))



//! Перечисление возможных бит управления.
enum _E_Smotor_Larionov_Control {
    SMOTOR_LARIONOV_CONTROL_NONE = CONTROL_NONE,
    SMOTOR_LARIONOV_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Smotor_Larionov_Status {
    SMOTOR_LARIONOV_STATUS_NONE = STATUS_NONE,
    SMOTOR_LARIONOV_STATUS_WARNING = STATUS_WARNING,
};

//! Перечисление возможных бит предупреждений.
enum _E_Smotor_Larionov_Warnings {
    SMOTOR_LARIONOV_WARNING_NONE = WARNING_NONE,
    // TODO: Larionov model warning handle.
    SMOTOR_LARIONOV_WARNING_INVALID_PARAMS = (WARNING_USER << 0),
};


//! Предварительная декларация типа модуля.
typedef struct _S_Smotor_Larionov M_smotor_larionov;


//! Структура модуля.
struct _S_Smotor_Larionov {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    warning_t warnings; //!< Слово предупреждений.
    // Входные данные.
    // Выпрямитель.
    reg_iq24_t in_Ua; // Напряжение фазы AB.
    reg_iq24_t in_Ub; // Напряжение фазы BC.
    reg_iq24_t in_Uc; // Напряжение фазы CA.
    reg_iq24_t in_Uref_angle; // Угол опорной фазы, в относительных единицах, [0; 2*pi).
    strobe_t in_control[SMOTOR_LARIONOV_KEYS_COUNT]; // Управление.
    reg_iq24_t in_control_delay_angle; // Угол до импульса управления, в относительных единицах.
    reg_iq24_t in_control_duration_angle; // Продолжительность (угол) управления, в относительных единицах.
    reg_iq24_t in_dt; // Интервал времени между вычислениями для вычисления модели.
    // СД.
    reg_iq24_t in_stator_Ua; // Напряжение статора СД фазы AB.
    reg_iq24_t in_stator_Ub; // Напряжение статора СД фазы BC.
    reg_iq24_t in_stator_Uc; // Напряжение статора СД фазы CA.
    flag_t in_stator_on; // Флаг коммутации обмотки статора.
    // Цепь пускового сопротивления.
    flag_t in_start_r_on; // Наличие сигнала управляющего на тиристорах.
    // Параметры нагрузки двигателя.
    reg_iq24_t in_k_Mc; // Масштабирование заданного момента сопротивления вращения на валу.
    // Выходные данные.
    // Выпрямитель.
    reg_iq24_t out_Ia; // Ток фазы AB.
    reg_iq24_t out_Ib; // Ток фазы BC.
    reg_iq24_t out_Ic; // Ток фазы CA.
    reg_iq24_t out_Ufld; // Выходное напряжение.
    reg_iq24_t out_Ifld; // Выходной ток.
    // СД.
    reg_iq24_t out_M; // Момент двигателя.
    reg_iq24_t out_w; // Угловая скорость двигателя.
    reg_iq24_t out_stator_Ia; // Ток фазы AB.
    reg_iq24_t out_stator_Ib; // Ток фазы BC.
    reg_iq24_t out_stator_Ic; // Ток фазы CA.
    // Цепь пускового сопротивления.
    reg_iq24_t out_Irstart; // Ток пускового сопротивления.
    // Параметры.
    // Выпрямитель.
    reg_iq15_t p_I_hold; // Ток удержания, А.
    // СД.
    reg_iq15_t p_Rs; // Сопротивление статора, Ом.
    reg_iq15_t p_Rr; // Сопротивление ротора, Ом.
    reg_iq15_t p_Rf; // Сопротивление возбуждения, Ом.
    reg_iq15_t p_Lsd; // Индуктивность статора по продольной оси, Гн.
    reg_iq15_t p_Lsq; // Индуктивность статора по поперечной оси, Гн.
    reg_iq15_t p_Lrd; // Индуктивность ротора по продольной оси, Гн.
    reg_iq15_t p_Lrq; // Индуктивность ротора по поперечной оси, Гн.
    reg_iq15_t p_Lfd; // Индуктивность возбуждения, Гн.
    reg_iq15_t p_Lmsrd; // Взаимная индуктивность статора и ротора по продольной оси, Гн.
    reg_iq15_t p_Lmsrq; // Взаимная индуктивность статора и ротора по поперечной оси, Гн.
    reg_iq15_t p_Lmsfd; // Взаимная индуктивность статора и возбуждения, Гн.
    reg_iq15_t p_Lmrfd; // Взаимная индуктивность ротора и возбуждения, Гн.
    reg_u32_t p_p; // Число пар полюсов.
    reg_iq15_t p_Mc; // Момент сопротивления вращению (нагрузки), Н*м.
    reg_iq15_t p_Kf; // Коэффициент трения, доля от Момента сопротивления.
    reg_iq15_t p_J; // Момент инерции, кг*м^2.
    // Цепь пускового сопротивления.
    reg_iq15_t p_Rstart; // Сопротивление пусковой цепочки, Ом.
    reg_iq15_t p_start_r_u_thr; // Пороговое напряжение открытия тиристоров, В.
    // Регистры.
    // Методы.
    METHOD_INIT(M_smotor_larionov);
    METHOD_DEINIT(M_smotor_larionov);
    METHOD_CALC(M_smotor_larionov);
    METHOD_IDLE(M_smotor_larionov);
    // Коллбэки.
    // Внутренние данные.
    // Выпрямитель.
    flag_t m_need_control; // Флаг необходимости управления.
    flag_t m_control[SMOTOR_LARIONOV_KEYS_COUNT]; // Сохранённое управление.
    iq24_t m_control_ref_angle; // Угол, с которого отсчитывается управление.
    iq24_t m_control_delay_angle; // Угол до начала управления.
    iq24_t m_control_ref_Uab; // Напряжение фазы AB до управления.
    iq24_t m_control_ref_Ubc; // Напряжение фазы BC до управления.
    iq24_t m_control_ref_Uca; // Напряжение фазы CA до управления.
    iq24_t m_cur_Uab; // Используемое напряжение фазы AB.
    iq24_t m_cur_Ubc; // Используемое напряжение фазы BC.
    iq24_t m_cur_Uca; // Используемое напряжение фазы CA.
    iq24_t m_cur_Uref_angle; // Используемый опорный угол.
    iq24_t m_cur_dt; // Используемый интервал времени.
    iq24_t m_gates_ref_angle; // Угол начала управления.
    flag_t m_gates_state[SMOTOR_LARIONOV_KEYS_COUNT]; // Состояния управляющих.
    flag_t m_scrs_gated; // Флаг отпирания тиристоров выпрямителя.
    flag_t m_scrs_state[SMOTOR_LARIONOV_KEYS_COUNT]; // Состояния тиристоров.
    flag_t m_scrs_opened; // Флаг открытых тиристоров выпрямителя.
    iq24_t m_scrs_I[SMOTOR_LARIONOV_KEYS_COUNT]; // Токи тиристоров.
    iq24_t m_I_hold; // Ток удержания, А.
    iq24_t m_U_rect; // Напряжение на выходе выпрямителя.
    // Данные нагрузки.
    iq24_t m_U_load; // Напряжение нагрузки.
    iq24_t m_I_load; // Ток нагрузки.
    // Система относительных единиц.
    iq24_t m_rfpu_k_U_r; //!< Коэффициент преобразования напряжения в с.е. ротора.
    iq24_t m_rfpu_k_I_r; //!< Коэффициент преобразования тока в с.е. ротора.
    iq15_t m_rfpu_k_L_rs; //!< Коэффициент преобразования индуктивности в с.е. ротора/статора.
    iq24_t m_rfpu_k_R_rs; //!< Коэффициент преобразования сопротивления в с.е. ротора/статора.
    iq24_t m_rfpu_k_Psi_s2rf; //!< Коэффициент преобразования потокосцепления из с.е. статора в с.е. ротора.
    iq24_t m_rfpu_k_Psi_rf2s; //!< Коэффициент преобразования потокосцепления из с.е. ротора в с.е. статора.
    iq24_t m_rfpu_k_I_s2rf; //!< Коэффициент преобразования тока из с.е. статора в с.е. ротора.
    iq24_t m_rfpu_k_I_rf2s; //!< Коэффициент преобразования тока из с.е. ротора в с.е. статора.
    iq24_t m_rfpu_k_U_rf2mt; //!< Коэффициент преобразования напряжения из с.е. ротора в с.е. двигателя.
    iq24_t m_rfpu_k_I_rf2mt; //!< Коэффициент преобразования тока из с.е. ротора в с.е. двигателя.
    iq24_t m_rfpu_k_U_ms2rf; //!< Коэффициент преобразования напряжения из с.е. основного ввода в с.е. ротора.
    iq24_t m_rfpu_k_I_rf2ms; //!< Коэффициент преобразования тока из с.е. ротора в с.е. основного ввода.
    // СД.
    iq24_t m_control_ref_stator_Uab; // Напряжение фазы AB статора до управления.
    iq24_t m_control_ref_stator_Ubc; // Напряжение фазы BC статора до управления.
    iq24_t m_control_ref_stator_Uca; // Напряжение фазы CA статора до управления.
    iq24_t m_cur_stator_Uab; // Используемое напряжение статора фазы AB.
    iq24_t m_cur_stator_Ubc; // Используемое напряжение статора фазы BC.
    iq24_t m_cur_stator_Uca; // Используемое напряжение статора фазы CA.
    // Используемые параметры модели.
    iq24_t m_Rs; // Сопротивление статоора.
    iq24_t m_Rr; // Сопротивление ротора.
    iq24_t m_Rf; // Сопротивление возбуждения.
    iq24_t m_Lsd; // Индуктивность статора по продольной оси.
    iq24_t m_Lsq; // Индуктивность статора по поперечной оси.
    iq24_t m_Lrd; // Индуктивность ротора по продольной оси.
    iq24_t m_Lrq; // Индуктивность ротора по поперечной оси.
    iq24_t m_Lfd; // Индуктивность возбуждения.
    iq24_t m_Lmsrd; // Взаимная индуктивность статора и ротора по продольной оси.
    iq24_t m_Lmsrq; // Взаимная индуктивность статора и ротора по поперечной оси.
    iq24_t m_Lmsfd; // Взаимная индуктивность статора и возбуждения.
    iq24_t m_Lmrfd; // Взаимная индуктивность ротора и возбуждения.
    int32_t m_p; // Число пар полюсов.
    iq24_t m_p_inv; // Инвертированное число пар полюсов.
    iq24_t m_Mc; // Момент сопротивления вращению (нагрузки).
    iq24_t m_Kf; // Коэффициент трения.
    iq24_t m_Tj_inv; // Инерционная постоянная времени. //Момент инерции.
    // Цепь пускового сопротивления.
    iq24_t m_Rstart; // Сопротивление пусковой цепочки.
    iq24_t m_start_r_u_thr; // Пороговое напряжение открытия тиристоров.
    // Данные для вычисления.
    // Коэффициенты уравнений потокосцеплений.
    iq24_t m_k_Psi_sd_ird;
    iq24_t m_k_Psi_sd_ifd;
    iq24_t m_k_Psi_sq_irq;
    iq24_t m_k_Psi_fd_isd;
    iq24_t m_k_Psi_fd_ird;
    // Статор выключен, возбуждение выключено.
    // Инвентированный знаменатель уравнений токов.
    iq24_t m_id_denom_inv_sf_off;
    iq24_t m_iq_denom_inv_sf_off;
    // Статор выключен, возбуждение включено.
    // Инвентированный знаменатель уравнений токов.
    iq24_t m_id_denom_inv_s_off;
    iq24_t m_iq_denom_inv_s_off;
    // Коэффициенты уравнения тока ротора.
    iq24_t m_k_ird_Psi_rd_s_off;
    iq24_t m_k_ird_Psi_fd_s_off;
    // Коэффициенты уравнения тока возбуждения.
    iq24_t m_k_ifd_Psi_rd_s_off;
    iq24_t m_k_ifd_Psi_fd_s_off;
    // Статор включен, возбуждение выключено.
    // Инвентированный знаменатель уравнений токов.
    iq24_t m_id_denom_inv_f_off;
    iq24_t m_iq_denom_inv_f_off;
    // Коэффициенты уравнения тока статора.
    iq24_t m_k_isd_Psi_sd_f_off;
    iq24_t m_k_isd_Psi_rd_f_off;
    iq24_t m_k_isq_Psi_sq_f_off;
    iq24_t m_k_isq_Psi_rq_f_off;
    // Коэффициенты уравнения тока ротора.
    iq24_t m_k_ird_Psi_sd_f_off;
    iq24_t m_k_ird_Psi_rd_f_off;
    iq24_t m_k_irq_Psi_sq_f_off;
    iq24_t m_k_irq_Psi_rq_f_off;
    // Статор включен, возбуждение включено.
    // Инвентированный знаменатель уравнений токов.
    iq24_t m_id_denom_inv;
    iq24_t m_iq_denom_inv;
    // Коэффициенты уравнения тока статора.
    iq24_t m_k_isd_Psi_sd;
    iq24_t m_k_isd_Psi_rd;
    iq24_t m_k_isd_Psi_fd;
    iq24_t m_k_isq_Psi_sq;
    iq24_t m_k_isq_Psi_rq;
    // Коэффициенты уравнения тока ротора.
    iq24_t m_k_ird_Psi_sd;
    iq24_t m_k_ird_Psi_rd;
    iq24_t m_k_ird_Psi_fd;
    iq24_t m_k_irq_Psi_sq;
    iq24_t m_k_irq_Psi_rq;
    // Коэффициенты уравнения тока возбуждения.
    iq24_t m_k_ifd_Psi_sd;
    iq24_t m_k_ifd_Psi_rd;
    iq24_t m_k_ifd_Psi_fd;
    // Промежуточные данные.
    // Напряжения.
    iq24_t m_Usa; // Входное напряжение по оси alpha.
    iq24_t m_Usb; // Входное напряжение по оси beta.
    iq24_t m_Usd; // Входное напряжение по оси d.
    iq24_t m_Usq; // Входное напряжение по оси q.
    //iq24_t m_out_Usd; // Выходное напряжение статора по оси d.
    //iq24_t m_out_Usq; // Выходное напряжение статора по оси q.
    iq24_t m_Ufd; // Выходное напряжение возбуждения по оси d.
    iq24_t m_Efd; // ЭДС возбуждения по оси d.
    // Потоки.
    iq24_t m_Psi_sd; // Потокосцепление статора по продольной оси.
    iq24_t m_Psi_sq; // Потокосцепление статора по поперечной оси.
    iq24_t m_Psi_rd; // Потокосцепление ротора по продольной оси.
    iq24_t m_Psi_rq; // Потокосцепление ротора по поперечной оси.
    iq24_t m_Psi_fd; // Потокосцепление возбуждения.
    iq24_t m_Psi_sd_z1; // Предыдущее потокосцепление статора по продольной оси.
    iq24_t m_Psi_sq_z1; // Предыдущее потокосцепление статора по поперечной оси.
    iq24_t m_Psi_rd_z1; // Предыдущее потокосцепление ротора по продольной оси.
    iq24_t m_Psi_rq_z1; // Предыдущее потокосцепление ротора по поперечной оси.
    iq24_t m_Psi_fd_z1; // Предыдущее потокосцепление возбуждения.
    // Токи.
    iq24_t m_Isa; // Входной ток по оси alpha.
    iq24_t m_Isb; // Входной ток по оси beta.
    iq24_t m_Isd; // Ток статора по продольной оси.
    iq24_t m_Isq; // Ток статора по поперечной оси.
    iq24_t m_Ird; // Ток ротора по продольной оси.
    iq24_t m_Irq; // Ток ротора по поперечной оси.
    iq24_t m_Ifd; // Ток возбуждения.
    iq24_t m_Irstart; // Ток пускового сопротивления.
    iq24_t m_Irect; // Ток выпрямителя.
    // Прочие данные модели.
    iq24_t m_M; // Момент двигателя.
    iq24_t m_w; // Угловая скорость вращения ротора.
    iq24_t m_teta; // Угол поворота ротора.
//    iq24_t m_stator_on_z1; // Флаг включения статора на прошлой итерации.
//    iq24_t m_field_on_z1; // Флаг включения возбуждения на прошлой итерации.
    flag_t m_start_r_scrs_gates[SMOTOR_LARIONOV_R_START_KEYS_COUNT]; // Управляющие тиристоров пускового сопротивления.
    flag_t m_start_r_scrs_state[SMOTOR_LARIONOV_R_START_KEYS_COUNT]; // Состояние тиристоров пускового сопротивления.
    // Внутренние модули.
    M_filter1 m_ef_filter; // Фильтр производной потокосцепления ротора (наведённой ЭДС).
    M_clarke m_clarke; // Модуль фазных преобразований.
    M_clarke_inv m_clarke_inv; // Модуль обратных фазных преобразований.
    M_park m_park; // Модуль координатных преобразований.
    M_park_inv m_park_inv; // Модуль обратных координатных преобразований.
};


EXTERN METHOD_INIT_PROTO(M_smotor_larionov);
EXTERN METHOD_DEINIT_PROTO(M_smotor_larionov);
EXTERN METHOD_CALC_PROTO(M_smotor_larionov);
EXTERN METHOD_IDLE_PROTO(M_smotor_larionov);


#define SMOTOR_LARIONOV_DEFAULTS {\
        /* Базовые поля */\
        CONTROL_ENABLE, 0, /* control, status */\
        0, /* warnings*/\
        /* Входные данные. */\
        /* Выпрямитель. */\
        0, /* in_Uab */\
        0, /* in_Ubc */\
        0, /* in_Uca */\
        0, /* in_Uref_angle */\
        {0}, /* in_control */\
        0, /* in_control_delay_angle */\
        (IQ24_PI4_PU/18), /* in_control_duration_angle */\
        SMOTOR_LARIONOV_DT_DEFAULT, /* in_dt */\
        /* СД. */\
        0, /* in_stator_Uab */\
        0, /* in_stator_Ubc */\
        0, /* in_stator_Uca */\
        0, /* in_stator_on */\
        /* Цепь пускового сопротивления. */\
        0, /* in_start_r_on */\
        /* Параметры нагрузки двигателя. */\
        IQ24(1.0), /* in_k_Mc */\
        /* Выходные данные. */\
        /* Выпрямитель. */\
        0, /* out_Iab */\
        0, /* out_Ibc */\
        0, /* out_Ica */\
        0, /* out_U */\
        0, /* out_I */\
        /* СД. */\
        0, /* out_M */\
        0, /* out_w */\
        0, /* out_stator_Iab */\
        0, /* out_stator_Ibc */\
        0, /* out_stator_Ica */\
        /* Цепь пускового сопротивления. */\
        0, /* out_Irstart */\
        /* Параметры. */\
        /* Выпрямитель. */\
        IQ15(0.05), /* p_I_hold */\
        /* СД. */\
        IQ15(0.860779), /* 1.160779 */ /* p_Rs */\
        IQ15(0.222817), /* 0.682817 */ /* p_Rr */\
        IQ15(0.222817), /* 0.682817 */ /* p_Rf */\
        IQ15(374.705247e-3), /* p_Lsd */\
        IQ15(314.705247e-3), /* p_Lsq */\
        IQ15(374.705247e-3), /* p_Lrd */\
        IQ15(314.705247e-3), /* p_Lrq */\
        IQ15(374.705247e-3), /* p_Lfd */\
        IQ15(368.539889e-3), /* p_Lmsrd */\
        IQ15(308.539889e-3), /* p_Lmsrq */\
        IQ15(368.539889e-3), /* p_Lmsfd */\
        IQ15(368.539889e-3), /* p_Lmrfd */\
        4, /* p_p */\
        IQ15(11000), /* p_Mc */\
        IQ15(0.05), /* p_Kf */\
        IQ15(750), /* p_J */\
        /* Цепь пускового сопротивления. */\
        IQ15(2.5), /* p_Rstart */\
        IQ15(250), /* p_start_r_u_thr */\
        /* Регистры */\
        /* Методы. */\
        METHOD_INIT_PTR(M_smotor_larionov), METHOD_DEINIT_PTR(M_smotor_larionov),\
        METHOD_CALC_PTR(M_smotor_larionov), METHOD_IDLE_PTR(M_smotor_larionov),\
        /* Коллбэки */\
        /* Внутренние данные. */\
        /* Выпрямитель. */\
        0, /* m_need_control */\
        {0}, /* m_control */\
        0, /* m_control_ref_angle */\
        0, /* m_control_delay_angle */\
        0, /* m_control_ref_Uab */\
        0, /* m_control_ref_Ubc */\
        0, /* m_control_ref_Uca */\
        0, /* m_cur_Uab */\
        0, /* m_cur_Ubc */\
        0, /* m_cur_Uca */\
        0, /* m_cur_Uref_angle */\
        0, /* m_cur_dt */\
        0, /* m_gates_ref_angle */\
        {0}, /* m_gates_state */\
        0, /* m_scrs_gated */\
        {0}, /* m_scrs_state */\
        0, /* m_scrs_opened */\
        {0}, /* m_scrs_I */\
        0, /* m_I_hold */\
        0, /* m_U_rect */\
        /* Данные нагрузки. */\
        0, /* m_U_load */\
        0, /* m_I_load */\
        /* Система относительных единиц */\
        0, /* m_rfpu_k_U_r */\
        0, /* m_rfpu_k_I_r */\
        0, /* m_rfpu_k_L_rs */\
        0, /* m_rfpu_k_R_rs */\
        0, /* m_rfpu_k_Psi_s2rf */\
        0, /* m_rfpu_k_Psi_rf2s */\
        0, /* m_rfpu_k_I_s2rf */\
        0, /* m_rfpu_k_I_rf2s */\
        0, /* m_rfpu_k_U_rf2mt */\
        0, /* m_rfpu_k_I_rf2mt */\
        0, /* m_rfpu_k_U_ms2rf */\
        0, /* m_rfpu_k_I_rf2ms */\
        /* СД. */\
        0, /* m_control_ref_stator_Uab */\
        0, /* m_control_ref_stator_Ubc */\
        0, /* m_control_ref_stator_Uca */\
        0, /* m_cur_stator_Uab */\
        0, /* m_cur_stator_Ubc */\
        0, /* m_cur_stator_Uca */\
        /* Используемые параметры модели. */\
        0, /* m_Rs */\
        0, /* m_Rr */\
        0, /* m_Rf */\
        0, /* m_Lsd */\
        0, /* m_Lsq */\
        0, /* m_Lrd */\
        0, /* m_Lrq */\
        0, /* m_Lfd */\
        0, /* m_Lmsrd */\
        0, /* m_Lmsrq */\
        0, /* m_Lmsfd */\
        0, /* m_Lmrfd */\
        0, /* m_p */\
        0, /* m_p_inv */\
        0, /* m_Mc */\
        0, /* m_Kf */\
        0, /* m_J */\
        /* Цепь пускового сопротивления. */\
        0, /* m_Rstart */\
        0, /* m_start_r_u_thr */\
        /* Данные для вычисления. */\
        /* Коэффициенты уравнений потокосцеплений. */\
        0, /* m_k_Psi_sd_ird */\
        0, /* m_k_Psi_sd_ifd */\
        0, /* m_k_Psi_sq_irq */\
        0, /* m_k_Psi_fd_isd */\
        0, /* m_k_Psi_fd_ird */\
        /* Статор выключен, возбуждение выключено. */\
        /* Инвентированный знаменатель уравнений токов. */\
        0, /* m_id_denom_inv_sf_off */\
        0, /* m_iq_denom_inv_sf_off */\
        /* Статор выключен, возбуждение включено. */\
        /* Инвентированный знаменатель уравнений токов. */\
        0, /* m_id_denom_inv_s_off */\
        0, /* m_iq_denom_inv_s_off */\
        /* Коэффициенты уравнения тока ротора. */\
        0, /* m_k_ird_Psi_rd_s_off */\
        0, /* m_k_ird_Psi_fd_s_off */\
        /* Коэффициенты уравнения тока возбуждения. */\
        0, /* m_k_ifd_Psi_rd_s_off */\
        0, /* m_k_ifd_Psi_fd_s_off */\
        /* Статор включен, возбуждение выключено. */\
        /* Инвентированный знаменатель уравнений токов. */\
        0, /* m_id_denom_inv_f_off */\
        0, /* m_iq_denom_inv_f_off */\
        /* Коэффициенты уравнения тока статора. */\
        0, /* m_k_isd_Psi_sd_f_off */\
        0, /* m_k_isd_Psi_rd_f_off */\
        0, /* m_k_isq_Psi_sq_f_off */\
        0, /* m_k_isq_Psi_rq_f_off */\
        /* Коэффициенты уравнения тока ротора. */\
        0, /* m_k_ird_Psi_sd_f_off */\
        0, /* m_k_ird_Psi_rd_f_off */\
        0, /* m_k_irq_Psi_sq_f_off */\
        0, /* m_k_irq_Psi_rq_f_off */\
        /* Статор включен, возбуждение включено. */\
        /* Инвентированный знаменатель уравнений токов. */\
        0, /* m_id_denom_inv */\
        0, /* m_iq_denom_inv */\
        /* Коэффициенты уравнения тока статора. */\
        0, /* m_k_isd_Psi_sd */\
        0, /* m_k_isd_Psi_rd */\
        0, /* m_k_isd_Psi_fd */\
        0, /* m_k_isq_Psi_sq */\
        0, /* m_k_isq_Psi_rq */\
        /* Коэффициенты уравнения тока ротора. */\
        0, /* m_k_ird_Psi_sd */\
        0, /* m_k_ird_Psi_rd */\
        0, /* m_k_ird_Psi_fd */\
        0, /* m_k_irq_Psi_sq */\
        0, /* m_k_irq_Psi_rq */\
        /* Коэффициенты уравнения тока возбуждения. */\
        0, /* m_k_ifd_Psi_sd */\
        0, /* m_k_ifd_Psi_rd */\
        0, /* m_k_ifd_Psi_fd */\
        /* Промежуточные данные. */\
        /* Напряжения. */\
        0, /* m_Usa */\
        0, /* m_Usb */\
        0, /* m_Usd */\
        0, /* m_Usq */\
        /* 0, m_out_Usd */\
        /* 0, m_out_Usq */\
        0, /* m_Ufd */\
        0, /* m_Efd */\
        /* Потоки. */\
        0, /* m_Psi_sd */\
        0, /* m_Psi_sq */\
        0, /* m_Psi_rd */\
        0, /* m_Psi_rq */\
        0, /* m_Psi_fd */\
        0, /* m_Psi_sd_z1 */\
        0, /* m_Psi_sq_z1 */\
        0, /* m_Psi_rd_z1 */\
        0, /* m_Psi_rq_z1 */\
        0, /* m_Psi_fd_z1 */\
        /* Токи. */\
        0, /* m_Isa */\
        0, /* m_Isb */\
        0, /* m_Isd */\
        0, /* m_Isq */\
        0, /* m_Ird */\
        0, /* m_Irq */\
        0, /* m_Ifd */\
        0, /* m_Irstart */\
        0, /* m_Irect */\
        /* Прочие данные модели. */\
        0, /* m_M */\
        0, /* m_w */\
        0, /* m_teta */\
        /* 0, m_stator_on_z1 */\
        /* 0, m_field_on_z1 */\
        {0}, /* m_start_r_scrs_gates */\
        {0}, /* m_start_r_scrs_state */\
        /* Внутренние модули. */\
        FILTER1_DEFCFG(SMOTOR_LARIONOV_FILTER_EDS_T_DEFAULT), /* m_ef_filter */\
        CLARKE_DEFAULTS, /* m_clarke */\
        CLARKE_INV_DEFAULTS, /* m_clarke_inv */\
        PARK_DEFAULTS, /* m_park */\
        PARK_INV_DEFAULTS, /* m_park_inv */\
    }

#endif /* SMOTOR_LARIONOV_H */
