#include "interrupts.h"
#include "priority.h"
#include "hardware/config.h"
#include "cpu.h"


void interrupts_init(void)
{
    // Grouping.
    NVIC_SetPriorityGrouping(GROUP_PRIORITY_VALUE);

    // Priorities.
    NVIC_SetPriority(SYS_CNT_TIM_IRQn, SYS_CNT_TIM_IRQ_PRIORITY);
    NVIC_SetPriority(ADC_TIM_IRQn, ADC_TIM_IRQ_PRIORITY);
    NVIC_SetPriority(SYS_TIM_IRQn, SYS_TIM_IRQ_PRIORITY);
    NVIC_SetPriority(MS_TIM_IRQn, MS_TIM_IRQ_PRIORITY);
    NVIC_SetPriority(NET_TIM_IRQn, NET_TIM_IRQ_PRIORITY);

    // Enabling.
    NVIC_EnableIRQ(SYS_CNT_TIM_IRQn);
    NVIC_EnableIRQ(ADC_TIM_IRQn);
    NVIC_EnableIRQ(SYS_TIM_IRQn);
    NVIC_EnableIRQ(MS_TIM_IRQn);
    NVIC_EnableIRQ(NET_TIM_IRQn);
}

