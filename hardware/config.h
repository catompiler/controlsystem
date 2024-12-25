#ifndef HARDWARE_CONFIG_H_
#define HARDWARE_CONFIG_H_

#include "cpu.h"


// Timers.
// Periodic.
#define PERIODIC_TIMS_RESET_ENABLE() do{\
        SCU_RESET->PRSET1 = SCU_RESET_PRSET1_CCU43RS_Msk;\
        __DMB();\
    }while(0)
#define PERIODIC_TIMS_RESET_DISABLE() do{\
        SCU_RESET->PRCLR1 = SCU_RESET_PRCLR1_CCU43RS_Msk;\
        __DMB();\
    }while(0)
#define PERIODIC_TIMS_CLOCK_ENABLE() do{\
        SCU_CLK->CLKSET = SCU_CLK_CLKSET_CCUCEN_Msk;\
        __DSB();\
        ADC_TIM_CCU4->GIDLC = CCU4_GIDLC_SPRB_Msk;\
        __DMB();\
    }while(0)
#define PERIODIC_TIMS_CLOCK_DISABLE() do{\
        ADC_TIM_CCU4->GIDLS = CCU4_GIDLS_CPRB_Msk;\
        __DSB();\
        SCU_CLK->CLKCLR = SCU_CLK_CLKCLR_CCUCDI_Msk;\
        __DMB();\
    }while(0)
// Adc timer.
#define ADC_TIM_CCU4 CCU43
#define ADC_TIM_CCU4_CC4 CCU43_CC40
#define ADC_TIM_IDLE_CLR_Msk CCU4_GIDLC_CS0I_Msk
#define ADC_TIM_IDLE_SET_Msk CCU4_GIDLS_SS0I_Msk
#define ADC_TIM_SR 0
#define ADC_TIM_IRQ_Handler CCU43_0_IRQHandler
#define ADC_TIM_IRQn CCU43_0_IRQn
// Sys timer.
#define SYS_TIM_CCU4 CCU43
#define SYS_TIM_CCU4_CC4 CCU43_CC41
#define SYS_TIM_IDLE_CLR_Msk CCU4_GIDLC_CS1I_Msk
#define SYS_TIM_IDLE_SET_Msk CCU4_GIDLS_SS1I_Msk
#define SYS_TIM_SR 1
#define SYS_TIM_IRQ_Handler CCU43_1_IRQHandler
#define SYS_TIM_IRQn CCU43_1_IRQn
// Ms timer.
#define MS_TIM_CCU4 CCU43
#define MS_TIM_CCU4_CC4 CCU43_CC42
#define MS_TIM_IDLE_CLR_Msk CCU4_GIDLC_CS2I_Msk
#define MS_TIM_IDLE_SET_Msk CCU4_GIDLS_SS2I_Msk
#define MS_TIM_SR 2
#define MS_TIM_IRQ_Handler CCU43_2_IRQHandler
#define MS_TIM_IRQn CCU43_2_IRQn
// Net timer.
#define NET_TIM_CCU4 CCU43
#define NET_TIM_CCU4_CC4 CCU43_CC43
#define NET_TIM_IDLE_CLR_Msk CCU4_GIDLC_CS3I_Msk
#define NET_TIM_IDLE_SET_Msk CCU4_GIDLS_SS3I_Msk
#define NET_TIM_SR 3
#define NET_TIM_IRQ_Handler CCU43_3_IRQHandler
#define NET_TIM_IRQn CCU43_3_IRQn

// Counting.
#define COUNTING_TIMS_RESET_ENABLE() do{\
        SCU_RESET->PRSET0 = SCU_RESET_PRSET0_CCU42RS_Msk;\
        __DMB();\
    }while(0)
#define COUNTING_TIMS_RESET_DISABLE() do{\
        SCU_RESET->PRCLR0 = SCU_RESET_PRCLR0_CCU42RS_Msk;\
        __DMB();\
    }while(0)
#define COUNTING_TIMS_CLOCK_ENABLE() do{\
        SCU_CLK->CLKSET = SCU_CLK_CLKSET_CCUCEN_Msk;\
        __DSB();\
        SYS_CNT_TIM_CCU4->GIDLC = CCU4_GIDLC_SPRB_Msk;\
        __DMB();\
    }while(0)
#define COUNTING_TIMS_CLOCK_DISABLE() do{\
        SYS_CNT_TIM_CCU4->GIDLS = CCU4_GIDLS_CPRB_Msk;\
        __DSB();\
        SCU_CLK->CLKCLR = SCU_CLK_CLKCLR_CCUCDI_Msk;\
        __DMB();\
    }while(0)
// Adc timer.
#define SYS_CNT_TIM_CCU4 CCU42
#define SYS_CNT_TIM_CCU4_CC4 CCU42_CC43
#define SYS_CNT_TIM_IDLE_CLR_Msk CCU4_GIDLC_CS3I_Msk
#define SYS_CNT_TIM_IDLE_SET_Msk CCU4_GIDLS_SS3I_Msk
#define SYS_CNT_TIM_SR 3
#define SYS_CNT_TIM_IRQ_Handler CCU42_3_IRQHandler
#define SYS_CNT_TIM_IRQn CCU42_3_IRQn



#endif /* HARDWARE_CONFIG_H_ */
