#include "port.h"

#ifndef HARDWARE_CONFIG_H_
#define HARDWARE_CONFIG_H_


#if defined(PORT_KIT_XMC45_RELAX_LITE_V1)
#include "config_kit_xmc45_relax_lite_v1.h"
#endif

#if defined(PORT_TVU_V2_0)
#include "config_tvu_v2_0.h"
#endif

#if defined(PORT_POSIX)
#endif


#endif /* HARDWARE_CONFIG_H_ */
