#if 0

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "eeprom_xmc4xxx.c"
#endif

#if defined(PORT_POSIX)
#include "eeprom_posix.c"
#endif

#endif
