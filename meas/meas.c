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
    mains_U.in_Ua[0] = adc.out_Ua;
    mains_U.in_Ua[1] = adc_model.out_Ua;
    // Напряжение фазы B.
    mains_U.in_Ub[0] = adc.out_Ub;
    mains_U.in_Ub[1] = adc_model.out_Ub;
    // Напряжение фазы C.
    mains_U.in_Uc[0] = adc.out_Uc;
    mains_U.in_Uc[1] = adc_model.out_Uc;
    CALC(mains_U);

    // Фаза и амплитуда.
    // Фаза A.
    phase_ampl_Ua.in_value = mains_U.out_Ua;
    CALC(phase_ampl_Ua);
    // Фаза B.
    phase_ampl_Ub.in_value = mains_U.out_Ub;
    CALC(phase_ampl_Ub);
    // Фаза C.
    phase_ampl_Uc.in_value = mains_U.out_Uc;
    CALC(phase_ampl_Uc);
}

METHOD_CALC_IMPL(M_meas, meas)
{
    // Остальные мультиплексоры измерений.
    // Мультиплексоры измерений тока.
    // Ток фазы A.
    mains_I.in_Ia[0] = adc.out_Ia;
    mains_I.in_Ia[1] = lrm.out_Iab;
    // Ток фазы B.
    mains_I.in_Ib[0] = adc.out_Ib;
    mains_I.in_Ib[1] = lrm.out_Ibc;
    // Ток фазы C.
    mains_I.in_Ic[0] = adc.out_Ic;
    mains_I.in_Ic[1] = lrm.out_Ica;
    CALC(mains_I);

    // Вычисление выходного тока по входным токам фаз.
    rect_curr.in_Ia = mains_I.out_Ia;
    rect_curr.in_Ib = mains_I.out_Ib;
    rect_curr.in_Ic = mains_I.out_Ic;
    CALC(rect_curr);

    // Мультиплексор измерений выходного напряжения.
    armature_U.in_Uarm[0] = adc.out_Uarm;
    armature_U.in_Uarm[1] = lrm.out_U;
    CALC(armature_U);
    // Мультиплексор измерений выходного тока.
    armature_I.in_Iarm[0] = rect_curr.out_I;
    armature_I.in_Iarm[1] = lrm.out_I;
    armature_I.in_Iarm[2] = adc.out_Iarm;
    CALC(armature_I);


    // Детект нуля и вычисление частоты.
    /*
     *       ________      _____      ________
     * U -> | Filter | -> | ZCD | -> | Filter | -> Freq
     *       --------      -----      --------
     *
     */
    // Фаза A.
    // Фильтр напряжения.
    filter_Ua_zcd.in_value = mains_U.out_Ua;
    CALC(filter_Ua_zcd);
    // Детект нуля.
    zcd_Ua.in_value = filter_Ua_zcd.out_value;
    CALC(zcd_Ua);
    // Фильтр частоты.
    filter_freq_Ua.in_value = zcd_Ua.out_freq;
    CALC(filter_freq_Ua);
    // Фаза B.
    // Фильтр напряжения.
    filter_Ub_zcd.in_value = mains_U.out_Ub;
    CALC(filter_Ub_zcd);
    // Детект нуля.
    zcd_Ub.in_value = filter_Ub_zcd.out_value;
    CALC(zcd_Ub);
    // Фильтр частоты.
    filter_freq_Ub.in_value = zcd_Ub.out_freq;
    CALC(filter_freq_Ub);
    // Фаза C.
    // Фильтр напряжения.
    filter_Uc_zcd.in_value = mains_U.out_Uc;
    CALC(filter_Uc_zcd);
    // Детект нуля.
    zcd_Uc.in_value = filter_Uc_zcd.out_value;
    CALC(zcd_Uc);
    // Фильтр частоты.
    filter_freq_Uc.in_value = zcd_Uc.out_freq;
    CALC(filter_freq_Uc);


    // RMS.
    // Фаза A.
    rms_Ua.in_value = mains_U.out_Ua;
    CALC(rms_Ua);
    // Фаза B.
    rms_Ub.in_value = mains_U.out_Ub;
    CALC(rms_Ub);
    // Фаза C.
    rms_Uc.in_value = mains_U.out_Uc;
    CALC(rms_Uc);


    // Среднее.
    // Выходной ток.
    mean_Iarm.in_value = armature_I.out_Iarm;
    CALC(mean_Iarm);
    // Фильтр выходного тока.
    filter_mean_Iarm.in_value = mean_Iarm.out_value;
    CALC(filter_mean_Iarm);
    // Выходное напряжение.
    mean_Uarm.in_value = armature_U.out_Uarm;
    CALC(mean_Uarm);
    // Фильтр выходного напряжения.
    filter_mean_Uarm.in_value = mean_Uarm.out_value;
    CALC(filter_mean_Uarm);

    // Допустимые диапазоны.
    // Допустимый диапазон напряжений.
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
