#ifndef MS_TIMER_H
#define MS_TIMER_H

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "ms_timer_xmc4xxx.h"
#endif

#if defined(PORT_POSIX)
#include "ms_timer_thread.h"
#endif

#endif /* MS_TIMER_H */
