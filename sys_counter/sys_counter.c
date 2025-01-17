#if 0

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "sys_counter_xmc4xxx.c"
#endif

#if defined(PORT_POSIX)
#include "sys_counter_posix.c"
#endif

#endif
