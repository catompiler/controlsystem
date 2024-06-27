#include "meas.h"
#include "modules/modules.h"
#include "utils/utils.h"
#include "iqmath/iqmath.h"



METHOD_INIT_IMPL(M_meas, meas)
{
}

METHOD_DEINIT_IMPL(M_meas, meas)
{
}

MEAS_METHOD_CALC_FOR_PHC_IMPL(M_meas, meas)
{
    // Мультиплексор измерений напряжения.
    // Напряжение фазы A.
    mains_U.in_A[0] = adc.out_Ua;
    mains_U.in_A[1] = adc_model.out_Ua;
    // Напряжение фазы B.
    mains_U.in_B[0] = adc.out_Ub;
    mains_U.in_B[1] = adc_model.out_Ub;
    // Напряжение фазы C.
    mains_U.in_C[0] = adc.out_Uc;
    mains_U.in_C[1] = adc_model.out_Uc;
    CALC(mains_U);

    // Фаза и амплитуда.
    // Фаза A.
    phase_ampl_Ua.in_value = mains_U.out_A;
    CALC(phase_ampl_Ua);
    // Фаза B.
    phase_ampl_Ub.in_value = mains_U.out_B;
    CALC(phase_ampl_Ub);
    // Фаза C.
    phase_ampl_Uc.in_value = mains_U.out_C;
    CALC(phase_ampl_Uc);
}

MEAS_METHOD_CALC_FOR_MODEL_IMPL(M_meas, meas)
{
    // Ячейка.
    // Мультиплексор измерений напряжения.
    // Напряжение фазы A.
    mux_cell_U.in_A[0] = adc.out_s_Ua;
    mux_cell_U.in_A[1] = adc_model.out_s_Ua;
    // Напряжение фазы B.
    mux_cell_U.in_B[0] = adc.out_s_Ub;
    mux_cell_U.in_B[1] = adc_model.out_s_Ub;
    // Напряжение фазы C.
    mux_cell_U.in_C[0] = adc.out_s_Uc;
    mux_cell_U.in_C[1] = adc_model.out_s_Uc;
    CALC(mux_cell_U);

    // Вычисление напряжения одной из фаз.
    cell_U.in_A = mux_cell_U.out_A;
    cell_U.in_B = mux_cell_U.out_B;
    cell_U.in_C = mux_cell_U.out_C;
    CALC(cell_U);

    // Преобразование фазных напряжений ячейки в линейные.
    cell_U_line.in_A = cell_U.out_A;
    cell_U_line.in_B = cell_U.out_B;
    cell_U_line.in_C = cell_U.out_C;
    CALC(cell_U_line);
}

static void meas_calc_mains(M_meas* meas)
{
    // Остальные мультиплексоры измерений.
    // Мультиплексоры измерений тока.
    // Ток фазы A.
    mains_I.in_A[0] = adc.out_Ia;
    mains_I.in_A[1] = lrm.out_Iab;
    // Ток фазы B.
    mains_I.in_B[0] = adc.out_Ib;
    mains_I.in_B[1] = lrm.out_Ibc;
    // Ток фазы C.
    mains_I.in_C[0] = adc.out_Ic;
    mains_I.in_C[1] = lrm.out_Ica;
    CALC(mains_I);

    // Вычисление выходного тока по входным токам фаз.
    rect_curr.in_Ia = mains_I.out_A;
    rect_curr.in_Ib = mains_I.out_B;
    rect_curr.in_Ic = mains_I.out_C;
    CALC(rect_curr);
}

static void meas_calc_armature(M_meas* meas)
{
    // Мультиплексор измерений выходного напряжения.
    armature_U.in_value[0] = adc.out_Uarm;
    armature_U.in_value[1] = lrm.out_U;
    CALC(armature_U);
    // Мультиплексор измерений выходного тока.
    armature_I.in_value[0] = rect_curr.out_I;
    armature_I.in_value[1] = lrm.out_I;
    armature_I.in_value[2] = adc.out_Iarm;
    CALC(armature_I);
    // Мультиплексор измерений тока пускового сопротивления.
    rstart_I.in_value[0] = adc.out_Ir;
    rstart_I.in_value[1] = lrm.out_Irstart;
    CALC(rstart_I);
}

static void meas_calc_cell(M_meas* meas)
{
    // Ячейка.
    // Мультиплексоры измерений тока.
    // Ток фазы A.
    mux_cell_I.in_A[0] = adc.out_s_Ia;
    mux_cell_I.in_A[1] = lrm.out_stator_Iab;
    // Ток фазы B.
    mux_cell_I.in_B[0] = adc.out_s_Ib;
    mux_cell_I.in_B[1] = lrm.out_stator_Ibc;
    // Ток фазы C.
    mux_cell_I.in_C[0] = adc.out_s_Ic;
    mux_cell_I.in_C[1] = lrm.out_stator_Ica;
    CALC(mux_cell_I);

    // Вычисление тока одной из фаз.
    cell_I.in_A = mux_cell_I.out_A;
    cell_I.in_B = mux_cell_I.out_B;
    cell_I.in_C = mux_cell_I.out_C;
    CALC(cell_I);
}

static void meas_calc_mains_freq(M_meas* meas)
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
    filter_Ua_zcd.in_value = mains_U.out_A;
    CALC(filter_Ua_zcd);
    // Детект нуля.
    zcd_Ua.in_value = filter_Ua_zcd.out_value;
    CALC(zcd_Ua);
    // Фильтр частоты.
    filter_freq_Ua.in_value = zcd_Ua.out_freq;
    CALC(filter_freq_Ua);
    // Фаза B.
    // Фильтр напряжения.
    filter_Ub_zcd.in_value = mains_U.out_B;
    CALC(filter_Ub_zcd);
    // Детект нуля.
    zcd_Ub.in_value = filter_Ub_zcd.out_value;
    CALC(zcd_Ub);
    // Фильтр частоты.
    filter_freq_Ub.in_value = zcd_Ub.out_freq;
    CALC(filter_freq_Ub);
    // Фаза C.
    // Фильтр напряжения.
    filter_Uc_zcd.in_value = mains_U.out_C;
    CALC(filter_Uc_zcd);
    // Детект нуля.
    zcd_Uc.in_value = filter_Uc_zcd.out_value;
    CALC(zcd_Uc);
    // Фильтр частоты.
    filter_freq_Uc.in_value = zcd_Uc.out_freq;
    CALC(filter_freq_Uc);
}

static void meas_calc_slip(M_meas* meas)
{
    // Скольжение.
    // Мультиплексор используемого значения.
    mux_slip.in_value[0] = rstart_I.out_value;
    mux_slip.in_value[1] = armature_U.out_value;
    CALC(mux_slip);
    // Ток пускового сопротивления.
    // Фильтр значения.
    filter_slip_zcd.in_value = mux_slip.out_value;
    CALC(filter_slip_zcd);
    // Детект нуля.
    zcd_slip.in_value = filter_slip_zcd.out_value;
    CALC(zcd_slip);
    // Фильтр частоты.
    filter_freq_slip.in_value = zcd_slip.out_freq;
    CALC(filter_freq_slip);
    // Вычисление скольжения.
    slip.in_value = filter_freq_slip.out_value;
    CALC(slip);
}

static void meas_calc_rms_mains(M_meas* meas)
{
    // RMS.
    // Основной ввод.
    // Напряжения.
    // Фаза A.
    rms_Ua.in_value = mains_U.out_A;
    CALC(rms_Ua);
    // Фаза B.
    rms_Ub.in_value = mains_U.out_B;
    CALC(rms_Ub);
    // Фаза C.
    rms_Uc.in_value = mains_U.out_C;
    CALC(rms_Uc);
    // Токи.
    // Фаза A.
    rms_Ia.in_value = mains_I.out_A;
    CALC(rms_Ia);
    // Фаза B.
    rms_Ib.in_value = mains_I.out_B;
    CALC(rms_Ib);
    // Фаза C.
    rms_Ic.in_value = mains_I.out_C;
    CALC(rms_Ic);
}

static void meas_calc_rms_cell(M_meas* meas)
{
    // RMS.
    // Ячейка.
    // Фазные напряжения.
    // Фаза A.
    rms_cell_Ua.in_value = cell_U.out_A;
    CALC(rms_cell_Ua);
    // Фаза B.
    rms_cell_Ub.in_value = cell_U.out_B;
    CALC(rms_cell_Ub);
    // Фаза C.
    rms_cell_Uc.in_value = cell_U.out_C;
    CALC(rms_cell_Uc);
    // Линейные напряжения.
    // Фаза A.
    rms_cell_Ua_line.in_value = cell_U_line.out_A;
    CALC(rms_cell_Ua_line);
    // Фаза B.
    rms_cell_Ub_line.in_value = cell_U_line.out_B;
    CALC(rms_cell_Ub_line);
    // Фаза C.
    rms_cell_Uc_line.in_value = cell_U_line.out_C;
    CALC(rms_cell_Uc_line);
    // Токи.
    // Фаза A.
    rms_cell_Ia.in_value = cell_I.out_A;
    CALC(rms_cell_Ia);
    // Фаза B.
    rms_cell_Ib.in_value = cell_I.out_B;
    CALC(rms_cell_Ib);
    // Фаза C.
    rms_cell_Ic.in_value = cell_I.out_C;
    CALC(rms_cell_Ic);

    // Среднее значение действующих значений токов ячейки.
    mean_rms_I_cell.in_value[0] = rms_cell_Ia.out_value;
    mean_rms_I_cell.in_value[1] = rms_cell_Ib.out_value;
    mean_rms_I_cell.in_value[2] = rms_cell_Ic.out_value;
    CALC(mean_rms_I_cell);
}

static void meas_calc_mean_armature(M_meas* meas)
{
    // Среднее.
    // Выходной ток.
    mean_Iarm.in_value = armature_I.out_value;
    CALC(mean_Iarm);
    // Фильтр выходного тока.
    filter_mean_Iarm.in_value = mean_Iarm.out_value;
    CALC(filter_mean_Iarm);
    // Выходное напряжение.
    mean_Uarm.in_value = armature_U.out_value;
    CALC(mean_Uarm);
    // Фильтр выходного напряжения.
    filter_mean_Uarm.in_value = mean_Uarm.out_value;
    CALC(filter_mean_Uarm);
    // Ток пускового сопротивления.
    mean_Irstart.in_value = rstart_I.out_value;
    CALC(mean_Irstart);
    // Фильтр тока пускового сопротивления.
    filter_mean_Irstart.in_value = mean_Irstart.out_value;
    CALC(filter_mean_Irstart);
}

static void meas_calc_power(M_meas* meas)
{
    // Мощности статора.
    // Фаза A.
    power_A.in_U = cell_U.out_A;
    power_A.in_I = cell_I.out_A;
    power_A.in_rms_U = rms_cell_Ua.out_value;
    power_A.in_rms_I = rms_cell_Ia.out_value;
    CALC(power_A);
    // Фаза B.
    power_B.in_U = cell_U.out_B;
    power_B.in_I = cell_I.out_B;
    power_B.in_rms_U = rms_cell_Ub.out_value;
    power_B.in_rms_I = rms_cell_Ib.out_value;
    CALC(power_B);
    // Фаза A.
    power_C.in_U = cell_U.out_C;
    power_C.in_I = cell_I.out_C;
    power_C.in_rms_U = rms_cell_Uc.out_value;
    power_C.in_rms_I = rms_cell_Ic.out_value;
    CALC(power_C);
}

static void meas_calc_power_factor(M_meas* meas)
{
    // Коэффициент мощности.
    power_factor.in_S = power_A.out_S + power_B.out_S + power_C.out_S;
    power_factor.in_P = power_A.out_P + power_B.out_P + power_C.out_P;
    power_factor.in_Q = power_A.out_Q + power_B.out_Q + power_C.out_Q;
    CALC(power_factor);
}

static void meas_calc_valid_ranges(M_meas* meas)
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
    vr_rms_Ucell.in_value[0] = rms_cell_Ua_line.out_value;
    vr_rms_Ucell.in_value[1] = rms_cell_Ub_line.out_value;
    vr_rms_Ucell.in_value[2] = rms_cell_Uc_line.out_value;
    CALC(vr_rms_Ucell);
}

static void meas_calc_start_time(M_meas* meas)
{
    (void) meas;

    CALC(cnt_start);
}

static void meas_calc_start_trig_I_s(M_meas* meas)
{
    // Ток статора больше порогового.
    thr_start_trig_I_s.in_value = mean_rms_I_cell.out_value;
    CALC(thr_start_trig_I_s);

    // Объединение условий.
    // TODO: Условие пуска по включению выключателя ячейки.
    om_start_trig.in_value[0] = 0;
    om_start_trig.in_value[1] = thr_start_trig_I_s.out_value;
    CALC(om_start_trig);

    // Таймер включения.
    tmr_start_trig_I_s.in_value = om_start_trig.out_value;
    CALC(tmr_start_trig_I_s);
}

static void meas_calc_field_on_conds(M_meas* meas)
{
    // Ток статора для условий пуска.
    iq24_t I_stator = mean_rms_I_cell.out_value;

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

    tmr_field_on.in_value = or_field_on.out_value;
    CALC(tmr_field_on);

    thr_field_on_I_s_sync.in_value = mean_Irstart.out_value;
    CALC(thr_field_on_I_s_sync);

    tmr_field_on_I_s_sync.in_value = thr_field_on_I_s_sync.out_value;
    CALC(tmr_field_on_I_s_sync);

    CALC(tmr_field_on_rstart_off);
}

/*

static void meas_calc_(M_meas* meas)
{
}
*/

METHOD_CALC_IMPL(M_meas, meas)
{
    // Mains.
    meas_calc_mains(meas);

    // Armature.
    meas_calc_armature(meas);

    // Cell.
    meas_calc_cell(meas);

    // Mains zcd & freq.
    meas_calc_mains_freq(meas);

    // Slip.
    meas_calc_slip(meas);

    // RMS mains.
    meas_calc_rms_mains(meas);

    // RMS cell.
    meas_calc_rms_cell(meas);

    // Mean.
    meas_calc_mean_armature(meas);

    // Power.
    meas_calc_power(meas);

    // Power factor.
    meas_calc_power_factor(meas);

    // Valid ranges.
    meas_calc_valid_ranges(meas);

    // Start time (ms) counter.
    meas_calc_start_time(meas);

    // Start trig by Istator > Ithreshold.
    meas_calc_start_trig_I_s(meas);

    // Field on conditions.
    meas_calc_field_on_conds(meas);
}
