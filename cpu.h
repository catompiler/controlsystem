#ifndef CPU_H
#define CPU_H

#include "port.h"

#if defined(PORT_XMC4500)
#include "XMC4500.h"
#define CPU_FREQ (120000000)
#elif defined(PORT_XMC4700)
#include "XMC4700.h"
#define CPU_FREQ (144000000)
#elif defined(PORT_STM32F10X_HD)
#include <stm32f10x.h>
#define CPU_FREQ (72000000)
#elif defined(PORT_POSIX)
#else
#error "Unknown CPU!"
#endif


#endif /* CPU_H */
