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
REG(REG_ID_CONF_U_NOM, conf.p_U_nom, REG_TYPE_IQ15, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_CONF_I_NOM, conf.p_I_nom, REG_TYPE_IQ15, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_CONF_F_NOM, conf.p_f_nom, REG_TYPE_IQ15, REG_FLAG_CONF, REG_ID_NONE)

// Motor
// Nominal values
REG(REG_ID_MOTOR_F_NOM, motor.p_f_nom, REG_TYPE_IQ15, REG_FLAG_CONF, REG_ID_NONE)
// Nominal stator values
REG(REG_ID_MOTOR_S_U_NOM, motor.p_s_U_nom, REG_TYPE_IQ15, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_MOTOR_S_I_NOM, motor.p_s_I_nom, REG_TYPE_IQ15, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_MOTOR_S_P_NOM, motor.r_s_P_base, REG_TYPE_IQ7, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_MOTOR_S_M_NOM, motor.r_s_M_base, REG_TYPE_IQ15, REG_FLAG_NONE, REG_ID_NONE)
// Nominal rotor values
REG(REG_ID_MOTOR_U_NOM, motor.p_U_nom, REG_TYPE_IQ15, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_MOTOR_I_NOM, motor.p_I_nom, REG_TYPE_IQ15, REG_FLAG_CONF, REG_ID_NONE)


// SysTime
REG(REG_ID_SYS_TIME_COUNTER_MS, sys_time.r_counter_ms, REG_TYPE_U32, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_SYS_TIME_COUNTER_S, sys_time.r_counter_s, REG_TYPE_U32, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_SYS_TIME_RUN_COUNTER_S, sys_time.r_run_counter_s, REG_TYPE_U32, REG_FLAG_NONE, REG_ID_NONE)

// ADC
// Phases voltage
// Raw
REG(REG_ID_ADC_UA_RAW, adc.out_Ua_raw, REG_TYPE_U32, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_ADC_UB_RAW, adc.out_Ub_raw, REG_TYPE_U32, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_ADC_UC_RAW, adc.out_Uc_raw, REG_TYPE_U32, REG_FLAG_NONE, REG_ID_NONE)
// Rel
REG(REG_ID_ADC_UA, adc.out_Ua, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_ADC_UB, adc.out_Ub, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_ADC_UC, adc.out_Uc, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
// Calibration
REG(REG_ID_ADC_UA_GAIN, adc.p_Ua_gain, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_ADC_UA_OFFSET, adc.p_Ua_offset, REG_TYPE_U32, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_ADC_UB_GAIN, adc.p_Ub_gain, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_ADC_UB_OFFSET, adc.p_Ub_offset, REG_TYPE_U32, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_ADC_UC_GAIN, adc.p_Uc_gain, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_ADC_UC_OFFSET, adc.p_Uc_offset, REG_TYPE_U32, REG_FLAG_CONF, REG_ID_NONE)

// Measurement
REG(REG_ID_MEAS_UA, mains_U.out_A, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_U_NOM)
REG(REG_ID_MEAS_UB, mains_U.out_B, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_U_NOM)
REG(REG_ID_MEAS_UC, mains_U.out_C, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_U_NOM)
REG(REG_ID_MEAS_IA, mains_I.out_A, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_I_NOM)
REG(REG_ID_MEAS_IB, mains_I.out_B, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_I_NOM)
REG(REG_ID_MEAS_IC, mains_I.out_C, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_I_NOM)
REG(REG_ID_MEAS_UARM, armature_U.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_U_NOM)
REG(REG_ID_MEAS_IARM, armature_I.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_I_NOM)
REG(REG_ID_MEAS_IRSTART, rstart_I.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_I_NOM)
REG(REG_ID_MEAS_CELL_UAB, cell_U.out_A, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_MEAS_CELL_UBC, cell_U.out_B, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_MEAS_CELL_UCA, cell_U.out_C, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_MEAS_CELL_UA, cell_U_phase.out_A, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_MEAS_CELL_UB, cell_U_phase.out_B, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_MEAS_CELL_UC, cell_U_phase.out_C, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_MEAS_CELL_IA, cell_I.out_A, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)
REG(REG_ID_MEAS_CELL_IB, cell_I.out_B, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)
REG(REG_ID_MEAS_CELL_IC, cell_I.out_C, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)

// Model
REG(REG_ID_MODEL_STATOR_UA, lrm.in_stator_Uab, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_MODEL_STATOR_UB, lrm.in_stator_Ubc, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_MODEL_STATOR_UC, lrm.in_stator_Uca, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_MODEL_STATOR_IAB, lrm.out_stator_Iab, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)
REG(REG_ID_MODEL_STATOR_IBC, lrm.out_stator_Ibc, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)
REG(REG_ID_MODEL_STATOR_ICA, lrm.out_stator_Ica, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)
REG(REG_ID_MODEL_STATOR_IA, lrm_I_stator_phase.out_A, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)
REG(REG_ID_MODEL_STATOR_IB, lrm_I_stator_phase.out_B, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)
REG(REG_ID_MODEL_STATOR_IC, lrm_I_stator_phase.out_C, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)
REG(REG_ID_MODEL_ROTOR_U, lrm.out_U, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_U_NOM)
REG(REG_ID_MODEL_ROTOR_I, lrm.out_I, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_I_NOM)
REG(REG_ID_MODEL_R_START_I, lrm.out_Irstart, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_I_NOM)
REG(REG_ID_MODEL_MOTOR_M, lrm.out_M, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_M_NOM)
REG(REG_ID_MODEL_MOTOR_W, lrm.out_w, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_F_NOM)
REG(REG_ID_MODEL_RECTIFIER_UA, lrm.in_Uab, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_U_NOM)
REG(REG_ID_MODEL_RECTIFIER_UB, lrm.in_Ubc, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_U_NOM)
REG(REG_ID_MODEL_RECTIFIER_UC, lrm.in_Uca, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_U_NOM)
REG(REG_ID_MODEL_RECTIFIER_IA, lrm.out_Iab, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_I_NOM)
REG(REG_ID_MODEL_RECTIFIER_IB, lrm.out_Ibc, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_I_NOM)
REG(REG_ID_MODEL_RECTIFIER_IC, lrm.out_Ica, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_I_NOM)

// Phase and Amplitude.
REG(REG_ID_PHASE_AMPL_UA_PHASE, phase_ampl_Ua.out_phase, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_PHASE_AMPL_UA_AMPL, phase_ampl_Ua.out_ampl, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_PHASE_AMPL_UB_PHASE, phase_ampl_Ub.out_phase, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_PHASE_AMPL_UB_AMPL, phase_ampl_Ub.out_ampl, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_PHASE_AMPL_UC_PHASE, phase_ampl_Uc.out_phase, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_PHASE_AMPL_UC_AMPL, phase_ampl_Uc.out_ampl, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)

// Phase A.
REG(REG_ID_LINE_FREQ_UA_FILTER_T, filter_Ua_zcd.p_T, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_LINE_FREQ_UA_FILT, filter_Ua_zcd.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_U_NOM)
REG(REG_ID_LINE_FREQ_UA_FREQ, zcd_Ua.out_freq, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_LINE_FREQ_UA_FREQ_FILTER_T, filter_freq_Ua.p_T, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_LINE_FREQ_UA_FREQ_FILT, filter_freq_Ua.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
// Phase B.
REG(REG_ID_LINE_FREQ_UB_FILTER_T, filter_Ub_zcd.p_T, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_LINE_FREQ_UB_FILT, filter_Ub_zcd.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_U_NOM)
REG(REG_ID_LINE_FREQ_UB_FREQ, zcd_Ub.out_freq, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_LINE_FREQ_UB_FREQ_FILTER_T, filter_freq_Ub.p_T, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_LINE_FREQ_UB_FREQ_FILT, filter_freq_Ub.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
// Phase C.
REG(REG_ID_LINE_FREQ_UC_FILTER_T, filter_Uc_zcd.p_T, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_LINE_FREQ_UC_FILT, filter_Uc_zcd.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_U_NOM)
REG(REG_ID_LINE_FREQ_UC_FREQ, zcd_Uc.out_freq, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_LINE_FREQ_UC_FREQ_FILTER_T, filter_freq_Uc.p_T, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_LINE_FREQ_UC_FREQ_FILT, filter_freq_Uc.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)


// I r start.
REG(REG_ID_ARM_FREQ_IRSTART_FILTER_T, filter_slip_zcd.p_T, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_ARM_FREQ_IRSTART_FILT, filter_slip_zcd.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_I_NOM)
REG(REG_ID_ARM_FREQ_IRSTART_FREQ, zcd_slip.out_freq, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_ARM_FREQ_IRSTART_FREQ_FILTER_T, filter_freq_slip.p_T, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_ARM_FREQ_IRSTART_FREQ_FILT, filter_freq_slip.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
// Slip.
REG(REG_ID_ARM_FREQ_SLIP, slip.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)


REG(REG_ID_RMS_UA, rms_Ua.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_U_NOM)
REG(REG_ID_RMS_UB, rms_Ub.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_U_NOM)
REG(REG_ID_RMS_UC, rms_Uc.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_U_NOM)
REG(REG_ID_RMS_IA, rms_Ia.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_I_NOM)
REG(REG_ID_RMS_IB, rms_Ib.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_I_NOM)
REG(REG_ID_RMS_IC, rms_Ic.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_CONF_I_NOM)
REG(REG_ID_RMS_CELL_UA, rms_cell_Ua.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_RMS_CELL_UB, rms_cell_Ub.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_RMS_CELL_UC, rms_cell_Uc.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_RMS_CELL_UA_PHASE, rms_cell_Ua_phase.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_RMS_CELL_UB_PHASE, rms_cell_Ub_phase.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_RMS_CELL_UC_PHASE, rms_cell_Uc_phase.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_U_NOM)
REG(REG_ID_RMS_CELL_IA, rms_cell_Ia.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)
REG(REG_ID_RMS_CELL_IB, rms_cell_Ib.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)
REG(REG_ID_RMS_CELL_IC, rms_cell_Ic.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_I_NOM)

REG(REG_ID_MEAN_UARM, mean_Uarm.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_U_NOM)
REG(REG_ID_MEAN_UARM_FILTER_T, filter_mean_Uarm.p_T, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_MEAN_UARM_FILT, filter_mean_Uarm.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_U_NOM)
REG(REG_ID_MEAN_IARM, mean_Iarm.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_I_NOM)
REG(REG_ID_MEAN_IARM_FILTER_T, filter_mean_Iarm.p_T, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_MEAN_IARM_FILT, filter_mean_Iarm.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_I_NOM)
REG(REG_ID_MEAN_IRSTART, mean_Irstart.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_I_NOM)
REG(REG_ID_MEAN_IRSTART_FILTER_T, filter_mean_Irstart.p_T, REG_TYPE_IQ24, REG_FLAG_CONF, REG_ID_NONE)
REG(REG_ID_MEAN_IRSTART_FILT, filter_mean_Irstart.out_value, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_I_NOM)

REG(REG_ID_POWER_A_S, power_A.out_S, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_P_NOM)
REG(REG_ID_POWER_A_P, power_A.out_P, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_P_NOM)
REG(REG_ID_POWER_A_Q, power_A.out_Q, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_P_NOM)
REG(REG_ID_POWER_B_S, power_B.out_S, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_P_NOM)
REG(REG_ID_POWER_B_P, power_B.out_P, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_P_NOM)
REG(REG_ID_POWER_B_Q, power_B.out_Q, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_P_NOM)
REG(REG_ID_POWER_C_S, power_C.out_S, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_P_NOM)
REG(REG_ID_POWER_C_P, power_C.out_P, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_P_NOM)
REG(REG_ID_POWER_C_Q, power_C.out_Q, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_MOTOR_S_P_NOM)

REG(REG_ID_POWER_FACTOR_COS_PHI, power_factor.out_cos_phi, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_POWER_FACTOR_SIN_PHI, power_factor.out_sin_phi, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)
REG(REG_ID_POWER_FACTOR_TAN_PHI, power_factor.out_tan_phi, REG_TYPE_IQ24, REG_FLAG_NONE, REG_ID_NONE)

// End
REGS_END()

#define REGS_COUNT REGS_COUNT_VALUE(REG_ARRAY_NAME)

#endif /* REG_LIST_DATA_H */
