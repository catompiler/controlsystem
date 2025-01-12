#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef HARDWARE_H
#define HARDWARE_H

#include "config.h"
#include "defs/defs.h"

//! Сбрасывает и разрешает тактирование периодических таймеров.
EXTERN void hardware_init_periodic_timers(void);

//! Сбрасывает и разрешает тактирование считающих таймеров.
EXTERN void hardware_init_counting_timers(void);

//! Сбрасывает и разрешает тактирование уартов.
EXTERN void hardware_init_usarts(void);

//! Сбрасывает и разрешает тактирование SPI.
EXTERN void hardware_init_spis(void);

//! Сбрасывает и разрешает тактирование ПДП.
EXTERN void hardware_init_dma(void);


#endif /* HARDWARE_H */

#endif
