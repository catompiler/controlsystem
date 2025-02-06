#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "defs/defs.h"

//! Инициализирует приоритеты и разрешает соответствующие прерывания.
EXTERN void interrupts_init(void);

//! Разрешает прерывания от ПДП.
EXTERN void interrupts_enable_dma(void);

//! Разрешает прерывания от CAN.
EXTERN void interrupts_enable_can(void);

//! Разрешает прерывания от EEP spi.
EXTERN void interrupts_enable_eep_spi(void);

//! Разрешает прерывания от UART stdio.
EXTERN void interrupts_enable_stdio_uart(void);

//! Разрешает прерывания от системного счётчика.
EXTERN void interrupts_enable_sys_counter(void);

//! Разрешает настроенные прерывания.
EXTERN void interrupts_inited_enable(void);

//! Запрещение прерываний.
#define interrupts_disable() __disable_irq()
//! Разрешение прерываний.
#define interrupts_enable() __enable_irq()


#endif /* INTERRUPTS_H */

#endif
