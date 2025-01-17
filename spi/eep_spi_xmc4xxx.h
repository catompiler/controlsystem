
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef EEP_SPI_XMC4XXX_H
#define EEP_SPI_XMC4XXX_H

#include "defs/defs.h"
#include "errors/errors.h"
#include <spi/spi_xmc4xxx.h>


//! Частота тактирующих импульсов.
#define EEP_SPI_FREQ 10000000

//! Oversampling.
#define EEP_SPI_OVERSAMPLING 2


/**
 * Инициализирует периферию и шину SPI.
 * @param spi_bus Шина SPI.
 * @return Код ошибки.
 */
EXTERN err_t eep_spi_init(spi_bus_t* spi_bus);

#endif /* EEP_SPI_XMC4XXX_H */

#endif
