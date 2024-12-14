#ifndef REGS_DATA_H
#define REGS_DATA_H

#include <stdint.h>


// THIS FILE IS GENERATED AUTOMATICALLY!
// DO NOT EDIT THIS FILE!


// user code begin

// user code end

struct _S_regs_data {

struct _S_deviceType {
    uint32_t value; /*  */
} deviceType;

struct _S_errorRegister {
    uint8_t value; /*  */
} errorRegister;

struct _S_pre_definedErrorField {
    uint8_t numberOfErrors; /* Number of sub-entries */
    uint32_t pre_definedErrorField[16]; /*  */
} pre_definedErrorField;

struct _S_COB_ID_SYNCMessage {
    uint32_t value; /*  */
} COB_ID_SYNCMessage;

struct _S_communicationCyclePeriod {
    uint32_t value; /*  */
} communicationCyclePeriod;

struct _S_synchronousWindowLength {
    uint32_t value; /*  */
} synchronousWindowLength;

struct _S_storeParameters {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t storeParameters[4]; /*  */
} storeParameters;

struct _S_restoreDefaultParameters {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t restoreDefaultParameters[4]; /*  */
} restoreDefaultParameters;

struct _S_COB_IDTimeStampObject {
    uint32_t value; /*  */
} COB_IDTimeStampObject;

struct _S_COB_ID_EMCY {
    uint32_t value; /*  */
} COB_ID_EMCY;

struct _S_inhibitTimeEMCY {
    uint16_t value; /*  */
} inhibitTimeEMCY;

struct _S_consumerHeartbeatTime {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t consumerHeartbeatTime[8]; /*  */
} consumerHeartbeatTime;

struct _S_producerHeartbeatTime {
    uint16_t value; /*  */
} producerHeartbeatTime;

struct _S_identity {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t vendor_id; /*  */
    uint32_t productCode; /*  */
    uint32_t revisionNumber; /*  */
    uint32_t serialNumber; /*  */
} identity;

struct _S_synchronousCounterOverflowValue {
    uint8_t value; /*  */
} synchronousCounterOverflowValue;

struct _S_SDOServerParameter {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t COB_IDClientToServer_rx_; /*  */
    uint32_t COB_IDServerToClient_tx_; /*  */
} SDOServerParameter;

struct _S_SDOClientParameter {
    uint8_t count; /* Number of sub-entries */
    uint32_t COB_IDClientToServer_tx_; /*  */
    uint32_t COB_IDServerToClient_rx_; /*  */
    uint8_t node_idOfTheSDOServer; /*  */
} SDOClientParameter;

struct _S_RPDOCommunicationParameter {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t COB_IDUsedByRPDO; /*  */
    uint8_t transmissionType; /*  */
    uint16_t eventTimer; /*  */
} RPDOCommunicationParameter;

struct _S_RPDOCommunicationParameter_1401 {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t COB_IDUsedByRPDO; /*  */
    uint8_t transmissionType; /*  */
    uint16_t eventTimer; /*  */
} RPDOCommunicationParameter_1401;

struct _S_RPDOCommunicationParameter_1402 {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t COB_IDUsedByRPDO; /*  */
    uint8_t transmissionType; /*  */
    uint16_t eventTimer; /*  */
} RPDOCommunicationParameter_1402;

struct _S_RPDOCommunicationParameter_1403 {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t COB_IDUsedByRPDO; /*  */
    uint8_t transmissionType; /*  */
    uint16_t eventTimer; /*  */
} RPDOCommunicationParameter_1403;

struct _S_RPDOMappingParameter {
    uint8_t numberOfMappedApplicationObjectsInPDO; /* Number of sub-entries */
    uint32_t applicationObject1; /*  */
    uint32_t applicationObject2; /*  */
    uint32_t applicationObject3; /*  */
    uint32_t applicationObject4; /*  */
    uint32_t applicationObject5; /*  */
    uint32_t applicationObject6; /*  */
    uint32_t applicationObject7; /*  */
    uint32_t applicationObject8; /*  */
} RPDOMappingParameter;

struct _S_RPDOMappingParameter_1601 {
    uint8_t numberOfMappedApplicationObjectsInPDO; /* Number of sub-entries */
    uint32_t applicationObject1; /*  */
    uint32_t applicationObject2; /*  */
    uint32_t applicationObject3; /*  */
    uint32_t applicationObject4; /*  */
    uint32_t applicationObject5; /*  */
    uint32_t applicationObject6; /*  */
    uint32_t applicationObject7; /*  */
    uint32_t applicationObject8; /*  */
} RPDOMappingParameter_1601;

struct _S_RPDOMappingParameter_1602 {
    uint8_t numberOfMappedApplicationObjectsInPDO; /* Number of sub-entries */
    uint32_t applicationObject1; /*  */
    uint32_t applicationObject2; /*  */
    uint32_t applicationObject3; /*  */
    uint32_t applicationObject4; /*  */
    uint32_t applicationObject5; /*  */
    uint32_t applicationObject6; /*  */
    uint32_t applicationObject7; /*  */
    uint32_t applicationObject8; /*  */
} RPDOMappingParameter_1602;

struct _S_RPDOMappingParameter_1603 {
    uint8_t numberOfMappedApplicationObjectsInPDO; /* Number of sub-entries */
    uint32_t applicationObject1; /*  */
    uint32_t applicationObject2; /*  */
    uint32_t applicationObject3; /*  */
    uint32_t applicationObject4; /*  */
    uint32_t applicationObject5; /*  */
    uint32_t applicationObject6; /*  */
    uint32_t applicationObject7; /*  */
    uint32_t applicationObject8; /*  */
} RPDOMappingParameter_1603;

struct _S_TPDOCommunicationParameter {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t COB_IDUsedByTPDO; /*  */
    uint8_t transmissionType; /*  */
    uint16_t inhibitTime; /*  */
    uint16_t eventTimer; /*  */
    uint8_t SYNCStartValue; /*  */
} TPDOCommunicationParameter;

struct _S_TPDOCommunicationParameter_1801 {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t COB_IDUsedByTPDO; /*  */
    uint8_t transmissionType; /*  */
    uint16_t inhibitTime; /*  */
    uint16_t eventTimer; /*  */
    uint8_t SYNCStartValue; /*  */
} TPDOCommunicationParameter_1801;

struct _S_TPDOCommunicationParameter_1802 {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t COB_IDUsedByTPDO; /*  */
    uint8_t transmissionType; /*  */
    uint16_t inhibitTime; /*  */
    uint16_t eventTimer; /*  */
    uint8_t SYNCStartValue; /*  */
} TPDOCommunicationParameter_1802;

struct _S_TPDOCommunicationParameter_1803 {
    uint8_t highestSub_indexSupported; /* Number of sub-entries */
    uint32_t COB_IDUsedByTPDO; /*  */
    uint8_t transmissionType; /*  */
    uint16_t inhibitTime; /*  */
    uint16_t eventTimer; /*  */
    uint8_t SYNCStartValue; /*  */
} TPDOCommunicationParameter_1803;

struct _S_TPDOMappingParameter {
    uint8_t numberOfMappedApplicationObjectsInPDO; /* Number of sub-entries */
    uint32_t applicationObject1; /*  */
    uint32_t applicationObject2; /*  */
    uint32_t applicationObject3; /*  */
    uint32_t applicationObject4; /*  */
    uint32_t applicationObject5; /*  */
    uint32_t applicationObject6; /*  */
    uint32_t applicationObject7; /*  */
    uint32_t applicationObject8; /*  */
} TPDOMappingParameter;

struct _S_TPDOMappingParameter_1a01 {
    uint8_t numberOfMappedApplicationObjectsInPDO; /* Number of sub-entries */
    uint32_t applicationObject1; /*  */
    uint32_t applicationObject2; /*  */
    uint32_t applicationObject3; /*  */
    uint32_t applicationObject4; /*  */
    uint32_t applicationObject5; /*  */
    uint32_t applicationObject6; /*  */
    uint32_t applicationObject7; /*  */
    uint32_t applicationObject8; /*  */
} TPDOMappingParameter_1a01;

struct _S_TPDOMappingParameter_1a02 {
    uint8_t numberOfMappedApplicationObjectsInPDO; /* Number of sub-entries */
    uint32_t applicationObject1; /*  */
    uint32_t applicationObject2; /*  */
    uint32_t applicationObject3; /*  */
    uint32_t applicationObject4; /*  */
    uint32_t applicationObject5; /*  */
    uint32_t applicationObject6; /*  */
    uint32_t applicationObject7; /*  */
    uint32_t applicationObject8; /*  */
} TPDOMappingParameter_1a02;

struct _S_TPDOMappingParameter_1a03 {
    uint8_t numberOfMappedApplicationObjectsInPDO; /* Number of sub-entries */
    uint32_t applicationObject1; /*  */
    uint32_t applicationObject2; /*  */
    uint32_t applicationObject3; /*  */
    uint32_t applicationObject4; /*  */
    uint32_t applicationObject5; /*  */
    uint32_t applicationObject6; /*  */
    uint32_t applicationObject7; /*  */
    uint32_t applicationObject8; /*  */
} TPDOMappingParameter_1a03;

struct _S_sys {
    uint8_t count; /* Number of sub entries count */
} sys;

struct _S_sys_cmd {
    uint8_t count; /* Number of sub entries count */
} sys_cmd;

struct _S_sys_ctrl {
    uint8_t count; /* Number of sub entries count */
} sys_ctrl;

struct _S_sys_stat {
    uint8_t count; /* Number of sub entries count */
} sys_stat;

struct _S_conf {
    uint8_t count; /* Number of sub entries count */
} conf;

struct _S_adc {
    uint8_t count; /* Number of sub entries count */
} adc;

struct _S_adc_model {
    uint8_t count; /* Number of sub entries count */
} adc_model;

struct _S_adc_tim {
    uint8_t count; /* Number of sub entries count */
} adc_tim;

struct _S_sys_tim {
    uint8_t count; /* Number of sub entries count */
} sys_tim;

struct _S_ms_tim {
    uint8_t count; /* Number of sub entries count */
} ms_tim;

struct _S_net_tim {
    uint8_t count; /* Number of sub entries count */
} net_tim;

struct _S_sys_time {
    uint8_t count; /* Number of sub entries count */
} sys_time;

struct _S_tmr_sys_fsm {
    uint8_t count; /* Number of sub entries count */
} tmr_sys_fsm;

struct _S_dlog {
    uint8_t count; /* Number of sub entries count */
} dlog;

struct _S_sys_calc {
    uint8_t count; /* Number of sub entries count */
} sys_calc;

struct _S_rect_curr {
    uint8_t count; /* Number of sub entries count */
} rect_curr;

struct _S_mux_umains {
    uint8_t count; /* Number of sub entries count */
} mux_umains;

struct _S_mux_imains {
    uint8_t count; /* Number of sub entries count */
} mux_imains;

struct _S_mux_uarm {
    uint8_t count; /* Number of sub entries count */
} mux_uarm;

struct _S_mux_iarm {
    uint8_t count; /* Number of sub entries count */
} mux_iarm;

struct _S_mux_irstart {
    uint8_t count; /* Number of sub entries count */
} mux_irstart;

struct _S_mux_ucell {
    uint8_t count; /* Number of sub entries count */
} mux_ucell;

struct _S_mux_icell {
    uint8_t count; /* Number of sub entries count */
} mux_icell;

struct _S_mux_slip {
    uint8_t count; /* Number of sub entries count */
} mux_slip;

struct _S_phase_ampl_ua {
    uint8_t count; /* Number of sub entries count */
} phase_ampl_ua;

struct _S_phase_ampl_ub {
    uint8_t count; /* Number of sub entries count */
} phase_ampl_ub;

struct _S_phase_ampl_uc {
    uint8_t count; /* Number of sub entries count */
} phase_ampl_uc;

struct _S_zcd_ua {
    uint8_t count; /* Number of sub entries count */
} zcd_ua;

struct _S_zcd_ub {
    uint8_t count; /* Number of sub entries count */
} zcd_ub;

struct _S_zcd_uc {
    uint8_t count; /* Number of sub entries count */
} zcd_uc;

struct _S_zcd_slip {
    uint8_t count; /* Number of sub entries count */
} zcd_slip;

struct _S_slip {
    uint8_t count; /* Number of sub entries count */
} slip;

struct _S_phase_lrm_i_stator {
    uint8_t count; /* Number of sub entries count */
} phase_lrm_i_stator;

struct _S_phase_ucell {
    uint8_t count; /* Number of sub entries count */
} phase_ucell;

struct _S_calc_ucell {
    uint8_t count; /* Number of sub entries count */
} calc_ucell;

struct _S_calc_icell {
    uint8_t count; /* Number of sub entries count */
} calc_icell;

struct _S_rms_ua {
    uint8_t count; /* Number of sub entries count */
} rms_ua;

struct _S_rms_ub {
    uint8_t count; /* Number of sub entries count */
} rms_ub;

struct _S_rms_uc {
    uint8_t count; /* Number of sub entries count */
} rms_uc;

struct _S_rms_ia {
    uint8_t count; /* Number of sub entries count */
} rms_ia;

struct _S_rms_ib {
    uint8_t count; /* Number of sub entries count */
} rms_ib;

struct _S_rms_ic {
    uint8_t count; /* Number of sub entries count */
} rms_ic;

struct _S_rms_cell_ua {
    uint8_t count; /* Number of sub entries count */
} rms_cell_ua;

struct _S_rms_cell_ub {
    uint8_t count; /* Number of sub entries count */
} rms_cell_ub;

struct _S_rms_cell_uc {
    uint8_t count; /* Number of sub entries count */
} rms_cell_uc;

struct _S_rms_cell_ua_phase {
    uint8_t count; /* Number of sub entries count */
} rms_cell_ua_phase;

struct _S_rms_cell_ub_phase {
    uint8_t count; /* Number of sub entries count */
} rms_cell_ub_phase;

struct _S_rms_cell_uc_phase {
    uint8_t count; /* Number of sub entries count */
} rms_cell_uc_phase;

struct _S_rms_cell_ia {
    uint8_t count; /* Number of sub entries count */
} rms_cell_ia;

struct _S_rms_cell_ib {
    uint8_t count; /* Number of sub entries count */
} rms_cell_ib;

struct _S_rms_cell_ic {
    uint8_t count; /* Number of sub entries count */
} rms_cell_ic;

struct _S_mean_iarm {
    uint8_t count; /* Number of sub entries count */
} mean_iarm;

struct _S_mean_uarm {
    uint8_t count; /* Number of sub entries count */
} mean_uarm;

struct _S_mean_irstart {
    uint8_t count; /* Number of sub entries count */
} mean_irstart;

struct _S_mean_rms_icell {
    uint8_t count; /* Number of sub entries count */
} mean_rms_icell;

struct _S_sum_s {
    uint8_t count; /* Number of sub entries count */
} sum_s;

struct _S_sum_p {
    uint8_t count; /* Number of sub entries count */
} sum_p;

struct _S_sum_q {
    uint8_t count; /* Number of sub entries count */
} sum_q;

struct _S_power_a {
    uint8_t count; /* Number of sub entries count */
} power_a;

struct _S_power_b {
    uint8_t count; /* Number of sub entries count */
} power_b;

struct _S_power_c {
    uint8_t count; /* Number of sub entries count */
} power_c;

struct _S_power_factor {
    uint8_t count; /* Number of sub entries count */
} power_factor;

struct _S_vr_rms_umains {
    uint8_t count; /* Number of sub entries count */
} vr_rms_umains;

struct _S_vr_filter_freq_umains {
    uint8_t count; /* Number of sub entries count */
} vr_filter_freq_umains;

struct _S_vr_rms_ucell {
    uint8_t count; /* Number of sub entries count */
} vr_rms_ucell;

struct _S_cell_cb {
    uint8_t count; /* Number of sub entries count */
} cell_cb;

struct _S_thr_run_trig_i_s {
    uint8_t count; /* Number of sub entries count */
} thr_run_trig_i_s;

struct _S_am_run_trig_i_s {
    uint8_t count; /* Number of sub entries count */
} am_run_trig_i_s;

struct _S_mux_run_trig {
    uint8_t count; /* Number of sub entries count */
} mux_run_trig;

struct _S_tmr_run_trig {
    uint8_t count; /* Number of sub entries count */
} tmr_run_trig;

struct _S_thr_prim_slip {
    uint8_t count; /* Number of sub entries count */
} thr_prim_slip;

struct _S_thr_prim_i_s {
    uint8_t count; /* Number of sub entries count */
} thr_prim_i_s;

struct _S_thr_prim_t {
    uint8_t count; /* Number of sub entries count */
} thr_prim_t;

struct _S_am_prim_field_on {
    uint8_t count; /* Number of sub entries count */
} am_prim_field_on;

struct _S_thr_sec_slip {
    uint8_t count; /* Number of sub entries count */
} thr_sec_slip;

struct _S_thr_sec_i_s {
    uint8_t count; /* Number of sub entries count */
} thr_sec_i_s;

struct _S_thr_sec_t {
    uint8_t count; /* Number of sub entries count */
} thr_sec_t;

struct _S_am_sec_field_on {
    uint8_t count; /* Number of sub entries count */
} am_sec_field_on;

struct _S_or_field_on {
    uint8_t count; /* Number of sub entries count */
} or_field_on;

struct _S_tmr_field_on {
    uint8_t count; /* Number of sub entries count */
} tmr_field_on;

struct _S_thr_value_for_slip_lt_zero {
    uint8_t count; /* Number of sub entries count */
} thr_value_for_slip_lt_zero;

struct _S_or_value_slip_lt_zero_i_r_sync {
    uint8_t count; /* Number of sub entries count */
} or_value_slip_lt_zero_i_r_sync;

struct _S_and_ready_to_exc {
    uint8_t count; /* Number of sub entries count */
} and_ready_to_exc;

struct _S_tmr_field_on_rstart_off {
    uint8_t count; /* Number of sub entries count */
} tmr_field_on_rstart_off;

struct _S_not_ready_to_exc {
    uint8_t count; /* Number of sub entries count */
} not_ready_to_exc;

struct _S_cmp_ctrl_state_is_start {
    uint8_t count; /* Number of sub entries count */
} cmp_ctrl_state_is_start;

struct _S_and_rstart_on {
    uint8_t count; /* Number of sub entries count */
} and_rstart_on;

struct _S_thr_field_on_i_r_sync {
    uint8_t count; /* Number of sub entries count */
} thr_field_on_i_r_sync;

struct _S_tmr_field_on_i_r_sync {
    uint8_t count; /* Number of sub entries count */
} tmr_field_on_i_r_sync;

struct _S_thr_field_supp_i_r {
    uint8_t count; /* Number of sub entries count */
} thr_field_supp_i_r;

struct _S_tmr_field_supp {
    uint8_t count; /* Number of sub entries count */
} tmr_field_supp;

struct _S_cnt_start {
    uint8_t count; /* Number of sub entries count */
} cnt_start;

struct _S_filter_zcd_ua {
    uint8_t count; /* Number of sub entries count */
} filter_zcd_ua;

struct _S_filter_zcd_ub {
    uint8_t count; /* Number of sub entries count */
} filter_zcd_ub;

struct _S_filter_zcd_uc {
    uint8_t count; /* Number of sub entries count */
} filter_zcd_uc;

struct _S_filter_zcd_slip {
    uint8_t count; /* Number of sub entries count */
} filter_zcd_slip;

struct _S_filter_freq_ua {
    uint8_t count; /* Number of sub entries count */
} filter_freq_ua;

struct _S_filter_freq_ub {
    uint8_t count; /* Number of sub entries count */
} filter_freq_ub;

struct _S_filter_freq_uc {
    uint8_t count; /* Number of sub entries count */
} filter_freq_uc;

struct _S_filter_freq_slip {
    uint8_t count; /* Number of sub entries count */
} filter_freq_slip;

struct _S_filter_mean_iarm {
    uint8_t count; /* Number of sub entries count */
} filter_mean_iarm;

struct _S_filter_mean_uarm {
    uint8_t count; /* Number of sub entries count */
} filter_mean_uarm;

struct _S_filter_mean_irstart {
    uint8_t count; /* Number of sub entries count */
} filter_mean_irstart;

struct _S_tmr_start_min_forcing {
    uint8_t count; /* Number of sub entries count */
} tmr_start_min_forcing;

struct _S_tmr_start_max_forcing {
    uint8_t count; /* Number of sub entries count */
} tmr_start_max_forcing;

struct _S_tmr_start_stab_forcing {
    uint8_t count; /* Number of sub entries count */
} tmr_start_stab_forcing;

struct _S_thr_start_q_le_zero {
    uint8_t count; /* Number of sub entries count */
} thr_start_q_le_zero;

struct _S_and_start_min_forcing_end {
    uint8_t count; /* Number of sub entries count */
} and_start_min_forcing_end;

struct _S_or_start_forcing_end {
    uint8_t count; /* Number of sub entries count */
} or_start_forcing_end;

struct _S_mux_field_regs {
    uint8_t count; /* Number of sub entries count */
} mux_field_regs;

struct _S_lim_field_regs_curr_ref {
    uint8_t count; /* Number of sub entries count */
} lim_field_regs_curr_ref;

struct _S_mux_field_force_ref {
    uint8_t count; /* Number of sub entries count */
} mux_field_force_ref;

struct _S_mot_pot_field_test {
    uint8_t count; /* Number of sub entries count */
} mot_pot_field_test;

struct _S_mot_pot_manual_curr_ref {
    uint8_t count; /* Number of sub entries count */
} mot_pot_manual_curr_ref;

struct _S_mux_curr_ref {
    uint8_t count; /* Number of sub entries count */
} mux_curr_ref;

struct _S_pid_i {
    uint8_t count; /* Number of sub entries count */
} pid_i;

struct _S_pid_coefs_i {
    uint8_t count; /* Number of sub entries count */
} pid_coefs_i;

struct _S_ph3c {
    uint8_t count; /* Number of sub entries count */
} ph3c;

struct _S_lrm {
    uint8_t count; /* Number of sub entries count */
} lrm;

struct _S_motor {
    uint8_t count; /* Number of sub entries count */
} motor;

struct _S_prot {
    uint8_t count; /* Number of sub entries count */
} prot;

struct _S_canopen {
    uint8_t count; /* Number of sub entries count */
} canopen;

};
extern struct _S_regs_data regs_data;


#endif /* REGS_DATA_H */
