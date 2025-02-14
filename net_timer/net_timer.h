#ifndef NET_TIMER_H
#define NET_TIMER_H

#include "port.h"

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "net_timer_xmc4xxx.h"
#endif

#if defined(PORT_POSIX)
#include "net_timer_thread.h"
#endif

#endif /* NET_TIMER_H */
