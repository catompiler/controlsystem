#include "regs_data.h"


// THIS FILE IS GENERATED AUTOMATICALLY!
// DO NOT EDIT THIS FILE!


// user code begin

// user code end

struct _S_regs_data regs_data = {
.deviceType = {
    .value = 0 /*  */
},
.errorRegister = {
    .value = 0 /*  */
},
.pre_definedErrorField = {
    .numberOfErrors = 0 /* Number of sub-entries */,
    .pre_definedErrorField = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } /*  */
},
.COB_ID_SYNCMessage = {
    .value = 0x80 /*  */
},
.communicationCyclePeriod = {
    .value = 0 /*  */
},
.synchronousWindowLength = {
    .value = 0 /*  */
},
.storeParameters = {
    .highestSub_indexSupported = 4 /* Number of sub-entries */,
    .storeParameters = { 1, 1, 1, 1 } /*  */
},
.restoreDefaultParameters = {
    .highestSub_indexSupported = 4 /* Number of sub-entries */,
    .restoreDefaultParameters = { 1, 1, 1, 1 } /*  */
},
.COB_IDTimeStampObject = {
    .value = 0x00000100 /*  */
},
.COB_ID_EMCY = {
    .value = 0x80 /*  */
},
.inhibitTimeEMCY = {
    .value = 0 /*  */
},
.consumerHeartbeatTime = {
    .highestSub_indexSupported = 8 /* Number of sub-entries */,
    .consumerHeartbeatTime = { 0, 0, 0, 0, 0, 0, 0, 0 } /*  */
},
.producerHeartbeatTime = {
    .value = 0 /*  */
},
.identity = {
    .highestSub_indexSupported = 4 /* Number of sub-entries */,
    .vendor_id = 0 /*  */,
    .productCode = 0 /*  */,
    .revisionNumber = 0 /*  */,
    .serialNumber = 0 /*  */
},
.synchronousCounterOverflowValue = {
    .value = 0 /*  */
},
.SDOServerParameter = {
    .highestSub_indexSupported = 2 /* Number of sub-entries */,
    .COB_IDClientToServer_rx_ = 0x600 /*  */,
    .COB_IDServerToClient_tx_ = 0x580 /*  */
},
.SDOClientParameter = {
    .count = 3 /* Number of sub-entries */,
    .COB_IDClientToServer_tx_ = 0x80000000 /*  */,
    .COB_IDServerToClient_rx_ = 0x80000000 /*  */,
    .node_idOfTheSDOServer = 1 /*  */
},
.RPDOCommunicationParameter = {
    .highestSub_indexSupported = 5 /* Number of sub-entries */,
    .COB_IDUsedByRPDO = 0x80000200 /*  */,
    .transmissionType = 254 /*  */,
    .eventTimer = 0 /*  */
},
.RPDOCommunicationParameter_1401 = {
    .highestSub_indexSupported = 5 /* Number of sub-entries */,
    .COB_IDUsedByRPDO = 0x80000300 /*  */,
    .transmissionType = 254 /*  */,
    .eventTimer = 0 /*  */
},
.RPDOCommunicationParameter_1402 = {
    .highestSub_indexSupported = 5 /* Number of sub-entries */,
    .COB_IDUsedByRPDO = 0x80000400 /*  */,
    .transmissionType = 254 /*  */,
    .eventTimer = 0 /*  */
},
.RPDOCommunicationParameter_1403 = {
    .highestSub_indexSupported = 5 /* Number of sub-entries */,
    .COB_IDUsedByRPDO = 0x80000500 /*  */,
    .transmissionType = 254 /*  */,
    .eventTimer = 0 /*  */
},
.RPDOMappingParameter = {
    .numberOfMappedApplicationObjectsInPDO = 0 /* Number of sub-entries */,
    .applicationObject1 = 0 /*  */,
    .applicationObject2 = 0 /*  */,
    .applicationObject3 = 0 /*  */,
    .applicationObject4 = 0 /*  */,
    .applicationObject5 = 0 /*  */,
    .applicationObject6 = 0 /*  */,
    .applicationObject7 = 0 /*  */,
    .applicationObject8 = 0 /*  */
},
.RPDOMappingParameter_1601 = {
    .numberOfMappedApplicationObjectsInPDO = 0 /* Number of sub-entries */,
    .applicationObject1 = 0 /*  */,
    .applicationObject2 = 0 /*  */,
    .applicationObject3 = 0 /*  */,
    .applicationObject4 = 0 /*  */,
    .applicationObject5 = 0 /*  */,
    .applicationObject6 = 0 /*  */,
    .applicationObject7 = 0 /*  */,
    .applicationObject8 = 0 /*  */
},
.RPDOMappingParameter_1602 = {
    .numberOfMappedApplicationObjectsInPDO = 0 /* Number of sub-entries */,
    .applicationObject1 = 0 /*  */,
    .applicationObject2 = 0 /*  */,
    .applicationObject3 = 0 /*  */,
    .applicationObject4 = 0 /*  */,
    .applicationObject5 = 0 /*  */,
    .applicationObject6 = 0 /*  */,
    .applicationObject7 = 0 /*  */,
    .applicationObject8 = 0 /*  */
},
.RPDOMappingParameter_1603 = {
    .numberOfMappedApplicationObjectsInPDO = 0 /* Number of sub-entries */,
    .applicationObject1 = 0 /*  */,
    .applicationObject2 = 0 /*  */,
    .applicationObject3 = 0 /*  */,
    .applicationObject4 = 0 /*  */,
    .applicationObject5 = 0 /*  */,
    .applicationObject6 = 0 /*  */,
    .applicationObject7 = 0 /*  */,
    .applicationObject8 = 0 /*  */
},
.TPDOCommunicationParameter = {
    .highestSub_indexSupported = 6 /* Number of sub-entries */,
    .COB_IDUsedByTPDO = 0xC0000180 /*  */,
    .transmissionType = 254 /*  */,
    .inhibitTime = 0 /*  */,
    .eventTimer = 0 /*  */,
    .SYNCStartValue = 0 /*  */
},
.TPDOCommunicationParameter_1801 = {
    .highestSub_indexSupported = 6 /* Number of sub-entries */,
    .COB_IDUsedByTPDO = 0xC0000280 /*  */,
    .transmissionType = 254 /*  */,
    .inhibitTime = 0 /*  */,
    .eventTimer = 0 /*  */,
    .SYNCStartValue = 0 /*  */
},
.TPDOCommunicationParameter_1802 = {
    .highestSub_indexSupported = 6 /* Number of sub-entries */,
    .COB_IDUsedByTPDO = 0xC0000380 /*  */,
    .transmissionType = 254 /*  */,
    .inhibitTime = 0 /*  */,
    .eventTimer = 0 /*  */,
    .SYNCStartValue = 0 /*  */
},
.TPDOCommunicationParameter_1803 = {
    .highestSub_indexSupported = 6 /* Number of sub-entries */,
    .COB_IDUsedByTPDO = 0xC0000480 /*  */,
    .transmissionType = 254 /*  */,
    .inhibitTime = 0 /*  */,
    .eventTimer = 0 /*  */,
    .SYNCStartValue = 0 /*  */
},
.TPDOMappingParameter = {
    .numberOfMappedApplicationObjectsInPDO = 0 /* Number of sub-entries */,
    .applicationObject1 = 0 /*  */,
    .applicationObject2 = 0 /*  */,
    .applicationObject3 = 0 /*  */,
    .applicationObject4 = 0 /*  */,
    .applicationObject5 = 0 /*  */,
    .applicationObject6 = 0 /*  */,
    .applicationObject7 = 0 /*  */,
    .applicationObject8 = 0 /*  */
},
.TPDOMappingParameter_1a01 = {
    .numberOfMappedApplicationObjectsInPDO = 0 /* Number of sub-entries */,
    .applicationObject1 = 0 /*  */,
    .applicationObject2 = 0 /*  */,
    .applicationObject3 = 0 /*  */,
    .applicationObject4 = 0 /*  */,
    .applicationObject5 = 0 /*  */,
    .applicationObject6 = 0 /*  */,
    .applicationObject7 = 0 /*  */,
    .applicationObject8 = 0 /*  */
},
.TPDOMappingParameter_1a02 = {
    .numberOfMappedApplicationObjectsInPDO = 0 /* Number of sub-entries */,
    .applicationObject1 = 0 /*  */,
    .applicationObject2 = 0 /*  */,
    .applicationObject3 = 0 /*  */,
    .applicationObject4 = 0 /*  */,
    .applicationObject5 = 0 /*  */,
    .applicationObject6 = 0 /*  */,
    .applicationObject7 = 0 /*  */,
    .applicationObject8 = 0 /*  */
},
.TPDOMappingParameter_1a03 = {
    .numberOfMappedApplicationObjectsInPDO = 0 /* Number of sub-entries */,
    .applicationObject1 = 0 /*  */,
    .applicationObject2 = 0 /*  */,
    .applicationObject3 = 0 /*  */,
    .applicationObject4 = 0 /*  */,
    .applicationObject5 = 0 /*  */,
    .applicationObject6 = 0 /*  */,
    .applicationObject7 = 0 /*  */,
    .applicationObject8 = 0 /*  */
},
.sys = {
    .count = 6 /* Number of sub entries count */
},
.sys_cmd = {
    .count = 3 /* Number of sub entries count */
},
.sys_ctrl = {
    .count = 11 /* Number of sub entries count */
},
.sys_stat = {
    .count = 3 /* Number of sub entries count */
},
.conf = {
    .count = 14 /* Number of sub entries count */
},
.adc = {
    .count = 62 /* Number of sub entries count */
},
.adc_model = {
    .count = 30 /* Number of sub entries count */
},
.adc_tim = {
    .count = 3 /* Number of sub entries count */
},
.sys_tim = {
    .count = 3 /* Number of sub entries count */
},
.ms_tim = {
    .count = 3 /* Number of sub entries count */
},
.net_tim = {
    .count = 3 /* Number of sub entries count */
},
.sys_time = {
    .count = 5 /* Number of sub entries count */
},
.tmr_sys_fsm = {
    .count = 5 /* Number of sub entries count */
},
.dlog = {
    .count = 149 /* Number of sub entries count */
},
.sys_calc = {
    .count = 2 /* Number of sub entries count */
},
.rect_curr = {
    .count = 6 /* Number of sub entries count */
},
.mux_umains = {
    .count = 15 /* Number of sub entries count */
},
.mux_imains = {
    .count = 15 /* Number of sub entries count */
},
.mux_uarm = {
    .count = 6 /* Number of sub entries count */
},
.mux_iarm = {
    .count = 7 /* Number of sub entries count */
},
.mux_irstart = {
    .count = 6 /* Number of sub entries count */
},
.mux_ucell = {
    .count = 15 /* Number of sub entries count */
},
.mux_icell = {
    .count = 15 /* Number of sub entries count */
},
.mux_slip = {
    .count = 6 /* Number of sub entries count */
},
.phase_ampl_ua = {
    .count = 5 /* Number of sub entries count */
},
.phase_ampl_ub = {
    .count = 5 /* Number of sub entries count */
},
.phase_ampl_uc = {
    .count = 5 /* Number of sub entries count */
},
.zcd_ua = {
    .count = 7 /* Number of sub entries count */
},
.zcd_ub = {
    .count = 7 /* Number of sub entries count */
},
.zcd_uc = {
    .count = 7 /* Number of sub entries count */
},
.zcd_slip = {
    .count = 7 /* Number of sub entries count */
},
.slip = {
    .count = 4 /* Number of sub entries count */
},
.phase_lrm_i_stator = {
    .count = 8 /* Number of sub entries count */
},
.phase_ucell = {
    .count = 8 /* Number of sub entries count */
},
.calc_ucell = {
    .count = 9 /* Number of sub entries count */
},
.calc_icell = {
    .count = 9 /* Number of sub entries count */
},
.rms_ua = {
    .count = 4 /* Number of sub entries count */
},
.rms_ub = {
    .count = 4 /* Number of sub entries count */
},
.rms_uc = {
    .count = 4 /* Number of sub entries count */
},
.rms_ia = {
    .count = 4 /* Number of sub entries count */
},
.rms_ib = {
    .count = 4 /* Number of sub entries count */
},
.rms_ic = {
    .count = 4 /* Number of sub entries count */
},
.rms_cell_ua = {
    .count = 4 /* Number of sub entries count */
},
.rms_cell_ub = {
    .count = 4 /* Number of sub entries count */
},
.rms_cell_uc = {
    .count = 4 /* Number of sub entries count */
},
.rms_cell_ua_phase = {
    .count = 4 /* Number of sub entries count */
},
.rms_cell_ub_phase = {
    .count = 4 /* Number of sub entries count */
},
.rms_cell_uc_phase = {
    .count = 4 /* Number of sub entries count */
},
.rms_cell_ia = {
    .count = 4 /* Number of sub entries count */
},
.rms_cell_ib = {
    .count = 4 /* Number of sub entries count */
},
.rms_cell_ic = {
    .count = 4 /* Number of sub entries count */
},
.mean_iarm = {
    .count = 4 /* Number of sub entries count */
},
.mean_uarm = {
    .count = 4 /* Number of sub entries count */
},
.mean_irstart = {
    .count = 4 /* Number of sub entries count */
},
.mean_rms_icell = {
    .count = 6 /* Number of sub entries count */
},
.sum_s = {
    .count = 6 /* Number of sub entries count */
},
.sum_p = {
    .count = 6 /* Number of sub entries count */
},
.sum_q = {
    .count = 6 /* Number of sub entries count */
},
.power_a = {
    .count = 9 /* Number of sub entries count */
},
.power_b = {
    .count = 9 /* Number of sub entries count */
},
.power_c = {
    .count = 9 /* Number of sub entries count */
},
.power_factor = {
    .count = 8 /* Number of sub entries count */
},
.vr_rms_umains = {
    .count = 11 /* Number of sub entries count */
},
.vr_filter_freq_umains = {
    .count = 11 /* Number of sub entries count */
},
.vr_rms_ucell = {
    .count = 11 /* Number of sub entries count */
},
.cell_cb = {
    .count = 5 /* Number of sub entries count */
},
.thr_run_trig_i_s = {
    .count = 5 /* Number of sub entries count */
},
.am_run_trig_i_s = {
    .count = 5 /* Number of sub entries count */
},
.mux_run_trig = {
    .count = 6 /* Number of sub entries count */
},
.tmr_run_trig = {
    .count = 9 /* Number of sub entries count */
},
.thr_prim_slip = {
    .count = 5 /* Number of sub entries count */
},
.thr_prim_i_s = {
    .count = 5 /* Number of sub entries count */
},
.thr_prim_t = {
    .count = 5 /* Number of sub entries count */
},
.am_prim_field_on = {
    .count = 9 /* Number of sub entries count */
},
.thr_sec_slip = {
    .count = 5 /* Number of sub entries count */
},
.thr_sec_i_s = {
    .count = 5 /* Number of sub entries count */
},
.thr_sec_t = {
    .count = 5 /* Number of sub entries count */
},
.am_sec_field_on = {
    .count = 9 /* Number of sub entries count */
},
.or_field_on = {
    .count = 5 /* Number of sub entries count */
},
.tmr_field_on = {
    .count = 9 /* Number of sub entries count */
},
.thr_value_for_slip_lt_zero = {
    .count = 5 /* Number of sub entries count */
},
.or_value_slip_lt_zero_i_r_sync = {
    .count = 5 /* Number of sub entries count */
},
.and_ready_to_exc = {
    .count = 5 /* Number of sub entries count */
},
.tmr_field_on_rstart_off = {
    .count = 9 /* Number of sub entries count */
},
.not_ready_to_exc = {
    .count = 4 /* Number of sub entries count */
},
.cmp_ctrl_state_is_start = {
    .count = 5 /* Number of sub entries count */
},
.and_rstart_on = {
    .count = 5 /* Number of sub entries count */
},
.thr_field_on_i_r_sync = {
    .count = 5 /* Number of sub entries count */
},
.tmr_field_on_i_r_sync = {
    .count = 9 /* Number of sub entries count */
},
.thr_field_supp_i_r = {
    .count = 5 /* Number of sub entries count */
},
.tmr_field_supp = {
    .count = 5 /* Number of sub entries count */
},
.cnt_start = {
    .count = 3 /* Number of sub entries count */
},
.filter_zcd_ua = {
    .count = 6 /* Number of sub entries count */
},
.filter_zcd_ub = {
    .count = 6 /* Number of sub entries count */
},
.filter_zcd_uc = {
    .count = 6 /* Number of sub entries count */
},
.filter_zcd_slip = {
    .count = 6 /* Number of sub entries count */
},
.filter_freq_ua = {
    .count = 6 /* Number of sub entries count */
},
.filter_freq_ub = {
    .count = 6 /* Number of sub entries count */
},
.filter_freq_uc = {
    .count = 6 /* Number of sub entries count */
},
.filter_freq_slip = {
    .count = 6 /* Number of sub entries count */
},
.filter_mean_iarm = {
    .count = 6 /* Number of sub entries count */
},
.filter_mean_uarm = {
    .count = 6 /* Number of sub entries count */
},
.filter_mean_irstart = {
    .count = 6 /* Number of sub entries count */
},
.tmr_start_min_forcing = {
    .count = 5 /* Number of sub entries count */
},
.tmr_start_max_forcing = {
    .count = 5 /* Number of sub entries count */
},
.tmr_start_stab_forcing = {
    .count = 9 /* Number of sub entries count */
},
.thr_start_q_le_zero = {
    .count = 5 /* Number of sub entries count */
},
.and_start_min_forcing_end = {
    .count = 5 /* Number of sub entries count */
},
.or_start_forcing_end = {
    .count = 5 /* Number of sub entries count */
},
.mux_field_regs = {
    .count = 8 /* Number of sub entries count */
},
.lim_field_regs_curr_ref = {
    .count = 6 /* Number of sub entries count */
},
.mux_field_force_ref = {
    .count = 6 /* Number of sub entries count */
},
.mot_pot_field_test = {
    .count = 9 /* Number of sub entries count */
},
.mot_pot_manual_curr_ref = {
    .count = 9 /* Number of sub entries count */
},
.mux_curr_ref = {
    .count = 8 /* Number of sub entries count */
},
.pid_i = {
    .count = 11 /* Number of sub entries count */
},
.pid_coefs_i = {
    .count = 11 /* Number of sub entries count */
},
.ph3c = {
    .count = 96 /* Number of sub entries count */
},
.lrm = {
    .count = 52 /* Number of sub entries count */
},
.motor = {
    .count = 42 /* Number of sub entries count */
},
.prot = {
    .count = 6 /* Number of sub entries count */
},
.canopen = {
    .count = 2 /* Number of sub entries count */
}
};
