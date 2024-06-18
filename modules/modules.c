#include "modules.h"
#include "conf/consts.h"


M_sys_main sys = SYS_MAIN_DEFAULTS;
M_sys_command sys_cmd = SYS_COMMAND_DEFAULTS;
M_sys_control sys_ctrl = SYS_CONTROL_DEFAULTS;
M_sys_status sys_stat = SYS_STATUS_DEFAULTS;

M_conf conf = CONF_DEFAULTS;

M_adc adc = ADC_DEFAULTS;

M_adc_model adc_model = ADC_MODEL_DEFAULTS;

M_adc_timer adc_tim = ADC_TIMER_DEFAULTS;
M_sys_timer sys_tim = SYS_TIMER_DEFAULTS;
M_ms_timer ms_tim = MS_TIMER_DEFAULTS;

M_sys_time sys_time = SYS_TIME_DEFAULTS;

M_timer tmr_sys_fsm = TIMER_DEFAULTS;

M_data_log dlog = DATA_LOG_DEFAULTS;

M_meas meas = MEAS_DEFAULTS;

M_rect_curr rect_curr = RECT_CURR_DEFAULTS;

M_mux_abc mains_U = MUX_ABC_DEFAULTS;
M_mux_abc mains_I = MUX_ABC_DEFAULTS;
M_mux2 armature_U = MUX2_DEFAULTS;
M_mux3 armature_I = MUX3_DEFAULTS;
M_mux2 rstart_I = MUX2_DEFAULTS;
M_mux_abc mux_cell_U = MUX_ABC_DEFAULTS;
M_mux_abc mux_cell_I = MUX_ABC_DEFAULTS;
M_mux2 mux_slip = MUX2_DEFAULTS;

M_phase_ampl phase_ampl_Ua = PHASE_AMPL_DEFAULTS;
M_phase_ampl phase_ampl_Ub = PHASE_AMPL_DEFAULTS;
M_phase_ampl phase_ampl_Uc = PHASE_AMPL_DEFAULTS;

M_zero_cross_detect zcd_Ua = ZERO_CROSS_DETECT_DEFAULTS;
M_zero_cross_detect zcd_Ub = ZERO_CROSS_DETECT_DEFAULTS;
M_zero_cross_detect zcd_Uc = ZERO_CROSS_DETECT_DEFAULTS;
M_zero_cross_detect zcd_slip = ZERO_CROSS_DETECT_DEFAULTS;

// Скольжение.
M_slip slip = SLIP_DEFAULTS;

M_phase_to_line cell_U_line = PHASE_TO_LINE_DEFAULTS;

M_value_3phase cell_U = VALUE_3PHASE_DEFAULTS;
M_value_3phase cell_I = VALUE_3PHASE_DEFAULTS;

M_rms rms_Ua = RMS_DEFAULTS;
M_rms rms_Ub = RMS_DEFAULTS;
M_rms rms_Uc = RMS_DEFAULTS;
M_rms rms_Ia = RMS_DEFAULTS;
M_rms rms_Ib = RMS_DEFAULTS;
M_rms rms_Ic = RMS_DEFAULTS;
M_rms rms_cell_Ua = RMS_DEFAULTS;
M_rms rms_cell_Ub = RMS_DEFAULTS;
M_rms rms_cell_Uc = RMS_DEFAULTS;
M_rms rms_cell_Ia = RMS_DEFAULTS;
M_rms rms_cell_Ib = RMS_DEFAULTS;
M_rms rms_cell_Ic = RMS_DEFAULTS;

#if (CONF_PERIOD_SAMPLES % 6 != 0)
M_fract_mean mean_Iarm = FRACT_MEAN_DEFAULTS;
M_fract_mean mean_Uarm = FRACT_MEAN_DEFAULTS;
M_fract_mean mean_Irstart = FRACT_MEAN_DEFAULTS;
#else // (CONF_PERIOD_SAMPLES % 6 != 0)
M_dc_mean mean_Iarm = DC_MEAN_DEFAULTS;
M_dc_mean mean_Uarm = DC_MEAN_DEFAULTS;
M_dc_mean mean_Irstart = DC_MEAN_DEFAULTS;
#endif // (CONF_PERIOD_SAMPLES % 6 != 0)

M_power power_A = POWER_DEFAULTS;
M_power power_B = POWER_DEFAULTS;
M_power power_C = POWER_DEFAULTS;

M_valid_range3 vr_rms_Umains = VALID_RANGE3_DEFCFG(IQ24(0.5), IQ24(1.5));

M_valid_range3 vr_filter_freq_Umains = VALID_RANGE3_DEFCFG(IQ24(44.9), IQ24(65.1));

M_filter1 filter_Ua_zcd = FILTER1_DEFCFG(IQ24(0.01)); // 100 Hz.
M_filter1 filter_Ub_zcd = FILTER1_DEFCFG(IQ24(0.01));
M_filter1 filter_Uc_zcd = FILTER1_DEFCFG(IQ24(0.01));
M_filter1 filter_slip_zcd = FILTER1_DEFCFG(IQ24(0.001));

M_filter1 filter_freq_Ua = FILTER1_DEFCFG(IQ24(0.04)); // 2 periods.
M_filter1 filter_freq_Ub = FILTER1_DEFCFG(IQ24(0.04));
M_filter1 filter_freq_Uc = FILTER1_DEFCFG(IQ24(0.04));
M_filter1 filter_freq_slip = FILTER1_DEFCFG(IQ24(0.001));

M_filter1 filter_mean_Iarm = FILTER1_DEFCFG(IQ24(0.00016));
M_filter1 filter_mean_Uarm = FILTER1_DEFCFG(IQ24(0.00033));
M_filter1 filter_mean_Irstart = FILTER1_DEFCFG(IQ24(0.00016));

M_phase3_control ph3c = PHASE3_CONTROL_DEFAULTS;

//M_larionov_model lrm = LARIONOV_MODEL_DEFAULTS;
M_smotor_larionov lrm = SMOTOR_LARIONOV_DEFAULTS;

M_motor motor = MOTOR_DEFAULTS;

M_prot prot = PROT_DEFAULTS;
