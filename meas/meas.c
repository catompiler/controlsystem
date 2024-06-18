#include "meas.h"
#include "modules/modules.h"


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

METHOD_CALC_IMPL(M_meas, meas)
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


    // Детект нуля и вычисление частоты.
    /*
     *       ________      _____      ________
     * U -> | Filter | -> | ZCD | -> | Filter | -> Freq
     *       --------      -----      --------
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
    // Ячейка.
    // Напряжения.
    // Фаза A.
    rms_cell_Ua.in_value = cell_U.out_A;
    CALC(rms_cell_Ua);
    // Фаза B.
    rms_cell_Ub.in_value = cell_U.out_B;
    CALC(rms_cell_Ub);
    // Фаза C.
    rms_cell_Uc.in_value = cell_U.out_C;
    CALC(rms_cell_Uc);
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
}
