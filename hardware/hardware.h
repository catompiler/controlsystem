#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef HARDWARE_H
#define HARDWARE_H

#include "config.h"
#include "defs/defs.h"


EXTERN void hardware_init_periodic_timers(void);
EXTERN void hardware_init_counting_timers(void);
EXTERN void hardware_init_usarts(void);


#endif /* HARDWARE_H */

#endif
