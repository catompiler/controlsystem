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
#define PRIORITY(GRP, SUB) (((GRP) << (SUBPRIORITY_BITS)) | ((SUB) & (GROUP_PRIORITY_MASK)))


//! Таймер-счётчик высокого разрешения.
#define SYS_CNT_TIM_IRQ_PRIORITY PRIORITY(4, 0)


//! Таймер АЦП.
#define ADC_TIM_IRQ_PRIORITY PRIORITY(8, 0)
//! Таймер системы.
#define SYS_TIM_IRQ_PRIORITY PRIORITY(8, 1)
//! Таймер 1 мс.
#define MS_TIM_IRQ_PRIORITY PRIORITY(9, 0)
//! Таймер сети.
#define NET_TIM_IRQ_PRIORITY PRIORITY(10, 0)

////! .
//#define _IRQ_PRIORITY PRIORITY(,)


#endif /* INTERRUPTS_PRIORITY_H_ */
