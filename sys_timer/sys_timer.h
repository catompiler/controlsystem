#ifndef SYS_TIMER_H
#define SYS_TIMER_H

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "sys_timer_xmc4xxx.h"
#endif

#if defined(PORT_POSIX)
#include "sys_timer_thread.h"
#endif

#endif /* SYS_TIMER_H */
