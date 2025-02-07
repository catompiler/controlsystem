#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef HARDWARE_CONFIG_H_
#define HARDWARE_CONFIG_H_

#include "cpu.h"



// PORTS.
#define PORTS_RESET_ENABLE() do{\
        SCU_RESET->PRSET1 = SCU_RESET_PRSET1_PPORTSRS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT1 & SCU_RESET_PRSTAT1_PPORTSRS_Msk) == 0){ __NOP(); }\
    }while(0)
#define PORTS_RESET_DISABLE() do{\
        SCU_RESET->PRCLR1 = SCU_RESET_PRCLR1_PPORTSRS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT1 & SCU_RESET_PRSTAT1_PPORTSRS_Msk) != 0){ __NOP(); }\
    }while(0)
#define PORTS_CLOCK_ENABLE() do{\
    }while(0)
#define PORTS_CLOCK_DISABLE() do{\
    }while(0)

// DMA.
#define DMA_RESET_ENABLE() do{\
        SCU_RESET->PRSET2 = (SCU_RESET_PRSET2_DMA0RS_Msk | SCU_RESET_PRSET2_DMA1RS_Msk);\
        __DMB();\
        while((SCU_RESET->PRSTAT2 & (SCU_RESET_PRSTAT2_DMA0RS_Msk | SCU_RESET_PRSTAT2_DMA1RS_Msk)) == 0){ __NOP(); }\
    }while(0)
#define DMA_RESET_DISABLE() do{\
        SCU_RESET->PRCLR2 = (SCU_RESET_PRCLR2_DMA0RS_Msk | SCU_RESET_PRCLR2_DMA1RS_Msk);\
        __DMB();\
        while((SCU_RESET->PRSTAT2 & (SCU_RESET_PRSTAT2_DMA0RS_Msk | SCU_RESET_PRSTAT2_DMA1RS_Msk)) != 0){ __NOP(); }\
    }while(0)
#define DMA_CLOCK_ENABLE() do{\
        GPDMA0->DMACFGREG = GPDMA0_DMACFGREG_DMA_EN_Msk;\
        GPDMA1->DMACFGREG = GPDMA1_DMACFGREG_DMA_EN_Msk;\
        __DSB();\
    }while(0)
#define DMA_CLOCK_DISABLE() do{\
        GPDMA0->DMACFGREG = 0;\
        GPDMA1->DMACFGREG = 0;\
        __DSB();\
    }while(0)
// DMA1.
#define DMA1_IRQ_Handler GPDMA0_0_IRQHandler
#define DMA1_IRQn GPDMA0_0_IRQn
// DMA2.
#define DMA2_IRQ_Handler GPDMA1_0_IRQHandler
#define DMA2_IRQn GPDMA1_0_IRQn


// Timers.
// Periodic.
#define PERIODIC_TIMS_RESET_ENABLE() do{\
        SCU_RESET->PRSET1 = SCU_RESET_PRSET1_CCU43RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT1 & SCU_RESET_PRSTAT1_CCU43RS_Msk) == 0){ __NOP(); }\
    }while(0)
#define PERIODIC_TIMS_RESET_DISABLE() do{\
        SCU_RESET->PRCLR1 = SCU_RESET_PRCLR1_CCU43RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT1 & SCU_RESET_PRSTAT1_CCU43RS_Msk) != 0){ __NOP(); }\
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
#define ADC_TIM_SHADOW_TRANSFER_Msk (CCU4_GCSS_S0SE_Msk | CCU4_GCSS_S0DSE_Msk | CCU4_GCSS_S0PSE_Msk)
#define ADC_TIM_IDLE_CLR_Msk CCU4_GIDLC_CS0I_Msk
#define ADC_TIM_IDLE_SET_Msk CCU4_GIDLS_SS0I_Msk
#define ADC_TIM_SR 0
#define ADC_TIM_IRQ_Handler CCU43_0_IRQHandler
#define ADC_TIM_IRQn CCU43_0_IRQn
// Sys timer.
#define SYS_TIM_CCU4 CCU43
#define SYS_TIM_CCU4_CC4 CCU43_CC41
#define SYS_TIM_SHADOW_TRANSFER_Msk (CCU4_GCSS_S1SE_Msk | CCU4_GCSS_S1DSE_Msk | CCU4_GCSS_S1PSE_Msk)
#define SYS_TIM_IDLE_CLR_Msk CCU4_GIDLC_CS1I_Msk
#define SYS_TIM_IDLE_SET_Msk CCU4_GIDLS_SS1I_Msk
#define SYS_TIM_SR 1
#define SYS_TIM_IRQ_Handler CCU43_1_IRQHandler
#define SYS_TIM_IRQn CCU43_1_IRQn
// Ms timer.
#define MS_TIM_CCU4 CCU43
#define MS_TIM_CCU4_CC4 CCU43_CC42
#define MS_TIM_SHADOW_TRANSFER_Msk (CCU4_GCSS_S2SE_Msk | CCU4_GCSS_S2DSE_Msk | CCU4_GCSS_S2PSE_Msk)
#define MS_TIM_IDLE_CLR_Msk CCU4_GIDLC_CS2I_Msk
#define MS_TIM_IDLE_SET_Msk CCU4_GIDLS_SS2I_Msk
#define MS_TIM_SR 2
#define MS_TIM_IRQ_Handler CCU43_2_IRQHandler
#define MS_TIM_IRQn CCU43_2_IRQn
// Net timer.
#define NET_TIM_CCU4 CCU43
#define NET_TIM_CCU4_CC4 CCU43_CC43
#define NET_TIM_SHADOW_TRANSFER_Msk (CCU4_GCSS_S3SE_Msk | CCU4_GCSS_S3DSE_Msk | CCU4_GCSS_S3PSE_Msk)
#define NET_TIM_IDLE_CLR_Msk CCU4_GIDLC_CS3I_Msk
#define NET_TIM_IDLE_SET_Msk CCU4_GIDLS_SS3I_Msk
#define NET_TIM_SR 3
#define NET_TIM_IRQ_Handler CCU43_3_IRQHandler
#define NET_TIM_IRQn CCU43_3_IRQn

// Counting.
#define COUNTING_TIMS_RESET_ENABLE() do{\
        SCU_RESET->PRSET0 = SCU_RESET_PRSET0_CCU42RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT0 & SCU_RESET_PRSTAT0_CCU42RS_Msk) == 0){ __NOP(); }\
    }while(0)
#define COUNTING_TIMS_RESET_DISABLE() do{\
        SCU_RESET->PRCLR0 = SCU_RESET_PRCLR0_CCU42RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT0 & SCU_RESET_PRSTAT0_CCU42RS_Msk) != 0){ __NOP(); }\
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
#define SYS_CNT_TIM_CCU4_CC4_PRE CCU42_CC40
#define SYS_CNT_TIM_CCU4_CC4_LO CCU42_CC41
#define SYS_CNT_TIM_CCU4_CC4_HI CCU42_CC42
#define SYS_CNT_TIM_IDLE_CLR_Msk (CCU4_GIDLC_CS2I_Msk | CCU4_GIDLC_CS1I_Msk | CCU4_GIDLC_CS0I_Msk)
#define SYS_CNT_TIM_IDLE_SET_Msk (CCU4_GIDLS_SS2I_Msk | CCU4_GIDLS_SS1I_Msk | CCU4_GIDLS_SS0I_Msk)
#define SYS_CNT_TIM_SHADOW_TRANSFER_Msk (CCU4_GCSS_S2SE_Msk | CCU4_GCSS_S1SE_Msk | CCU4_GCSS_S0SE_Msk)
#define SYS_CNT_TIM_SR 2
#define SYS_CNT_TIM_IRQ_Handler CCU42_2_IRQHandler
#define SYS_CNT_TIM_IRQn CCU42_2_IRQn


// Triacs.
#define TRIACS_TIMS_RESET_ENABLE() do{\
        SCU_RESET->PRSET0 = SCU_RESET_PRSET0_CCU80RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT0 & SCU_RESET_PRSTAT0_CCU80RS_Msk) == 0){ __NOP(); }\
    }while(0)
#define TRIACS_TIMS_RESET_DISABLE() do{\
        SCU_RESET->PRCLR0 = SCU_RESET_PRCLR0_CCU80RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT0 & SCU_RESET_PRSTAT0_CCU80RS_Msk) != 0){ __NOP(); }\
    }while(0)
#define TRIACS_TIMS_CLOCK_ENABLE() do{\
        SCU_CLK->CLKSET = SCU_CLK_CLKSET_CCUCEN_Msk;\
        __DSB();\
        TRIACS_MAINS_A_MOD_TIM_CCU8->GIDLC = CCU8_GIDLC_SPRB_Msk;\
        TRIACS_MAINS_A_OUT_TIM_CCU8->GIDLC = CCU8_GIDLC_SPRB_Msk;\
        __DMB();\
    }while(0)
#define TRIACS_TIMS_CLOCK_DISABLE() do{\
        TRIACS_MAINS_A_MOD_TIM_CCU8->GIDLS = CCU8_GIDLS_CPRB_Msk;\
        TRIACS_MAINS_A_OUT_TIM_CCU8->GIDLS = CCU8_GIDLS_CPRB_Msk;\
        __DSB();\
        SCU_CLK->CLKCLR = SCU_CLK_CLKCLR_CCUCDI_Msk;\
        __DMB();\
    }while(0)
// Phase A.
// Modulation timer.
#define TRIACS_MAINS_A_MOD_TIM_CCU8 CCU80
#define TRIACS_MAINS_A_MOD_TIM_CCU8_CC8 CCU80_CC80
#define TRIACS_MAINS_A_MOD_TIM_SHADOW_TRANSFER_Msk (CCU8_GCSS_S0SE_Msk | CCU8_GCSS_S0DSE_Msk | CCU8_GCSS_S0PSE_Msk)
#define TRIACS_MAINS_A_MOD_TIM_IDLE_CLR_Msk CCU8_GIDLC_CS0I_Msk
#define TRIACS_MAINS_A_MOD_TIM_IDLE_SET_Msk CCU8_GIDLS_SS0I_Msk
#define TRIACS_MAINS_A_MOD_TIM_SR 2
#define TRIACS_MAINS_A_MOD_TIM_IRQ_Handler CCU80_0_IRQHandler
#define TRIACS_MAINS_A_MOD_TIM_IRQn CCU80_0_IRQn
// Output timer.
#define TRIACS_MAINS_A_OUT_TIM_CCU8 CCU80
#define TRIACS_MAINS_A_OUT_TIM_CCU8_CC8 CCU80_CC81
#define TRIACS_MAINS_A_OUT_TIM_SHADOW_TRANSFER_Msk (CCU8_GCSS_S1SE_Msk | CCU8_GCSS_S1DSE_Msk | CCU8_GCSS_S1PSE_Msk)
#define TRIACS_MAINS_A_OUT_TIM_IDLE_CLR_Msk CCU8_GIDLC_CS1I_Msk
#define TRIACS_MAINS_A_OUT_TIM_IDLE_SET_Msk CCU8_GIDLS_SS1I_Msk
#define TRIACS_MAINS_A_OUT_TIM_SR 2
#define TRIACS_MAINS_A_OUT_TIM_IRQ_Handler CCU80_1_IRQHandler
#define TRIACS_MAINS_A_OUT_TIM_IRQn CCU80_1_IRQn
#define TRIACS_MAINS_AP_PORT PORT0
#define TRIACS_MAINS_AP_PIN_Pos 4
#define TRIACS_MAINS_AP_PIN_Msk ((1)<<(TRIACS_MAINS_AP_PIN_Pos))
#define TRIACS_MAINS_AP_PIN_CONF GPIO_CONF_OUTPUT_PP_ALT3 // out10
#define TRIACS_MAINS_AP_PIN_DRIVER GPIO_PAD_A2_DRIVER_STRONG_EDGE_SOFT
#define TRIACS_MAINS_AN_PORT PORT0
#define TRIACS_MAINS_AN_PIN_Pos 9
#define TRIACS_MAINS_AN_PIN_Msk ((1)<<(TRIACS_MAINS_AN_PIN_Pos))
#define TRIACS_MAINS_AN_PIN_CONF GPIO_CONF_OUTPUT_PP_ALT3 // out12
#define TRIACS_MAINS_AN_PIN_DRIVER GPIO_PAD_A2_DRIVER_STRONG_EDGE_SOFT



// Usarts.
#define USARTS_RESET_ENABLE() do{\
        SCU_RESET->PRSET1 = SCU_RESET_PRSET1_USIC1RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT1 & SCU_RESET_PRSTAT1_USIC1RS_Msk) == 0){ __NOP(); }\
    }while(0)
#define USARTS_RESET_DISABLE() do{\
        SCU_RESET->PRCLR1 = SCU_RESET_PRCLR1_USIC1RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT1 & SCU_RESET_PRSTAT1_USIC1RS_Msk) != 0){ __NOP(); }\
    }while(0)
// stdio uart.
// gpio.
// tx.
#define STDIO_UART_PORT_TX PORT0
#define STDIO_UART_PIN_TX_Pos 1
#define STDIO_UART_PIN_TX_Msk ((1)<<(STDIO_UART_PIN_TX_Pos))
#define STDIO_UART_PIN_TX_CONF GPIO_CONF_OUTPUT_PP_ALT2
#define STDIO_UART_PIN_TX_DRIVER GPIO_PAD_A1P_DRIVER_STRONG_EDGE_SOFT
// rx.
#define STDIO_UART_PORT_RX PORT0
#define STDIO_UART_PIN_RX_Pos 0
#define STDIO_UART_PIN_RX_Msk ((1)<<(STDIO_UART_PIN_RX_Pos))
#define STDIO_UART_PIN_RX_CONF GPIO_CONF_INPUT_PU
// usic.
#define STDIO_UART_USIC USIC1
#define STDIO_UART_USIC_CH USIC1_CH1
#define STDIO_UART_USIC_CH_RX 0b011
#define STDIO_UART_USIC_CH_TX 0b101
#define STDIO_UART_USIC_CH_FIFO_TX_OFFSET 0
#define STDIO_UART_USIC_CH_FIFO_TX_SIZE 16
#define STDIO_UART_USIC_CH_FIFO_TX_SIZE_SEL 0b100 // 16
#define STDIO_UART_USIC_CH_FIFO_TX_LIMIT 8
#define STDIO_UART_USIC_CH_FIFO_RX_OFFSET 16
#define STDIO_UART_USIC_CH_FIFO_RX_SIZE 16
#define STDIO_UART_USIC_CH_FIFO_RX_SIZE_SEL 0b100 // 16
//#define STDIO_UART_USIC_CH_FIFO_RX_LIMIT 0
#define STDIO_UART_USIC_CH_SR_SEL 0b000
#define STDIO_UART_USIC_CH_IRQ_Handler USIC1_0_IRQHandler
#define STDIO_UART_USIC_CH_IRQn USIC1_0_IRQn
// slcan uart.
// gpio.
// tx.
#define SLCAN_UART_PORT_TX PORT0
#define SLCAN_UART_PIN_TX_Pos 1
#define SLCAN_UART_PIN_TX_Msk ((1)<<(SLCAN_UART_PIN_TX_Pos))
#define SLCAN_UART_PIN_TX_CONF GPIO_CONF_OUTPUT_PP_ALT2
#define SLCAN_UART_PIN_TX_DRIVER GPIO_PAD_A1P_DRIVER_STRONG_EDGE_SOFT
// rx.
#define SLCAN_UART_PORT_RX PORT0
#define SLCAN_UART_PIN_RX_Pos 0
#define SLCAN_UART_PIN_RX_Msk ((1)<<(SLCAN_UART_PIN_RX_Pos))
#define SLCAN_UART_PIN_RX_CONF GPIO_CONF_INPUT_PU
// usic.
#define SLCAN_UART_USIC USIC1
#define SLCAN_UART_USIC_CH USIC1_CH1
#define SLCAN_UART_USIC_CH_RX 0b011
#define SLCAN_UART_USIC_CH_TX 0b101
#define SLCAN_UART_USIC_CH_FIFO_TX_OFFSET 0
#define SLCAN_UART_USIC_CH_FIFO_TX_SIZE 16
#define SLCAN_UART_USIC_CH_FIFO_TX_SIZE_SEL 0b100 // 16
#define SLCAN_UART_USIC_CH_FIFO_TX_LIMIT 8
#define SLCAN_UART_USIC_CH_FIFO_RX_OFFSET 16
#define SLCAN_UART_USIC_CH_FIFO_RX_SIZE 16
#define SLCAN_UART_USIC_CH_FIFO_RX_SIZE_SEL 0b100 // 16
//#define SLCAN_UART_USIC_CH_FIFO_RX_LIMIT 0
#define SLCAN_UART_USIC_CH_SR_SEL 0b000
#define SLCAN_UART_USIC_CH_IRQ_Handler USIC1_0_IRQHandler
#define SLCAN_UART_USIC_CH_IRQn USIC1_0_IRQn



// SPIs.
#define SPIS_RESET_ENABLE() do{\
        SCU_RESET->PRSET0 = SCU_RESET_PRSET0_USIC0RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT0 & SCU_RESET_PRSTAT0_USIC0RS_Msk) == 0){ __NOP(); }\
    }while(0)
#define SPIS_RESET_DISABLE() do{\
        SCU_RESET->PRCLR0 = SCU_RESET_PRCLR0_USIC0RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT0 & SCU_RESET_PRSTAT0_USIC0RS_Msk) != 0){ __NOP(); }\
    }while(0)
// eep spi.
// gpio.
// nWP.
#define EEP_PORT_nWP PORT1
#define EEP_PIN_nWP_Pos 3
#define EEP_PIN_nWP_Msk ((1)<<(EEP_PIN_nWP_Pos))
#define EEP_PIN_nWP_CONF GPIO_CONF_INPUT_PU//GPIO_CONF_OUTPUT_PP
#define EEP_PIN_nWP_DRIVER GPIO_PAD_A2_DRIVER_STRONG_EDGE_SOFT
// nHOLD.
#define EEP_PORT_nHOLD PORT1
#define EEP_PIN_nHOLD_Pos 2
#define EEP_PIN_nHOLD_Msk ((1)<<(EEP_PIN_nHOLD_Pos))
#define EEP_PIN_nHOLD_CONF GPIO_CONF_INPUT_PU//GPIO_CONF_OUTPUT_PP
#define EEP_PIN_nHOLD_DRIVER GPIO_PAD_A2_DRIVER_STRONG_EDGE_SOFT
// cs.
#define EEP_CS_SEL_Pos 0
#define EEP_CS_SEL_Msk ((1)<<(EEP_CS_SEL_Pos))
#define EEP_SPI_PORT_CS PORT1
#define EEP_SPI_PIN_CS_Pos 11
#define EEP_SPI_PIN_CS_Msk ((1)<<(EEP_SPI_PIN_CS_Pos))
#define EEP_SPI_PIN_CS_CONF GPIO_CONF_OUTPUT_PP_ALT2 // SELO0 P1.11
#define EEP_SPI_PIN_CS_DRIVER GPIO_PAD_A1P_DRIVER_STRONG_EDGE_SOFT
// sck.
#define EEP_SPI_PORT_SCK PORT1
#define EEP_SPI_PIN_SCK_Pos 10
#define EEP_SPI_PIN_SCK_Msk ((1)<<(EEP_SPI_PIN_SCK_Pos))
#define EEP_SPI_PIN_SCK_CONF GPIO_CONF_OUTPUT_PP_ALT2 // SCLKOUT P1.10
#define EEP_SPI_PIN_SCK_DRIVER GPIO_PAD_A1P_DRIVER_STRONG_EDGE_SOFT
// mosi.
#define EEP_SPI_PORT_MOSI PORT1
#define EEP_SPI_PIN_MOSI_Pos 5
#define EEP_SPI_PIN_MOSI_Msk ((1)<<(EEP_SPI_PIN_MOSI_Pos))
#define EEP_SPI_PIN_MOSI_CONF GPIO_CONF_OUTPUT_PP_ALT2 // DOUT0 P1.5
#define EEP_SPI_PIN_MOSI_DRIVER GPIO_PAD_A1P_DRIVER_STRONG_EDGE_SOFT
// miso.
#define EEP_SPI_PORT_MISO PORT1
#define EEP_SPI_PIN_MISO_Pos 4
#define EEP_SPI_PIN_MISO_Msk ((1)<<(EEP_SPI_PIN_MISO_Pos)) // DX0B P1.4
#define EEP_SPI_PIN_MISO_CONF GPIO_CONF_INPUT_PU
// usic.
#define EEP_SPI_USIC USIC0
#define EEP_SPI_USIC_CH USIC0_CH0
#define EEP_SPI_USIC_CH_MISO 0b001
#define EEP_SPI_USIC_CH_FIFO_TX_OFFSET 0
#define EEP_SPI_USIC_CH_FIFO_TX_SIZE 16
#define EEP_SPI_USIC_CH_FIFO_TX_SIZE_SEL 0b100 // 16
#define EEP_SPI_USIC_CH_FIFO_TX_LIMIT 8
#define EEP_SPI_USIC_CH_FIFO_RX_OFFSET 16
#define EEP_SPI_USIC_CH_FIFO_RX_SIZE 16
#define EEP_SPI_USIC_CH_FIFO_RX_SIZE_SEL 0b100 // 16
//#define EEP_SPI_USIC_CH_FIFO_RX_LIMIT 0
#define EEP_SPI_USIC_CH_SR_SEL 0b010
#define EEP_SPI_USIC_CH_IRQ_Handler USIC0_2_IRQHandler
#define EEP_SPI_USIC_CH_IRQn USIC0_2_IRQn
// pre / post delay time in half SCK cycles.
#define EEP_SPI_USIC_Tld_Ttd 1
// dma.
// tx.
#define EEP_SPI_USIC_TX_SR_SEL 0b000
#define EEP_SPI_DMA_TX_CHANNEL 0
#define EEP_SPI_DMA_TX_REQ_LINE 0
#define EEP_SPI_DMA_TX_REQ_LINE_SOURCE 0b1010
// rx.
#define EEP_SPI_USIC_RX_SR_SEL 0b001
#define EEP_SPI_DMA_RX_CHANNEL 1
#define EEP_SPI_DMA_RX_REQ_LINE 2
#define EEP_SPI_DMA_RX_REQ_LINE_SOURCE 0b1011



// CAN.
#define CAN_RESET_ENABLE() do{\
        SCU_RESET->PRSET1 = SCU_RESET_PRSET1_MCAN0RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT1 & SCU_RESET_PRSTAT1_MCAN0RS_Msk) == 0){ __NOP(); }\
    }while(0)
#define CAN_RESET_DISABLE() do{\
        SCU_RESET->PRCLR1 = SCU_RESET_PRCLR1_MCAN0RS_Msk;\
        __DMB();\
        while((SCU_RESET->PRSTAT1 & SCU_RESET_PRSTAT1_MCAN0RS_Msk) != 0){ __NOP(); }\
    }while(0)
// can.
#define CAN_N 0
#define CAN_NODE_N 1
#define CAN_FIFO_TX_SIZE 4
#define CAN_FIFO_RX_SIZE 4
// gpio.
// tx.
#define CAN_NODE_PORT_TX PORT1
#define CAN_NODE_PIN_TX_Pos 12
#define CAN_NODE_PIN_TX_Msk ((1)<<(CAN_NODE_PIN_TX_Pos))
#define CAN_NODE_PIN_TX_CONF GPIO_CONF_OUTPUT_PP_ALT2 // N1_TXD P1.12
#define CAN_NODE_PIN_TX_DRIVER GPIO_PAD_A1P_DRIVER_STRONG_EDGE_SOFT
// rx.
#define CAN_NODE_PORT_RX PORT2
#define CAN_NODE_PIN_RX_Pos 6
#define CAN_NODE_PIN_RX_Msk ((1)<<(CAN_NODE_PIN_RX_Pos)) // N1_RXDC1A P2.6
#define CAN_NODE_PIN_RX_CONF GPIO_CONF_INPUT
#define CAN_NODE_RX_SEL 0b0 //0b10


#endif /* HARDWARE_CONFIG_H_ */

#endif
