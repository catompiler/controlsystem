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

M_mux_abc mux_Umains = MUX_ABC_DEFAULTS;
M_mux_abc mux_Imains = MUX_ABC_DEFAULTS;
M_mux2 mux_Uarm = MUX2_DEFAULTS;
M_mux3 mux_Iarm = MUX3_DEFAULTS;
M_mux2 mux_Irstart = MUX2_DEFAULTS;
M_mux_abc mux_Ucell = MUX_ABC_DEFAULTS;
M_mux_abc mux_Icell = MUX_ABC_DEFAULTS;
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

M_delta_line_to_phase phase_lrm_I_stator = DELTA_LINE_TO_PHASE_DEFAULTS;

M_star_line_to_phase phase_Ucell = STAR_LINE_TO_PHASE_DEFAULTS;

M_value_3phase calc_Ucell = VALUE_3PHASE_DEFAULTS;
M_value_3phase calc_Icell = VALUE_3PHASE_DEFAULTS;

M_rms rms_Ua = RMS_DEFAULTS;
M_rms rms_Ub = RMS_DEFAULTS;
M_rms rms_Uc = RMS_DEFAULTS;
M_rms rms_Ia = RMS_DEFAULTS;
M_rms rms_Ib = RMS_DEFAULTS;
M_rms rms_Ic = RMS_DEFAULTS;
M_rms rms_cell_Ua = RMS_DEFAULTS;
M_rms rms_cell_Ub = RMS_DEFAULTS;
M_rms rms_cell_Uc = RMS_DEFAULTS;
M_rms rms_cell_Ua_phase = RMS_DEFAULTS;
M_rms rms_cell_Ub_phase = RMS_DEFAULTS;
M_rms rms_cell_Uc_phase = RMS_DEFAULTS;
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
M_mean3 mean_rms_Icell = MEAN3_DEFAULTS;

M_power power_A = POWER_DEFAULTS;
M_power power_B = POWER_DEFAULTS;
M_power power_C = POWER_DEFAULTS;

M_power_factor power_factor = POWER_FACTOR_DEFAULTS;

M_valid_range3 vr_rms_Umains = VALID_RANGE3_DEFCFG(IQ24(0.5), IQ24(1.5));
M_valid_range3 vr_filter_freq_Umains = VALID_RANGE3_DEFCFG(IQ24(44.9), IQ24(65.1));
M_valid_range3 vr_rms_Ucell = VALID_RANGE3_DEFCFG(IQ24(0.5), IQ24(1.5));

M_cell_cb cell_cb = CELL_CB_DEFAULTS;

M_threshold_gt thr_run_trig_I_s = THRESHOLD_GT_DEFCFG(IQ24(0.1));
M_and1_mask am_run_trig_I_s = AND1_MASK_DEFCFG(1);
M_mux2 mux_run_trig = MUX2_DEFAULTS;
M_timer_on tmr_run_trig = TIMER_ON_DEFCFG(10);

M_threshold_lt thr_prim_Slip = THRESHOLD_LT_DEFCFG(IQ24(0.05));
M_threshold_lt thr_prim_I_s = THRESHOLD_LT_DEFCFG(IQ24(1.5));
M_threshold_gt thr_prim_T = THRESHOLD_GT_DEFCFG(500);
M_and3_mask am_prim_field_on = AND3_MASK_DEFCFG(7);
M_threshold_lt thr_sec_Slip = THRESHOLD_LT_DEFCFG(IQ24(0.05));
M_threshold_lt thr_sec_I_s = THRESHOLD_LT_DEFCFG(IQ24(2.0));
M_threshold_gt thr_sec_T = THRESHOLD_GT_DEFCFG(5000);
M_and3_mask am_sec_field_on = AND3_MASK_DEFCFG(6);
M_or2 or_field_on = OR2_DEFAULTS;
M_timer_on tmr_field_on = TIMER_ON_DEFCFG(10);
M_threshold_lt thr_field_on_I_r_sync = THRESHOLD_LT_DEFCFG(IQ24(0.01));
M_timer_on tmr_field_on_I_r_sync = TIMER_ON_DEFCFG(2500);

M_comp_lt cmp_value_for_slip_lt_zero = COMP_LT_DEFAULTS;
M_or2 or_value_slip_lt_zero_I_r_sync = OR2_DEFAULTS;
M_and2 and_ready_to_exc = AND2_DEFAULTS;
M_timer_on tmr_field_on_rstart_off = TIMER_ON_DEFCFG(10);
M_not not_ready_to_exc = NOT_DEFAULTS;
M_comp_eq cmp_ctrl_state_is_start = COMP_EQ_DEFAULTS;
M_and2 and_rstart_on = AND2_DEFAULTS;

M_threshold_lt thr_field_supp_I_r = THRESHOLD_LT_DEFCFG(IQ24(0.01));
M_timer tmr_field_supp = TIMER_DEFCFG(1000);

M_counter cnt_start = COUNTER_DEFAULTS;

M_filter1 filter_zcd_Ua = FILTER1_DEFCFG(IQ24(0.01)); // 100 Hz.
M_filter1 filter_zcd_Ub = FILTER1_DEFCFG(IQ24(0.01));
M_filter1 filter_zcd_Uc = FILTER1_DEFCFG(IQ24(0.01));
M_filter1 filter_zcd_slip = FILTER1_DEFCFG(IQ24(0.001));

M_filter1 filter_freq_Ua = FILTER1_DEFCFG(IQ24(0.04)); // 2 periods.
M_filter1 filter_freq_Ub = FILTER1_DEFCFG(IQ24(0.04));
M_filter1 filter_freq_Uc = FILTER1_DEFCFG(IQ24(0.04));
M_filter1 filter_freq_slip = FILTER1_DEFCFG(IQ24(0.001));

M_filter1 filter_mean_Iarm = FILTER1_DEFCFG(IQ24(0.00016));
M_filter1 filter_mean_Uarm = FILTER1_DEFCFG(IQ24(0.00033));
M_filter1 filter_mean_Irstart = FILTER1_DEFCFG(IQ24(0.00016));

M_pid pid_i = PID_DEFCFG(IQ24(1), IQ24(1), IQ24(0), IQ24(0), IQ24(0), IQ24(1));
M_pid_coefs pid_coefs_i = PID_COEFS_DEFCFG(IQ24(0.5), IQ24(0.025), IQ24(0.0), IQ24(0.0));

M_phase3_control ph3c = PHASE3_CONTROL_DEFAULTS;

//M_larionov_model lrm = LARIONOV_MODEL_DEFAULTS;
M_smotor_larionov lrm = SMOTOR_LARIONOV_DEFAULTS;

M_motor motor = MOTOR_DEFAULTS;

M_prot prot = PROT_DEFAULTS;
