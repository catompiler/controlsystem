#include "larionov_model.h"
#include "modules/modules.h"
#include "iqmath/iqmath.h"
#include "motor/motor.h"
#include "conf/conf.h"

//
// Модели.
//

//
// Модель активной нагрузки.
//

#define LARIONOV_MODEL_LOAD_R_R_DEFAULT IQ15(1)

// Вычисление.
static void larionov_model_load_R_calc(M_larionov_model *lrm)
{
    iq24_t U = lrm->m_U_rect;

    iq24_t I = iq24_div(U, lrm->m_load_r_R);

    if (I < lrm->m_I_hold) {
        U = 0;
        I = 0;
    }

    lrm->m_load_r_U = U;
    lrm->m_load_r_I = I;
}

// Сброс.
static void larionov_model_load_R_reset(M_larionov_model *lrm)
{
    lrm->m_load_r_U = 0;
    lrm->m_load_r_I = 0;
}

// Обновление констант.
static status_t larionov_model_load_R_update(M_larionov_model *lrm)
{
    status_t res_status = STATUS_READY;

    iq15_t R = lrm->p_load_r_R;

    if(R <= 0){
        res_status = STATUS_ERROR;
        R = LARIONOV_MODEL_LOAD_R_R_DEFAULT;
    }

    lrm->m_load_r_R = iq15_mul(R, motor.r_R_base_inv);

    return res_status;
}

//
// Модель активно-индуктивной нагрузки.
//

#define LARIONOV_MODEL_LOAD_LR_L_DEFAULT IQ15(0.001)

// Вычисление.
static void larionov_model_load_RL_calc(M_larionov_model *lrm)
{
    if(lrm->m_load_rl_L == 0){
        return;
    }

    iq24_t tmp;

    iq24_t U = lrm->m_U_rect;

    // dt* = dt / t_base = dt * w_base.
    iq24_t dt = iq15_mul(lrm->m_cur_dt, motor.r_w_base);

    // dI = (U - I * R) * dt / L.
    iq24_t dI;
    // I * R.
    tmp = iq24_mul(lrm->m_load_rl_I, lrm->m_load_rl_R);
    // U - (I * R).
    tmp = iq24_sub(U, tmp);
    // (U - (I * R)) * dt.
    tmp = iq24_mul(tmp, dt);
    // (U - (I * R)) * dt / L.
    dI = iq24_div(tmp, lrm->m_load_rl_L);

    iq24_t I = lrm->m_load_rl_I + dI;

    if (I < lrm->m_I_hold) {
        U = 0;
        I = 0;
    }

    lrm->m_load_rl_U = U;
    lrm->m_load_rl_I = I;
}

// Сброс.
static void larionov_model_load_RL_reset(M_larionov_model *lrm)
{
    lrm->m_load_rl_U = 0;
    lrm->m_load_rl_I = 0;
}

// Обновление констант.
static status_t larionov_model_load_RL_update(M_larionov_model *lrm)
{
    status_t res_status = STATUS_READY;

    iq15_t R = lrm->p_load_rl_R;
    iq15_t L = lrm->p_load_rl_L;

    if(L == 0){
        res_status = STATUS_ERROR;
        L = LARIONOV_MODEL_LOAD_LR_L_DEFAULT;
    }

    lrm->m_load_rl_R = iq15_mul(R, motor.r_R_base_inv);
    lrm->m_load_rl_L = iq15_mul24(L, motor.r_L_base_inv);

    return res_status;
}

//
// Модель нагрузки ДПТ.
//

#define LARIONOV_MODEL_LOAD_DCM_U_NOM_DEFAULT IQ15(440)
#define LARIONOV_MODEL_LOAD_DCM_I_NOM_DEFAULT IQ15(361)
#define LARIONOV_MODEL_LOAD_DCM_N_NOM_DEFAULT IQ15(1475)
#define LARIONOV_MODEL_LOAD_DCM_R_DEFAULT IQ15(0.1)
#define LARIONOV_MODEL_LOAD_DCM_L_DEFAULT IQ15(0.01)
#define LARIONOV_MODEL_LOAD_DCM_Mr_DEFAULT IQ15(1)
#define LARIONOV_MODEL_LOAD_DCM_J_DEFAULT IQ15(1)
#define LARIONOV_MODEL_LOAD_DCM_Tj_DEFAULT IQ15(1)
#define LARIONOV_MODEL_LOAD_DCM_Wnom_pu_DEFAULT IQ24(1475.0/3000)

// Вычисление.
static void larionov_model_load_DCM_calc(M_larionov_model *lrm)
{
    if(lrm->m_load_dcm_L == 0 || lrm->m_load_dcm_Tj == 0){
        return;
    }

    iq24_t tmp;

    iq24_t U = lrm->m_U_rect;

    // dt* = dt / t_base = dt * w_base.
    iq24_t dt = iq15_mul(lrm->m_cur_dt, motor.r_w_base);

    // E = kF * w.
    iq24_t E = iq24_mul(lrm->m_load_dcm_kF, lrm->m_load_dcm_W);

    // dI = (U - I * R) * dt / L.
    iq24_t dI;
    // I * R.
    tmp = iq24_mul(lrm->m_load_dcm_I, lrm->m_load_dcm_R);
    // U - E - (I * R) = U - (E + I * R).
    // E + (I * R).
    tmp = iq24_add(E, tmp);
    // U - (E + I * R).
    tmp = iq24_sub(U, tmp);
    // (U - (I * R)) * dt.
    tmp = iq24_mul(tmp, dt);
    // (U - (I * R)) * dt / L.
    dI = iq24_div(tmp, lrm->m_load_dcm_L);

    iq24_t I = lrm->m_load_dcm_I + dI;

    if (I < lrm->m_I_hold) {
        U = E;
        I = 0;
    }

    iq24_t M = iq24_mul(lrm->m_load_dcm_kF, lrm->m_load_dcm_I);

    // dW = (M - Mc) * dt / J.
    iq24_t dW;
    // M - Mc.
    tmp = iq24_sub(M, lrm->m_load_dcm_Mr);
    // (M - Mc) * dt.
    tmp = iq24_mul(tmp, dt);
    // dW = (M - Mc) * dt / Tj.
    // IQ(24) = IQ(24 + 15 - 15).
    dW = iq15_div(tmp, lrm->m_load_dcm_Tj);

    iq24_t W = lrm->m_load_dcm_W + dW;
    if (W < 0) {
        W = 0;
    }

    lrm->m_load_dcm_U = U;
    lrm->m_load_dcm_I = I;
    lrm->m_load_dcm_W = W;
}

// Сброс.
static void larionov_model_load_DCM_reset(M_larionov_model *lrm)
{
    lrm->m_load_dcm_U = 0;
    lrm->m_load_dcm_I = 0;
    lrm->m_load_dcm_W = 0;
}

// Обновление констант.
static status_t larionov_model_load_DCM_update(M_larionov_model *lrm)
{
    status_t res_status = STATUS_READY;

    iql_t tmp;

    iq15_t Unom = lrm->p_load_dcm_Unom;
    iq15_t Inom = lrm->p_load_dcm_Inom;
    iq15_t Nnom = lrm->p_load_dcm_Nnom;
    iq15_t R = lrm->p_load_dcm_R;
    iq15_t L = lrm->p_load_dcm_L;
    iq15_t Mr = lrm->p_load_dcm_Mr;
    iq15_t J = lrm->p_load_dcm_J;

    if(Unom <= 0){
        res_status = STATUS_ERROR;
        Unom = LARIONOV_MODEL_LOAD_DCM_U_NOM_DEFAULT;
    }

    if(Inom <= 0){
        res_status = STATUS_ERROR;
        Inom = LARIONOV_MODEL_LOAD_DCM_I_NOM_DEFAULT;
    }

    if(Nnom <= 0){
        res_status = STATUS_ERROR;
        Nnom = LARIONOV_MODEL_LOAD_DCM_N_NOM_DEFAULT;
    }

    if(R < 0){
        res_status = STATUS_ERROR;
        R = LARIONOV_MODEL_LOAD_DCM_R_DEFAULT;
    }

    if(L <= 0){
        res_status = STATUS_ERROR;
        L = LARIONOV_MODEL_LOAD_DCM_L_DEFAULT;
    }

    if(Mr < 0){
        res_status = STATUS_ERROR;
        Mr = LARIONOV_MODEL_LOAD_DCM_Mr_DEFAULT;
    }

    if(J <= 0){
        res_status = STATUS_ERROR;
        J = LARIONOV_MODEL_LOAD_DCM_J_DEFAULT;
    }

    lrm->m_load_dcm_Unom = iq15_mul(Unom, motor.r_U_base_inv); // mul(q15, q24) == q24.
    lrm->m_load_dcm_Inom = iq15_mul(Inom, motor.r_I_base_inv); // mul(q15, q24) == q24.
    lrm->m_load_dcm_R = iq15_mul(R, motor.r_R_base_inv); // mul(q15, q24) == q24.
    lrm->m_load_dcm_L = iq15_mul24(L, motor.r_L_base_inv); // mul15_24(q15, q15) == q24.
    lrm->m_load_dcm_Mr = iq15_mul(Mr, motor.r_M_base_inv); // mul(q15, q24) == q24.

    // Wnom = PI * N / 30.
    iq15_t Wnom;
    // N / 30.
    tmp = iq15_idiv(Nnom, 30);
    // PI * (N / 30).
    Wnom = iq15_mul(tmp, IQ15_PI);

    // http://simenergy.ru/energy-system/primary-equipment/equation-rotor
    // Tj = J * w^2 / S.
    // S = Unom * Inom.
    // J * w.
    tmp = iq15_mul(J, Wnom);
    // (J * w) / Unom.
    tmp = iq15_div(tmp, Unom);
    // (J * w / Unom) * w.
    tmp = iq15_mul(tmp, Wnom);
    // (J * w^2 / Unom) / Inom.
    // IQ(15) = IQ(15 + 15 - 15). // IQ(24) = IQ(15 + 24 - 15).
    tmp = iq15_div(tmp, Inom);
    // Tj* = Tj / t_base = Tj * w_base.
    lrm->m_load_dcm_Tj = iq15_mul(tmp, motor.r_w_base);

    if(lrm->m_load_dcm_Tj <= 0){
        res_status = STATUS_ERROR;
        lrm->m_load_dcm_Tj = LARIONOV_MODEL_LOAD_DCM_Tj_DEFAULT;
    }

    // Wnom = PI * N / 30.
    iq24_t Wnom_pu;
    // N / 30.
    //tmp = iq15_idiv(Nnom, 30);
    // PI * (N / 30).
    //tmp = iq15_mul(tmp, IQ15_PI);
    // /w_base.
    Wnom_pu = iq15_mul(Wnom, motor.r_w_base_inv);
    if(Wnom_pu == 0){
        res_status = STATUS_ERROR;
        Wnom_pu = LARIONOV_MODEL_LOAD_DCM_Wnom_pu_DEFAULT;
    }

    // kF = (U - I * R) / Wnom.
    iq24_t kF;
    // I * R.
    tmp = iq24_mul(lrm->m_load_dcm_Inom, lrm->m_load_dcm_R);
    // U - (I * R).
    tmp = iq24_sub(lrm->m_load_dcm_Unom, tmp);
    // (U - I * R) / Wnom.
    kF = iq24_div(tmp, Wnom_pu);

    lrm->m_load_dcm_kF = kF;

    return res_status;
}

// Проверяет наличие хотя бы одного флага в массиве.
static flag_t larionov_model_has_active_state(flag_t *f)
{
    int i;
    for (i = 0; i < LARIONOV_MODEL_KEYS_COUNT; i++) {
        if (f[i]) {
            return 1;
        }
    }
    return 0;
}

// Проверяет наличие хотя бы одного флага в массиве.
static void larionov_model_reset_state(flag_t *f)
{
    int i;
    for (i = 0; i < LARIONOV_MODEL_KEYS_COUNT; i++) {
        f[i] = 0;
    }
}

static int larionov_model_next_scr_index(int index)
{
    int next_index = index - 1;

    if (next_index < 0) {
        next_index += LARIONOV_MODEL_KEYS_COUNT;
    }

    return next_index;
}

static void larionov_model_set_states(flag_t* out_states, flag_t* in_states)
{
    int i;
    for (i = 0; i < LARIONOV_MODEL_KEYS_COUNT; i++) {
        out_states[i] = in_states[i];
    }
}

// Обновляет управляющие.
static void larionov_model_update_gates(M_larionov_model *lrm)
{
    // Флаг наличия управляющих.
    flag_t has_gates = larionov_model_has_active_state(lrm->m_gates_state);
    // Если есть.
    if (has_gates) {
        // Угол с начала подачи управления.
        iq24_t gates_da = iq24_angle_norm_pu(
                lrm->m_cur_Uref_angle - lrm->m_gates_ref_angle);
        // Если превышает заданную продолжительность.
        if (gates_da > lrm->in_control_duration_angle_pu) {
            // Сбросим управляющие.
            larionov_model_reset_state(lrm->m_gates_state);
        }
    }

}

// Обновляет выходное напряжение.
static void larionov_model_update_voltage_and_state(M_larionov_model *lrm)
{
    // [ AB, AC, BC, BA, CA, CB ]
    iq24_t voltages[LARIONOV_MODEL_KEYS_COUNT] = { lrm->m_cur_Uab,
            -lrm->m_cur_Uca, lrm->m_cur_Ubc, -lrm->m_cur_Uab, lrm->m_cur_Uca,
            -lrm->m_cur_Ubc };

    int i;

    int pair_first = -1;
    int pair_second = -1;
    iq24_t U = 0;

    // Выбор максимального напряжения открытых пар тиристоров и соответствующей пары.
    for (i = 0; i < LARIONOV_MODEL_KEYS_COUNT; i++) {
        int self_index = i;
        int pair_index = larionov_model_next_scr_index(i);

        flag_t self_gated = lrm->m_gates_state[self_index];
        flag_t pair_gated = lrm->m_gates_state[pair_index];

        flag_t self_opened = lrm->m_scrs_state[self_index];
        flag_t pair_opened = lrm->m_scrs_state[pair_index];

        iq24_t voltage = voltages[i];

        if ((self_gated != 0 && pair_gated != 0 && voltage > 0)
                || (self_opened != 0 && pair_opened != 0)) {
            if (voltage > U || pair_first == -1) {
                pair_first = self_index;
                pair_second = pair_index;
                U = voltage;
            }
        }
    }

    // Напряжение сети переводится в напряжение нагрузки.
    lrm->m_U_rect = iq24_mul(U, motor.r_k_U_mains_to_mot);

    // Установка состояния тиристоров.
    for (i = 0; i < LARIONOV_MODEL_KEYS_COUNT; i++) {
        if (i == pair_first || i == pair_second) {
            lrm->m_scrs_state[i] = 1;
        } else {
            lrm->m_scrs_state[i] = 0;
        }
    }
}

// Вычисляет нагрузку, в зависимости от типа.
static void larionov_model_calc_load(M_larionov_model *lrm)
{
    if (lrm->p_load_type == 0) {
        larionov_model_load_R_calc(lrm);

        lrm->m_U_load = lrm->m_load_r_U;
        lrm->m_I_load = lrm->m_load_r_I;
    } else if (lrm->p_load_type == 1) {
        larionov_model_load_RL_calc(lrm);

        lrm->m_U_load = lrm->m_load_rl_U;
        lrm->m_I_load = lrm->m_load_rl_I;
    } else if (lrm->p_load_type == 2) {
        larionov_model_load_DCM_calc(lrm);

        lrm->m_U_load = lrm->m_load_dcm_U;
        lrm->m_I_load = lrm->m_load_dcm_I;
    }
}

// Обновляет токи и состояния тиристоров.
static void larionov_model_update_currents_and_state(M_larionov_model *lrm)
{
    // Модель всегда "отпирает" только два тиристора,
    // Поэтому считать число открытых тиристоров не нужно,
    // Ток через каждый открытый тиристор
    // будет всегда равен току нагрузки.

    // Ток нагрузки переводится в ток сети.
    iq24_t I_load = iq24_mul(lrm->m_I_load, motor.r_k_I_mot_to_mains);

    int i;

    // Обновление тока тиристоров.
    for (i = 0; i < LARIONOV_MODEL_KEYS_COUNT; i++) {
        if (lrm->m_scrs_state[i] != 0) {
            lrm->m_scrs_I[i] = I_load;
        }
    }

    // Обновление состояния тиристоров.
    for (i = 0; i < LARIONOV_MODEL_KEYS_COUNT; i++) {
        if (lrm->m_scrs_I[i] <= 0) { //lrm->m_I_hold
            lrm->m_scrs_state[i] = 0;
        }
    }
}

// Обновляет выходные переменные.
static void larionov_model_update_outputs(M_larionov_model *lrm)
{
    lrm->out_Iab = lrm->m_scrs_I[LARIONOV_MODEL_A_HI] - lrm->m_scrs_I[LARIONOV_MODEL_A_LO];
    lrm->out_Ibc = lrm->m_scrs_I[LARIONOV_MODEL_B_HI] - lrm->m_scrs_I[LARIONOV_MODEL_B_LO];
    lrm->out_Ica = lrm->m_scrs_I[LARIONOV_MODEL_C_HI] - lrm->m_scrs_I[LARIONOV_MODEL_C_LO];

    lrm->out_U = lrm->m_U_load;
    lrm->out_I = lrm->m_I_load;
}

// Выполняет расчёт модели.
static void larionov_model_sim(M_larionov_model *lrm)
{
    // Обновим состояния управляющих.
    larionov_model_update_gates(lrm);

    // Обновим напряжения и состояния.
    larionov_model_update_voltage_and_state(lrm);

    // Вычисление модели.
    larionov_model_calc_load(lrm);

    // Обработаем ток модели.
    larionov_model_update_currents_and_state(lrm);
}

static status_t recalc_values(M_larionov_model* lrm)
{
    status_t res_status = STATUS_READY;
    status_t status = STATUS_NONE;

    // IQ(24) = IQ(15 + 24 - 15).
    lrm->m_I_hold = iq15_mul(lrm->p_I_hold, motor.r_I_base_inv);

    // Обновим рассчитываемые константы.
    status = larionov_model_load_R_update(lrm);
    if(status != STATUS_READY) { res_status = status; }

    status = larionov_model_load_RL_update(lrm);
    if(status != STATUS_READY) { res_status = status; }

    status = larionov_model_load_DCM_update(lrm);
    if(status != STATUS_READY) { res_status = status; }

    return res_status;
}

METHOD_INIT_IMPL(M_larionov_model, lrm)
{
    IDLE((*lrm));
}

METHOD_DEINIT_IMPL(M_larionov_model, lrm)
{
}

METHOD_CALC_IMPL(M_larionov_model, lrm)
{
    // Обработка управления.

    // Если разрешён расчёт.
    if (lrm->control & CONTROL_ENABLE) {
        // Флаг начала подачи управления.
        flag_t control_occurred = 0;
        // Доля времени до подачи управления.
        iq24_t dt_ratio = 0.0;

        // Есть ли управление?
        flag_t has_control = larionov_model_has_active_state(lrm->in_control);
        // Если есть новое управление -
        // Сохраним для обработки.
        if (has_control) {
            lrm->m_need_control = 1;
            larionov_model_set_states(lrm->m_control, lrm->in_control);

            lrm->m_control_delay_angle = lrm->in_control_delay_angle_pu;
            lrm->m_control_ref_Uab = lrm->in_Uab;
            lrm->m_control_ref_Ubc = lrm->in_Ubc;
            lrm->m_control_ref_Uca = lrm->in_Uca;
            lrm->m_control_ref_angle = lrm->in_Uref_angle_pu;
        }

        // Если есть текущее управление.
        if (lrm->m_need_control == 1) {
            // Прошедший угол с момента получения управления.
            iq24_t control_da = iq24_angle_norm_pu(
                    lrm->in_Uref_angle_pu - lrm->m_control_ref_angle);

            // Если с момента получения произошло управление.
            if (control_da > lrm->m_control_delay_angle) {
                // Сбросим флаг необходимости управления.
                lrm->m_need_control = 0;

                // Доля времени до подачи упраления.
                dt_ratio = iq24_div(lrm->m_control_delay_angle, control_da);

                // Установим флаг того что управление произошло.
                control_occurred = 1;

            } else {
                // Иначе сохраним текущий момент как опорный.
                lrm->m_control_delay_angle = lrm->m_control_delay_angle
                        - control_da;
                lrm->m_control_ref_Uab = lrm->in_Uab;
                lrm->m_control_ref_Ubc = lrm->in_Ubc;
                lrm->m_control_ref_Uca = lrm->in_Uca;
                lrm->m_control_ref_angle = lrm->in_Uref_angle_pu;
            }
        }

        // Расчёт.
        // Установим текущий интервал времени.
        lrm->m_cur_dt = lrm->in_dt;

        // Если произошло управление.
        if (control_occurred) {
            // Установим текущий угол.
            lrm->m_cur_Uref_angle = lrm->m_control_ref_angle
                    + lrm->m_control_delay_angle;
            // Установим интервал времени до момент управления.
            lrm->m_cur_dt = iq24_mul(lrm->in_dt, dt_ratio);
            // Проинтерполируем напряжения к моменту подачи управления.
            lrm->m_cur_Uab = iq24_lerp(lrm->m_control_ref_Uab,
                    lrm->in_Uab, dt_ratio);
            lrm->m_cur_Ubc = iq24_lerp(lrm->m_control_ref_Ubc,
                    lrm->in_Ubc, dt_ratio);
            lrm->m_cur_Uca = iq24_lerp(lrm->m_control_ref_Uca,
                    lrm->in_Uca, dt_ratio);

            larionov_model_sim(lrm);

            // Установим начало подачи управления.
            larionov_model_set_states(lrm->m_gates_state, lrm->m_control);
            lrm->m_gates_ref_angle = lrm->m_cur_Uref_angle;

            // Установим интервал времени после момента управления.
            lrm->m_cur_dt = lrm->in_dt - lrm->m_cur_dt;
        }

        // Установим текущий угол.
        lrm->m_cur_Uref_angle = lrm->in_Uref_angle_pu;
        // Устновим текущие значения напряжений.
        lrm->m_cur_Uab = lrm->in_Uab;
        lrm->m_cur_Ubc = lrm->in_Ubc;
        lrm->m_cur_Uca = lrm->in_Uca;

        // Симуляция модели.
        larionov_model_sim(lrm);

        // Обновление выходов.
        larionov_model_update_outputs(lrm);
    }
}

METHOD_IDLE_IMPL(M_larionov_model, lrm)
{
    // Сбросим неиспользуемые модели.
    if (lrm->p_load_type != 0) {
        larionov_model_load_R_reset(lrm);
    }

    if (lrm->p_load_type != 1) {
        larionov_model_load_RL_reset(lrm);
    }

    if (lrm->p_load_type != 2) {
        larionov_model_load_DCM_reset(lrm);
    }

    status_t status = recalc_values(lrm);

    if(status == STATUS_READY){
        lrm->warnings = LARIONOV_MODEL_WARNING_NONE;
        lrm->status = STATUS_NONE;
    }else{
        lrm->warnings = LARIONOV_MODEL_WARNING_INVALID_PARAMS;
        lrm->status = STATUS_WARNING;
    }
}

