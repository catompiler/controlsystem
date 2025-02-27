#define OD_DEFINITION
#include "301/CO_ODinterface.h"
#include "OD.h"

#if CO_VERSION_MAJOR < 4
#error This Object dictionary is compatible with CANopenNode V4.0 and above!
#endif


#include "regs_data.h"

// user code begin
// Модули.
#include "modules/modules.h"
// user code end

// All OD objects (constant definitions)
typedef struct {
    OD_obj_var_t o_1000_deviceType;
    OD_obj_var_t o_1001_errorRegister;
    OD_obj_array_t o_1003_pre_definedErrorField;
    OD_obj_var_t o_1005_COB_ID_SYNCMessage;
    OD_obj_var_t o_1006_communicationCyclePeriod;
    OD_obj_var_t o_1007_synchronousWindowLength;
    OD_obj_array_t o_1010_storeParameters;
    OD_obj_array_t o_1011_restoreDefaultParameters;
    OD_obj_var_t o_1012_COB_IDTimeStampObject;
    OD_obj_var_t o_1014_COB_ID_EMCY;
    OD_obj_var_t o_1015_inhibitTimeEMCY;
    OD_obj_array_t o_1016_consumerHeartbeatTime;
    OD_obj_var_t o_1017_producerHeartbeatTime;
    OD_obj_record_t o_1018_identity[5];
    OD_obj_var_t o_1019_synchronousCounterOverflowValue;
    OD_obj_record_t o_1200_SDOServerParameter[3];
    OD_obj_record_t o_1201_SDOServerParameter[3];
    OD_obj_record_t o_1280_SDOClientParameter[4];
    OD_obj_record_t o_1400_RPDOCommunicationParameter[4];
    OD_obj_record_t o_1401_RPDOCommunicationParameter[4];
    OD_obj_record_t o_1402_RPDOCommunicationParameter[4];
    OD_obj_record_t o_1403_RPDOCommunicationParameter[4];
    OD_obj_record_t o_1600_RPDOMappingParameter[9];
    OD_obj_record_t o_1601_RPDOMappingParameter[9];
    OD_obj_record_t o_1602_RPDOMappingParameter[9];
    OD_obj_record_t o_1603_RPDOMappingParameter[9];
    OD_obj_record_t o_1800_TPDOCommunicationParameter[6];
    OD_obj_record_t o_1801_TPDOCommunicationParameter[6];
    OD_obj_record_t o_1802_TPDOCommunicationParameter[6];
    OD_obj_record_t o_1803_TPDOCommunicationParameter[6];
    OD_obj_record_t o_1A00_TPDOMappingParameter[9];
    OD_obj_record_t o_1A01_TPDOMappingParameter[9];
    OD_obj_record_t o_1A02_TPDOMappingParameter[9];
    OD_obj_record_t o_1A03_TPDOMappingParameter[9];
    OD_obj_record_t o_2000_sys[12];
    OD_obj_record_t o_2010_sys_cmd[4];
    OD_obj_record_t o_2020_sys_ctrl[12];
    OD_obj_record_t o_2030_sys_stat[4];
    OD_obj_record_t o_2040_conf[15];
    OD_obj_record_t o_2050_adc[63];
    OD_obj_record_t o_2060_dac[5];
    OD_obj_record_t o_2070_adc_model[31];
    OD_obj_record_t o_2080_adc_tim[4];
    OD_obj_record_t o_2090_sys_tim[4];
    OD_obj_record_t o_20A0_ms_tim[4];
    OD_obj_record_t o_20B0_net_tim[4];
    OD_obj_record_t o_20C0_sys_time[6];
    OD_obj_record_t o_20D0_tmr_sys_fsm[6];
    OD_obj_record_t o_20E0_dlog[54];
    OD_obj_record_t o_20F0_sys_calc[3];
    OD_obj_record_t o_2100_rect_curr[7];
    OD_obj_record_t o_2110_mux_umains[16];
    OD_obj_record_t o_2120_mux_imains[16];
    OD_obj_record_t o_2130_mux_uarm[7];
    OD_obj_record_t o_2140_mux_iarm[8];
    OD_obj_record_t o_2150_mux_irstart[7];
    OD_obj_record_t o_2160_mux_ucell[16];
    OD_obj_record_t o_2170_mux_icell[16];
    OD_obj_record_t o_2180_mux_slip[7];
    OD_obj_record_t o_2190_phase_ampl_ua[6];
    OD_obj_record_t o_21A0_phase_ampl_ub[6];
    OD_obj_record_t o_21B0_phase_ampl_uc[6];
    OD_obj_record_t o_21C0_zcd_ua[8];
    OD_obj_record_t o_21D0_zcd_ub[8];
    OD_obj_record_t o_21E0_zcd_uc[8];
    OD_obj_record_t o_21F0_zcd_slip[8];
    OD_obj_record_t o_2200_slip[5];
    OD_obj_record_t o_2210_phase_lrm_i_stator[9];
    OD_obj_record_t o_2220_phase_ucell[9];
    OD_obj_record_t o_2230_calc_ucell[10];
    OD_obj_record_t o_2240_calc_icell[10];
    OD_obj_record_t o_2250_rms_ua[5];
    OD_obj_record_t o_2260_rms_ub[5];
    OD_obj_record_t o_2270_rms_uc[5];
    OD_obj_record_t o_2280_rms_ia[5];
    OD_obj_record_t o_2290_rms_ib[5];
    OD_obj_record_t o_22A0_rms_ic[5];
    OD_obj_record_t o_22B0_rms_cell_ua[5];
    OD_obj_record_t o_22C0_rms_cell_ub[5];
    OD_obj_record_t o_22D0_rms_cell_uc[5];
    OD_obj_record_t o_22E0_rms_cell_ua_phase[5];
    OD_obj_record_t o_22F0_rms_cell_ub_phase[5];
    OD_obj_record_t o_2300_rms_cell_uc_phase[5];
    OD_obj_record_t o_2310_rms_cell_ia[5];
    OD_obj_record_t o_2320_rms_cell_ib[5];
    OD_obj_record_t o_2330_rms_cell_ic[5];
    OD_obj_record_t o_2340_mean_iarm[5];
    OD_obj_record_t o_2350_mean_uarm[5];
    OD_obj_record_t o_2360_mean_irstart[5];
    OD_obj_record_t o_2370_mean_rms_icell[7];
    OD_obj_record_t o_2380_sum_s[7];
    OD_obj_record_t o_2390_sum_p[7];
    OD_obj_record_t o_23A0_sum_q[7];
    OD_obj_record_t o_23B0_power_a[10];
    OD_obj_record_t o_23C0_power_b[10];
    OD_obj_record_t o_23D0_power_c[10];
    OD_obj_record_t o_23E0_power_factor[9];
    OD_obj_record_t o_23F0_vr_rms_umains[12];
    OD_obj_record_t o_2400_vr_filter_freq_umains[12];
    OD_obj_record_t o_2410_vr_rms_ucell[12];
    OD_obj_record_t o_2420_cell_cb[6];
    OD_obj_record_t o_2430_run_trig[4];
    OD_obj_record_t o_2440_thr_run_trig_i_s[6];
    OD_obj_record_t o_2450_am_run_trig_i_s[6];
    OD_obj_record_t o_2460_tmr_run_trig[10];
    OD_obj_record_t o_2470_thr_prim_slip[6];
    OD_obj_record_t o_2480_thr_prim_i_s[6];
    OD_obj_record_t o_2490_thr_prim_t[6];
    OD_obj_record_t o_24A0_am_prim_field_on[10];
    OD_obj_record_t o_24B0_thr_sec_slip[6];
    OD_obj_record_t o_24C0_thr_sec_i_s[6];
    OD_obj_record_t o_24D0_thr_sec_t[6];
    OD_obj_record_t o_24E0_am_sec_field_on[10];
    OD_obj_record_t o_24F0_or_field_on[6];
    OD_obj_record_t o_2500_tmr_field_on[10];
    OD_obj_record_t o_2510_thr_value_for_slip_lt_zero[6];
    OD_obj_record_t o_2520_or_value_slip_lt_zero_i_r_sync[6];
    OD_obj_record_t o_2530_and_ready_to_exc[6];
    OD_obj_record_t o_2540_tmr_field_on_rstart_off[10];
    OD_obj_record_t o_2550_not_ready_to_exc[5];
    OD_obj_record_t o_2560_cmp_ctrl_state_is_start[6];
    OD_obj_record_t o_2570_and_rstart_on[6];
    OD_obj_record_t o_2580_thr_field_on_i_r_sync[6];
    OD_obj_record_t o_2590_tmr_field_on_i_r_sync[10];
    OD_obj_record_t o_25A0_thr_field_supp_i_r[6];
    OD_obj_record_t o_25B0_tmr_field_supp[6];
    OD_obj_record_t o_25C0_cnt_start[4];
    OD_obj_record_t o_25D0_filter_zcd_ua[7];
    OD_obj_record_t o_25E0_filter_zcd_ub[7];
    OD_obj_record_t o_25F0_filter_zcd_uc[7];
    OD_obj_record_t o_2600_filter_zcd_slip[7];
    OD_obj_record_t o_2610_filter_freq_ua[7];
    OD_obj_record_t o_2620_filter_freq_ub[7];
    OD_obj_record_t o_2630_filter_freq_uc[7];
    OD_obj_record_t o_2640_filter_freq_slip[7];
    OD_obj_record_t o_2650_filter_mean_iarm[7];
    OD_obj_record_t o_2660_filter_mean_uarm[7];
    OD_obj_record_t o_2670_filter_mean_irstart[7];
    OD_obj_record_t o_2680_tmr_start_min_forcing[6];
    OD_obj_record_t o_2690_tmr_start_max_forcing[6];
    OD_obj_record_t o_26A0_tmr_start_stab_forcing[10];
    OD_obj_record_t o_26B0_thr_start_q_le_zero[6];
    OD_obj_record_t o_26C0_and_start_min_forcing_end[6];
    OD_obj_record_t o_26D0_or_start_forcing_end[6];
    OD_obj_record_t o_26E0_mux_field_regs[9];
    OD_obj_record_t o_26F0_lim_field_regs_curr_ref[7];
    OD_obj_record_t o_2700_mux_field_force_ref[7];
    OD_obj_record_t o_2710_mot_pot_field_test[10];
    OD_obj_record_t o_2720_mot_pot_manual_curr_ref[10];
    OD_obj_record_t o_2730_mux_curr_ref[9];
    OD_obj_record_t o_2740_pid_i[12];
    OD_obj_record_t o_2750_pid_coefs_i[12];
    OD_obj_record_t o_2760_ph3c[97];
    OD_obj_record_t o_2770_triacs[11];
    OD_obj_record_t o_2780_lrm[53];
    OD_obj_record_t o_2790_motor[43];
    OD_obj_record_t o_27A0_prot[87];
    OD_obj_record_t o_27B0_canopen[3];
    OD_obj_record_t o_27C0_storage[3];
    OD_obj_record_t o_27D0_settings[4];
} ODObjs_t;

static CO_PROGMEM ODObjs_t ODObjs = {
.o_1000_deviceType = {
    .dataOrig = &regs_data.deviceType.value,
    .attribute = ODA_MB,
    .dataLength = 4
},
.o_1001_errorRegister = {
    .dataOrig = &regs_data.errorRegister.value,
    .attribute = ODA_TPDO,
    .dataLength = 1
},
.o_1003_pre_definedErrorField = {
    .dataOrig0 = &regs_data.pre_definedErrorField.numberOfErrors,
    .dataOrig = &regs_data.pre_definedErrorField.pre_definedErrorField[0],
    .attribute0 = ODA_SDO_RW,
    .attribute = ODA_SDO_R,
    .dataElementLength = 4,
    .dataElementSizeof = sizeof(uint32_t)
},
.o_1005_COB_ID_SYNCMessage = {
    .dataOrig = &regs_data.COB_ID_SYNCMessage.value,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
},
.o_1006_communicationCyclePeriod = {
    .dataOrig = &regs_data.communicationCyclePeriod.value,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
},
.o_1007_synchronousWindowLength = {
    .dataOrig = &regs_data.synchronousWindowLength.value,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
},
.o_1010_storeParameters = {
    .dataOrig0 = &regs_data.storeParameters.highestSub_indexSupported,
    .dataOrig = &regs_data.storeParameters.storeParameters[0],
    .attribute0 = ODA_SDO_R,
    .attribute = ODA_SDO_RW,
    .dataElementLength = 4,
    .dataElementSizeof = sizeof(uint32_t)
},
.o_1011_restoreDefaultParameters = {
    .dataOrig0 = &regs_data.restoreDefaultParameters.highestSub_indexSupported,
    .dataOrig = &regs_data.restoreDefaultParameters.restoreDefaultParameters[0],
    .attribute0 = ODA_SDO_R,
    .attribute = ODA_SDO_RW,
    .dataElementLength = 4,
    .dataElementSizeof = sizeof(uint32_t)
},
.o_1012_COB_IDTimeStampObject = {
    .dataOrig = &regs_data.COB_IDTimeStampObject.value,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
},
.o_1014_COB_ID_EMCY = {
    .dataOrig = &regs_data.COB_ID_EMCY.value,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
},
.o_1015_inhibitTimeEMCY = {
    .dataOrig = &regs_data.inhibitTimeEMCY.value,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
},
.o_1016_consumerHeartbeatTime = {
    .dataOrig0 = &regs_data.consumerHeartbeatTime.highestSub_indexSupported,
    .dataOrig = &regs_data.consumerHeartbeatTime.consumerHeartbeatTime[0],
    .attribute0 = ODA_SDO_R,
    .attribute = ODA_SDO_RW,
    .dataElementLength = 4,
    .dataElementSizeof = sizeof(uint32_t)
},
.o_1017_producerHeartbeatTime = {
    .dataOrig = &regs_data.producerHeartbeatTime.value,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
},
.o_1018_identity = {
    {
    .dataOrig = &regs_data.identity.highestSub_indexSupported,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.identity.vendor_id,
    .subIndex = 1,
    .attribute = ODA_SDO_R | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.identity.productCode,
    .subIndex = 2,
    .attribute = ODA_SDO_R | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.identity.revisionNumber,
    .subIndex = 3,
    .attribute = ODA_SDO_R | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.identity.serialNumber,
    .subIndex = 4,
    .attribute = ODA_SDO_R | ODA_MB,
    .dataLength = 4
    }
},
.o_1019_synchronousCounterOverflowValue = {
    .dataOrig = &regs_data.synchronousCounterOverflowValue.value,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
},
.o_1200_SDOServerParameter = {
    {
    .dataOrig = &regs_data.SDOServerParameter.highestSub_indexSupported,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.SDOServerParameter.COB_IDClientToServer_rx_,
    .subIndex = 1,
    .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.SDOServerParameter.COB_IDServerToClient_tx_,
    .subIndex = 2,
    .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
    .dataLength = 4
    }
},
.o_1201_SDOServerParameter = {
    {
    .dataOrig = &regs_data.SDOServerParameter_1201.highestSub_indexSupported,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.SDOServerParameter_1201.COB_IDClientToServer_rx_,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_TPDO | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.SDOServerParameter_1201.COB_IDServerToClient_tx_,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_TPDO | ODA_MB,
    .dataLength = 4
    }
},
.o_1280_SDOClientParameter = {
    {
    .dataOrig = &regs_data.SDOClientParameter.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.SDOClientParameter.COB_IDClientToServer_tx_,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.SDOClientParameter.COB_IDServerToClient_rx_,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.SDOClientParameter.node_idOfTheSDOServer,
    .subIndex = 3,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    }
},
.o_1400_RPDOCommunicationParameter = {
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter.highestSub_indexSupported,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter.COB_IDUsedByRPDO,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter.transmissionType,
    .subIndex = 2,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter.eventTimer,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    }
},
.o_1401_RPDOCommunicationParameter = {
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1401.highestSub_indexSupported,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1401.COB_IDUsedByRPDO,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1401.transmissionType,
    .subIndex = 2,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1401.eventTimer,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    }
},
.o_1402_RPDOCommunicationParameter = {
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1402.highestSub_indexSupported,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1402.COB_IDUsedByRPDO,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1402.transmissionType,
    .subIndex = 2,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1402.eventTimer,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    }
},
.o_1403_RPDOCommunicationParameter = {
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1403.highestSub_indexSupported,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1403.COB_IDUsedByRPDO,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1403.transmissionType,
    .subIndex = 2,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOCommunicationParameter_1403.eventTimer,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    }
},
.o_1600_RPDOMappingParameter = {
    {
    .dataOrig = &regs_data.RPDOMappingParameter.numberOfMappedApplicationObjectsInPDO,
    .subIndex = 0,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter.applicationObject1,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter.applicationObject2,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter.applicationObject3,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter.applicationObject4,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter.applicationObject5,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter.applicationObject6,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter.applicationObject7,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter.applicationObject8,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_1601_RPDOMappingParameter = {
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1601.numberOfMappedApplicationObjectsInPDO,
    .subIndex = 0,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1601.applicationObject1,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1601.applicationObject2,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1601.applicationObject3,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1601.applicationObject4,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1601.applicationObject5,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1601.applicationObject6,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1601.applicationObject7,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1601.applicationObject8,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_1602_RPDOMappingParameter = {
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1602.numberOfMappedApplicationObjectsInPDO,
    .subIndex = 0,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1602.applicationObject1,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1602.applicationObject2,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1602.applicationObject3,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1602.applicationObject4,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1602.applicationObject5,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1602.applicationObject6,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1602.applicationObject7,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1602.applicationObject8,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_1603_RPDOMappingParameter = {
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1603.numberOfMappedApplicationObjectsInPDO,
    .subIndex = 0,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1603.applicationObject1,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1603.applicationObject2,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1603.applicationObject3,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1603.applicationObject4,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1603.applicationObject5,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1603.applicationObject6,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1603.applicationObject7,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.RPDOMappingParameter_1603.applicationObject8,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_1800_TPDOCommunicationParameter = {
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter.highestSub_indexSupported,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter.COB_IDUsedByTPDO,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter.transmissionType,
    .subIndex = 2,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter.inhibitTime,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter.eventTimer,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter.SYNCStartValue,
    .subIndex = 6,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    }
},
.o_1801_TPDOCommunicationParameter = {
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1801.highestSub_indexSupported,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1801.COB_IDUsedByTPDO,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1801.transmissionType,
    .subIndex = 2,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1801.inhibitTime,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1801.eventTimer,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1801.SYNCStartValue,
    .subIndex = 6,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    }
},
.o_1802_TPDOCommunicationParameter = {
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1802.highestSub_indexSupported,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1802.COB_IDUsedByTPDO,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1802.transmissionType,
    .subIndex = 2,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1802.inhibitTime,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1802.eventTimer,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1802.SYNCStartValue,
    .subIndex = 6,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    }
},
.o_1803_TPDOCommunicationParameter = {
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1803.highestSub_indexSupported,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1803.COB_IDUsedByTPDO,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1803.transmissionType,
    .subIndex = 2,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1803.inhibitTime,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1803.eventTimer,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 2
    },
    {
    .dataOrig = &regs_data.TPDOCommunicationParameter_1803.SYNCStartValue,
    .subIndex = 6,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    }
},
.o_1A00_TPDOMappingParameter = {
    {
    .dataOrig = &regs_data.TPDOMappingParameter.numberOfMappedApplicationObjectsInPDO,
    .subIndex = 0,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter.applicationObject1,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter.applicationObject2,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter.applicationObject3,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter.applicationObject4,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter.applicationObject5,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter.applicationObject6,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter.applicationObject7,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter.applicationObject8,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_1A01_TPDOMappingParameter = {
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a01.numberOfMappedApplicationObjectsInPDO,
    .subIndex = 0,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a01.applicationObject1,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a01.applicationObject2,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a01.applicationObject3,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a01.applicationObject4,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a01.applicationObject5,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a01.applicationObject6,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a01.applicationObject7,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a01.applicationObject8,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_1A02_TPDOMappingParameter = {
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a02.numberOfMappedApplicationObjectsInPDO,
    .subIndex = 0,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a02.applicationObject1,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a02.applicationObject2,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a02.applicationObject3,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a02.applicationObject4,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a02.applicationObject5,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a02.applicationObject6,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a02.applicationObject7,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a02.applicationObject8,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_1A03_TPDOMappingParameter = {
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a03.numberOfMappedApplicationObjectsInPDO,
    .subIndex = 0,
    .attribute = ODA_SDO_RW,
    .dataLength = 1
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a03.applicationObject1,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a03.applicationObject2,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a03.applicationObject3,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a03.applicationObject4,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a03.applicationObject5,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a03.applicationObject6,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a03.applicationObject7,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &regs_data.TPDOMappingParameter_1a03.applicationObject8,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2000_sys = {
    {
    .dataOrig = &regs_data.sys.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &sys.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys.errors,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys.warnings,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys.fsm_state.state,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys.fsm_state.prev_state,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys.r_adc_tim_run_time_us,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys.r_sys_tim_run_time_us,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys.r_ms_tim_run_time_us,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys.r_net_run_time_us,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys.r_idle_run_time_us,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2010_sys_cmd = {
    {
    .dataOrig = &regs_data.sys_cmd.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &sys_cmd.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_cmd.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_cmd.out_command,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2020_sys_ctrl = {
    {
    .dataOrig = &regs_data.sys_ctrl.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &sys_ctrl.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_ctrl.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_ctrl.errors,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_ctrl.warnings,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_ctrl.fsm_state.state,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_ctrl.fsm_state.prev_state,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_ctrl.out_command,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_ctrl.fsm_check.state,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_ctrl.fsm_check.prev_state,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_ctrl.fsm_idle.state,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_ctrl.fsm_idle.prev_state,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2030_sys_stat = {
    {
    .dataOrig = &regs_data.sys_stat.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &sys_stat.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_stat.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_stat.in_command,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2040_conf = {
    {
    .dataOrig = &regs_data.conf.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &conf.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.warnings,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.p_U_nom,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.p_I_nom,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.p_f_nom,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.r_U_base,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.r_U_base_inv,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.r_I_base,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.r_I_base_inv,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.r_f_base,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.r_f_base_inv,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.r_P_base,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.r_P_base_inv,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2050_adc = {
    {
    .dataOrig = &regs_data.adc.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &adc.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ua_raw,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ub_raw,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Uc_raw,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ua,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ub,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Uc,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ia_raw,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ib_raw,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ic_raw,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ia,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ib,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ic,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Uarm_raw,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Uarm,
    .subIndex = 16,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Iarm_raw,
    .subIndex = 17,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Iarm,
    .subIndex = 18,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ir_raw,
    .subIndex = 19,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Irstart,
    .subIndex = 20,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Ua_raw,
    .subIndex = 21,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Ub_raw,
    .subIndex = 22,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Uc_raw,
    .subIndex = 23,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Ua,
    .subIndex = 24,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Ub,
    .subIndex = 25,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Uc,
    .subIndex = 26,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Ia_raw,
    .subIndex = 27,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Ib_raw,
    .subIndex = 28,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Ic_raw,
    .subIndex = 29,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Ia,
    .subIndex = 30,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Ib,
    .subIndex = 31,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_s_Ic,
    .subIndex = 32,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ua_gain,
    .subIndex = 33,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ua_offset,
    .subIndex = 34,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ub_gain,
    .subIndex = 35,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ub_offset,
    .subIndex = 36,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Uc_gain,
    .subIndex = 37,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Uc_offset,
    .subIndex = 38,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ia_gain,
    .subIndex = 39,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ia_offset,
    .subIndex = 40,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ib_gain,
    .subIndex = 41,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ib_offset,
    .subIndex = 42,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ic_gain,
    .subIndex = 43,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ic_offset,
    .subIndex = 44,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Uarm_gain,
    .subIndex = 45,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Uarm_offset,
    .subIndex = 46,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Iarm_gain,
    .subIndex = 47,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Iarm_offset,
    .subIndex = 48,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ir_gain,
    .subIndex = 49,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ir_offset,
    .subIndex = 50,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Ua_gain,
    .subIndex = 51,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Ua_offset,
    .subIndex = 52,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Ub_gain,
    .subIndex = 53,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Ub_offset,
    .subIndex = 54,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Uc_gain,
    .subIndex = 55,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Uc_offset,
    .subIndex = 56,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Ia_gain,
    .subIndex = 57,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Ia_offset,
    .subIndex = 58,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Ib_gain,
    .subIndex = 59,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Ib_offset,
    .subIndex = 60,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Ic_gain,
    .subIndex = 61,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_s_Ic_offset,
    .subIndex = 62,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2060_dac = {
    {
    .dataOrig = &regs_data.dac.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &dac.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dac.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dac.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dac.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2070_adc_model = {
    {
    .dataOrig = &regs_data.adc_model.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &adc_model.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.in_U_scale,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.in_F_scale,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.in_s_U_scale,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.in_s_F_scale,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_Ua_raw,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_Ub_raw,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_Uc_raw,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_Ua,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_Ub,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_Uc,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_s_Ua_raw,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_s_Ub_raw,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_s_Uc_raw,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_s_Ua,
    .subIndex = 16,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_s_Ub,
    .subIndex = 17,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.out_s_Uc,
    .subIndex = 18,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_Ua_gain,
    .subIndex = 19,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_Ua_offset,
    .subIndex = 20,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_Ub_gain,
    .subIndex = 21,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_Ub_offset,
    .subIndex = 22,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_Uc_gain,
    .subIndex = 23,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_Uc_offset,
    .subIndex = 24,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_s_Ua_gain,
    .subIndex = 25,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_s_Ua_offset,
    .subIndex = 26,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_s_Ub_gain,
    .subIndex = 27,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_s_Ub_offset,
    .subIndex = 28,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_s_Uc_gain,
    .subIndex = 29,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_model.p_s_Uc_offset,
    .subIndex = 30,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2080_adc_tim = {
    {
    .dataOrig = &regs_data.adc_tim.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &adc_tim.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_tim.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc_tim.out_counter,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2090_sys_tim = {
    {
    .dataOrig = &regs_data.sys_tim.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &sys_tim.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_tim.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_tim.out_counter,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_20A0_ms_tim = {
    {
    .dataOrig = &regs_data.ms_tim.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &ms_tim.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ms_tim.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ms_tim.out_counter,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_20B0_net_tim = {
    {
    .dataOrig = &regs_data.net_tim.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &net_tim.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &net_tim.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &net_tim.out_counter,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_20C0_sys_time = {
    {
    .dataOrig = &regs_data.sys_time.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &sys_time.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_time.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_time.r_counter_ms,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_time.r_counter_s,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_time.r_run_counter_s,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_20D0_tmr_sys_fsm = {
    {
    .dataOrig = &regs_data.tmr_sys_fsm.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &tmr_sys_fsm.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_sys_fsm.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_sys_fsm.out_expired,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_sys_fsm.out_timeout,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_sys_fsm.p_interval,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_20E0_dlog = {
    {
    .dataOrig = &regs_data.dlog.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &dlog.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[0].enabled,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[0].reg_id,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[1].enabled,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[1].reg_id,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[2].enabled,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[2].reg_id,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[3].enabled,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[3].reg_id,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[4].enabled,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[4].reg_id,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[5].enabled,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[5].reg_id,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[6].enabled,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[6].reg_id,
    .subIndex = 16,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[7].enabled,
    .subIndex = 17,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[7].reg_id,
    .subIndex = 18,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[8].enabled,
    .subIndex = 19,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[8].reg_id,
    .subIndex = 20,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[9].enabled,
    .subIndex = 21,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[9].reg_id,
    .subIndex = 22,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[10].enabled,
    .subIndex = 23,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[10].reg_id,
    .subIndex = 24,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[11].enabled,
    .subIndex = 25,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[11].reg_id,
    .subIndex = 26,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[12].enabled,
    .subIndex = 27,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[12].reg_id,
    .subIndex = 28,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[13].enabled,
    .subIndex = 29,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[13].reg_id,
    .subIndex = 30,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[14].enabled,
    .subIndex = 31,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[14].reg_id,
    .subIndex = 32,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[15].enabled,
    .subIndex = 33,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.p_ch[15].reg_id,
    .subIndex = 34,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.r_count,
    .subIndex = 35,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.r_get_index,
    .subIndex = 36,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.r_put_index,
    .subIndex = 37,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &dlog.r_ch[0].data[0],
    .subIndex = 38,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[1].data[0],
    .subIndex = 39,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[2].data[0],
    .subIndex = 40,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[3].data[0],
    .subIndex = 41,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[4].data[0],
    .subIndex = 42,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[5].data[0],
    .subIndex = 43,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[6].data[0],
    .subIndex = 44,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[7].data[0],
    .subIndex = 45,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[8].data[0],
    .subIndex = 46,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[9].data[0],
    .subIndex = 47,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[10].data[0],
    .subIndex = 48,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[11].data[0],
    .subIndex = 49,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[12].data[0],
    .subIndex = 50,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[13].data[0],
    .subIndex = 51,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[14].data[0],
    .subIndex = 52,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    },
    {
    .dataOrig = &dlog.r_ch[15].data[0],
    .subIndex = 53,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 1024
    }
},
.o_20F0_sys_calc = {
    {
    .dataOrig = &regs_data.sys_calc.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &sys_calc.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_calc.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2100_rect_curr = {
    {
    .dataOrig = &regs_data.rect_curr.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rect_curr.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rect_curr.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rect_curr.in_Ia,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rect_curr.in_Ib,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rect_curr.in_Ic,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rect_curr.out_I,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2110_mux_umains = {
    {
    .dataOrig = &regs_data.mux_umains.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_Umains.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.in_A[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.in_A[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.in_A[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.in_B[0],
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.in_B[1],
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.in_B[2],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.in_C[0],
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.in_C[1],
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.in_C[2],
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.out_A,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.out_B,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.out_C,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.p_sel,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2120_mux_imains = {
    {
    .dataOrig = &regs_data.mux_imains.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_Imains.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.in_A[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.in_A[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.in_A[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.in_B[0],
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.in_B[1],
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.in_B[2],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.in_C[0],
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.in_C[1],
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.in_C[2],
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.out_A,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.out_B,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.out_C,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.p_sel,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2130_mux_uarm = {
    {
    .dataOrig = &regs_data.mux_uarm.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_Uarm.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Uarm.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Uarm.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Uarm.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Uarm.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Uarm.p_sel,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2140_mux_iarm = {
    {
    .dataOrig = &regs_data.mux_iarm.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_Iarm.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Iarm.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Iarm.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Iarm.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Iarm.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Iarm.out_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Iarm.p_sel,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2150_mux_irstart = {
    {
    .dataOrig = &regs_data.mux_irstart.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_Irstart.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Irstart.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Irstart.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Irstart.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Irstart.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Irstart.p_sel,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2160_mux_ucell = {
    {
    .dataOrig = &regs_data.mux_ucell.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_Ucell.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.in_A[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.in_A[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.in_A[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.in_B[0],
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.in_B[1],
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.in_B[2],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.in_C[0],
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.in_C[1],
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.in_C[2],
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.out_A,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.out_B,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.out_C,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.p_sel,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2170_mux_icell = {
    {
    .dataOrig = &regs_data.mux_icell.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_Icell.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.in_A[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.in_A[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.in_A[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.in_B[0],
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.in_B[1],
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.in_B[2],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.in_C[0],
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.in_C[1],
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.in_C[2],
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.out_A,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.out_B,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.out_C,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.p_sel,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2180_mux_slip = {
    {
    .dataOrig = &regs_data.mux_slip.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_slip.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_slip.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_slip.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_slip.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_slip.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_slip.p_sel,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2190_phase_ampl_ua = {
    {
    .dataOrig = &regs_data.phase_ampl_ua.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &phase_ampl_Ua.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Ua.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Ua.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Ua.out_phase,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Ua.out_ampl,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_21A0_phase_ampl_ub = {
    {
    .dataOrig = &regs_data.phase_ampl_ub.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &phase_ampl_Ub.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Ub.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Ub.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Ub.out_phase,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Ub.out_ampl,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_21B0_phase_ampl_uc = {
    {
    .dataOrig = &regs_data.phase_ampl_uc.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &phase_ampl_Uc.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Uc.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Uc.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Uc.out_phase,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Uc.out_ampl,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_21C0_zcd_ua = {
    {
    .dataOrig = &regs_data.zcd_ua.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &zcd_Ua.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ua.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ua.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ua.out_zero_cross,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ua.out_period,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ua.out_freq,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ua.r_samples_period,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_21D0_zcd_ub = {
    {
    .dataOrig = &regs_data.zcd_ub.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &zcd_Ub.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ub.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ub.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ub.out_zero_cross,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ub.out_period,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ub.out_freq,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ub.r_samples_period,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_21E0_zcd_uc = {
    {
    .dataOrig = &regs_data.zcd_uc.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &zcd_Uc.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Uc.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Uc.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Uc.out_zero_cross,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Uc.out_period,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Uc.out_freq,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Uc.r_samples_period,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_21F0_zcd_slip = {
    {
    .dataOrig = &regs_data.zcd_slip.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &zcd_slip.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_slip.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_slip.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_slip.out_zero_cross,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_slip.out_period,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_slip.out_freq,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_slip.r_samples_period,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2200_slip = {
    {
    .dataOrig = &regs_data.slip.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &slip.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &slip.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &slip.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &slip.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2210_phase_lrm_i_stator = {
    {
    .dataOrig = &regs_data.phase_lrm_i_stator.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &phase_lrm_I_stator.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_lrm_I_stator.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_lrm_I_stator.in_A,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_lrm_I_stator.in_B,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_lrm_I_stator.in_C,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_lrm_I_stator.out_A,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_lrm_I_stator.out_B,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_lrm_I_stator.out_C,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2220_phase_ucell = {
    {
    .dataOrig = &regs_data.phase_ucell.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &phase_Ucell.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_Ucell.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_Ucell.in_A,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_Ucell.in_B,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_Ucell.in_C,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_Ucell.out_A,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_Ucell.out_B,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_Ucell.out_C,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2230_calc_ucell = {
    {
    .dataOrig = &regs_data.calc_ucell.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &calc_Ucell.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Ucell.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Ucell.in_A,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Ucell.in_B,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Ucell.in_C,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Ucell.out_A,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Ucell.out_B,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Ucell.out_C,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Ucell.p_sel,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2240_calc_icell = {
    {
    .dataOrig = &regs_data.calc_icell.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &calc_Icell.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Icell.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Icell.in_A,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Icell.in_B,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Icell.in_C,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Icell.out_A,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Icell.out_B,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Icell.out_C,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &calc_Icell.p_sel,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2250_rms_ua = {
    {
    .dataOrig = &regs_data.rms_ua.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_Ua.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ua.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ua.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ua.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2260_rms_ub = {
    {
    .dataOrig = &regs_data.rms_ub.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_Ub.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ub.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ub.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ub.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2270_rms_uc = {
    {
    .dataOrig = &regs_data.rms_uc.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_Uc.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Uc.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Uc.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Uc.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2280_rms_ia = {
    {
    .dataOrig = &regs_data.rms_ia.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_Ia.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ia.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ia.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ia.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2290_rms_ib = {
    {
    .dataOrig = &regs_data.rms_ib.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_Ib.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ib.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ib.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ib.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_22A0_rms_ic = {
    {
    .dataOrig = &regs_data.rms_ic.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_Ic.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ic.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ic.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ic.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_22B0_rms_cell_ua = {
    {
    .dataOrig = &regs_data.rms_cell_ua.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_cell_Ua.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ua.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ua.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ua.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_22C0_rms_cell_ub = {
    {
    .dataOrig = &regs_data.rms_cell_ub.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_cell_Ub.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ub.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ub.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ub.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_22D0_rms_cell_uc = {
    {
    .dataOrig = &regs_data.rms_cell_uc.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_cell_Uc.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Uc.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Uc.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Uc.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_22E0_rms_cell_ua_phase = {
    {
    .dataOrig = &regs_data.rms_cell_ua_phase.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_cell_Ua_phase.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ua_phase.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ua_phase.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ua_phase.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_22F0_rms_cell_ub_phase = {
    {
    .dataOrig = &regs_data.rms_cell_ub_phase.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_cell_Ub_phase.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ub_phase.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ub_phase.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ub_phase.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2300_rms_cell_uc_phase = {
    {
    .dataOrig = &regs_data.rms_cell_uc_phase.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_cell_Uc_phase.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Uc_phase.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Uc_phase.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Uc_phase.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2310_rms_cell_ia = {
    {
    .dataOrig = &regs_data.rms_cell_ia.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_cell_Ia.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ia.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ia.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ia.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2320_rms_cell_ib = {
    {
    .dataOrig = &regs_data.rms_cell_ib.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_cell_Ib.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ib.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ib.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ib.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2330_rms_cell_ic = {
    {
    .dataOrig = &regs_data.rms_cell_ic.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_cell_Ic.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ic.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ic.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ic.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2340_mean_iarm = {
    {
    .dataOrig = &regs_data.mean_iarm.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mean_Iarm.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_Iarm.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_Iarm.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_Iarm.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2350_mean_uarm = {
    {
    .dataOrig = &regs_data.mean_uarm.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mean_Uarm.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_Uarm.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_Uarm.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_Uarm.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2360_mean_irstart = {
    {
    .dataOrig = &regs_data.mean_irstart.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mean_Irstart.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_Irstart.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_Irstart.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_Irstart.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2370_mean_rms_icell = {
    {
    .dataOrig = &regs_data.mean_rms_icell.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mean_rms_Icell.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_rms_Icell.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_rms_Icell.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_rms_Icell.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_rms_Icell.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_rms_Icell.out_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2380_sum_s = {
    {
    .dataOrig = &regs_data.sum_s.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &sum_S.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_S.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_S.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_S.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_S.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_S.out_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2390_sum_p = {
    {
    .dataOrig = &regs_data.sum_p.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &sum_P.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_P.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_P.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_P.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_P.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_P.out_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_23A0_sum_q = {
    {
    .dataOrig = &regs_data.sum_q.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &sum_Q.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_Q.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_Q.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_Q.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_Q.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sum_Q.out_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_23B0_power_a = {
    {
    .dataOrig = &regs_data.power_a.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &power_A.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_A.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_A.in_U,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_A.in_I,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_A.in_rms_U,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_A.in_rms_I,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_A.out_S,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_A.out_P,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_A.out_Q,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_23C0_power_b = {
    {
    .dataOrig = &regs_data.power_b.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &power_B.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_B.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_B.in_U,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_B.in_I,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_B.in_rms_U,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_B.in_rms_I,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_B.out_S,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_B.out_P,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_B.out_Q,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_23D0_power_c = {
    {
    .dataOrig = &regs_data.power_c.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &power_C.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_C.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_C.in_U,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_C.in_I,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_C.in_rms_U,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_C.in_rms_I,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_C.out_S,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_C.out_P,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_C.out_Q,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_23E0_power_factor = {
    {
    .dataOrig = &regs_data.power_factor.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &power_factor.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_factor.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_factor.in_S,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_factor.in_P,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_factor.in_Q,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_factor.out_cos_phi,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_factor.out_sin_phi,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_factor.out_tan_phi,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_23F0_vr_rms_umains = {
    {
    .dataOrig = &regs_data.vr_rms_umains.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &vr_rms_Umains.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Umains.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Umains.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Umains.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Umains.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Umains.out_value[0],
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Umains.out_value[1],
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Umains.out_value[2],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Umains.out_value_all,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Umains.p_min_value,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Umains.p_max_value,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2400_vr_filter_freq_umains = {
    {
    .dataOrig = &regs_data.vr_filter_freq_umains.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &vr_filter_freq_Umains.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_filter_freq_Umains.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_filter_freq_Umains.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_filter_freq_Umains.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_filter_freq_Umains.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_filter_freq_Umains.out_value[0],
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_filter_freq_Umains.out_value[1],
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_filter_freq_Umains.out_value[2],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_filter_freq_Umains.out_value_all,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_filter_freq_Umains.p_min_value,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_filter_freq_Umains.p_max_value,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2410_vr_rms_ucell = {
    {
    .dataOrig = &regs_data.vr_rms_ucell.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &vr_rms_Ucell.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Ucell.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Ucell.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Ucell.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Ucell.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Ucell.out_value[0],
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Ucell.out_value[1],
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Ucell.out_value[2],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Ucell.out_value_all,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Ucell.p_min_value,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &vr_rms_Ucell.p_max_value,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2420_cell_cb = {
    {
    .dataOrig = &regs_data.cell_cb.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &cell_cb.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &cell_cb.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &cell_cb.in_no_state,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &cell_cb.in_nc_state,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &cell_cb.out_state,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2430_run_trig = {
    {
    .dataOrig = &regs_data.run_trig.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &run_trig.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &run_trig.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &run_trig.out_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2440_thr_run_trig_i_s = {
    {
    .dataOrig = &regs_data.thr_run_trig_i_s.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &thr_run_trig_I_s.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_run_trig_I_s.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_run_trig_I_s.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_run_trig_I_s.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_run_trig_I_s.p_threshold,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2450_am_run_trig_i_s = {
    {
    .dataOrig = &regs_data.am_run_trig_i_s.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &am_run_trig_I_s.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_run_trig_I_s.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_run_trig_I_s.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_run_trig_I_s.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_run_trig_I_s.p_mask[0],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2460_tmr_run_trig = {
    {
    .dataOrig = &regs_data.tmr_run_trig.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &tmr_run_trig.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_run_trig.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_run_trig.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_run_trig.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_run_trig.r_tmr.control,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_run_trig.r_tmr.status,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_run_trig.r_tmr.out_expired,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_run_trig.r_tmr.out_timeout,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_run_trig.r_tmr.p_interval,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2470_thr_prim_slip = {
    {
    .dataOrig = &regs_data.thr_prim_slip.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &thr_prim_Slip.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_Slip.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_Slip.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_Slip.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_Slip.p_threshold,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2480_thr_prim_i_s = {
    {
    .dataOrig = &regs_data.thr_prim_i_s.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &thr_prim_I_s.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_I_s.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_I_s.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_I_s.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_I_s.p_threshold,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2490_thr_prim_t = {
    {
    .dataOrig = &regs_data.thr_prim_t.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &thr_prim_T.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_T.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_T.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_T.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_prim_T.p_threshold,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_24A0_am_prim_field_on = {
    {
    .dataOrig = &regs_data.am_prim_field_on.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &am_prim_field_on.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_prim_field_on.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_prim_field_on.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_prim_field_on.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_prim_field_on.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_prim_field_on.out_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_prim_field_on.p_mask[0],
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_prim_field_on.p_mask[1],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_prim_field_on.p_mask[2],
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_24B0_thr_sec_slip = {
    {
    .dataOrig = &regs_data.thr_sec_slip.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &thr_sec_Slip.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_Slip.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_Slip.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_Slip.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_Slip.p_threshold,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_24C0_thr_sec_i_s = {
    {
    .dataOrig = &regs_data.thr_sec_i_s.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &thr_sec_I_s.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_I_s.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_I_s.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_I_s.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_I_s.p_threshold,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_24D0_thr_sec_t = {
    {
    .dataOrig = &regs_data.thr_sec_t.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &thr_sec_T.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_T.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_T.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_T.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_sec_T.p_threshold,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_24E0_am_sec_field_on = {
    {
    .dataOrig = &regs_data.am_sec_field_on.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &am_sec_field_on.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_sec_field_on.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_sec_field_on.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_sec_field_on.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_sec_field_on.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_sec_field_on.out_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_sec_field_on.p_mask[0],
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_sec_field_on.p_mask[1],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &am_sec_field_on.p_mask[2],
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_24F0_or_field_on = {
    {
    .dataOrig = &regs_data.or_field_on.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &or_field_on.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_field_on.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_field_on.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_field_on.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_field_on.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2500_tmr_field_on = {
    {
    .dataOrig = &regs_data.tmr_field_on.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &tmr_field_on.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on.r_tmr.control,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on.r_tmr.status,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on.r_tmr.out_expired,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on.r_tmr.out_timeout,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on.r_tmr.p_interval,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2510_thr_value_for_slip_lt_zero = {
    {
    .dataOrig = &regs_data.thr_value_for_slip_lt_zero.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &thr_value_for_slip_lt_zero.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_value_for_slip_lt_zero.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_value_for_slip_lt_zero.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_value_for_slip_lt_zero.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_value_for_slip_lt_zero.p_threshold,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2520_or_value_slip_lt_zero_i_r_sync = {
    {
    .dataOrig = &regs_data.or_value_slip_lt_zero_i_r_sync.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &or_value_slip_lt_zero_I_r_sync.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_value_slip_lt_zero_I_r_sync.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_value_slip_lt_zero_I_r_sync.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_value_slip_lt_zero_I_r_sync.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_value_slip_lt_zero_I_r_sync.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2530_and_ready_to_exc = {
    {
    .dataOrig = &regs_data.and_ready_to_exc.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &and_ready_to_exc.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_ready_to_exc.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_ready_to_exc.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_ready_to_exc.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_ready_to_exc.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2540_tmr_field_on_rstart_off = {
    {
    .dataOrig = &regs_data.tmr_field_on_rstart_off.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &tmr_field_on_rstart_off.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_rstart_off.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_rstart_off.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_rstart_off.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_rstart_off.r_tmr.control,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_rstart_off.r_tmr.status,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_rstart_off.r_tmr.out_expired,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_rstart_off.r_tmr.out_timeout,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_rstart_off.r_tmr.p_interval,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2550_not_ready_to_exc = {
    {
    .dataOrig = &regs_data.not_ready_to_exc.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &not_ready_to_exc.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &not_ready_to_exc.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &not_ready_to_exc.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &not_ready_to_exc.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2560_cmp_ctrl_state_is_start = {
    {
    .dataOrig = &regs_data.cmp_ctrl_state_is_start.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &cmp_ctrl_state_is_start.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &cmp_ctrl_state_is_start.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &cmp_ctrl_state_is_start.in_A,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &cmp_ctrl_state_is_start.in_B,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &cmp_ctrl_state_is_start.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2570_and_rstart_on = {
    {
    .dataOrig = &regs_data.and_rstart_on.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &and_rstart_on.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_rstart_on.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_rstart_on.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_rstart_on.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_rstart_on.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2580_thr_field_on_i_r_sync = {
    {
    .dataOrig = &regs_data.thr_field_on_i_r_sync.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &thr_field_on_I_r_sync.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_field_on_I_r_sync.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_field_on_I_r_sync.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_field_on_I_r_sync.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_field_on_I_r_sync.p_threshold,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2590_tmr_field_on_i_r_sync = {
    {
    .dataOrig = &regs_data.tmr_field_on_i_r_sync.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &tmr_field_on_I_r_sync.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_I_r_sync.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_I_r_sync.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_I_r_sync.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_I_r_sync.r_tmr.control,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_I_r_sync.r_tmr.status,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_I_r_sync.r_tmr.out_expired,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_I_r_sync.r_tmr.out_timeout,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_on_I_r_sync.r_tmr.p_interval,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_25A0_thr_field_supp_i_r = {
    {
    .dataOrig = &regs_data.thr_field_supp_i_r.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &thr_field_supp_I_r.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_field_supp_I_r.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_field_supp_I_r.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_field_supp_I_r.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_field_supp_I_r.p_threshold,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_25B0_tmr_field_supp = {
    {
    .dataOrig = &regs_data.tmr_field_supp.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &tmr_field_supp.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_supp.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_supp.out_expired,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_supp.out_timeout,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_field_supp.p_interval,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_25C0_cnt_start = {
    {
    .dataOrig = &regs_data.cnt_start.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &cnt_start.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &cnt_start.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &cnt_start.out_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_25D0_filter_zcd_ua = {
    {
    .dataOrig = &regs_data.filter_zcd_ua.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_zcd_Ua.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ua.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ua.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ua.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ua.p_T,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ua.r_Ts,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_25E0_filter_zcd_ub = {
    {
    .dataOrig = &regs_data.filter_zcd_ub.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_zcd_Ub.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ub.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ub.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ub.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ub.p_T,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ub.r_Ts,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_25F0_filter_zcd_uc = {
    {
    .dataOrig = &regs_data.filter_zcd_uc.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_zcd_Uc.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Uc.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Uc.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Uc.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Uc.p_T,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Uc.r_Ts,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2600_filter_zcd_slip = {
    {
    .dataOrig = &regs_data.filter_zcd_slip.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_zcd_slip.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_slip.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_slip.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_slip.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_slip.p_T,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_slip.r_Ts,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2610_filter_freq_ua = {
    {
    .dataOrig = &regs_data.filter_freq_ua.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_freq_Ua.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ua.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ua.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ua.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ua.p_T,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ua.r_Ts,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2620_filter_freq_ub = {
    {
    .dataOrig = &regs_data.filter_freq_ub.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_freq_Ub.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ub.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ub.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ub.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ub.p_T,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ub.r_Ts,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2630_filter_freq_uc = {
    {
    .dataOrig = &regs_data.filter_freq_uc.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_freq_Uc.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Uc.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Uc.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Uc.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Uc.p_T,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Uc.r_Ts,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2640_filter_freq_slip = {
    {
    .dataOrig = &regs_data.filter_freq_slip.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_freq_slip.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_slip.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_slip.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_slip.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_slip.p_T,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_slip.r_Ts,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2650_filter_mean_iarm = {
    {
    .dataOrig = &regs_data.filter_mean_iarm.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_mean_Iarm.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Iarm.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Iarm.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Iarm.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Iarm.p_T,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Iarm.r_Ts,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2660_filter_mean_uarm = {
    {
    .dataOrig = &regs_data.filter_mean_uarm.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_mean_Uarm.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Uarm.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Uarm.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Uarm.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Uarm.p_T,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Uarm.r_Ts,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2670_filter_mean_irstart = {
    {
    .dataOrig = &regs_data.filter_mean_irstart.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_mean_Irstart.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Irstart.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Irstart.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Irstart.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Irstart.p_T,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Irstart.r_Ts,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2680_tmr_start_min_forcing = {
    {
    .dataOrig = &regs_data.tmr_start_min_forcing.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &tmr_start_min_forcing.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_min_forcing.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_min_forcing.out_expired,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_min_forcing.out_timeout,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_min_forcing.p_interval,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2690_tmr_start_max_forcing = {
    {
    .dataOrig = &regs_data.tmr_start_max_forcing.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &tmr_start_max_forcing.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_max_forcing.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_max_forcing.out_expired,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_max_forcing.out_timeout,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_max_forcing.p_interval,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_26A0_tmr_start_stab_forcing = {
    {
    .dataOrig = &regs_data.tmr_start_stab_forcing.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &tmr_start_stab_forcing.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_stab_forcing.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_stab_forcing.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_stab_forcing.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_stab_forcing.r_tmr.control,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_stab_forcing.r_tmr.status,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_stab_forcing.r_tmr.out_expired,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_stab_forcing.r_tmr.out_timeout,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &tmr_start_stab_forcing.r_tmr.p_interval,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_26B0_thr_start_q_le_zero = {
    {
    .dataOrig = &regs_data.thr_start_q_le_zero.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &thr_start_Q_le_zero.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_start_Q_le_zero.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_start_Q_le_zero.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_start_Q_le_zero.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &thr_start_Q_le_zero.p_threshold,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_26C0_and_start_min_forcing_end = {
    {
    .dataOrig = &regs_data.and_start_min_forcing_end.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &and_start_min_forcing_end.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_start_min_forcing_end.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_start_min_forcing_end.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_start_min_forcing_end.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &and_start_min_forcing_end.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_26D0_or_start_forcing_end = {
    {
    .dataOrig = &regs_data.or_start_forcing_end.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &or_start_forcing_end.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_start_forcing_end.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_start_forcing_end.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_start_forcing_end.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &or_start_forcing_end.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_26E0_mux_field_regs = {
    {
    .dataOrig = &regs_data.mux_field_regs.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_field_regs.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_regs.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_regs.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_regs.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_regs.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_regs.in_value[3],
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_regs.out_value,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_regs.p_sel,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_26F0_lim_field_regs_curr_ref = {
    {
    .dataOrig = &regs_data.lim_field_regs_curr_ref.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &lim_field_regs_curr_ref.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lim_field_regs_curr_ref.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lim_field_regs_curr_ref.in_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lim_field_regs_curr_ref.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lim_field_regs_curr_ref.p_min_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lim_field_regs_curr_ref.p_max_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2700_mux_field_force_ref = {
    {
    .dataOrig = &regs_data.mux_field_force_ref.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_field_force_ref.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_force_ref.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_force_ref.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_force_ref.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_force_ref.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_field_force_ref.p_sel,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2710_mot_pot_field_test = {
    {
    .dataOrig = &regs_data.mot_pot_field_test.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mot_pot_field_test.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_field_test.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_field_test.in_dec,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_field_test.in_inc,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_field_test.p_time,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_field_test.p_min,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_field_test.p_max,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_field_test.r_value,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_field_test.r_Ts,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2720_mot_pot_manual_curr_ref = {
    {
    .dataOrig = &regs_data.mot_pot_manual_curr_ref.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mot_pot_manual_curr_ref.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_manual_curr_ref.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_manual_curr_ref.in_dec,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_manual_curr_ref.in_inc,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_manual_curr_ref.p_time,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_manual_curr_ref.p_min,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_manual_curr_ref.p_max,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_manual_curr_ref.r_value,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mot_pot_manual_curr_ref.r_Ts,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2730_mux_curr_ref = {
    {
    .dataOrig = &regs_data.mux_curr_ref.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_curr_ref.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_curr_ref.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_curr_ref.in_value[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_curr_ref.in_value[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_curr_ref.in_value[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_curr_ref.in_value[3],
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_curr_ref.out_value,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_curr_ref.p_sel,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2740_pid_i = {
    {
    .dataOrig = &regs_data.pid_i.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &pid_i.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_i.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_i.in_ref,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_i.in_fbk,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_i.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_i.r_kp,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_i.r_ki,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_i.r_kd,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_i.r_kf,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_i.r_min,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_i.r_max,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2750_pid_coefs_i = {
    {
    .dataOrig = &regs_data.pid_coefs_i.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &pid_coefs_i.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_coefs_i.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_coefs_i.out_kp,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_coefs_i.out_ki,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_coefs_i.out_kd,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_coefs_i.out_kf,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_coefs_i.p_kp,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_coefs_i.p_Ti,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_coefs_i.p_Td,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_coefs_i.p_Tf,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &pid_coefs_i.r_Ts,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2760_ph3c = {
    {
    .dataOrig = &regs_data.ph3c.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &ph3c.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.in_Ua_angle,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.in_Ub_angle,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.in_Uc_angle,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.in_control_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.out_control[0],
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.out_control[1],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.out_control[2],
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.out_control[3],
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.out_control[4],
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.out_control[5],
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.out_control_delay_angle,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.out_control_max_duration_angle,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.out_min_control_value,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.out_max_control_value,
    .subIndex = 16,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.p_min_control_angle,
    .subIndex = 17,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.p_max_control_angle,
    .subIndex = 18,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].control,
    .subIndex = 19,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].status,
    .subIndex = 20,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].in_angle_pu,
    .subIndex = 21,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].in_control_angle_pu,
    .subIndex = 22,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].out_cycle,
    .subIndex = 23,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].out_period,
    .subIndex = 24,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].out_control,
    .subIndex = 25,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].out_control_angle_pu,
    .subIndex = 26,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].out_control_late,
    .subIndex = 27,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].out_control_between,
    .subIndex = 28,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].r_angle_win_pu,
    .subIndex = 29,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].r_min_angle_to_control_pu,
    .subIndex = 30,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[0].r_max_angle_to_control_pu,
    .subIndex = 31,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].control,
    .subIndex = 32,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].status,
    .subIndex = 33,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].in_angle_pu,
    .subIndex = 34,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].in_control_angle_pu,
    .subIndex = 35,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].out_cycle,
    .subIndex = 36,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].out_period,
    .subIndex = 37,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].out_control,
    .subIndex = 38,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].out_control_angle_pu,
    .subIndex = 39,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].out_control_late,
    .subIndex = 40,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].out_control_between,
    .subIndex = 41,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].r_angle_win_pu,
    .subIndex = 42,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].r_min_angle_to_control_pu,
    .subIndex = 43,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[1].r_max_angle_to_control_pu,
    .subIndex = 44,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].control,
    .subIndex = 45,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].status,
    .subIndex = 46,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].in_angle_pu,
    .subIndex = 47,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].in_control_angle_pu,
    .subIndex = 48,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].out_cycle,
    .subIndex = 49,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].out_period,
    .subIndex = 50,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].out_control,
    .subIndex = 51,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].out_control_angle_pu,
    .subIndex = 52,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].out_control_late,
    .subIndex = 53,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].out_control_between,
    .subIndex = 54,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].r_angle_win_pu,
    .subIndex = 55,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].r_min_angle_to_control_pu,
    .subIndex = 56,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[2].r_max_angle_to_control_pu,
    .subIndex = 57,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].control,
    .subIndex = 58,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].status,
    .subIndex = 59,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].in_angle_pu,
    .subIndex = 60,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].in_control_angle_pu,
    .subIndex = 61,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].out_cycle,
    .subIndex = 62,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].out_period,
    .subIndex = 63,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].out_control,
    .subIndex = 64,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].out_control_angle_pu,
    .subIndex = 65,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].out_control_late,
    .subIndex = 66,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].out_control_between,
    .subIndex = 67,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].r_angle_win_pu,
    .subIndex = 68,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].r_min_angle_to_control_pu,
    .subIndex = 69,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[3].r_max_angle_to_control_pu,
    .subIndex = 70,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].control,
    .subIndex = 71,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].status,
    .subIndex = 72,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].in_angle_pu,
    .subIndex = 73,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].in_control_angle_pu,
    .subIndex = 74,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].out_cycle,
    .subIndex = 75,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].out_period,
    .subIndex = 76,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].out_control,
    .subIndex = 77,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].out_control_angle_pu,
    .subIndex = 78,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].out_control_late,
    .subIndex = 79,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].out_control_between,
    .subIndex = 80,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].r_angle_win_pu,
    .subIndex = 81,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].r_min_angle_to_control_pu,
    .subIndex = 82,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[4].r_max_angle_to_control_pu,
    .subIndex = 83,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].control,
    .subIndex = 84,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].status,
    .subIndex = 85,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].in_angle_pu,
    .subIndex = 86,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].in_control_angle_pu,
    .subIndex = 87,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].out_cycle,
    .subIndex = 88,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].out_period,
    .subIndex = 89,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].out_control,
    .subIndex = 90,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].out_control_angle_pu,
    .subIndex = 91,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].out_control_late,
    .subIndex = 92,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].out_control_between,
    .subIndex = 93,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].r_angle_win_pu,
    .subIndex = 94,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].r_min_angle_to_control_pu,
    .subIndex = 95,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &ph3c.phc[5].r_max_angle_to_control_pu,
    .subIndex = 96,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2770_triacs = {
    {
    .dataOrig = &regs_data.triacs.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &triacs.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &triacs.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &triacs.in_control[0],
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &triacs.in_control[1],
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &triacs.in_control[2],
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &triacs.in_control[3],
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &triacs.in_control[4],
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &triacs.in_control[5],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &triacs.in_control_delay_angle,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &triacs.in_control_max_duration_angle,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2780_lrm = {
    {
    .dataOrig = &regs_data.lrm.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &lrm.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.warnings,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_Ua,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_Ub,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_Uc,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_Uref_angle,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_control[0],
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_control[1],
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_control[2],
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_control[3],
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_control[4],
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_control[5],
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_control_delay_angle,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_control_duration_angle,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_dt,
    .subIndex = 16,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_stator_Ua,
    .subIndex = 17,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_stator_Ub,
    .subIndex = 18,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_stator_Uc,
    .subIndex = 19,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_stator_on,
    .subIndex = 20,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_start_r_on,
    .subIndex = 21,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_k_Mc,
    .subIndex = 22,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Ia,
    .subIndex = 23,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Ib,
    .subIndex = 24,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Ic,
    .subIndex = 25,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Ufld,
    .subIndex = 26,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Ifld,
    .subIndex = 27,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_M,
    .subIndex = 28,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_w,
    .subIndex = 29,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_stator_Ia,
    .subIndex = 30,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_stator_Ib,
    .subIndex = 31,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_stator_Ic,
    .subIndex = 32,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Irstart,
    .subIndex = 33,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_I_hold,
    .subIndex = 34,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Rs,
    .subIndex = 35,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Rr,
    .subIndex = 36,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Rf,
    .subIndex = 37,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Lsd,
    .subIndex = 38,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Lsq,
    .subIndex = 39,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Lrd,
    .subIndex = 40,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Lrq,
    .subIndex = 41,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Lfd,
    .subIndex = 42,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Lmsrd,
    .subIndex = 43,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Lmsrq,
    .subIndex = 44,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Lmsfd,
    .subIndex = 45,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Lmrfd,
    .subIndex = 46,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_p,
    .subIndex = 47,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Mc,
    .subIndex = 48,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Kf,
    .subIndex = 49,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_J,
    .subIndex = 50,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_Rstart,
    .subIndex = 51,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.p_start_r_u_thr,
    .subIndex = 52,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2790_motor = {
    {
    .dataOrig = &regs_data.motor.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &motor.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.warnings,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.p_f_nom,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.p_s_U_nom,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.p_s_I_nom,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.p_U_nom,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.p_I_nom,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_f_base,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_f_base_inv,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_w_base,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_w_base_inv,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_t_base,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_t_base_inv,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_U_base,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_U_base_inv,
    .subIndex = 16,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_I_base,
    .subIndex = 17,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_I_base_inv,
    .subIndex = 18,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_P_base,
    .subIndex = 19,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_P_base_inv,
    .subIndex = 20,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_M_base,
    .subIndex = 21,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_M_base_inv,
    .subIndex = 22,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_J_base,
    .subIndex = 23,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_J_base_inv,
    .subIndex = 24,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_Psi_base,
    .subIndex = 25,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_Psi_base_inv,
    .subIndex = 26,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_R_base,
    .subIndex = 27,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_R_base_inv,
    .subIndex = 28,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_L_base,
    .subIndex = 29,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_L_base_inv,
    .subIndex = 30,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_r_U_base,
    .subIndex = 31,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_r_U_base_inv,
    .subIndex = 32,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_r_I_base,
    .subIndex = 33,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_r_I_base_inv,
    .subIndex = 34,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_r_P_base,
    .subIndex = 35,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_r_P_base_inv,
    .subIndex = 36,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_k_U_mains_to_mot,
    .subIndex = 37,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_k_I_mains_to_mot,
    .subIndex = 38,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_k_I_mot_to_mains,
    .subIndex = 39,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_r_k_U_mains_to_mot,
    .subIndex = 40,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_r_k_I_mains_to_mot,
    .subIndex = 41,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_r_k_I_mot_to_mains,
    .subIndex = 42,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_27A0_prot = {
    {
    .dataOrig = &regs_data.prot.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &prot.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.errors0,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.errors1,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.errors2,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.warnings0,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.warnings1,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.out_has_errors,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.out_error_occured,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.p_mains_lost_U_low,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.p_mains_invalid_A_delta,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.p_mains_invalid_F_delta,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.p_mains_undervoltage_U_low,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.p_mains_overvoltage_U_hi,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.p_mains_overcurrent_I_hi,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.p_overvoltage_U_hi,
    .subIndex = 16,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.p_overcurrent_I_hi,
    .subIndex = 17,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.raw_errors0,
    .subIndex = 18,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.raw_errors1,
    .subIndex = 19,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.raw_errors2,
    .subIndex = 20,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.mask_errors0,
    .subIndex = 21,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.mask_errors1,
    .subIndex = 22,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.mask_errors2,
    .subIndex = 23,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_lost_timer.control,
    .subIndex = 24,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_lost_timer.status,
    .subIndex = 25,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_lost_timer.in_value,
    .subIndex = 26,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_lost_timer.out_value,
    .subIndex = 27,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_lost_timer.r_tmr.control,
    .subIndex = 28,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_lost_timer.r_tmr.status,
    .subIndex = 29,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_lost_timer.r_tmr.out_expired,
    .subIndex = 30,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_lost_timer.r_tmr.out_timeout,
    .subIndex = 31,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_lost_timer.r_tmr.p_interval,
    .subIndex = 32,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_invalid_timer.control,
    .subIndex = 33,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_invalid_timer.status,
    .subIndex = 34,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_invalid_timer.in_value,
    .subIndex = 35,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_invalid_timer.out_value,
    .subIndex = 36,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_invalid_timer.r_tmr.control,
    .subIndex = 37,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_invalid_timer.r_tmr.status,
    .subIndex = 38,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_invalid_timer.r_tmr.out_expired,
    .subIndex = 39,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_invalid_timer.r_tmr.out_timeout,
    .subIndex = 40,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_invalid_timer.r_tmr.p_interval,
    .subIndex = 41,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_undervoltage_timer.control,
    .subIndex = 42,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_undervoltage_timer.status,
    .subIndex = 43,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_undervoltage_timer.in_value,
    .subIndex = 44,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_undervoltage_timer.out_value,
    .subIndex = 45,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_undervoltage_timer.r_tmr.control,
    .subIndex = 46,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_undervoltage_timer.r_tmr.status,
    .subIndex = 47,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_undervoltage_timer.r_tmr.out_expired,
    .subIndex = 48,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_undervoltage_timer.r_tmr.out_timeout,
    .subIndex = 49,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_undervoltage_timer.r_tmr.p_interval,
    .subIndex = 50,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overvoltage_timer.control,
    .subIndex = 51,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overvoltage_timer.status,
    .subIndex = 52,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overvoltage_timer.in_value,
    .subIndex = 53,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overvoltage_timer.out_value,
    .subIndex = 54,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overvoltage_timer.r_tmr.control,
    .subIndex = 55,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overvoltage_timer.r_tmr.status,
    .subIndex = 56,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overvoltage_timer.r_tmr.out_expired,
    .subIndex = 57,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overvoltage_timer.r_tmr.out_timeout,
    .subIndex = 58,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overvoltage_timer.r_tmr.p_interval,
    .subIndex = 59,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overcurrent_timer.control,
    .subIndex = 60,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overcurrent_timer.status,
    .subIndex = 61,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overcurrent_timer.in_value,
    .subIndex = 62,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overcurrent_timer.out_value,
    .subIndex = 63,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overcurrent_timer.r_tmr.control,
    .subIndex = 64,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overcurrent_timer.r_tmr.status,
    .subIndex = 65,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overcurrent_timer.r_tmr.out_expired,
    .subIndex = 66,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overcurrent_timer.r_tmr.out_timeout,
    .subIndex = 67,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_mains_overcurrent_timer.r_tmr.p_interval,
    .subIndex = 68,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overvoltage_timer.control,
    .subIndex = 69,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overvoltage_timer.status,
    .subIndex = 70,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overvoltage_timer.in_value,
    .subIndex = 71,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overvoltage_timer.out_value,
    .subIndex = 72,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overvoltage_timer.r_tmr.control,
    .subIndex = 73,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overvoltage_timer.r_tmr.status,
    .subIndex = 74,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overvoltage_timer.r_tmr.out_expired,
    .subIndex = 75,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overvoltage_timer.r_tmr.out_timeout,
    .subIndex = 76,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overvoltage_timer.r_tmr.p_interval,
    .subIndex = 77,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overcurrent_timer.control,
    .subIndex = 78,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overcurrent_timer.status,
    .subIndex = 79,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overcurrent_timer.in_value,
    .subIndex = 80,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overcurrent_timer.out_value,
    .subIndex = 81,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overcurrent_timer.r_tmr.control,
    .subIndex = 82,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overcurrent_timer.r_tmr.status,
    .subIndex = 83,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overcurrent_timer.r_tmr.out_expired,
    .subIndex = 84,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overcurrent_timer.r_tmr.out_timeout,
    .subIndex = 85,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &prot.r_overcurrent_timer.r_tmr.p_interval,
    .subIndex = 86,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_27B0_canopen = {
    {
    .dataOrig = &regs_data.canopen.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &canopen.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &canopen.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_27C0_storage = {
    {
    .dataOrig = &regs_data.storage.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &storage.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &storage.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_27D0_settings = {
    {
    .dataOrig = &regs_data.settings.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &settings.control,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &settings.status,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &settings.errors,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
}
};
// Object dictionary
static OD_ATTR_OD OD_entry_t ODList[] = {
    {0x1000, 0x01, ODT_VAR, &ODObjs.o_1000_deviceType, NULL},
    {0x1001, 0x01, ODT_VAR, &ODObjs.o_1001_errorRegister, NULL},
    {0x1003, 0x11, ODT_ARR, &ODObjs.o_1003_pre_definedErrorField, NULL},
    {0x1005, 0x01, ODT_VAR, &ODObjs.o_1005_COB_ID_SYNCMessage, NULL},
    {0x1006, 0x01, ODT_VAR, &ODObjs.o_1006_communicationCyclePeriod, NULL},
    {0x1007, 0x01, ODT_VAR, &ODObjs.o_1007_synchronousWindowLength, NULL},
    {0x1010, 0x05, ODT_ARR, &ODObjs.o_1010_storeParameters, NULL},
    {0x1011, 0x05, ODT_ARR, &ODObjs.o_1011_restoreDefaultParameters, NULL},
    {0x1012, 0x01, ODT_VAR, &ODObjs.o_1012_COB_IDTimeStampObject, NULL},
    {0x1014, 0x01, ODT_VAR, &ODObjs.o_1014_COB_ID_EMCY, NULL},
    {0x1015, 0x01, ODT_VAR, &ODObjs.o_1015_inhibitTimeEMCY, NULL},
    {0x1016, 0x09, ODT_ARR, &ODObjs.o_1016_consumerHeartbeatTime, NULL},
    {0x1017, 0x01, ODT_VAR, &ODObjs.o_1017_producerHeartbeatTime, NULL},
    {0x1018, 0x05, ODT_REC, &ODObjs.o_1018_identity, NULL},
    {0x1019, 0x01, ODT_VAR, &ODObjs.o_1019_synchronousCounterOverflowValue, NULL},
    {0x1200, 0x03, ODT_REC, &ODObjs.o_1200_SDOServerParameter, NULL},
    {0x1201, 0x03, ODT_REC, &ODObjs.o_1201_SDOServerParameter, NULL},
    {0x1280, 0x04, ODT_REC, &ODObjs.o_1280_SDOClientParameter, NULL},
    {0x1400, 0x04, ODT_REC, &ODObjs.o_1400_RPDOCommunicationParameter, NULL},
    {0x1401, 0x04, ODT_REC, &ODObjs.o_1401_RPDOCommunicationParameter, NULL},
    {0x1402, 0x04, ODT_REC, &ODObjs.o_1402_RPDOCommunicationParameter, NULL},
    {0x1403, 0x04, ODT_REC, &ODObjs.o_1403_RPDOCommunicationParameter, NULL},
    {0x1600, 0x09, ODT_REC, &ODObjs.o_1600_RPDOMappingParameter, NULL},
    {0x1601, 0x09, ODT_REC, &ODObjs.o_1601_RPDOMappingParameter, NULL},
    {0x1602, 0x09, ODT_REC, &ODObjs.o_1602_RPDOMappingParameter, NULL},
    {0x1603, 0x09, ODT_REC, &ODObjs.o_1603_RPDOMappingParameter, NULL},
    {0x1800, 0x06, ODT_REC, &ODObjs.o_1800_TPDOCommunicationParameter, NULL},
    {0x1801, 0x06, ODT_REC, &ODObjs.o_1801_TPDOCommunicationParameter, NULL},
    {0x1802, 0x06, ODT_REC, &ODObjs.o_1802_TPDOCommunicationParameter, NULL},
    {0x1803, 0x06, ODT_REC, &ODObjs.o_1803_TPDOCommunicationParameter, NULL},
    {0x1a00, 0x09, ODT_REC, &ODObjs.o_1A00_TPDOMappingParameter, NULL},
    {0x1a01, 0x09, ODT_REC, &ODObjs.o_1A01_TPDOMappingParameter, NULL},
    {0x1a02, 0x09, ODT_REC, &ODObjs.o_1A02_TPDOMappingParameter, NULL},
    {0x1a03, 0x09, ODT_REC, &ODObjs.o_1A03_TPDOMappingParameter, NULL},
    {0x2000, 0x0c, ODT_REC, &ODObjs.o_2000_sys, NULL},
    {0x2010, 0x04, ODT_REC, &ODObjs.o_2010_sys_cmd, NULL},
    {0x2020, 0x0c, ODT_REC, &ODObjs.o_2020_sys_ctrl, NULL},
    {0x2030, 0x04, ODT_REC, &ODObjs.o_2030_sys_stat, NULL},
    {0x2040, 0x0f, ODT_REC, &ODObjs.o_2040_conf, NULL},
    {0x2050, 0x3f, ODT_REC, &ODObjs.o_2050_adc, NULL},
    {0x2060, 0x05, ODT_REC, &ODObjs.o_2060_dac, NULL},
    {0x2070, 0x1f, ODT_REC, &ODObjs.o_2070_adc_model, NULL},
    {0x2080, 0x04, ODT_REC, &ODObjs.o_2080_adc_tim, NULL},
    {0x2090, 0x04, ODT_REC, &ODObjs.o_2090_sys_tim, NULL},
    {0x20a0, 0x04, ODT_REC, &ODObjs.o_20A0_ms_tim, NULL},
    {0x20b0, 0x04, ODT_REC, &ODObjs.o_20B0_net_tim, NULL},
    {0x20c0, 0x06, ODT_REC, &ODObjs.o_20C0_sys_time, NULL},
    {0x20d0, 0x06, ODT_REC, &ODObjs.o_20D0_tmr_sys_fsm, NULL},
    {0x20e0, 0x36, ODT_REC, &ODObjs.o_20E0_dlog, NULL},
    {0x20f0, 0x03, ODT_REC, &ODObjs.o_20F0_sys_calc, NULL},
    {0x2100, 0x07, ODT_REC, &ODObjs.o_2100_rect_curr, NULL},
    {0x2110, 0x10, ODT_REC, &ODObjs.o_2110_mux_umains, NULL},
    {0x2120, 0x10, ODT_REC, &ODObjs.o_2120_mux_imains, NULL},
    {0x2130, 0x07, ODT_REC, &ODObjs.o_2130_mux_uarm, NULL},
    {0x2140, 0x08, ODT_REC, &ODObjs.o_2140_mux_iarm, NULL},
    {0x2150, 0x07, ODT_REC, &ODObjs.o_2150_mux_irstart, NULL},
    {0x2160, 0x10, ODT_REC, &ODObjs.o_2160_mux_ucell, NULL},
    {0x2170, 0x10, ODT_REC, &ODObjs.o_2170_mux_icell, NULL},
    {0x2180, 0x07, ODT_REC, &ODObjs.o_2180_mux_slip, NULL},
    {0x2190, 0x06, ODT_REC, &ODObjs.o_2190_phase_ampl_ua, NULL},
    {0x21a0, 0x06, ODT_REC, &ODObjs.o_21A0_phase_ampl_ub, NULL},
    {0x21b0, 0x06, ODT_REC, &ODObjs.o_21B0_phase_ampl_uc, NULL},
    {0x21c0, 0x08, ODT_REC, &ODObjs.o_21C0_zcd_ua, NULL},
    {0x21d0, 0x08, ODT_REC, &ODObjs.o_21D0_zcd_ub, NULL},
    {0x21e0, 0x08, ODT_REC, &ODObjs.o_21E0_zcd_uc, NULL},
    {0x21f0, 0x08, ODT_REC, &ODObjs.o_21F0_zcd_slip, NULL},
    {0x2200, 0x05, ODT_REC, &ODObjs.o_2200_slip, NULL},
    {0x2210, 0x09, ODT_REC, &ODObjs.o_2210_phase_lrm_i_stator, NULL},
    {0x2220, 0x09, ODT_REC, &ODObjs.o_2220_phase_ucell, NULL},
    {0x2230, 0x0a, ODT_REC, &ODObjs.o_2230_calc_ucell, NULL},
    {0x2240, 0x0a, ODT_REC, &ODObjs.o_2240_calc_icell, NULL},
    {0x2250, 0x05, ODT_REC, &ODObjs.o_2250_rms_ua, NULL},
    {0x2260, 0x05, ODT_REC, &ODObjs.o_2260_rms_ub, NULL},
    {0x2270, 0x05, ODT_REC, &ODObjs.o_2270_rms_uc, NULL},
    {0x2280, 0x05, ODT_REC, &ODObjs.o_2280_rms_ia, NULL},
    {0x2290, 0x05, ODT_REC, &ODObjs.o_2290_rms_ib, NULL},
    {0x22a0, 0x05, ODT_REC, &ODObjs.o_22A0_rms_ic, NULL},
    {0x22b0, 0x05, ODT_REC, &ODObjs.o_22B0_rms_cell_ua, NULL},
    {0x22c0, 0x05, ODT_REC, &ODObjs.o_22C0_rms_cell_ub, NULL},
    {0x22d0, 0x05, ODT_REC, &ODObjs.o_22D0_rms_cell_uc, NULL},
    {0x22e0, 0x05, ODT_REC, &ODObjs.o_22E0_rms_cell_ua_phase, NULL},
    {0x22f0, 0x05, ODT_REC, &ODObjs.o_22F0_rms_cell_ub_phase, NULL},
    {0x2300, 0x05, ODT_REC, &ODObjs.o_2300_rms_cell_uc_phase, NULL},
    {0x2310, 0x05, ODT_REC, &ODObjs.o_2310_rms_cell_ia, NULL},
    {0x2320, 0x05, ODT_REC, &ODObjs.o_2320_rms_cell_ib, NULL},
    {0x2330, 0x05, ODT_REC, &ODObjs.o_2330_rms_cell_ic, NULL},
    {0x2340, 0x05, ODT_REC, &ODObjs.o_2340_mean_iarm, NULL},
    {0x2350, 0x05, ODT_REC, &ODObjs.o_2350_mean_uarm, NULL},
    {0x2360, 0x05, ODT_REC, &ODObjs.o_2360_mean_irstart, NULL},
    {0x2370, 0x07, ODT_REC, &ODObjs.o_2370_mean_rms_icell, NULL},
    {0x2380, 0x07, ODT_REC, &ODObjs.o_2380_sum_s, NULL},
    {0x2390, 0x07, ODT_REC, &ODObjs.o_2390_sum_p, NULL},
    {0x23a0, 0x07, ODT_REC, &ODObjs.o_23A0_sum_q, NULL},
    {0x23b0, 0x0a, ODT_REC, &ODObjs.o_23B0_power_a, NULL},
    {0x23c0, 0x0a, ODT_REC, &ODObjs.o_23C0_power_b, NULL},
    {0x23d0, 0x0a, ODT_REC, &ODObjs.o_23D0_power_c, NULL},
    {0x23e0, 0x09, ODT_REC, &ODObjs.o_23E0_power_factor, NULL},
    {0x23f0, 0x0c, ODT_REC, &ODObjs.o_23F0_vr_rms_umains, NULL},
    {0x2400, 0x0c, ODT_REC, &ODObjs.o_2400_vr_filter_freq_umains, NULL},
    {0x2410, 0x0c, ODT_REC, &ODObjs.o_2410_vr_rms_ucell, NULL},
    {0x2420, 0x06, ODT_REC, &ODObjs.o_2420_cell_cb, NULL},
    {0x2430, 0x04, ODT_REC, &ODObjs.o_2430_run_trig, NULL},
    {0x2440, 0x06, ODT_REC, &ODObjs.o_2440_thr_run_trig_i_s, NULL},
    {0x2450, 0x06, ODT_REC, &ODObjs.o_2450_am_run_trig_i_s, NULL},
    {0x2460, 0x0a, ODT_REC, &ODObjs.o_2460_tmr_run_trig, NULL},
    {0x2470, 0x06, ODT_REC, &ODObjs.o_2470_thr_prim_slip, NULL},
    {0x2480, 0x06, ODT_REC, &ODObjs.o_2480_thr_prim_i_s, NULL},
    {0x2490, 0x06, ODT_REC, &ODObjs.o_2490_thr_prim_t, NULL},
    {0x24a0, 0x0a, ODT_REC, &ODObjs.o_24A0_am_prim_field_on, NULL},
    {0x24b0, 0x06, ODT_REC, &ODObjs.o_24B0_thr_sec_slip, NULL},
    {0x24c0, 0x06, ODT_REC, &ODObjs.o_24C0_thr_sec_i_s, NULL},
    {0x24d0, 0x06, ODT_REC, &ODObjs.o_24D0_thr_sec_t, NULL},
    {0x24e0, 0x0a, ODT_REC, &ODObjs.o_24E0_am_sec_field_on, NULL},
    {0x24f0, 0x06, ODT_REC, &ODObjs.o_24F0_or_field_on, NULL},
    {0x2500, 0x0a, ODT_REC, &ODObjs.o_2500_tmr_field_on, NULL},
    {0x2510, 0x06, ODT_REC, &ODObjs.o_2510_thr_value_for_slip_lt_zero, NULL},
    {0x2520, 0x06, ODT_REC, &ODObjs.o_2520_or_value_slip_lt_zero_i_r_sync, NULL},
    {0x2530, 0x06, ODT_REC, &ODObjs.o_2530_and_ready_to_exc, NULL},
    {0x2540, 0x0a, ODT_REC, &ODObjs.o_2540_tmr_field_on_rstart_off, NULL},
    {0x2550, 0x05, ODT_REC, &ODObjs.o_2550_not_ready_to_exc, NULL},
    {0x2560, 0x06, ODT_REC, &ODObjs.o_2560_cmp_ctrl_state_is_start, NULL},
    {0x2570, 0x06, ODT_REC, &ODObjs.o_2570_and_rstart_on, NULL},
    {0x2580, 0x06, ODT_REC, &ODObjs.o_2580_thr_field_on_i_r_sync, NULL},
    {0x2590, 0x0a, ODT_REC, &ODObjs.o_2590_tmr_field_on_i_r_sync, NULL},
    {0x25a0, 0x06, ODT_REC, &ODObjs.o_25A0_thr_field_supp_i_r, NULL},
    {0x25b0, 0x06, ODT_REC, &ODObjs.o_25B0_tmr_field_supp, NULL},
    {0x25c0, 0x04, ODT_REC, &ODObjs.o_25C0_cnt_start, NULL},
    {0x25d0, 0x07, ODT_REC, &ODObjs.o_25D0_filter_zcd_ua, NULL},
    {0x25e0, 0x07, ODT_REC, &ODObjs.o_25E0_filter_zcd_ub, NULL},
    {0x25f0, 0x07, ODT_REC, &ODObjs.o_25F0_filter_zcd_uc, NULL},
    {0x2600, 0x07, ODT_REC, &ODObjs.o_2600_filter_zcd_slip, NULL},
    {0x2610, 0x07, ODT_REC, &ODObjs.o_2610_filter_freq_ua, NULL},
    {0x2620, 0x07, ODT_REC, &ODObjs.o_2620_filter_freq_ub, NULL},
    {0x2630, 0x07, ODT_REC, &ODObjs.o_2630_filter_freq_uc, NULL},
    {0x2640, 0x07, ODT_REC, &ODObjs.o_2640_filter_freq_slip, NULL},
    {0x2650, 0x07, ODT_REC, &ODObjs.o_2650_filter_mean_iarm, NULL},
    {0x2660, 0x07, ODT_REC, &ODObjs.o_2660_filter_mean_uarm, NULL},
    {0x2670, 0x07, ODT_REC, &ODObjs.o_2670_filter_mean_irstart, NULL},
    {0x2680, 0x06, ODT_REC, &ODObjs.o_2680_tmr_start_min_forcing, NULL},
    {0x2690, 0x06, ODT_REC, &ODObjs.o_2690_tmr_start_max_forcing, NULL},
    {0x26a0, 0x0a, ODT_REC, &ODObjs.o_26A0_tmr_start_stab_forcing, NULL},
    {0x26b0, 0x06, ODT_REC, &ODObjs.o_26B0_thr_start_q_le_zero, NULL},
    {0x26c0, 0x06, ODT_REC, &ODObjs.o_26C0_and_start_min_forcing_end, NULL},
    {0x26d0, 0x06, ODT_REC, &ODObjs.o_26D0_or_start_forcing_end, NULL},
    {0x26e0, 0x09, ODT_REC, &ODObjs.o_26E0_mux_field_regs, NULL},
    {0x26f0, 0x07, ODT_REC, &ODObjs.o_26F0_lim_field_regs_curr_ref, NULL},
    {0x2700, 0x07, ODT_REC, &ODObjs.o_2700_mux_field_force_ref, NULL},
    {0x2710, 0x0a, ODT_REC, &ODObjs.o_2710_mot_pot_field_test, NULL},
    {0x2720, 0x0a, ODT_REC, &ODObjs.o_2720_mot_pot_manual_curr_ref, NULL},
    {0x2730, 0x09, ODT_REC, &ODObjs.o_2730_mux_curr_ref, NULL},
    {0x2740, 0x0c, ODT_REC, &ODObjs.o_2740_pid_i, NULL},
    {0x2750, 0x0c, ODT_REC, &ODObjs.o_2750_pid_coefs_i, NULL},
    {0x2760, 0x61, ODT_REC, &ODObjs.o_2760_ph3c, NULL},
    {0x2770, 0x0b, ODT_REC, &ODObjs.o_2770_triacs, NULL},
    {0x2780, 0x35, ODT_REC, &ODObjs.o_2780_lrm, NULL},
    {0x2790, 0x2b, ODT_REC, &ODObjs.o_2790_motor, NULL},
    {0x27a0, 0x57, ODT_REC, &ODObjs.o_27A0_prot, NULL},
    {0x27b0, 0x03, ODT_REC, &ODObjs.o_27B0_canopen, NULL},
    {0x27c0, 0x03, ODT_REC, &ODObjs.o_27C0_storage, NULL},
    {0x27d0, 0x04, ODT_REC, &ODObjs.o_27D0_settings, NULL},
    {0x0000, 0x00, 0, NULL, NULL}
};

static OD_t _OD = {
    (sizeof(ODList) / sizeof(ODList[0])) - 1,
    &ODList[0]
};

OD_t *OD = &_OD;


