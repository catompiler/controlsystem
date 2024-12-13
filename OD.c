#define OD_DEFINITION
#include "301/CO_ODinterface.h"
#include "OD.h"

#if CO_VERSION_MAJOR < 4
#error This Object dictionary is compatible with CANopenNode V4.0 and above!
#endif


#include <regs_data.h>

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
    OD_obj_record_t o_2000_conf[4];
    OD_obj_record_t o_2050_sysTime[4];
    OD_obj_record_t o_2100_motor[8];
    OD_obj_record_t o_2300_adc[13];
    OD_obj_record_t o_2400_meas[19];
    OD_obj_record_t o_2500_model[21];
    OD_obj_record_t o_2600_phaseAmpl[7];
    OD_obj_record_t o_2700_lineFreq[16];
    OD_obj_record_t o_2800_armFreq[7];
    OD_obj_record_t o_2900_rms[16];
    OD_obj_record_t o_3000_mean[10];
    OD_obj_record_t o_3100_power[10];
    OD_obj_record_t o_3200_powerFactor[4];
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
.o_2000_conf = {
    {
    .dataOrig = &regs_data.conf.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &conf.p_U_nom,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.p_I_nom,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &conf.p_f_nom,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2050_sysTime = {
    {
    .dataOrig = &regs_data.sysTime.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &sys_time.r_counter_ms,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_time.r_counter_s,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &sys_time.r_run_counter_s,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2100_motor = {
    {
    .dataOrig = &regs_data.motor.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &motor.p_f_nom,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.p_s_U_nom,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.p_s_I_nom,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_P_base,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.r_s_M_base,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.p_U_nom,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &motor.p_I_nom,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2300_adc = {
    {
    .dataOrig = &regs_data.adc.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &adc.out_Ua_raw,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ub_raw,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Uc_raw,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ua,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Ub,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.out_Uc,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ua_gain,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ua_offset,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ub_gain,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Ub_offset,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Uc_gain,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &adc.p_Uc_offset,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2400_meas = {
    {
    .dataOrig = &regs_data.meas.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mux_Umains.out_A,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.out_B,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Umains.out_C,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.out_A,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.out_B,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Imains.out_C,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Uarm.out_value,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Iarm.out_value,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Irstart.out_value,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.out_A,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.out_B,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Ucell.out_C,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_Ucell.out_A,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_Ucell.out_B,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_Ucell.out_C,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.out_A,
    .subIndex = 16,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.out_B,
    .subIndex = 17,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mux_Icell.out_C,
    .subIndex = 18,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2500_model = {
    {
    .dataOrig = &regs_data.model.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &lrm.in_stator_Ua,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_stator_Ub,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_stator_Uc,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_stator_Ia,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_stator_Ib,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_stator_Ic,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_lrm_I_stator.out_A,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_lrm_I_stator.out_B,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_lrm_I_stator.out_C,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Ufld,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Ifld,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Irstart,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_M,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_w,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_Ua,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_Ub,
    .subIndex = 16,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.in_Uc,
    .subIndex = 17,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Ia,
    .subIndex = 18,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Ib,
    .subIndex = 19,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &lrm.out_Ic,
    .subIndex = 20,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2600_phaseAmpl = {
    {
    .dataOrig = &regs_data.phaseAmpl.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &phase_ampl_Ua.out_phase,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Ua.out_ampl,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Ub.out_phase,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Ub.out_ampl,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Uc.out_phase,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &phase_ampl_Uc.out_ampl,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2700_lineFreq = {
    {
    .dataOrig = &regs_data.lineFreq.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_zcd_Ua.p_T,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ua.out_value,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ua.out_freq,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ua.p_T,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ua.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ub.p_T,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Ub.out_value,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Ub.out_freq,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ub.p_T,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Ub.out_value,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Uc.p_T,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_Uc.out_value,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_Uc.out_freq,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Uc.p_T,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_Uc.out_value,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2800_armFreq = {
    {
    .dataOrig = &regs_data.armFreq.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &filter_zcd_slip.p_T,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_zcd_slip.out_value,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &zcd_slip.out_freq,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_slip.p_T,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_freq_slip.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &slip.out_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_2900_rms = {
    {
    .dataOrig = &regs_data.rms.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &rms_Ua.out_value,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ub.out_value,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Uc.out_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ia.out_value,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ib.out_value,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_Ic.out_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ua.out_value,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ub.out_value,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Uc.out_value,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ua_phase.out_value,
    .subIndex = 10,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ub_phase.out_value,
    .subIndex = 11,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Uc_phase.out_value,
    .subIndex = 12,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ia.out_value,
    .subIndex = 13,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ib.out_value,
    .subIndex = 14,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &rms_cell_Ic.out_value,
    .subIndex = 15,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_3000_mean = {
    {
    .dataOrig = &regs_data.mean.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &mean_Uarm.out_value,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Uarm.p_T,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Uarm.out_value,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_Iarm.out_value,
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
    .dataOrig = &filter_mean_Iarm.out_value,
    .subIndex = 6,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &mean_Irstart.out_value,
    .subIndex = 7,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Irstart.p_T,
    .subIndex = 8,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &filter_mean_Irstart.out_value,
    .subIndex = 9,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    }
},
.o_3100_power = {
    {
    .dataOrig = &regs_data.power.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &power_A.out_S,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_A.out_P,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_A.out_Q,
    .subIndex = 3,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_B.out_S,
    .subIndex = 4,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_B.out_P,
    .subIndex = 5,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_B.out_Q,
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
.o_3200_powerFactor = {
    {
    .dataOrig = &regs_data.powerFactor.count,
    .subIndex = 0,
    .attribute = ODA_SDO_R,
    .dataLength = 1
    },
    {
    .dataOrig = &power_factor.out_cos_phi,
    .subIndex = 1,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_factor.out_sin_phi,
    .subIndex = 2,
    .attribute = ODA_SDO_RW | ODA_MB,
    .dataLength = 4
    },
    {
    .dataOrig = &power_factor.out_tan_phi,
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
    {0x2000, 0x04, ODT_REC, &ODObjs.o_2000_conf, NULL},
    {0x2050, 0x04, ODT_REC, &ODObjs.o_2050_sysTime, NULL},
    {0x2100, 0x08, ODT_REC, &ODObjs.o_2100_motor, NULL},
    {0x2300, 0x0d, ODT_REC, &ODObjs.o_2300_adc, NULL},
    {0x2400, 0x13, ODT_REC, &ODObjs.o_2400_meas, NULL},
    {0x2500, 0x15, ODT_REC, &ODObjs.o_2500_model, NULL},
    {0x2600, 0x07, ODT_REC, &ODObjs.o_2600_phaseAmpl, NULL},
    {0x2700, 0x10, ODT_REC, &ODObjs.o_2700_lineFreq, NULL},
    {0x2800, 0x07, ODT_REC, &ODObjs.o_2800_armFreq, NULL},
    {0x2900, 0x10, ODT_REC, &ODObjs.o_2900_rms, NULL},
    {0x3000, 0x0a, ODT_REC, &ODObjs.o_3000_mean, NULL},
    {0x3100, 0x0a, ODT_REC, &ODObjs.o_3100_power, NULL},
    {0x3200, 0x04, ODT_REC, &ODObjs.o_3200_powerFactor, NULL},
    {0x0000, 0x00, 0, NULL, NULL}
};

static OD_t _OD = {
    (sizeof(ODList) / sizeof(ODList[0])) - 1,
    &ODList[0]
};

OD_t *OD = &_OD;


