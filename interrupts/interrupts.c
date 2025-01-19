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
    NVIC_SetPriority(DMA1_IRQn, DMA1_IRQ_PRIORITY);
    NVIC_SetPriority(DMA2_IRQn, DMA2_IRQ_PRIORITY);
    NVIC_SetPriority(EEP_SPI_USIC_CH_IRQn, EEP_SPI_IRQ_PRIORITY);
    NVIC_SetPriority(CAN_IRQn, CAN_IRQ_PRIORITY);
}


void interrupts_enable_dma(void)
{
    NVIC_EnableIRQ(DMA1_IRQn);
    NVIC_EnableIRQ(DMA2_IRQn);
}

void interrupts_enable_can(void)
{
    NVIC_EnableIRQ(CAN_IRQn);
}

void interrupts_enable_eep_spi(void)
{
    NVIC_EnableIRQ(EEP_SPI_USIC_CH_IRQn);
}

void interrupts_enable_stdio_uart(void)
{
    NVIC_EnableIRQ(STDIO_UART_USIC_CH_IRQn);
}

void interrupts_enable_sys_counter(void)
{
    NVIC_EnableIRQ(SYS_CNT_TIM_IRQn);
}


void interrupts_inited_enable(void)
{
    // Enabling.
    NVIC_EnableIRQ(SYS_CNT_TIM_IRQn);
    NVIC_EnableIRQ(ADC_TIM_IRQn);
    NVIC_EnableIRQ(SYS_TIM_IRQn);
    NVIC_EnableIRQ(MS_TIM_IRQn);
    NVIC_EnableIRQ(NET_TIM_IRQn);
    NVIC_EnableIRQ(STDIO_UART_USIC_CH_IRQn);
    NVIC_EnableIRQ(DMA1_IRQn);
    NVIC_EnableIRQ(DMA2_IRQn);
    NVIC_EnableIRQ(EEP_SPI_USIC_CH_IRQn);
}

#endif
