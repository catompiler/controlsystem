#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "usart_stdio_xmc4xxx.h"
#include "gpio/gpio_xmc4xxx.h"
#include "hardware/config.h"
#define USART_STDIO
#include "usart_buf_xmc4xxx.h"
#include "buffer/circular_buffer.h"
#include <stdint.h>
#include <stddef.h>


//! Структура stdio uart.
typedef struct _S_Stdio_Uart {
	usart_buf_t usart_buf;
	uint8_t tx_buf[USART_STDIO_TX_BUFFER_LEN];
	uint8_t rx_buf[USART_STDIO_RX_BUFFER_LEN];
} stdio_uart_t;


//! stdio uart.
static stdio_uart_t stdio_uart;


//! Обработчик прерывания.
void STDIO_UART_USIC_CH_IRQ_Handler(void)
{
	/*if(STDIO_UART_USIC_CH->PSR_ASCMode & USIC_CH_PSR_ASCMode_RIF_Msk){
		STDIO_UART_USIC_CH->PSCR = USIC_CH_PSCR_CRIF_Msk;
	}

	if(STDIO_UART_USIC_CH->PSR_ASCMode & USIC_CH_PSR_ASCMode_TBIF_Msk){
		STDIO_UART_USIC_CH->PSCR = USIC_CH_PSCR_CTBIF_Msk;
	}*/

	usart_buf_irq_handler(&stdio_uart.usart_buf);
}


err_t usart_stdio_init(void)
{
	// enable module.
    STDIO_UART_USIC_CH->KSCFG = USIC_CH_KSCFG_MODEN_Msk | USIC_CH_KSCFG_BPMODEN_Msk;
    while((STDIO_UART_USIC_CH->KSCFG & USIC_CH_KSCFG_MODEN_Msk) == 0){ __NOP(); }

    // set idle.
    STDIO_UART_USIC_CH->CCR &= ~USIC_CH_CCR_MODE_Msk;

    // clk.
    STDIO_UART_USIC_CH->FDR = ((1024 - (SystemCoreClock / (16 * USART_STDIO_BAUD))) << USIC_CH_FDR_STEP_Pos) |
                              ((0b01) << USIC_CH_FDR_DM_Pos);
    STDIO_UART_USIC_CH->BRG = ((15) << USIC_CH_BRG_DCTQ_Pos);

    // inputs.
    STDIO_UART_USIC_CH->DX0CR = ((SLCAN_UART_USIC_CH_RX) << USIC_CH_DX0CR_DSEL_Pos);
    STDIO_UART_USIC_CH->DX1CR = ((SLCAN_UART_USIC_CH_TX) << USIC_CH_DX1CR_DSEL_Pos);

    // data shifting.
    STDIO_UART_USIC_CH->SCTR = ((0b01) << USIC_CH_SCTR_TRM_Pos) |
                               ((7) << USIC_CH_SCTR_FLE_Pos) |
                               ((7) << USIC_CH_SCTR_WLE_Pos) |
                               (USIC_CH_SCTR_PDL_Msk);

    // uart.
    STDIO_UART_USIC_CH->PCR_ASCMode = ((0b1) << USIC_CH_PCR_ASCMode_SMD_Pos)  | // 3 sample.
                                      ((0b0) << USIC_CH_PCR_ASCMode_STPB_Pos) | // 1 stop bit.
                                      ((0b0) << USIC_CH_PCR_ASCMode_IDM_Pos)  | // disable idle detection.
                                      ((8) << USIC_CH_PCR_ASCMode_SP_Pos)     | // 3 samples before 8'st bit.
                                      (USIC_CH_PCR_ASCMode_RSTEN_Msk | USIC_CH_PCR_ASCMode_TSTEN_Msk);

    // interrup selector.
    STDIO_UART_USIC_CH->INPR = ((STDIO_UART_USIC_CH_SR_SEL) << USIC_CH_INPR_RINP_Pos) |
    						   ((STDIO_UART_USIC_CH_SR_SEL) << USIC_CH_INPR_TBINP_Pos);

    // enable tbuf.
    STDIO_UART_USIC_CH->TCSR = ((1) << USIC_CH_TCSR_TDEN_Pos) |
                               (USIC_CH_TCSR_TDSSM_Msk);

    // clear status.
    STDIO_UART_USIC_CH->PSCR = 0xffffffffU;

    // set mode.
    STDIO_UART_USIC_CH->CCR = ((0x2) << USIC_CH_CCR_MODE_Pos) | // ASC mode.
                              ((0) << USIC_CH_CCR_PM_Pos) |     // Parity: none.
							  ((1) << USIC_CH_CCR_RIEN_Pos) |   // Rx Irq.
							  ((1) << USIC_CH_CCR_TBIEN_Pos);   // Tx Irq.

    // tx.
    gpio_set_pad_driver(STDIO_UART_PORT_TX, STDIO_UART_PIN_TX_Msk, STDIO_UART_PIN_TX_DRIVER);
    gpio_set(STDIO_UART_PORT_TX, STDIO_UART_PIN_TX_Msk);
    gpio_init(STDIO_UART_PORT_TX, STDIO_UART_PIN_TX_Msk, STDIO_UART_PIN_TX_CONF);
    // rx.
    gpio_init(STDIO_UART_PORT_RX, STDIO_UART_PIN_RX_Msk, STDIO_UART_PIN_RX_CONF);


    usart_buf_init_t ubi;
    ubi.usart = STDIO_UART_USIC_CH;
    ubi.write_buffer = stdio_uart.tx_buf;
    ubi.write_buffer_size = USART_STDIO_TX_BUFFER_LEN;
    ubi.read_buffer = stdio_uart.rx_buf;
    ubi.read_buffer_size = USART_STDIO_RX_BUFFER_LEN;

    err_t err = usart_buf_init(&stdio_uart.usart_buf, &ubi);

    // if error.
    if(err != E_NO_ERROR){
    	// disable module.
        STDIO_UART_USIC_CH->KSCFG = USIC_CH_KSCFG_BPMODEN_Msk;

        // deinit gpio.
        gpio_init(STDIO_UART_PORT_TX, STDIO_UART_PIN_TX_Msk, GPIO_CONF_INPUT);
        gpio_init(STDIO_UART_PORT_RX, STDIO_UART_PIN_RX_Msk, GPIO_CONF_INPUT);
    }else{
#if defined(USART_STDIO)
    	usart_setup_stdio(&stdio_uart.usart_buf);
#endif
    }

    return err;
}

#endif
