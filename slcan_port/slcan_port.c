#if 0

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "slcan_port_xmc4xxx.c"
#endif

#if defined(PORT_POSIX)
#include "slcan_port_posix.c"
#endif

#endif
