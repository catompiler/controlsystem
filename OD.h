#ifndef OD_H
#define OD_H


// THIS FILE IS GENERATED AUTOMATICALLY!
// DO NOT EDIT THIS FILE!


// user code begin

// user code end

// Counters of OD objects
#define OD_CNT_NMT 1
#define OD_CNT_EM 1
#define OD_CNT_SYNC 1
#define OD_CNT_SYNC_PROD 1
#define OD_CNT_STORAGE 1
#define OD_CNT_TIME 1
#define OD_CNT_EM_PROD 1
#define OD_CNT_HB_CONS 1
#define OD_CNT_HB_PROD 1
#define OD_CNT_SDO_SRV 2
#define OD_CNT_SDO_CLI 1
#define OD_CNT_RPDO 4
#define OD_CNT_TPDO 4


// Sizes of OD arrays
#define OD_CNT_ARR_1003 16
#define OD_CNT_ARR_1010 4
#define OD_CNT_ARR_1011 4
#define OD_CNT_ARR_1016 8


#ifndef OD_ATTR_OD
#define OD_ATTR_OD
#endif
extern OD_ATTR_OD OD_t *OD;


// Object dictionary entries - shortcuts
#define OD_ENTRY_H1000 &OD->list[0]
#define OD_ENTRY_H1001 &OD->list[1]
#define OD_ENTRY_H1003 &OD->list[2]
#define OD_ENTRY_H1005 &OD->list[3]
#define OD_ENTRY_H1006 &OD->list[4]
#define OD_ENTRY_H1007 &OD->list[5]
#define OD_ENTRY_H1010 &OD->list[6]
#define OD_ENTRY_H1011 &OD->list[7]
#define OD_ENTRY_H1012 &OD->list[8]
#define OD_ENTRY_H1014 &OD->list[9]
#define OD_ENTRY_H1015 &OD->list[10]
#define OD_ENTRY_H1016 &OD->list[11]
#define OD_ENTRY_H1017 &OD->list[12]
#define OD_ENTRY_H1018 &OD->list[13]
#define OD_ENTRY_H1019 &OD->list[14]
#define OD_ENTRY_H1200 &OD->list[15]
#define OD_ENTRY_H1201 &OD->list[16]
#define OD_ENTRY_H1280 &OD->list[17]
#define OD_ENTRY_H1400 &OD->list[18]
#define OD_ENTRY_H1401 &OD->list[19]
#define OD_ENTRY_H1402 &OD->list[20]
#define OD_ENTRY_H1403 &OD->list[21]
#define OD_ENTRY_H1600 &OD->list[22]
#define OD_ENTRY_H1601 &OD->list[23]
#define OD_ENTRY_H1602 &OD->list[24]
#define OD_ENTRY_H1603 &OD->list[25]
#define OD_ENTRY_H1800 &OD->list[26]
#define OD_ENTRY_H1801 &OD->list[27]
#define OD_ENTRY_H1802 &OD->list[28]
#define OD_ENTRY_H1803 &OD->list[29]
#define OD_ENTRY_H1A00 &OD->list[30]
#define OD_ENTRY_H1A01 &OD->list[31]
#define OD_ENTRY_H1A02 &OD->list[32]
#define OD_ENTRY_H1A03 &OD->list[33]
#define OD_ENTRY_H2000 &OD->list[34]
#define OD_ENTRY_H2010 &OD->list[35]
#define OD_ENTRY_H2020 &OD->list[36]
#define OD_ENTRY_H2030 &OD->list[37]
#define OD_ENTRY_H2040 &OD->list[38]
#define OD_ENTRY_H2050 &OD->list[39]
#define OD_ENTRY_H2060 &OD->list[40]
#define OD_ENTRY_H2070 &OD->list[41]
#define OD_ENTRY_H2080 &OD->list[42]
#define OD_ENTRY_H2090 &OD->list[43]
#define OD_ENTRY_H20A0 &OD->list[44]
#define OD_ENTRY_H20B0 &OD->list[45]
#define OD_ENTRY_H20C0 &OD->list[46]
#define OD_ENTRY_H20D0 &OD->list[47]
#define OD_ENTRY_H20E0 &OD->list[48]
#define OD_ENTRY_H20F0 &OD->list[49]
#define OD_ENTRY_H2100 &OD->list[50]
#define OD_ENTRY_H2110 &OD->list[51]
#define OD_ENTRY_H2120 &OD->list[52]
#define OD_ENTRY_H2130 &OD->list[53]
#define OD_ENTRY_H2140 &OD->list[54]
#define OD_ENTRY_H2150 &OD->list[55]
#define OD_ENTRY_H2160 &OD->list[56]
#define OD_ENTRY_H2170 &OD->list[57]
#define OD_ENTRY_H2180 &OD->list[58]
#define OD_ENTRY_H2190 &OD->list[59]
#define OD_ENTRY_H21A0 &OD->list[60]
#define OD_ENTRY_H21B0 &OD->list[61]
#define OD_ENTRY_H21C0 &OD->list[62]
#define OD_ENTRY_H21D0 &OD->list[63]
#define OD_ENTRY_H21E0 &OD->list[64]
#define OD_ENTRY_H21F0 &OD->list[65]
#define OD_ENTRY_H2200 &OD->list[66]
#define OD_ENTRY_H2210 &OD->list[67]
#define OD_ENTRY_H2220 &OD->list[68]
#define OD_ENTRY_H2230 &OD->list[69]
#define OD_ENTRY_H2240 &OD->list[70]
#define OD_ENTRY_H2250 &OD->list[71]
#define OD_ENTRY_H2260 &OD->list[72]
#define OD_ENTRY_H2270 &OD->list[73]
#define OD_ENTRY_H2280 &OD->list[74]
#define OD_ENTRY_H2290 &OD->list[75]
#define OD_ENTRY_H22A0 &OD->list[76]
#define OD_ENTRY_H22B0 &OD->list[77]
#define OD_ENTRY_H22C0 &OD->list[78]
#define OD_ENTRY_H22D0 &OD->list[79]
#define OD_ENTRY_H22E0 &OD->list[80]
#define OD_ENTRY_H22F0 &OD->list[81]
#define OD_ENTRY_H2300 &OD->list[82]
#define OD_ENTRY_H2310 &OD->list[83]
#define OD_ENTRY_H2320 &OD->list[84]
#define OD_ENTRY_H2330 &OD->list[85]
#define OD_ENTRY_H2340 &OD->list[86]
#define OD_ENTRY_H2350 &OD->list[87]
#define OD_ENTRY_H2360 &OD->list[88]
#define OD_ENTRY_H2370 &OD->list[89]
#define OD_ENTRY_H2380 &OD->list[90]
#define OD_ENTRY_H2390 &OD->list[91]
#define OD_ENTRY_H23A0 &OD->list[92]
#define OD_ENTRY_H23B0 &OD->list[93]
#define OD_ENTRY_H23C0 &OD->list[94]
#define OD_ENTRY_H23D0 &OD->list[95]
#define OD_ENTRY_H23E0 &OD->list[96]
#define OD_ENTRY_H23F0 &OD->list[97]
#define OD_ENTRY_H2400 &OD->list[98]
#define OD_ENTRY_H2410 &OD->list[99]
#define OD_ENTRY_H2420 &OD->list[100]
#define OD_ENTRY_H2430 &OD->list[101]
#define OD_ENTRY_H2440 &OD->list[102]
#define OD_ENTRY_H2450 &OD->list[103]
#define OD_ENTRY_H2460 &OD->list[104]
#define OD_ENTRY_H2470 &OD->list[105]
#define OD_ENTRY_H2480 &OD->list[106]
#define OD_ENTRY_H2490 &OD->list[107]
#define OD_ENTRY_H24A0 &OD->list[108]
#define OD_ENTRY_H24B0 &OD->list[109]
#define OD_ENTRY_H24C0 &OD->list[110]
#define OD_ENTRY_H24D0 &OD->list[111]
#define OD_ENTRY_H24E0 &OD->list[112]
#define OD_ENTRY_H24F0 &OD->list[113]
#define OD_ENTRY_H2500 &OD->list[114]
#define OD_ENTRY_H2510 &OD->list[115]
#define OD_ENTRY_H2520 &OD->list[116]
#define OD_ENTRY_H2530 &OD->list[117]
#define OD_ENTRY_H2540 &OD->list[118]
#define OD_ENTRY_H2550 &OD->list[119]
#define OD_ENTRY_H2560 &OD->list[120]
#define OD_ENTRY_H2570 &OD->list[121]
#define OD_ENTRY_H2580 &OD->list[122]
#define OD_ENTRY_H2590 &OD->list[123]
#define OD_ENTRY_H25A0 &OD->list[124]
#define OD_ENTRY_H25B0 &OD->list[125]
#define OD_ENTRY_H25C0 &OD->list[126]
#define OD_ENTRY_H25D0 &OD->list[127]
#define OD_ENTRY_H25E0 &OD->list[128]
#define OD_ENTRY_H25F0 &OD->list[129]
#define OD_ENTRY_H2600 &OD->list[130]
#define OD_ENTRY_H2610 &OD->list[131]
#define OD_ENTRY_H2620 &OD->list[132]
#define OD_ENTRY_H2630 &OD->list[133]
#define OD_ENTRY_H2640 &OD->list[134]
#define OD_ENTRY_H2650 &OD->list[135]
#define OD_ENTRY_H2660 &OD->list[136]
#define OD_ENTRY_H2670 &OD->list[137]
#define OD_ENTRY_H2680 &OD->list[138]
#define OD_ENTRY_H2690 &OD->list[139]
#define OD_ENTRY_H26A0 &OD->list[140]
#define OD_ENTRY_H26B0 &OD->list[141]
#define OD_ENTRY_H26C0 &OD->list[142]
#define OD_ENTRY_H26D0 &OD->list[143]
#define OD_ENTRY_H26E0 &OD->list[144]
#define OD_ENTRY_H26F0 &OD->list[145]
#define OD_ENTRY_H2700 &OD->list[146]
#define OD_ENTRY_H2710 &OD->list[147]
#define OD_ENTRY_H2720 &OD->list[148]
#define OD_ENTRY_H2730 &OD->list[149]
#define OD_ENTRY_H2740 &OD->list[150]
#define OD_ENTRY_H2750 &OD->list[151]
#define OD_ENTRY_H2760 &OD->list[152]


// Object dictionary entries - shortcuts with names
#define OD_ENTRY_H1000_deviceType &OD->list[0]
#define OD_ENTRY_H1001_errorRegister &OD->list[1]
#define OD_ENTRY_H1003_pre_definedErrorField &OD->list[2]
#define OD_ENTRY_H1005_COB_ID_SYNCMessage &OD->list[3]
#define OD_ENTRY_H1006_communicationCyclePeriod &OD->list[4]
#define OD_ENTRY_H1007_synchronousWindowLength &OD->list[5]
#define OD_ENTRY_H1010_storeParameters &OD->list[6]
#define OD_ENTRY_H1011_restoreDefaultParameters &OD->list[7]
#define OD_ENTRY_H1012_COB_IDTimeStampObject &OD->list[8]
#define OD_ENTRY_H1014_COB_ID_EMCY &OD->list[9]
#define OD_ENTRY_H1015_inhibitTimeEMCY &OD->list[10]
#define OD_ENTRY_H1016_consumerHeartbeatTime &OD->list[11]
#define OD_ENTRY_H1017_producerHeartbeatTime &OD->list[12]
#define OD_ENTRY_H1018_identity &OD->list[13]
#define OD_ENTRY_H1019_synchronousCounterOverflowValue &OD->list[14]
#define OD_ENTRY_H1200_SDOServerParameter &OD->list[15]
#define OD_ENTRY_H1201_SDOServerParameter &OD->list[16]
#define OD_ENTRY_H1280_SDOClientParameter &OD->list[17]
#define OD_ENTRY_H1400_RPDOCommunicationParameter &OD->list[18]
#define OD_ENTRY_H1401_RPDOCommunicationParameter &OD->list[19]
#define OD_ENTRY_H1402_RPDOCommunicationParameter &OD->list[20]
#define OD_ENTRY_H1403_RPDOCommunicationParameter &OD->list[21]
#define OD_ENTRY_H1600_RPDOMappingParameter &OD->list[22]
#define OD_ENTRY_H1601_RPDOMappingParameter &OD->list[23]
#define OD_ENTRY_H1602_RPDOMappingParameter &OD->list[24]
#define OD_ENTRY_H1603_RPDOMappingParameter &OD->list[25]
#define OD_ENTRY_H1800_TPDOCommunicationParameter &OD->list[26]
#define OD_ENTRY_H1801_TPDOCommunicationParameter &OD->list[27]
#define OD_ENTRY_H1802_TPDOCommunicationParameter &OD->list[28]
#define OD_ENTRY_H1803_TPDOCommunicationParameter &OD->list[29]
#define OD_ENTRY_H1A00_TPDOMappingParameter &OD->list[30]
#define OD_ENTRY_H1A01_TPDOMappingParameter &OD->list[31]
#define OD_ENTRY_H1A02_TPDOMappingParameter &OD->list[32]
#define OD_ENTRY_H1A03_TPDOMappingParameter &OD->list[33]
#define OD_ENTRY_H2000_sys &OD->list[34]
#define OD_ENTRY_H2010_sys_cmd &OD->list[35]
#define OD_ENTRY_H2020_sys_ctrl &OD->list[36]
#define OD_ENTRY_H2030_sys_stat &OD->list[37]
#define OD_ENTRY_H2040_conf &OD->list[38]
#define OD_ENTRY_H2050_adc &OD->list[39]
#define OD_ENTRY_H2060_dac &OD->list[40]
#define OD_ENTRY_H2070_adc_model &OD->list[41]
#define OD_ENTRY_H2080_adc_tim &OD->list[42]
#define OD_ENTRY_H2090_sys_tim &OD->list[43]
#define OD_ENTRY_H20A0_ms_tim &OD->list[44]
#define OD_ENTRY_H20B0_net_tim &OD->list[45]
#define OD_ENTRY_H20C0_sys_time &OD->list[46]
#define OD_ENTRY_H20D0_tmr_sys_fsm &OD->list[47]
#define OD_ENTRY_H20E0_dlog &OD->list[48]
#define OD_ENTRY_H20F0_sys_calc &OD->list[49]
#define OD_ENTRY_H2100_rect_curr &OD->list[50]
#define OD_ENTRY_H2110_mux_umains &OD->list[51]
#define OD_ENTRY_H2120_mux_imains &OD->list[52]
#define OD_ENTRY_H2130_mux_uarm &OD->list[53]
#define OD_ENTRY_H2140_mux_iarm &OD->list[54]
#define OD_ENTRY_H2150_mux_irstart &OD->list[55]
#define OD_ENTRY_H2160_mux_ucell &OD->list[56]
#define OD_ENTRY_H2170_mux_icell &OD->list[57]
#define OD_ENTRY_H2180_mux_slip &OD->list[58]
#define OD_ENTRY_H2190_phase_ampl_ua &OD->list[59]
#define OD_ENTRY_H21A0_phase_ampl_ub &OD->list[60]
#define OD_ENTRY_H21B0_phase_ampl_uc &OD->list[61]
#define OD_ENTRY_H21C0_zcd_ua &OD->list[62]
#define OD_ENTRY_H21D0_zcd_ub &OD->list[63]
#define OD_ENTRY_H21E0_zcd_uc &OD->list[64]
#define OD_ENTRY_H21F0_zcd_slip &OD->list[65]
#define OD_ENTRY_H2200_slip &OD->list[66]
#define OD_ENTRY_H2210_phase_lrm_i_stator &OD->list[67]
#define OD_ENTRY_H2220_phase_ucell &OD->list[68]
#define OD_ENTRY_H2230_calc_ucell &OD->list[69]
#define OD_ENTRY_H2240_calc_icell &OD->list[70]
#define OD_ENTRY_H2250_rms_ua &OD->list[71]
#define OD_ENTRY_H2260_rms_ub &OD->list[72]
#define OD_ENTRY_H2270_rms_uc &OD->list[73]
#define OD_ENTRY_H2280_rms_ia &OD->list[74]
#define OD_ENTRY_H2290_rms_ib &OD->list[75]
#define OD_ENTRY_H22A0_rms_ic &OD->list[76]
#define OD_ENTRY_H22B0_rms_cell_ua &OD->list[77]
#define OD_ENTRY_H22C0_rms_cell_ub &OD->list[78]
#define OD_ENTRY_H22D0_rms_cell_uc &OD->list[79]
#define OD_ENTRY_H22E0_rms_cell_ua_phase &OD->list[80]
#define OD_ENTRY_H22F0_rms_cell_ub_phase &OD->list[81]
#define OD_ENTRY_H2300_rms_cell_uc_phase &OD->list[82]
#define OD_ENTRY_H2310_rms_cell_ia &OD->list[83]
#define OD_ENTRY_H2320_rms_cell_ib &OD->list[84]
#define OD_ENTRY_H2330_rms_cell_ic &OD->list[85]
#define OD_ENTRY_H2340_mean_iarm &OD->list[86]
#define OD_ENTRY_H2350_mean_uarm &OD->list[87]
#define OD_ENTRY_H2360_mean_irstart &OD->list[88]
#define OD_ENTRY_H2370_mean_rms_icell &OD->list[89]
#define OD_ENTRY_H2380_sum_s &OD->list[90]
#define OD_ENTRY_H2390_sum_p &OD->list[91]
#define OD_ENTRY_H23A0_sum_q &OD->list[92]
#define OD_ENTRY_H23B0_power_a &OD->list[93]
#define OD_ENTRY_H23C0_power_b &OD->list[94]
#define OD_ENTRY_H23D0_power_c &OD->list[95]
#define OD_ENTRY_H23E0_power_factor &OD->list[96]
#define OD_ENTRY_H23F0_vr_rms_umains &OD->list[97]
#define OD_ENTRY_H2400_vr_filter_freq_umains &OD->list[98]
#define OD_ENTRY_H2410_vr_rms_ucell &OD->list[99]
#define OD_ENTRY_H2420_cell_cb &OD->list[100]
#define OD_ENTRY_H2430_field_trig &OD->list[101]
#define OD_ENTRY_H2440_thr_run_trig_i_s &OD->list[102]
#define OD_ENTRY_H2450_am_run_trig_i_s &OD->list[103]
#define OD_ENTRY_H2460_tmr_run_trig &OD->list[104]
#define OD_ENTRY_H2470_thr_prim_slip &OD->list[105]
#define OD_ENTRY_H2480_thr_prim_i_s &OD->list[106]
#define OD_ENTRY_H2490_thr_prim_t &OD->list[107]
#define OD_ENTRY_H24A0_am_prim_field_on &OD->list[108]
#define OD_ENTRY_H24B0_thr_sec_slip &OD->list[109]
#define OD_ENTRY_H24C0_thr_sec_i_s &OD->list[110]
#define OD_ENTRY_H24D0_thr_sec_t &OD->list[111]
#define OD_ENTRY_H24E0_am_sec_field_on &OD->list[112]
#define OD_ENTRY_H24F0_tmr_field_on &OD->list[113]
#define OD_ENTRY_H2500_thr_field_on_i_r_sync &OD->list[114]
#define OD_ENTRY_H2510_tmr_field_on_i_r_sync &OD->list[115]
#define OD_ENTRY_H2520_thr_value_for_slip_lt_zero &OD->list[116]
#define OD_ENTRY_H2530_tmr_field_on_rstart_off &OD->list[117]
#define OD_ENTRY_H2540_tmr_start_min_forcing &OD->list[118]
#define OD_ENTRY_H2550_tmr_start_max_forcing &OD->list[119]
#define OD_ENTRY_H2560_tmr_start_stab_forcing &OD->list[120]
#define OD_ENTRY_H2570_thr_start_q_le_zero &OD->list[121]
#define OD_ENTRY_H2580_thr_field_supp_i_r &OD->list[122]
#define OD_ENTRY_H2590_tmr_field_supp &OD->list[123]
#define OD_ENTRY_H25A0_cnt_start &OD->list[124]
#define OD_ENTRY_H25B0_filter_zcd_ua &OD->list[125]
#define OD_ENTRY_H25C0_filter_zcd_ub &OD->list[126]
#define OD_ENTRY_H25D0_filter_zcd_uc &OD->list[127]
#define OD_ENTRY_H25E0_filter_zcd_slip &OD->list[128]
#define OD_ENTRY_H25F0_filter_freq_ua &OD->list[129]
#define OD_ENTRY_H2600_filter_freq_ub &OD->list[130]
#define OD_ENTRY_H2610_filter_freq_uc &OD->list[131]
#define OD_ENTRY_H2620_filter_freq_slip &OD->list[132]
#define OD_ENTRY_H2630_filter_mean_iarm &OD->list[133]
#define OD_ENTRY_H2640_filter_mean_uarm &OD->list[134]
#define OD_ENTRY_H2650_filter_mean_irstart &OD->list[135]
#define OD_ENTRY_H2660_mux_field_regs &OD->list[136]
#define OD_ENTRY_H2670_lim_field_regs_curr_ref &OD->list[137]
#define OD_ENTRY_H2680_mux_field_force_ref &OD->list[138]
#define OD_ENTRY_H2690_mot_pot_field_test &OD->list[139]
#define OD_ENTRY_H26A0_mot_pot_manual_curr_ref &OD->list[140]
#define OD_ENTRY_H26B0_mux_curr_ref &OD->list[141]
#define OD_ENTRY_H26C0_pid_i &OD->list[142]
#define OD_ENTRY_H26D0_pid_coefs_i &OD->list[143]
#define OD_ENTRY_H26E0_ph3c &OD->list[144]
#define OD_ENTRY_H26F0_triacs &OD->list[145]
#define OD_ENTRY_H2700_lrm &OD->list[146]
#define OD_ENTRY_H2710_motor &OD->list[147]
#define OD_ENTRY_H2720_prot &OD->list[148]
#define OD_ENTRY_H2730_canopen &OD->list[149]
#define OD_ENTRY_H2740_storage &OD->list[150]
#define OD_ENTRY_H2750_settings &OD->list[151]
#define OD_ENTRY_H2760_event_log &OD->list[152]


// OD config structure
#ifdef CO_MULTIPLE_OD
#define OD_INIT_CONFIG(config) {\
(config).CNT_NMT = OD_CNT_NMT;\
(config).ENTRY_H1017 = OD_ENTRY_H1017_producerHeartbeatTime;\
(config).CNT_HB_CONS = OD_CNT_HB_CONS;\
(config).CNT_ARR_1016 = OD_CNT_ARR_1016;\
(config).ENTRY_H1016 = OD_ENTRY_H1016_consumerHeartbeatTime;\
(config).CNT_EM = OD_CNT_EM;\
(config).ENTRY_H1001 = OD_ENTRY_H1001_errorRegister;\
(config).ENTRY_H1014 = OD_ENTRY_H1014_COB_ID_EMCY;\
(config).ENTRY_H1015 = OD_ENTRY_H1015_inhibitTimeEMCY;\
(config).CNT_ARR_1003 = OD_CNT_ARR_1003;\
(config).ENTRY_H1003 = OD_ENTRY_H1003_pre_definedErrorField;\
(config).CNT_SDO_SRV = OD_CNT_SDO_SRV;\
(config).ENTRY_H1200 = OD_ENTRY_H1200_SDOServerParameter;\
(config).CNT_SDO_CLI = OD_CNT_SDO_CLI;\
(config).ENTRY_H1280 = OD_ENTRY_H1280_SDOClientParameter;\
(config).CNT_TIME = OD_CNT_TIME;\
(config).ENTRY_H1012 = OD_ENTRY_H1012_COB_IDTimeStampObject;\
(config).CNT_SYNC = OD_CNT_SYNC;\
(config).ENTRY_H1005 = OD_ENTRY_H1005_COB_ID_SYNCMessage;\
(config).ENTRY_H1006 = OD_ENTRY_H1006_communicationCyclePeriod;\
(config).ENTRY_H1007 = OD_ENTRY_H1007_synchronousWindowLength;\
(config).ENTRY_H1019 = OD_ENTRY_H1019_synchronousCounterOverflowValue;\
(config).CNT_RPDO = OD_CNT_RPDO;\
(config).ENTRY_H1400 = OD_ENTRY_H1400_RPDOCommunicationParameter;\
(config).ENTRY_H1600 = OD_ENTRY_H1600_RPDOMappingParameter;\
(config).CNT_TPDO = OD_CNT_TPDO;\
(config).ENTRY_H1800 = OD_ENTRY_H1800_TPDOCommunicationParameter;\
(config).ENTRY_H1A00 = OD_ENTRY_H1A00_TPDOMappingParameter;\
(config).CNT_LEDS = 0;\
(config).CNT_GFC = 0;\
(config).ENTRY_H1300 = NULL;\
(config).CNT_SRDO = 0;\
(config).ENTRY_H1301 = NULL;\
(config).ENTRY_H1381 = NULL;\
(config).ENTRY_H13FE = NULL;\
(config).ENTRY_H13FF = NULL;\
(config).CNT_LSS_SLV = 0;\
(config).CNT_LSS_MST = 0;\
(config).CNT_GTWA = 0;\
(config).CNT_TRACE = 0;\
}
#endif

#endif /* OD_H */
