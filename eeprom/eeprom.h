#ifndef EEPROM_H
#define EEPROM_H

#include "port.h"

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "eeprom_xmc4xxx.h"
#endif

#if defined(PORT_POSIX)
#include "eeprom_posix.h"
#endif

#endif /* EEPROM_H */
