#ifndef REG_IDS_H
#define REG_IDS_H


// THIS FILE IS GENERATED AUTOMATICALLY!
// DO NOT EDIT THIS FILE!

// Modules for registers

// Begin

// Conf
// Nominal values
#define REG_ID_CONF_U_NOM    0
#define REG_ID_CONF_I_NOM    1
#define REG_ID_CONF_F_NOM    2

// Motor
// Nominal values
#define REG_ID_MOTOR_F_NOM    50
// Nominal stator values
#define REG_ID_MOTOR_S_U_NOM    51
#define REG_ID_MOTOR_S_I_NOM    52
#define REG_ID_MOTOR_S_P_NOM    53
#define REG_ID_MOTOR_S_M_NOM    54
// Nominal rotor values
#define REG_ID_MOTOR_U_NOM    55
#define REG_ID_MOTOR_I_NOM    56


// SysTime
#define REG_ID_SYS_TIME_COUNTER_MS    200
#define REG_ID_SYS_TIME_COUNTER_S    201
#define REG_ID_SYS_TIME_RUN_COUNTER_S    202

// ADC
// Phases voltage
// Raw
#define REG_ID_ADC_UA_RAW    300
#define REG_ID_ADC_UB_RAW    301
#define REG_ID_ADC_UC_RAW    302
// Rel
#define REG_ID_ADC_UA    303
#define REG_ID_ADC_UB    304
#define REG_ID_ADC_UC    305
// Calibration
#define REG_ID_ADC_UA_GAIN    306
#define REG_ID_ADC_UA_OFFSET    307
#define REG_ID_ADC_UB_GAIN    308
#define REG_ID_ADC_UB_OFFSET    309
#define REG_ID_ADC_UC_GAIN    310
#define REG_ID_ADC_UC_OFFSET    311

// Measurement
#define REG_ID_MEAS_UA    500
#define REG_ID_MEAS_UB    501
#define REG_ID_MEAS_UC    502
#define REG_ID_MEAS_IA    503
#define REG_ID_MEAS_IB    504
#define REG_ID_MEAS_IC    505
#define REG_ID_MEAS_UARM    506
#define REG_ID_MEAS_IARM    507
#define REG_ID_MEAS_IRSTART    508
#define REG_ID_MEAS_CELL_UAB    509
#define REG_ID_MEAS_CELL_UBC    510
#define REG_ID_MEAS_CELL_UCA    511
#define REG_ID_MEAS_CELL_UA    512
#define REG_ID_MEAS_CELL_UB    513
#define REG_ID_MEAS_CELL_UC    514
#define REG_ID_MEAS_CELL_IA    515
#define REG_ID_MEAS_CELL_IB    516
#define REG_ID_MEAS_CELL_IC    517

// Model
#define REG_ID_MODEL_STATOR_UA    700
#define REG_ID_MODEL_STATOR_UB    701
#define REG_ID_MODEL_STATOR_UC    702
#define REG_ID_MODEL_STATOR_IAB    703
#define REG_ID_MODEL_STATOR_IBC    704
#define REG_ID_MODEL_STATOR_ICA    705
#define REG_ID_MODEL_STATOR_IA    706
#define REG_ID_MODEL_STATOR_IB    707
#define REG_ID_MODEL_STATOR_IC    708
#define REG_ID_MODEL_ROTOR_U    709
#define REG_ID_MODEL_ROTOR_I    710
#define REG_ID_MODEL_R_START_I    711
#define REG_ID_MODEL_MOTOR_M    712
#define REG_ID_MODEL_MOTOR_W    713
#define REG_ID_MODEL_RECTIFIER_UA    714
#define REG_ID_MODEL_RECTIFIER_UB    715
#define REG_ID_MODEL_RECTIFIER_UC    716
#define REG_ID_MODEL_RECTIFIER_IA    717
#define REG_ID_MODEL_RECTIFIER_IB    718
#define REG_ID_MODEL_RECTIFIER_IC    719

// Phase and Amplitude.
#define REG_ID_PHASE_AMPL_UA_PHASE    1000
#define REG_ID_PHASE_AMPL_UA_AMPL    1001
#define REG_ID_PHASE_AMPL_UB_PHASE    1002
#define REG_ID_PHASE_AMPL_UB_AMPL    1003
#define REG_ID_PHASE_AMPL_UC_PHASE    1004
#define REG_ID_PHASE_AMPL_UC_AMPL    1005

// Phase A.
#define REG_ID_LINE_FREQ_UA_FILTER_T    1200
#define REG_ID_LINE_FREQ_UA_FILT    1201
#define REG_ID_LINE_FREQ_UA_FREQ    1202
#define REG_ID_LINE_FREQ_UA_FREQ_FILTER_T    1203
#define REG_ID_LINE_FREQ_UA_FREQ_FILT    1204
// Phase B.
#define REG_ID_LINE_FREQ_UB_FILTER_T    1205
#define REG_ID_LINE_FREQ_UB_FILT    1206
#define REG_ID_LINE_FREQ_UB_FREQ    1207
#define REG_ID_LINE_FREQ_UB_FREQ_FILTER_T    1208
#define REG_ID_LINE_FREQ_UB_FREQ_FILT    1209
// Phase C.
#define REG_ID_LINE_FREQ_UC_FILTER_T    1210
#define REG_ID_LINE_FREQ_UC_FILT    1211
#define REG_ID_LINE_FREQ_UC_FREQ    1212
#define REG_ID_LINE_FREQ_UC_FREQ_FILTER_T    1213
#define REG_ID_LINE_FREQ_UC_FREQ_FILT    1214


// I r start.
#define REG_ID_ARM_FREQ_IRSTART_FILTER_T    1250
#define REG_ID_ARM_FREQ_IRSTART_FILT    1251
#define REG_ID_ARM_FREQ_IRSTART_FREQ    1252
#define REG_ID_ARM_FREQ_IRSTART_FREQ_FILTER_T    1253
#define REG_ID_ARM_FREQ_IRSTART_FREQ_FILT    1254
// Slip.
#define REG_ID_ARM_FREQ_SLIP    1255


#define REG_ID_RMS_UA    1400
#define REG_ID_RMS_UB    1401
#define REG_ID_RMS_UC    1402
#define REG_ID_RMS_IA    1403
#define REG_ID_RMS_IB    1404
#define REG_ID_RMS_IC    1405
#define REG_ID_RMS_CELL_UA    1406
#define REG_ID_RMS_CELL_UB    1407
#define REG_ID_RMS_CELL_UC    1408
#define REG_ID_RMS_CELL_UA_PHASE    1409
#define REG_ID_RMS_CELL_UB_PHASE    1410
#define REG_ID_RMS_CELL_UC_PHASE    1411
#define REG_ID_RMS_CELL_IA    1412
#define REG_ID_RMS_CELL_IB    1413
#define REG_ID_RMS_CELL_IC    1414

#define REG_ID_MEAN_UARM    1500
#define REG_ID_MEAN_UARM_FILTER_T    1501
#define REG_ID_MEAN_UARM_FILT    1502
#define REG_ID_MEAN_IARM    1503
#define REG_ID_MEAN_IARM_FILTER_T    1504
#define REG_ID_MEAN_IARM_FILT    1505
#define REG_ID_MEAN_IRSTART    1506
#define REG_ID_MEAN_IRSTART_FILTER_T    1507
#define REG_ID_MEAN_IRSTART_FILT    1508

#define REG_ID_POWER_A_S    1600
#define REG_ID_POWER_A_P    1601
#define REG_ID_POWER_A_Q    1602
#define REG_ID_POWER_B_S    1603
#define REG_ID_POWER_B_P    1604
#define REG_ID_POWER_B_Q    1605
#define REG_ID_POWER_C_S    1606
#define REG_ID_POWER_C_P    1607
#define REG_ID_POWER_C_Q    1608

#define REG_ID_POWER_FACTOR_COS_PHI    1700
#define REG_ID_POWER_FACTOR_SIN_PHI    1701
#define REG_ID_POWER_FACTOR_TAN_PHI    1702

// End

#endif /* REG_IDS_H */
