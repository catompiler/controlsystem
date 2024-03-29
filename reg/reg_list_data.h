#ifndef REG_LIST_DATA_H
#define REG_LIST_DATA_H


// THIS FILE IS GENERATED AUTOMATICALLY!
// DO NOT EDIT THIS FILE!

// Modules for registers
#include "modules/modules.h"

// Begin
REGS_BEGIN(REG_ARRAY_NAME)

// Conf
// Nominal values
REG(REG_ID_CONF_U_NOM, conf.p_U_nom, REG_TYPE_IQ15, REG_FLAG_CONF)
REG(REG_ID_CONF_I_NOM, conf.p_I_nom, REG_TYPE_IQ15, REG_FLAG_CONF)


// SysTime
REG(REG_ID_SYS_TIME_COUNTER_MS, sys_time.r_counter_ms, REG_TYPE_U32, REG_FLAG_NONE)
REG(REG_ID_SYS_TIME_COUNTER_S, sys_time.r_counter_s, REG_TYPE_U32, REG_FLAG_NONE)
REG(REG_ID_SYS_TIME_RUN_COUNTER_S, sys_time.r_run_counter_s, REG_TYPE_U32, REG_FLAG_NONE)

// ADC
// Phases voltage
// Raw
REG(REG_ID_ADC_UA_RAW, adc.out_Ua_raw, REG_TYPE_U32, REG_FLAG_NONE)
REG(REG_ID_ADC_UB_RAW, adc.out_Ub_raw, REG_TYPE_U32, REG_FLAG_NONE)
REG(REG_ID_ADC_UC_RAW, adc.out_Uc_raw, REG_TYPE_U32, REG_FLAG_NONE)
// Rel
REG(REG_ID_ADC_UA, adc.out_Ua, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_ADC_UB, adc.out_Ub, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_ADC_UC, adc.out_Uc, REG_TYPE_IQ24, REG_FLAG_NONE)
// Calibration
REG(REG_ID_ADC_UA_GAIN, adc.p_Ua_gain, REG_TYPE_IQ24, REG_FLAG_CONF)
REG(REG_ID_ADC_UA_OFFSET, adc.p_Ua_offset, REG_TYPE_U32, REG_FLAG_CONF)
REG(REG_ID_ADC_UB_GAIN, adc.p_Ub_gain, REG_TYPE_IQ24, REG_FLAG_CONF)
REG(REG_ID_ADC_UB_OFFSET, adc.p_Ub_offset, REG_TYPE_U32, REG_FLAG_CONF)
REG(REG_ID_ADC_UC_GAIN, adc.p_Uc_gain, REG_TYPE_IQ24, REG_FLAG_CONF)
REG(REG_ID_ADC_UC_OFFSET, adc.p_Uc_offset, REG_TYPE_U32, REG_FLAG_CONF)

// Measurement
REG(REG_ID_MEAS_UA, mains_U.out_Ua, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_MEAS_UB, mains_U.out_Ub, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_MEAS_UC, mains_U.out_Uc, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_MEAS_IA, mains_I.out_Ia, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_MEAS_IB, mains_I.out_Ib, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_MEAS_IC, mains_I.out_Ic, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_MEAS_UARM, armature_U.out_Uarm, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_MEAS_IARM, armature_I.out_Iarm, REG_TYPE_IQ24, REG_FLAG_NONE)

// Phase and Amplitude.
REG(REG_ID_PHASE_AMPL_UA_PHASE, phase_ampl_Ua.out_phase, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_PHASE_AMPL_UA_AMPL, phase_ampl_Ua.out_ampl, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_PHASE_AMPL_UB_PHASE, phase_ampl_Ub.out_phase, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_PHASE_AMPL_UB_AMPL, phase_ampl_Ub.out_ampl, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_PHASE_AMPL_UC_PHASE, phase_ampl_Uc.out_phase, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_PHASE_AMPL_UC_AMPL, phase_ampl_Uc.out_ampl, REG_TYPE_IQ24, REG_FLAG_NONE)

REG(REG_ID_LINE_FREQ_UA, zcd_Ua.out_freq, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_LINE_FREQ_UA_FILTER_T, filter_freq_Ua.p_T, REG_TYPE_IQ24, REG_FLAG_CONF)
REG(REG_ID_LINE_FREQ_UA_FILT, filter_freq_Ua.out_value, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_LINE_FREQ_UB, zcd_Ub.out_freq, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_LINE_FREQ_UB_FILTER_T, filter_freq_Ub.p_T, REG_TYPE_IQ24, REG_FLAG_CONF)
REG(REG_ID_LINE_FREQ_UB_FILT, filter_freq_Ub.out_value, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_LINE_FREQ_UC, zcd_Uc.out_freq, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_LINE_FREQ_UC_FILTER_T, filter_freq_Uc.p_T, REG_TYPE_IQ24, REG_FLAG_CONF)
REG(REG_ID_LINE_FREQ_UC_FILT, filter_freq_Uc.out_value, REG_TYPE_IQ24, REG_FLAG_NONE)

REG(REG_ID_RMS_UA, rms_Ua.out_value, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_RMS_UB, rms_Ub.out_value, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_RMS_UC, rms_Uc.out_value, REG_TYPE_IQ24, REG_FLAG_NONE)

REG(REG_ID_MEAN_IARM, mean_Iarm.out_value, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_MEAN_IARM_FILTER_T, filter_mean_Iarm.p_T, REG_TYPE_IQ24, REG_FLAG_CONF)
REG(REG_ID_MEAN_IARM_FILT, filter_mean_Iarm.out_value, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_MEAN_UARM, mean_Uarm.out_value, REG_TYPE_IQ24, REG_FLAG_NONE)
REG(REG_ID_MEAN_UARM_FILTER_T, filter_mean_Uarm.p_T, REG_TYPE_IQ24, REG_FLAG_CONF)
REG(REG_ID_MEAN_UARM_FILT, filter_mean_Uarm.out_value, REG_TYPE_IQ24, REG_FLAG_NONE)

// End
REGS_END()

#define REGS_COUNT REGS_COUNT_VALUE(REG_ARRAY_NAME)

#endif /* REG_LIST_DATA_H */
