#if 0

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "adc_timer_xmc4xxx.c"
#endif

#if defined(PORT_POSIX)
#include "adc_timer_thread.c"
#endif

#endif
