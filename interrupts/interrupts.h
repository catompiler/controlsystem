#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "defs/defs.h"

//! Инициализирует приоритеты и разрешает соответствующие прерывания.
EXTERN void interrupts_init(void);

//! Разрешает настроенные прерывания.
EXTERN void interrupts_init_enable(void);

//! Запрещение прерываний.
#define interrupts_disable() __disable_irq()
//! Разрешение прерываний.
#define interrupts_enable() __enable_irq()


#endif /* INTERRUPTS_H */

#endif
