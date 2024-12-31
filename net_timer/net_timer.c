#if 0

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "net_timer_xmc4xxx.c"
#endif

#if defined(PORT_POSIX)
#include "net_timer_thread.c"
#endif

#endif
