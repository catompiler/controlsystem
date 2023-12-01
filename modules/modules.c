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

M_mains_u_mux mains_U = MAINS_U_MUX_DEFAULTS;
M_mains_i_mux mains_I = MAINS_I_MUX_DEFAULTS;
M_armature_u_mux armature_U = ARMATURE_U_MUX_DEFAULTS;
M_armature_i_mux armature_I = ARMATURE_I_MUX_DEFAULTS;

M_phase_ampl phase_ampl_Ua = PHASE_AMPL_DEFAULTS;
M_phase_ampl phase_ampl_Ub = PHASE_AMPL_DEFAULTS;
M_phase_ampl phase_ampl_Uc = PHASE_AMPL_DEFAULTS;

M_zero_cross_detect zcd_Ua = ZERO_CROSS_DETECT_DEFAULTS;
M_zero_cross_detect zcd_Ub = ZERO_CROSS_DETECT_DEFAULTS;
M_zero_cross_detect zcd_Uc = ZERO_CROSS_DETECT_DEFAULTS;

M_rms rms_Ua = RMS_DEFAULTS;
M_rms rms_Ub = RMS_DEFAULTS;
M_rms rms_Uc = RMS_DEFAULTS;

M_fract_mean mean_Iarm = FRACT_MEAN_DEFAULTS;

M_valid_range3 vr_rms_Umains = VALID_RANGE3_DEFCFG(IQ24(0.5), IQ24(1.5));

M_valid_range3 vr_filter_freq_Umains = VALID_RANGE3_DEFCFG(IQ24(44.9), IQ24(65.1));

M_filter1 filter_Ua_zcd = FILTER1_DEFCFG(IQ24(0.01)); // 100 Hz.
M_filter1 filter_Ub_zcd = FILTER1_DEFCFG(IQ24(0.01));
M_filter1 filter_Uc_zcd = FILTER1_DEFCFG(IQ24(0.01));

M_filter1 filter_freq_Ua = FILTER1_DEFCFG(IQ24(0.04)); // 2 periods.
M_filter1 filter_freq_Ub = FILTER1_DEFCFG(IQ24(0.04));
M_filter1 filter_freq_Uc = FILTER1_DEFCFG(IQ24(0.04));

M_filter1 filter_mean_Iarm = FILTER1_DEFCFG(IQ24(0.00016));

M_phase3_control ph3c = PHASE3_CONTROL_DEFAULTS;

M_larionov_model lrm = LARIONOV_MODEL_DEFAULTS;

M_prot prot = PROT_DEFAULTS;
