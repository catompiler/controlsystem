#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef INTERRUPTS_PRIORITY_H_
#define INTERRUPTS_PRIORITY_H_

#include "cpu.h"


//! Число бит под-приоритета.
//! 16 приоритетов групп и 4 под-приоритета.
#define SUBPRIORITY_BITS 2
//! Маска под-приоритета.
#define GROUP_PRIORITY_MASK ((1<<(SUBPRIORITY_BITS)) - 1)
//! Значение Group priority.
#define GROUP_PRIORITY_VALUE GROUP_PRIORITY_MASK

//! Значение приоритета.
#define IRQ_PRIORITY(GRP, SUB) (((GRP) << (SUBPRIORITY_BITS)) | ((SUB) & (GROUP_PRIORITY_MASK)))


//! Таймер-счётчик высокого разрешения.
#define SYS_CNT_TIM_IRQ_PRIORITY IRQ_PRIORITY(4, 0)


//! Eeprom SPI.
#define EEP_SPI_IRQ_PRIORITY IRQ_PRIORITY(6, 0)

//! ПДП.
#define DMA1_IRQ_PRIORITY IRQ_PRIORITY(6, 1)
#define DMA2_IRQ_PRIORITY IRQ_PRIORITY(6, 2)


//! Уарт для stdio.
#define STDIO_UART_IRQ_PRIORITY IRQ_PRIORITY(7, 0)


//! Таймер АЦП.
#define ADC_TIM_IRQ_PRIORITY IRQ_PRIORITY(8, 0)
//! Таймер системы.
#define SYS_TIM_IRQ_PRIORITY IRQ_PRIORITY(8, 1)
//! Таймер 1 мс.
#define MS_TIM_IRQ_PRIORITY IRQ_PRIORITY(9, 0)
//! Таймер сети.
#define NET_TIM_IRQ_PRIORITY IRQ_PRIORITY(10, 3)

//! CAN.
#define CAN_IRQ_PRIORITY IRQ_PRIORITY(10, 0)

////! .
//#define _IRQ_PRIORITY PRIORITY(,)


#endif /* INTERRUPTS_PRIORITY_H_ */

#endif
