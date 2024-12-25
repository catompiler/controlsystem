#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "ms_timer_xmc4xxx.c"
#endif

#if defined(PORT_POSIX)
#include "ms_timer_thread.c"
#endif
