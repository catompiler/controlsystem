#ifndef SPI_H
#define SPI_H

#include "port.h"

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "spi_xmc4xxx.h"
#endif

#if defined(PORT_POSIX)
#endif

#endif /* SPI_H */
