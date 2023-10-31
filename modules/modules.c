#include "modules.h"
#include "conf/consts.h"


M_sys_main sys = SYS_MAIN_DEFAULTS;

M_conf conf = CONF_DEFAULTS;

M_adc adc = ADC_DEFAULTS;

M_adc_model adc_model = ADC_MODEL_DEFAULTS;

M_adc_timer adc_tim = ADC_TIMER_DEFAULTS;
M_sys_timer sys_tim = SYS_TIMER_DEFAULTS;
M_ms_timer ms_tim = MS_TIMER_DEFAULTS;

M_sys_time sys_time = SYS_TIME_DEFAULTS;

M_timer tmr_sys_fsm = TIMER_DEFAULTS;

M_data_log dlog = DATA_LOG_DEFAULTS;

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

M_threshold th_rms_Ua = THRESHOLD_DEFCFG(IQ24(0.5), IQ24(1.5));
M_threshold th_rms_Ub = THRESHOLD_DEFCFG(IQ24(0.5), IQ24(1.5));
M_threshold th_rms_Uc = THRESHOLD_DEFCFG(IQ24(0.5), IQ24(1.5));

M_filter1 filter_Ua_freq = FILTER1_DEFCFG(CONF_LINE_FREQ_FILTER_T);
M_filter1 filter_Ub_freq = FILTER1_DEFCFG(CONF_LINE_FREQ_FILTER_T);
M_filter1 filter_Uc_freq = FILTER1_DEFCFG(CONF_LINE_FREQ_FILTER_T);

M_phase3_control ph3c = PHASE3_CONTROL_DEFAULTS;

M_larionov_model lrm = LARIONOV_MODEL_DEFAULTS;
