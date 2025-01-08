#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef EEP_SPI_XMC4XXX_H
#define EEP_SPI_XMC4XXX_H

#include "defs/defs.h"
#include "errors/errors.h"


//! Частота тактирующих импульсов.
#define EEP_SPI_FREQ 10000000


EXTERN err_t eep_spi_init(void);

#endif /* EEP_SPI_XMC4XXX_H */

#endif
