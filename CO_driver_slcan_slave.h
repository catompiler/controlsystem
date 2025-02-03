#ifndef CO_DRIVER_SLCAN_SLAVE_H_
#define CO_DRIVER_SLCAN_SLAVE_H_


#include "CO_driver_target.h"


// Необходимость данных порта в структуре CANrx.
#ifndef CO_DRIVER_CANRX_PORT_DATA_NEEDED
//#define CO_DRIVER_CANRX_PORT_DATA_NEEDED
#endif

// Необходимость указателя порта в структуре CANrx.
#ifndef CO_DRIVER_CANRX_PORT_PTR_NEEDED
//#define CO_DRIVER_CANRX_PORT_PTR_NEEDED
#endif

// Необходимость данных порта в структуре CANtx.
#ifndef CO_DRIVER_CANTX_PORT_DATA_NEEDED
//#define CO_DRIVER_CANTX_PORT_DATA_NEEDED
#endif

// Необходимость указателя порта в структуре CANtx.
#ifndef CO_DRIVER_CANTX_PORT_PTR_NEEDED
//#define CO_DRIVER_CANTX_PORT_PTR_NEEDED
#endif

// Необходимость данных порта в структуре CANmodule.
#ifndef CO_DRIVER_CANMODULE_PORT_DATA_NEEDED
//#define CO_DRIVER_CANMODULE_PORT_DATA_NEEDED
#endif

// Необходимость указателя порта в структуре CANmodule.
#ifndef CO_DRIVER_CANMODULE_PORT_PTR_NEEDED
//#define CO_DRIVER_CANMODULE_PORT_PTR_NEEDED
#endif


CO_driver_id_t CO_driver_init_slcan_slave(CO_driver_t* drv);


#endif /* CO_DRIVER_SLCAN_SLAVE_H_ */
