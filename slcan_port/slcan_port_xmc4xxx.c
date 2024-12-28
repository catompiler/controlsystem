#include "slcan/slcan_port.h"
#include "sys_counter/sys_counter.h"
#include "usart/usart_buf_xmc4xxx.h"
#include "hardware/config.h"



int slcan_clock_gettime (struct timespec *tp)
{
    return clock_gettime(CLOCK_MONOTONIC, tp);
}



//! Размер кольцевого буфера.
#define SLCAN_USART_BUF_SIZE 64

//! Структура буферизированного уарта.
typedef struct _Slcan_Usart_Buf {
    circular_buffer_t circ_buf;
    uint8_t circ_buf_data[SLCAN_USART_BUF_SIZE];
    usart_buf_t usart_buf;
} slcan_usart_buf_t;


static slcan_usart_buf_t _slcan_usart_buf;


// Преобразует тип последовательного порта в slcan_serial_handle_t.
#define SERIAL_TO_HANDLE(S) ((slcan_serial_handle_t)(long)(S))
// Преобразует slcan_serial_handle_t в тип последовательного порта.
#define HANDLE_TO_SERIAL(H) ((slcan_usart_buf_t*)(H))



slcan_usart_buf_t* get_slcan_usart_buf(void)
{
    return &_slcan_usart_buf;
}



void SLCAN_UART_USIC_CH_IRQ_Handler(void)
{
    //slcan_usart_buf_t* ubuf = get_slcan_usart_buf();
}



int slcan_serial_open(const char* serial_port_name, slcan_serial_handle_t* serial_port)
{
    assert(serial_port != NULL);

    (void) serial_port_name;

    if((SLCAN_UART_USIC_CH->CCFG & USIC_CH_CCFG_ASC_Msk) == 0) return SLCAN_IO_FAIL;

    slcan_usart_buf_t* ubuf = get_slcan_usart_buf();

    circular_buffer_init(&ubuf->circ_buf, ubuf->circ_buf_data, SLCAN_USART_BUF_SIZE);

    // enable module.
    SLCAN_UART_USIC_CH->KSCFG = USIC_CH_KSCFG_MODEN_Msk | USIC_CH_KSCFG_BPMODEN_Msk |
                              (0 << USIC_CH_KSCFG_NOMCFG_Pos) | USIC_CH_KSCFG_BPNOM_Msk |
                              (0 << USIC_CH_KSCFG_SUMCFG_Pos) | USIC_CH_KSCFG_BPSUM_Msk;

    SLCAN_UART_USIC_CH->DX0CR = ((SLCAN_UART_USIC_CH_RX) << USIC_CH_DX0CR_DSEL_Pos) |
                              ((0) << USIC_CH_DX0CR_INSW_Pos);
    SLCAN_UART_USIC_CH->DX1CR = ((0b110) << USIC_CH_DX1CR_DSEL_Pos) |
                              ((0) << USIC_CH_DX1CR_INSW_Pos);
    SLCAN_UART_USIC_CH->DX2CR = ((0) << USIC_CH_DX2CR_DSEL_Pos) |
                              ((0) << USIC_CH_DX2CR_INSW_Pos);

    SLCAN_UART_USIC_CH->SCTR = ((0) << USIC_CH_SCTR_SDIR_Pos) |
                             ((0) << USIC_CH_SCTR_PDL_Pos) |
                             ((0) << USIC_CH_SCTR_DSM_Pos) |
                             ((0) << USIC_CH_SCTR_DOCFG_Pos) |
                             ((0b01) << USIC_CH_SCTR_TRM_Pos) |
                             ((8) << USIC_CH_SCTR_FLE_Pos) |
                             ((8) << USIC_CH_SCTR_WLE_Pos);

    // fifo.
    // tx.
    SLCAN_UART_USIC_CH->TBCTR = ((SLCAN_UART_USIC_CH_FIFO_TX_OFFSET) << USIC_CH_TBCTR_DPTR_Pos) |
                              ((SLCAN_UART_USIC_CH_FIFO_TX_SIZE_SEL) << USIC_CH_TBCTR_SIZE_Pos) |
                              ((0) << USIC_CH_TBCTR_LOF_Pos) | // < LIMIT
                              ((SLCAN_UART_USIC_CH_FIFO_TX_LIMIT) << USIC_CH_TBCTR_LIMIT_Pos) |
                              ((0) << USIC_CH_TBCTR_STBTM_Pos) |
                              ((1) << USIC_CH_TBCTR_STBTEN_Pos) |
                              ((SLCAN_UART_USIC_CH_SR_SEL) << USIC_CH_TBCTR_STBINP_Pos) |
                              ((SLCAN_UART_USIC_CH_SR_SEL) << USIC_CH_TBCTR_ATBINP_Pos) |
                              ((1) << USIC_CH_TBCTR_STBIEN_Pos) |
                              ((1) << USIC_CH_TBCTR_TBERIEN_Pos);
    // rx.
    SLCAN_UART_USIC_CH->RBCTR = ((SLCAN_UART_USIC_CH_FIFO_RX_OFFSET) << USIC_CH_RBCTR_DPTR_Pos) |
                              ((SLCAN_UART_USIC_CH_FIFO_RX_SIZE_SEL) << USIC_CH_RBCTR_SIZE_Pos) |
                              ((1) << USIC_CH_TBCTR_LOF_Pos) | // > LIMIT
                              ((SLCAN_UART_USIC_CH_FIFO_TX_LIMIT) << USIC_CH_TBCTR_LIMIT_Pos) |
                              ((0) << USIC_CH_RBCTR_SRBTM_Pos) |
                              ((1) << USIC_CH_RBCTR_SRBTEN_Pos) |
                              ((SLCAN_UART_USIC_CH_SR_SEL) << USIC_CH_RBCTR_SRBINP_Pos) |
                              ((SLCAN_UART_USIC_CH_SR_SEL) << USIC_CH_RBCTR_ARBINP_Pos) |
                              ((1) << USIC_CH_RBCTR_SRBIEN_Pos) |
                              ((1) << USIC_CH_RBCTR_RBERIEN_Pos);

    // usart - default.
    slcan_port_conf_t port_conf;
    slcan_get_default_port_config(&port_conf);
    slcan_serial_configure(SERIAL_TO_HANDLE(ubuf), &port_conf);

    // gpio.
    // tx.
    gpio_set(SLCAN_UART_PORT_TX, SLCAN_UART_PIN_TX_Pos);
    gpio_set_pad_driver(SLCAN_UART_PORT_TX, SLCAN_UART_PIN_TX_Pos, SLCAN_UART_PIN_TX_DRIVER);
    gpio_init(SLCAN_UART_PORT_TX, SLCAN_UART_PIN_TX_Pos, SLCAN_UART_PIN_TX_CONF);
    // rx.
    gpio_init(SLCAN_UART_PORT_RX, SLCAN_UART_PIN_RX_Pos, SLCAN_UART_PIN_RX_CONF);

    *serial_port = SERIAL_TO_HANDLE(ubuf);

    return SLCAN_IO_SUCCESS;
}

int slcan_serial_configure(slcan_serial_handle_t serial_port, const slcan_port_conf_t* conf)
{
    assert(serial_port != NULL);

    static const uint32_t bauds[] = {
        230400,
        115200,
        57600,
        38400,
        19200,
        9600,
        2400,
    };
    const uint32_t bauds_count = sizeof(bauds) / sizeof(bauds[0]);

    if(conf->baud >= bauds_count) return SLCAN_IO_FAIL;

    uint32_t baud = bauds[conf->baud];

    const uint32_t PDIV = 0;
    const uint32_t PCTQ = 0;
    const uint32_t DCTQ = 15;

    uint32_t step = (2048 - CPU_FREQ * 2 / baud / (1 + PDIV) / (1 + PCTQ) / (1 + DCTQ) + 1) / 2;
    if(step >= 1024) return -1;

    uint32_t stop_bits = (conf->stop_bits == SLCAN_PORT_STOP_BITS_2) ? 1 : 0;

    uint32_t parity = 0;
    switch(conf->parity){
    default:
    case SLCAN_PORT_PARITY_NONE:
        //parity = 0;
        break;
    case SLCAN_PORT_PARITY_EVEN:
        parity = 0b10;
        break;
    case SLCAN_PORT_PARITY_ODD:
        parity = 0b11;
        break;
    }

    // mode -> disable.
    SLCAN_UART_USIC_CH->CCR = 0;

    // baud.
    SLCAN_UART_USIC_CH->BRG = ((0) << USIC_CH_BRG_CLKSEL_Pos) |
                            ((0) << USIC_CH_BRG_CTQSEL_Pos) |
                            ((PCTQ) << USIC_CH_BRG_PCTQ_Pos) |
                            ((DCTQ) << USIC_CH_BRG_DCTQ_Pos) |
                            ((PDIV) << USIC_CH_BRG_PDIV_Pos) |
                            ((0) << USIC_CH_BRG_SCLKOSEL_Pos);

    // protocol.
    SLCAN_UART_USIC_CH->PCR_ASCMode = ((1) << USIC_CH_PCR_ASCMode_SMD_Pos) |
                                    ((stop_bits) << USIC_CH_PCR_ASCMode_STPB_Pos) |
                                    ((0) << USIC_CH_PCR_ASCMode_IDM_Pos) |
                                    (((DCTQ + 1)/2) << USIC_CH_PCR_ASCMode_SP_Pos) |
                                    ((0) << USIC_CH_PCR_ASCMode_PL_Pos);

    // mode -> ASC & parity.
    SLCAN_UART_USIC_CH->CCR = ((2) << USIC_CH_CCR_MODE_Pos) |
                            ((0) << USIC_CH_CCR_HPCEN_Pos) |
                            ((parity) << USIC_CH_CCR_PM_Pos);

    return SLCAN_IO_FAIL;
}

void slcan_serial_close(slcan_serial_handle_t serial_port)
{
    assert(serial_port != NULL);

    // HANDLE_TO_SERIAL(serial_port);
}

int slcan_serial_read(slcan_serial_handle_t serial_port, void* data, size_t data_size)
{
    assert(serial_port != NULL);

    return SLCAN_IO_FAIL;
}

int slcan_serial_write(slcan_serial_handle_t serial_port, const void* data, size_t data_size)
{
    assert(serial_port != NULL);

    return SLCAN_IO_FAIL;
}

int slcan_serial_flush(slcan_serial_handle_t serial_port)
{
    assert(serial_port != NULL);

    return SLCAN_IO_FAIL;
}

// POLLIN
// POLLPRI
// POLLOUT
// POLLERR
// POLLHUP
// POLLNVAL
int slcan_serial_poll(slcan_serial_handle_t serial_port, int events, int* revents, int timeout)
{
    assert(serial_port != NULL);

    return SLCAN_IO_FAIL;
}

int slcan_serial_nbytes(slcan_serial_handle_t serial_port, size_t* size)
{
    assert(serial_port != NULL);

    return SLCAN_IO_FAIL;
}
