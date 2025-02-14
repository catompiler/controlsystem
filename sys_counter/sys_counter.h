#ifndef SYSTEM_COUNTER_H
#define SYSTEM_COUNTER_H

#include "port.h"

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "sys_counter_xmc4xxx.h"
#endif

#if defined(PORT_POSIX)
#include "sys_counter_posix.h"
#endif

#endif /* SYSTEM_COUNTER_H */

