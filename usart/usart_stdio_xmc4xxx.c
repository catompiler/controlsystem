#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "usart_stdio_xmc4xxx.h"
#include "gpio/gpio_xmc4xxx.h"
#include "hardware/config.h"



void usart_stdio_init(void)
{
    STDIO_UART_USIC_CH->KSCFG = USIC_CH_KSCFG_MODEN_Msk | USIC_CH_KSCFG_BPMODEN_Msk;

    // clk.
    STDIO_UART_USIC_CH->FDR = ((SystemCoreClock / (16 * USART_STDIO_BAUD)) << USIC_CH_FDR_STEP_Pos) |
                              ((0b01) << USIC_CH_FDR_DM_Pos);
    STDIO_UART_USIC_CH->BRG = ((15) << USIC_CH_BRG_DCTQ_Pos);

    // data shifting.
    STDIO_UART_USIC_CH->SCTR = ((0b01) << USIC_CH_SCTR_TRM_Pos) |
                               ((7) << USIC_CH_SCTR_FLE_Pos) |
                               ((7) << USIC_CH_SCTR_WLE_Pos);

    STDIO_UART_USIC_CH->PCR_ASCMode = ((0b1) << USIC_CH_PCR_ASCMode_SMD_Pos)  | // 3 sample.
                                      ((0b0) << USIC_CH_PCR_ASCMode_STPB_Pos) | // 1 stop bit.
                                      ((0b1) << USIC_CH_PCR_ASCMode_IDM_Pos)  | // disable idle detection.
                                      ((8) << USIC_CH_PCR_ASCMode_SP_Pos);      // 3 samples before 8'st bit.

    STDIO_UART_USIC_CH->CCR = ((0x2) << USIC_CH_CCR_MODE_Pos) | // ASC mode.
                              ((0) << USIC_CH_CCR_PM_Pos);      // Parity: none.

    gpio_set_pad_driver(STDIO_UART_PORT_TX, STDIO_UART_PIN_TX_Msk, STDIO_UART_PIN_TX_DRIVER);
    gpio_set(STDIO_UART_PORT_TX, STDIO_UART_PIN_TX_Msk);
    gpio_init(STDIO_UART_PORT_TX, STDIO_UART_PIN_TX_Msk, STDIO_UART_PIN_TX_CONF);

    gpio_init(STDIO_UART_PORT_RX, STDIO_UART_PIN_RX_Msk, STDIO_UART_PIN_RX_CONF);
}





#endif
