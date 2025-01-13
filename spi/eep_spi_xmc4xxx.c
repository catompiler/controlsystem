
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "eep_spi_xmc4xxx.h"
#include "gpio/gpio_xmc4xxx.h"
#include "hardware/config.h"
#include "spi/spi_xmc4xxx.h"
#include <stdint.h>
#include <stddef.h>


//! Структура eep spi.
typedef struct _S_Eep_Spi {
    spi_bus_t* spi_bus;
} eep_spi_t;


//! stdio uart.
static eep_spi_t eep_spi;


//! Обработчик прерывания.
void EEP_SPI_USIC_CH_IRQ_Handler(void)
{
    spi_bus_irq_handler(eep_spi.spi_bus);
}


err_t eep_spi_init(spi_bus_t* spi_bus)
{
    if(spi_bus == NULL) return E_NULL_POINTER;

    eep_spi.spi_bus = spi_bus;

    // enable module.
    EEP_SPI_USIC_CH->KSCFG = USIC_CH_KSCFG_MODEN_Msk | USIC_CH_KSCFG_BPMODEN_Msk;
    while((EEP_SPI_USIC_CH->KSCFG & USIC_CH_KSCFG_MODEN_Msk) == 0){ __NOP(); }

    // set idle.
    EEP_SPI_USIC_CH->CCR = 0;

    uint32_t step = SystemCoreClock / (EEP_SPI_OVERSAMPLING * EEP_SPI_FREQ);

    // clk.
    EEP_SPI_USIC_CH->FDR = ((1) << USIC_CH_FDR_DM_Pos) |
                           ((1024 - step) << USIC_CH_FDR_STEP_Pos);
    EEP_SPI_USIC_CH->BRG = ((0) << USIC_CH_BRG_PDIV_Pos) |
                           ((0b00) << USIC_CH_BRG_CTQSEL_Pos) |
                           ((0) << USIC_CH_BRG_PCTQ_Pos) |
                           ((EEP_SPI_OVERSAMPLING - 1) << USIC_CH_BRG_DCTQ_Pos) |
                           ((0) << USIC_CH_BRG_SCLKOSEL_Pos) |
                           ((0) << USIC_CH_BRG_MCLKCFG_Pos) |
                           ((0) << USIC_CH_BRG_SCLKCFG_Pos);

    // inputs.
    EEP_SPI_USIC_CH->DX0CR = ((EEP_SPI_USIC_CH_MISO) << USIC_CH_DX0CR_DSEL_Pos);

    // data shifting.
    EEP_SPI_USIC_CH->SCTR = ((0b01) << USIC_CH_SCTR_TRM_Pos) | // needed.
                               ((63) << USIC_CH_SCTR_FLE_Pos) | // Inf bit frame.
                               ((7) << USIC_CH_SCTR_WLE_Pos) | // 8 bit word.
                               ((0) << USIC_CH_SCTR_PDL_Pos) | // 0 passive.
                               ((1) << USIC_CH_SCTR_SDIR_Pos) | // MSB first.
                               ((0) << USIC_CH_SCTR_DOCFG_Pos) | // not inverted.
                               ((0) << USIC_CH_SCTR_DSM_Pos); // 1 bit.

    // uart.
    EEP_SPI_USIC_CH->PCR_SSCMode = ((1) << USIC_CH_PCR_SSCMode_MSLSEN_Pos) | // clk gen.
                                   ((1) << USIC_CH_PCR_SSCMode_SELCTR_Pos) | // direct sel.
                                   ((1) << USIC_CH_PCR_SSCMode_SELINV_Pos) | // sel active low.
                                   ((1) << USIC_CH_PCR_SSCMode_FEM_Pos);// | // sw sel management.
                                   //((1) << USIC_CH_PCR_SSCMode_MSLSIEN_Pos); // sel interrupt.

    // interrup selector.
    EEP_SPI_USIC_CH->INPR = ((EEP_SPI_USIC_CH_SR_SEL) << USIC_CH_INPR_PINP_Pos) |
                            ((EEP_SPI_USIC_RX_SR_SEL) << USIC_CH_INPR_AINP_Pos) |
                            ((EEP_SPI_USIC_RX_SR_SEL) << USIC_CH_INPR_RINP_Pos) |
                            ((EEP_SPI_USIC_TX_SR_SEL) << USIC_CH_INPR_TBINP_Pos);

    // enable tbuf.
    EEP_SPI_USIC_CH->TCSR = ((1) << USIC_CH_TCSR_TDEN_Pos) |
                            ((1) << USIC_CH_TCSR_TDSSM_Pos);

    // clear status.
    EEP_SPI_USIC_CH->PSCR = 0xffffffffU;

    // set mode.
    EEP_SPI_USIC_CH->CCR = ((0x1) << USIC_CH_CCR_MODE_Pos) | // SSC mode.
                              ((0) << USIC_CH_CCR_PM_Pos);     // Parity: none.
                              //((1) << USIC_CH_CCR_RIEN_Pos) |   // Rx Irq.
                              //((1) << USIC_CH_CCR_TBIEN_Pos);   // Tx Irq.

    // fifo.
    // disable.
    EEP_SPI_USIC_CH->TBCTR = 0;
    EEP_SPI_USIC_CH->RBCTR = 0;

#if defined(SPI_BUS_USE_FIFO) && SPI_BUS_USE_FIFO == 1
    __DSB();
    EEP_SPI_USIC_CH->TBCTR = ((EEP_SPI_USIC_CH_FIFO_TX_OFFSET) << USIC_CH_TBCTR_DPTR_Pos) |
                                ((EEP_SPI_USIC_CH_FIFO_TX_SIZE_SEL) << USIC_CH_TBCTR_SIZE_Pos) |
                                ((0) << USIC_CH_TBCTR_LIMIT_Pos) | // EEP_SPI_USIC_CH_FIFO_TX_LIMIT
                                ((0) << USIC_CH_TBCTR_LOF_Pos) | // < level.
                                ((1) << USIC_CH_TBCTR_STBTM_Pos) | // 0
                                ((1) << USIC_CH_TBCTR_STBTEN_Pos) |
                                ((EEP_SPI_USIC_CH_SR_SEL) << USIC_CH_TBCTR_STBINP_Pos)/* |
                                ((1) << USIC_CH_TBCTR_STBIEN_Pos)*/;
    EEP_SPI_USIC_CH->RBCTR = ((EEP_SPI_USIC_CH_FIFO_RX_OFFSET) << USIC_CH_RBCTR_DPTR_Pos) |
                                ((EEP_SPI_USIC_CH_FIFO_RX_SIZE_SEL) << USIC_CH_RBCTR_SIZE_Pos) |
                                ((0) << USIC_CH_RBCTR_LIMIT_Pos) | // EEP_SPI_USIC_CH_FIFO_RX_LIMIT
                                ((1) << USIC_CH_RBCTR_LOF_Pos) | // > level.
                                ((1) << USIC_CH_RBCTR_SRBTM_Pos) | // 0
                                ((1) << USIC_CH_RBCTR_SRBTEN_Pos) |
                                ((EEP_SPI_USIC_CH_SR_SEL) << USIC_CH_RBCTR_SRBINP_Pos) |
                                /*((1) << USIC_CH_RBCTR_SRBIEN_Pos) |*/
                                ((0b11) << USIC_CH_RBCTR_RCIM_Pos) |
                                ((0) << USIC_CH_RBCTR_RNM_Pos);
#endif

    // cs.
    gpio_set_pad_driver(EEP_SPI_PORT_CS, EEP_SPI_PIN_CS_Msk, EEP_SPI_PIN_CS_DRIVER);
    gpio_set(EEP_SPI_PORT_CS, EEP_SPI_PIN_CS_Msk);
    gpio_init(EEP_SPI_PORT_CS, EEP_SPI_PIN_CS_Msk, EEP_SPI_PIN_CS_CONF);
    // sck.
    gpio_set_pad_driver(EEP_SPI_PORT_SCK, EEP_SPI_PIN_SCK_Msk, EEP_SPI_PIN_SCK_DRIVER);
    gpio_set(EEP_SPI_PORT_SCK, EEP_SPI_PIN_SCK_Msk);
    gpio_init(EEP_SPI_PORT_SCK, EEP_SPI_PIN_SCK_Msk, EEP_SPI_PIN_SCK_CONF);
    // mosi.
    gpio_set_pad_driver(EEP_SPI_PORT_MOSI, EEP_SPI_PIN_MOSI_Msk, EEP_SPI_PIN_MOSI_DRIVER);
    gpio_set(EEP_SPI_PORT_MOSI, EEP_SPI_PIN_MOSI_Msk);
    gpio_init(EEP_SPI_PORT_MOSI, EEP_SPI_PIN_MOSI_Msk, EEP_SPI_PIN_MOSI_CONF);
    // miso.
    gpio_init(EEP_SPI_PORT_MISO, EEP_SPI_PIN_MISO_Msk, EEP_SPI_PIN_MISO_CONF);


    spi_bus_init_t sbi;
    sbi.spi_device = EEP_SPI_USIC_CH;
    sbi.dma_rx_ch_n = EEP_SPI_DMA_RX_CHANNEL;
    sbi.dma_rx_line_n = EEP_SPI_DMA_RX_REQ_LINE;
    sbi.dma_rx_line_req_n = EEP_SPI_DMA_RX_REQ_LINE_SOURCE;
    sbi.dma_rx_sr_n = EEP_SPI_USIC_RX_SR_SEL;
    sbi.dma_tx_ch_n = EEP_SPI_DMA_TX_CHANNEL;
    sbi.dma_tx_line_n = EEP_SPI_DMA_TX_REQ_LINE;
    sbi.dma_tx_line_req_n = EEP_SPI_DMA_TX_REQ_LINE_SOURCE;
    sbi.dma_tx_sr_n = EEP_SPI_USIC_TX_SR_SEL;

    err_t err = spi_bus_init(eep_spi.spi_bus, &sbi);

    // if error.
    if(err != E_NO_ERROR){
        // disable module.
        EEP_SPI_USIC_CH->KSCFG = USIC_CH_KSCFG_BPMODEN_Msk;

        // deinit gpio.
        gpio_init(EEP_SPI_PORT_CS, EEP_SPI_PIN_CS_Msk, GPIO_CONF_INPUT);
        gpio_init(EEP_SPI_PORT_SCK, EEP_SPI_PIN_SCK_Msk, GPIO_CONF_INPUT);
        gpio_init(EEP_SPI_PORT_MOSI, EEP_SPI_PIN_MOSI_Msk, GPIO_CONF_INPUT);
        gpio_init(EEP_SPI_PORT_MISO, EEP_SPI_PIN_MISO_Msk, GPIO_CONF_INPUT);
    }else{
    }

    return err;
}

#endif
