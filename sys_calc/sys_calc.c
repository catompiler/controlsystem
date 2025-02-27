#include "sys_calc.h"
#include "modules/modules.h"
#include "utils/utils.h"
#include "iqmath/iqmath.h"



METHOD_INIT_IMPL(M_sys_calc, sys_calc)
{
}

METHOD_DEINIT_IMPL(M_sys_calc, sys_calc)
{
}

SYS_CALC_METHOD_CALC_FOR_PHC_IMPL(M_sys_calc, sys_calc)
{
    // Мультиплексор измерений напряжения.
    // Напряжение фазы A.
    mux_Umains.in_A[0] = adc.out_Ua;
    mux_Umains.in_A[1] = adc_model.out_Ua;
    // Напряжение фазы B.
    mux_Umains.in_B[0] = adc.out_Ub;
    mux_Umains.in_B[1] = adc_model.out_Ub;
    // Напряжение фазы C.
    mux_Umains.in_C[0] = adc.out_Uc;
    mux_Umains.in_C[1] = adc_model.out_Uc;
    CALC(mux_Umains);

    // Фаза и амплитуда.
    // Фаза A.
    phase_ampl_Ua.in_value = mux_Umains.out_A;
    CALC(phase_ampl_Ua);
    // Фаза B.
    phase_ampl_Ub.in_value = mux_Umains.out_B;
    CALC(phase_ampl_Ub);
    // Фаза C.
    phase_ampl_Uc.in_value = mux_Umains.out_C;
    CALC(phase_ampl_Uc);
}

SYS_CALC_METHOD_CALC_FOR_MODEL_IMPL(M_sys_calc, sys_calc)
{
    // Ячейка.
    // Мультиплексор измерений напряжения.
    // Напряжение фазы A.
    mux_Ucell.in_A[0] = adc.out_s_Ua;
    mux_Ucell.in_A[1] = adc_model.out_s_Ua;
    // Напряжение фазы B.
    mux_Ucell.in_B[0] = adc.out_s_Ub;
    mux_Ucell.in_B[1] = adc_model.out_s_Ub;
    // Напряжение фазы C.
    mux_Ucell.in_C[0] = adc.out_s_Uc;
    mux_Ucell.in_C[1] = adc_model.out_s_Uc;
    CALC(mux_Ucell);

    // Вычисление напряжения одной из фаз.
    calc_Ucell.in_A = mux_Ucell.out_A;
    calc_Ucell.in_B = mux_Ucell.out_B;
    calc_Ucell.in_C = mux_Ucell.out_C;
    CALC(calc_Ucell);
}

static void sys_calc_calc_mains(M_sys_calc* sys_calc)
{
    // Остальные мультиплексоры измерений.
    // Мультиплексоры измерений тока.
    // Ток фазы A.
    mux_Imains.in_A[0] = adc.out_Ia;
    mux_Imains.in_A[1] = lrm.out_Ia;
    // Ток фазы B.
    mux_Imains.in_B[0] = adc.out_Ib;
    mux_Imains.in_B[1] = lrm.out_Ib;
    // Ток фазы C.
    mux_Imains.in_C[0] = adc.out_Ic;
    mux_Imains.in_C[1] = lrm.out_Ic;
    CALC(mux_Imains);

    // Вычисление выходного тока по входным токам фаз.
    rect_curr.in_Ia = mux_Imains.out_A;
    rect_curr.in_Ib = mux_Imains.out_B;
    rect_curr.in_Ic = mux_Imains.out_C;
    CALC(rect_curr);
}

static void sys_calc_calc_armature(M_sys_calc* sys_calc)
{
    // Мультиплексор измерений выходного напряжения.
    mux_Uarm.in_value[0] = adc.out_Uarm;
    mux_Uarm.in_value[1] = lrm.out_Ufld;
    CALC(mux_Uarm);
    // Мультиплексор измерений выходного тока.
    mux_Iarm.in_value[0] = rect_curr.out_I;
    mux_Iarm.in_value[1] = lrm.out_Ifld;
    mux_Iarm.in_value[2] = adc.out_Iarm;
    CALC(mux_Iarm);
    // Мультиплексор измерений тока пускового сопротивления.
    mux_Irstart.in_value[0] = adc.out_Irstart;
    mux_Irstart.in_value[1] = lrm.out_Irstart;
    CALC(mux_Irstart);
}

static void sys_calc_calc_cell(M_sys_calc* sys_calc)
{
    // Из ячейки приходят линейные напряжения.
    // Преобразуем из в фазные.
    phase_Ucell.in_A = calc_Ucell.out_A;
    phase_Ucell.in_B = calc_Ucell.out_B;
    phase_Ucell.in_C = calc_Ucell.out_C;
    CALC(phase_Ucell);


    // Модель отдаёт линейные токи,
    // а в ячейке измеряются фазные.
    // Преобразование линейных токов в фазные.
    phase_lrm_I_stator.in_A = lrm.out_stator_Ia;
    phase_lrm_I_stator.in_B = lrm.out_stator_Ib;
    phase_lrm_I_stator.in_C = lrm.out_stator_Ic;
    CALC(phase_lrm_I_stator);

    // Ячейка.
    // Мультиплексоры измерений тока.
    // Ток фазы A.
    mux_Icell.in_A[0] = adc.out_s_Ia;
    mux_Icell.in_A[1] = phase_lrm_I_stator.out_A;
    // Ток фазы B.
    mux_Icell.in_B[0] = adc.out_s_Ib;
    mux_Icell.in_B[1] = phase_lrm_I_stator.out_B;
    // Ток фазы C.
    mux_Icell.in_C[0] = adc.out_s_Ic;
    mux_Icell.in_C[1] = phase_lrm_I_stator.out_C;
    CALC(mux_Icell);

    // Вычисление тока одной из фаз.
    calc_Icell.in_A = mux_Icell.out_A;
    calc_Icell.in_B = mux_Icell.out_B;
    calc_Icell.in_C = mux_Icell.out_C;
    CALC(calc_Icell);
}

static void sys_calc_calc_mains_freq(M_sys_calc* sys_calc)
{
    // Детект нуля и вычисление частоты.
    // echo "[ Ua ] {border:none} -> [ filter1 ] {label:filter} -> [ zcd freq ] - freq -> [ filter2 ]{label:filter} -> [ Freq ] {border: none}" | graph-easy
    /*
     *         +--------+     +----------+  freq   +--------+
     * Ua  --> | filter | --> | zcd freq | ------> | filter | -->  Freq
     *         +--------+     +----------+         +--------+
     *
     */
    // Основной ввод.
    // Фаза A.
    // Фильтр напряжения.
    filter_zcd_Ua.in_value = mux_Umains.out_A;
    CALC(filter_zcd_Ua);
    // Детект нуля.
    zcd_Ua.in_value = filter_zcd_Ua.out_value;
    CALC(zcd_Ua);
    // Фильтр частоты.
    filter_freq_Ua.in_value = zcd_Ua.out_freq;
    CALC(filter_freq_Ua);
    // Фаза B.
    // Фильтр напряжения.
    filter_zcd_Ub.in_value = mux_Umains.out_B;
    CALC(filter_zcd_Ub);
    // Детект нуля.
    zcd_Ub.in_value = filter_zcd_Ub.out_value;
    CALC(zcd_Ub);
    // Фильтр частоты.
    filter_freq_Ub.in_value = zcd_Ub.out_freq;
    CALC(filter_freq_Ub);
    // Фаза C.
    // Фильтр напряжения.
    filter_zcd_Uc.in_value = mux_Umains.out_C;
    CALC(filter_zcd_Uc);
    // Детект нуля.
    zcd_Uc.in_value = filter_zcd_Uc.out_value;
    CALC(zcd_Uc);
    // Фильтр частоты.
    filter_freq_Uc.in_value = zcd_Uc.out_freq;
    CALC(filter_freq_Uc);
}

static void sys_calc_calc_slip(M_sys_calc* sys_calc)
{
    // Скольжение.
    // Мультиплексор используемого значения.
    mux_slip.in_value[0] = mux_Irstart.out_value;
    mux_slip.in_value[1] = mux_Uarm.out_value;
    CALC(mux_slip);
    // Ток пускового сопротивления.
    // Фильтр значения.
    filter_zcd_slip.in_value = mux_slip.out_value;
    CALC(filter_zcd_slip);
    // Детект нуля.
    zcd_slip.in_value = filter_zcd_slip.out_value;
    CALC(zcd_slip);
    // Фильтр частоты.
    filter_freq_slip.in_value = zcd_slip.out_freq;
    CALC(filter_freq_slip);
    // Вычисление скольжения.
    slip.in_value = filter_freq_slip.out_value;
    CALC(slip);
}

static void sys_calc_calc_rms_mains(M_sys_calc* sys_calc)
{
    // RMS.
    // Основной ввод.
    // Напряжения.
    // Фаза A.
    rms_Ua.in_value = mux_Umains.out_A;
    CALC(rms_Ua);
    // Фаза B.
    rms_Ub.in_value = mux_Umains.out_B;
    CALC(rms_Ub);
    // Фаза C.
    rms_Uc.in_value = mux_Umains.out_C;
    CALC(rms_Uc);
    // Токи.
    // Фаза A.
    rms_Ia.in_value = mux_Imains.out_A;
    CALC(rms_Ia);
    // Фаза B.
    rms_Ib.in_value = mux_Imains.out_B;
    CALC(rms_Ib);
    // Фаза C.
    rms_Ic.in_value = mux_Imains.out_C;
    CALC(rms_Ic);
}

static void sys_calc_calc_rms_cell(M_sys_calc* sys_calc)
{
    // RMS.
    // Ячейка.
    // Линейные напряжения.
    // Фаза A.
    rms_cell_Ua.in_value = calc_Ucell.out_A;
    CALC(rms_cell_Ua);
    // Фаза B.
    rms_cell_Ub.in_value = calc_Ucell.out_B;
    CALC(rms_cell_Ub);
    // Фаза C.
    rms_cell_Uc.in_value = calc_Ucell.out_C;
    CALC(rms_cell_Uc);
    // Фазные напряжения.
    // Фаза A.
    rms_cell_Ua_phase.in_value = phase_Ucell.out_A;
    CALC(rms_cell_Ua_phase);
    // Фаза B.
    rms_cell_Ub_phase.in_value = phase_Ucell.out_B;
    CALC(rms_cell_Ub_phase);
    // Фаза C.
    rms_cell_Uc_phase.in_value = phase_Ucell.out_C;
    CALC(rms_cell_Uc_phase);
    // Токи.
    // Фаза A.
    rms_cell_Ia.in_value = calc_Icell.out_A;
    CALC(rms_cell_Ia);
    // Фаза B.
    rms_cell_Ib.in_value = calc_Icell.out_B;
    CALC(rms_cell_Ib);
    // Фаза C.
    rms_cell_Ic.in_value = calc_Icell.out_C;
    CALC(rms_cell_Ic);

    // Среднее значение действующих значений токов ячейки.
    mean_rms_Icell.in_value[0] = rms_cell_Ia.out_value;
    mean_rms_Icell.in_value[1] = rms_cell_Ib.out_value;
    mean_rms_Icell.in_value[2] = rms_cell_Ic.out_value;
    CALC(mean_rms_Icell);
}

static void sys_calc_calc_mean_armature(M_sys_calc* sys_calc)
{
    // Среднее.
    // Выходной ток.
    mean_Iarm.in_value = mux_Iarm.out_value;
    CALC(mean_Iarm);
    // Фильтр выходного тока.
    filter_mean_Iarm.in_value = mean_Iarm.out_value;
    CALC(filter_mean_Iarm);
    // Выходное напряжение.
    mean_Uarm.in_value = mux_Uarm.out_value;
    CALC(mean_Uarm);
    // Фильтр выходного напряжения.
    filter_mean_Uarm.in_value = mean_Uarm.out_value;
    CALC(filter_mean_Uarm);
    // Ток пускового сопротивления.
    mean_Irstart.in_value = mux_Irstart.out_value;
    CALC(mean_Irstart);
    // Фильтр тока пускового сопротивления.
    filter_mean_Irstart.in_value = mean_Irstart.out_value;
    CALC(filter_mean_Irstart);
}

static void sys_calc_calc_power(M_sys_calc* sys_calc)
{
    // Мощности статора.
    // Фаза A.
    power_A.in_U = phase_Ucell.out_A;
    power_A.in_I = calc_Icell.out_A;
    power_A.in_rms_U = rms_cell_Ua_phase.out_value;
    power_A.in_rms_I = rms_cell_Ia.out_value;
    CALC(power_A);
    // Фаза B.
    power_B.in_U = phase_Ucell.out_B;
    power_B.in_I = calc_Icell.out_B;
    power_B.in_rms_U = rms_cell_Ub_phase.out_value;
    power_B.in_rms_I = rms_cell_Ib.out_value;
    CALC(power_B);
    // Фаза A.
    power_C.in_U = phase_Ucell.out_C;
    power_C.in_I = calc_Icell.out_C;
    power_C.in_rms_U = rms_cell_Uc_phase.out_value;
    power_C.in_rms_I = rms_cell_Ic.out_value;
    CALC(power_C);

    // Суммы мощностей.
    // S.
    sum_S.in_value[0] = power_A.out_S;
    sum_S.in_value[1] = power_B.out_S;
    sum_S.in_value[2] = power_C.out_S;
    CALC(sum_S);
    // P.
    sum_P.in_value[0] = power_A.out_P;
    sum_P.in_value[1] = power_B.out_P;
    sum_P.in_value[2] = power_C.out_P;
    CALC(sum_P);
    // Q.
    sum_Q.in_value[0] = power_A.out_Q;
    sum_Q.in_value[1] = power_B.out_Q;
    sum_Q.in_value[2] = power_C.out_Q;
    CALC(sum_Q);

    // Коэффициент мощности.
    power_factor.in_S = sum_S.out_value;
    power_factor.in_P = sum_P.out_value;
    power_factor.in_Q = sum_Q.out_value;
    CALC(power_factor);
}

static void sys_calc_calc_valid_ranges(M_sys_calc* sys_calc)
{
    // Допустимые диапазоны.
    // Допустимый диапазон напряжений сети.
    vr_rms_Umains.in_value[0] = rms_Ua.out_value;
    vr_rms_Umains.in_value[1] = rms_Ub.out_value;
    vr_rms_Umains.in_value[2] = rms_Uc.out_value;
    CALC(vr_rms_Umains);
    // Допустимый диапазон частоты сети.
    vr_filter_freq_Umains.in_value[0] = filter_freq_Ua.out_value;
    vr_filter_freq_Umains.in_value[1] = filter_freq_Ub.out_value;
    vr_filter_freq_Umains.in_value[2] = filter_freq_Uc.out_value;
    CALC(vr_filter_freq_Umains);
    // Допустимый диапазон напряжений ячейки.
    vr_rms_Ucell.in_value[0] = rms_cell_Ua.out_value;
    vr_rms_Ucell.in_value[1] = rms_cell_Ub.out_value;
    vr_rms_Ucell.in_value[2] = rms_cell_Uc.out_value;
    CALC(vr_rms_Ucell);
}

static void sys_calc_calc_start_time(M_sys_calc* sys_calc)
{
    (void) sys_calc;

    CALC(cnt_start);
}

static void sys_calc_calc_run_trig(M_sys_calc* sys_calc)
{
    (void) sys_calc;

    CALC(run_trig);
}

static void sys_calc_calc_field_on_conds(M_sys_calc* sys_calc)
{
    // Ток статора для условий пуска.
    iq24_t I_stator = mean_rms_Icell.out_value;

    // Основное условие пуска.
    // Порог скольжения.
    thr_prim_Slip.in_value = slip.out_value;
    CALC(thr_prim_Slip);
    // Порог тока.
    thr_prim_I_s.in_value = I_stator;
    CALC(thr_prim_I_s);
    // Порог времени.
    thr_prim_T.in_value = cnt_start.out_value;
    CALC(thr_prim_T);
    // И с маской.
    am_prim_field_on.in_value[0] = thr_prim_Slip.out_value;
    am_prim_field_on.in_value[1] = thr_prim_I_s.out_value;
    am_prim_field_on.in_value[2] = thr_prim_T.out_value;
    CALC(am_prim_field_on);

    // Дополнительное условие пуска.
    // Порог скольжения.
    thr_sec_Slip.in_value = slip.out_value;
    CALC(thr_sec_Slip);
    // Порог тока.
    thr_sec_I_s.in_value = I_stator;
    CALC(thr_sec_I_s);
    // Порог времени.
    thr_sec_T.in_value = cnt_start.out_value;
    CALC(thr_sec_T);
    // И с маской.
    am_sec_field_on.in_value[0] = thr_sec_Slip.out_value;
    am_sec_field_on.in_value[1] = thr_sec_I_s.out_value;
    am_sec_field_on.in_value[2] = thr_sec_T.out_value;
    CALC(am_sec_field_on);

    // Объединение условий.
    or_field_on.in_value[0] = am_prim_field_on.out_value;
    or_field_on.in_value[1] = am_sec_field_on.out_value;
    CALC(or_field_on);

    // Таймер подачи возбуждения по условиям.
    tmr_field_on.in_value = or_field_on.out_value;
    CALC(tmr_field_on);

    // Подача возбуждения при самопроизвольном втягивании двигателя в синхронизм.
    // Триггер.
    thr_field_on_I_r_sync.in_value = mean_Irstart.out_value;
    CALC(thr_field_on_I_r_sync);
    // Таймер.
    tmr_field_on_I_r_sync.in_value = thr_field_on_I_r_sync.out_value;
    CALC(tmr_field_on_I_r_sync);
}

static void sys_calc_calc_start_exc(M_sys_calc* sys_calc)
{
    (void) sys_calc;

    // Цепочка завершения запуска и переход к подаче возбуждения.

    // Компаратор отрицательного значения величины для определения скольжения.
    thr_value_for_slip_lt_zero.in_value = filter_zcd_slip.out_value;
    CALC(thr_value_for_slip_lt_zero);

    // Величина для определения меньше нуля ИЛИ ротор сам втянулся в синхронизм.
    or_value_slip_lt_zero_I_r_sync.in_value[0] = thr_value_for_slip_lt_zero.out_value;
    or_value_slip_lt_zero_I_r_sync.in_value[1] = tmr_field_on_I_r_sync.out_value;
    CALC(or_value_slip_lt_zero_I_r_sync);

    // Нужно подавать возбуждение И можно открывать тиристоры.
    and_ready_to_exc.in_value[0] = tmr_field_on.out_value;
    and_ready_to_exc.in_value[1] = or_value_slip_lt_zero_I_r_sync.out_value;
    CALC(and_ready_to_exc);

    // Таймер отключения пускового сопротивления.
    tmr_field_on_rstart_off.in_value = and_ready_to_exc.out_value;
    CALC(tmr_field_on_rstart_off);

    // Цепочка управления пусковым сопротивлением.

    // НЕ готовность подачи возбуждения.
    not_ready_to_exc.in_value = and_ready_to_exc.out_value;
    CALC(not_ready_to_exc);

    // Компаратор состояния системы управления.
    cmp_ctrl_state_is_start.in_A = fsm_state(&sys_ctrl.fsm_state);
    cmp_ctrl_state_is_start.in_B = SYS_CONTROL_STATE_START;
    CALC(cmp_ctrl_state_is_start);

    // Включение пускового сопротивления == Не готов к подаче возбуждения И запуск.
    and_rstart_on.in_value[0] = not_ready_to_exc.out_value;
    and_rstart_on.in_value[1] = cmp_ctrl_state_is_start.out_value;
    CALC(and_rstart_on);
}

static void sys_calc_calc_start_forcing(M_sys_calc* sys_calc)
{
    (void) sys_calc;

    // Компаратор реактивной мощности.
    thr_start_Q_le_zero.in_value = sum_Q.out_value;
    CALC(thr_start_Q_le_zero);

    // Таймер стабилизации.
    tmr_start_stab_forcing.in_value = thr_start_Q_le_zero.out_value;
    CALC(tmr_start_stab_forcing);

    // Таймер минимального времени форсировки.
    CALC(tmr_start_min_forcing);

    // Таймер максимального времени форсировки.
    CALC(tmr_start_max_forcing);

    and_start_min_forcing_end.in_value[0] = tmr_start_min_forcing.out_expired;
    and_start_min_forcing_end.in_value[1] = tmr_start_stab_forcing.out_value;
    CALC(and_start_min_forcing_end);

    or_start_forcing_end.in_value[0] = tmr_start_max_forcing.out_expired;
    or_start_forcing_end.in_value[1] = and_start_min_forcing_end.out_value;
    CALC(or_start_forcing_end);
}

static void sys_calc_calc_current_regulator(M_sys_calc* sys_calc)
{
    (void) sys_calc;

    // Цифровой потенциометр ручного задания тока.
    // TODO: mot_pot_manual_curr_ref inc / dec.
    CALC(mot_pot_manual_curr_ref);

    //! Мультиплексор регуляторов.
    mux_field_regs.in_value[0] = mot_pot_manual_curr_ref.r_value; // Ручной.
    //mux_field_regs.in_value[1] = 0;
    //mux_field_regs.in_value[2] = 0;
    //mux_field_regs.in_value[3] = 0;
    CALC(mux_field_regs);

    //! Ограничитель тока регуляторов.
    // lim_field_regs_curr_ref.p_max_value => Parameter - field current max value.
    lim_field_regs_curr_ref.in_value = mux_field_regs.out_value;
    CALC(lim_field_regs_curr_ref);

    //! Мультиплексор задания тока при форсировке.
    // TODO: I2T -> sel.
    mux_field_force_ref.p_sel = 0;

    // in_value[0] => Parameter - field force current.
    //mux_field_force_ref.in_value[0] = IQ24(1.4);
    // in_value[1] => Max current value.
    mux_field_force_ref.in_value[1] = lim_field_regs_curr_ref.p_max_value;
    CALC(mux_field_force_ref);

    //! Цифровой потенциометр для опробования.
    // TODO: mot_pot_field_test inc / dec.
    CALC(mot_pot_field_test);

    //! Мультиплексор задания тока.
    mux_curr_ref.in_value[0] = 0;
    mux_curr_ref.in_value[1] = mot_pot_field_test.r_value;
    mux_curr_ref.in_value[2] = mux_field_force_ref.out_value;
    mux_curr_ref.in_value[3] = lim_field_regs_curr_ref.out_value;
    CALC(mux_curr_ref);

    //! ПИД тока.
    pid_i.in_ref = mux_curr_ref.out_value;
    pid_i.in_fbk = mean_Iarm.out_value;
    CALC(pid_i);

    // СИФУ.
    ph3c.in_control_value = pid_i.out_value;
}

static void sys_calc_calc_field_supp(M_sys_calc* sys_calc)
{
    (void) sys_calc;

    thr_field_supp_I_r.in_value = mean_Iarm.out_value;
    CALC(thr_field_supp_I_r);

    CALC(tmr_field_supp);
}

/*

static void sys_calc_calc_(M_sys_calc* sys_calc)
{
}
*/

METHOD_CALC_IMPL(M_sys_calc, sys_calc)
{
    // Mains.
    sys_calc_calc_mains(sys_calc);

    // Armature.
    sys_calc_calc_armature(sys_calc);

    // Cell.
    sys_calc_calc_cell(sys_calc);

    // Mains zcd & freq.
    sys_calc_calc_mains_freq(sys_calc);

    // Slip.
    sys_calc_calc_slip(sys_calc);

    // RMS mains.
    sys_calc_calc_rms_mains(sys_calc);

    // RMS cell.
    sys_calc_calc_rms_cell(sys_calc);

    // Mean.
    sys_calc_calc_mean_armature(sys_calc);

    // Power and power factor.
    sys_calc_calc_power(sys_calc);

    // Valid ranges.
    sys_calc_calc_valid_ranges(sys_calc);

    // Start time (ms) counter.
    sys_calc_calc_start_time(sys_calc);

    // Start trig by Istator > Ithreshold.
    sys_calc_calc_run_trig(sys_calc);

    // Field on conditions.
    sys_calc_calc_field_on_conds(sys_calc);

    // Field start.
    sys_calc_calc_start_exc(sys_calc);

    // Field forcing at start.
    sys_calc_calc_start_forcing(sys_calc);

    // Контур тока.
    sys_calc_calc_current_regulator(sys_calc);

    // Field suppression.
    sys_calc_calc_field_supp(sys_calc);
}
