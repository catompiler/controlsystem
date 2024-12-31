#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

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
    NVIC_SetPriority(STDIO_UART_USIC_CH_IRQn, STDIO_UART_IRQ_PRIORITY);
}


void interrupts_init_enable(void)
{
    // Enabling.
    NVIC_EnableIRQ(SYS_CNT_TIM_IRQn);
    NVIC_EnableIRQ(ADC_TIM_IRQn);
    NVIC_EnableIRQ(SYS_TIM_IRQn);
    NVIC_EnableIRQ(MS_TIM_IRQn);
    NVIC_EnableIRQ(NET_TIM_IRQn);
    NVIC_EnableIRQ(STDIO_UART_USIC_CH_IRQn);
}

#endif
