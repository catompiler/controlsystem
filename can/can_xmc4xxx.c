#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "can_xmc4xxx.h"
#include "hardware/config.h"
#include "gpio/gpio_xmc4xxx.h"


static const uint32_t NBTR_values[] = {
    0x00009b31, // 10 kbit
    0x00009b18, // 20 kbit
    0x00009b09, // 50 kbit
    0x00001b27, // 100 kbit
    0x00001c1d, // 125 kbit
    0x00001c0e, // 250 kbit
    0x00001b07, // 500 kbit
    0x00001b04, // 800 kbit
    0x00001b03  // 1000 kbit
};

const size_t NBTR_values_count = (sizeof(NBTR_values)/sizeof(NBTR_values[0]));


#define CAN_MO_INVALID_INDEX (0xffffffff)

//#define CAN_MO_FIFO_LIST ((CAN_NODES) + 1)

#define CAN_NODE_LIST_N ((CAN_NODE_N) + 1)


#define CAN_RX_FIFO_PRI 0b01 // 0b01 by list order, 0b10 - by priority

#define CAN_TX_FIFO_PRI 0b01 // 0b01 by list order, 0b10 - by priority



void CAN_IRQ_Handler(void)
{
    if(CAN_NODE->NSR & CAN_NODE_NSR_TXOK_Msk){
        CAN_NODE->NSR = ~CAN_NODE_NSR_TXOK_Msk;
    }
    if(CAN_NODE->NSR & CAN_NODE_NSR_RXOK_Msk){
        CAN_NODE->NSR = ~CAN_NODE_NSR_RXOK_Msk;
    }
    // clear all.
    CAN_NODE->NSR = 0x0;
}



err_t can_init(can_t* can)
{
    err_t err = E_NO_ERROR;

    // Enable clock.
    CAN->CLC = CAN->CLC & ~(CAN_CLC_SBWE_Msk | CAN_CLC_DISR_Msk);
    // wait.
    while(CAN->CLC & CAN_CLC_DISS_Msk){ __NOP(); }

    // Prescaler.
    uint32_t step = SystemCoreClock / (CAN_FREQ);

    // clk.
    CAN->FDR = ((1) << USIC_CH_FDR_DM_Pos) |
               ((1024 - step) << USIC_CH_FDR_STEP_Pos);

    // Set MPR bit select to manual (by MOIPR_MPN).
    CAN->MCR = 0;

    // Set default and configuration mode.
    CAN_NODE->NCR = CAN_NODE_NCR_CCE_Msk | CAN_NODE_NCR_INIT_Msk;

    err = can_set_bitrate(can, CAN_BIT_RATE_DEFAULT);
    if(err != E_NO_ERROR) return err;

    // Count of recv & send frames.
    CAN_NODE->NFCR = ((0) << CAN_NODE_NFCR_CFMOD_Pos) |
                     ((0b110) << CAN_NODE_NFCR_CFSEL_Pos);

    CAN_NODE->NPCR = ((CAN_LOOPBACK) << CAN_NODE_NPCR_LBM_Pos) |
                     ((CAN_NODE_RX_SEL) << CAN_NODE_NPCR_RXSEL_Pos);

    CAN_NODE->NIPR = ((CAN_SR) << CAN_NODE_NIPR_ALINP_Pos) |
                     ((CAN_SR) << CAN_NODE_NIPR_CFCINP_Pos) |
                     ((CAN_SR) << CAN_NODE_NIPR_LECINP_Pos) |
                     ((CAN_SR) << CAN_NODE_NIPR_TRINP_Pos);

    // Enable TxRx interrupt.
    CAN_NODE->NCR |= CAN_NODE_NCR_TRIE_Msk;

    // gpio.
    // tx.
    gpio_set_pad_driver(CAN_PORT_TX, CAN_PIN_TX_Msk, CAN_PIN_TX_DRIVER);
    gpio_reset(CAN_PORT_TX, CAN_PIN_TX_Msk);
    gpio_init(CAN_PORT_TX, CAN_PIN_TX_Msk, CAN_PIN_TX_CONF);
    // RX.
    gpio_init(CAN_PORT_RX, CAN_PIN_RX_Msk, CAN_PIN_RX_CONF);

    // Wait list 0 init.
    while(CAN->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }

    return E_NO_ERROR;
}

void can_disable(can_t* can)
{
    // Disable clock.
    CAN->CLC |= CAN_CLC_DISR_Msk;
    // wait.
    while((CAN->CLC & CAN_CLC_DISS_Msk) == 0){ __NOP(); }
}

void can_set_configuration_mode(can_t* can)
{
    CAN_NODE->NCR |= CAN_NODE_NCR_CCE_Msk | CAN_NODE_NCR_INIT_Msk;
}

err_t can_set_bitrate(can_t* can, can_bit_rate_t bit_rate)
{
    if((size_t)bit_rate >= NBTR_values_count) return E_INVALID_VALUE;

    CAN_NODE->NBTR = NBTR_values[(size_t)bit_rate];

    return E_NO_ERROR;
}

void can_set_normal_mode(can_t* can)
{
    CAN_NODE->NCR &= ~(CAN_NODE_NCR_CCE_Msk | CAN_NODE_NCR_INIT_Msk);
}

ALWAYS_INLINE static CAN_MO_TypeDef* can_get_mo(can_t* can, size_t index)
{
    // Согласно Reference Manual.
    return &CAN_MO0[index];
}

//! Получает номер объекта для сообщения по индексу буфера и номеру в fifo.
static uint32_t can_mo_get_number(can_t* can, size_t buf_index, size_t fifo_n)
{
    return buf_index * CAN_FIFO_SIZE + fifo_n;
}

//! Получает номер объекта для приёма сообщения по индексу буфера и номеру в fifo.
static uint32_t can_mo_get_number_rx(can_t* can, size_t buf_index, size_t fifo_n)
{
    uint32_t mo_n = can_mo_get_number(can, buf_index, fifo_n);

    mo_n = (mo_n << 1);

    return mo_n;
}

//! Получает номер объекта для передачи сообщения по индексу буфера и номеру в fifo.
static uint32_t can_mo_get_number_tx(can_t* can, size_t buf_index, size_t fifo_n)
{
    uint32_t mo_n = can_mo_get_number(can, buf_index, fifo_n);

    mo_n = (mo_n << 1) + 1;

    return mo_n;
}

static bool can_mo_is_tx(can_t* can, uint32_t mo_n)
{
    return mo_n & 0x1;
}

static size_t can_mo_buf_index_rx(can_t* can, uint32_t mo_n)
{
    return (mo_n) / (2 * CAN_FIFO_SIZE);
}

static size_t can_mo_buf_index_tx(can_t* can, uint32_t mo_n)
{
    return (mo_n - 1) / (2 * CAN_FIFO_SIZE);
}

static size_t can_mo_fifo_n_rx(can_t* can, uint32_t mo_n)
{
    size_t bi = can_mo_buf_index_rx(can, mo_n);

    size_t fn = (mo_n) / 2 - bi * CAN_FIFO_SIZE;

    return fn;
}

static size_t can_mo_fifo_n_tx(can_t* can, uint32_t mo_n)
{
    size_t bi = can_mo_buf_index_tx(can, mo_n);

    size_t fn = (mo_n - 1) / 2 - bi * CAN_FIFO_SIZE;

    return fn;
}

static uint32_t can_list_alloc_mo_static(can_t* can, uint32_t mo_n, size_t list_index)
{
    while(CAN->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }

    CAN->PANCTR = ((0x2) << CAN_PANCTR_PANCMD_Pos) |
                  ((mo_n) << CAN_PANCTR_PANAR1_Pos) |
                  ((list_index) << CAN_PANCTR_PANAR2_Pos);

    return mo_n;
}

//static uint32_t can_list_alloc_mo(can_t* can, size_t list_index)
//{
//    while(CAN->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }
//
//    CAN->PANCTR = ((0x3) << CAN_PANCTR_PANCMD_Pos) |
//                  ((0) << CAN_PANCTR_PANAR1_Pos) |
//                  ((list_index) << CAN_PANCTR_PANAR2_Pos);
//
//    while(CAN->PANCTR & CAN_PANCTR_RBUSY_Msk){ __NOP(); }
//
//    if((CAN->PANCTR >> CAN_PANCTR_PANAR2_Pos) & 0x80) return CAN_MO_INVALID_INDEX;
//
//    uint32_t mo_n = (CAN->PANCTR & CAN_PANCTR_PANAR1_Msk) >> CAN_PANCTR_PANAR1_Pos;
//
//    return mo_n;
//}

err_t can_init_rx_buffer(can_t* can, size_t index, uint16_t ident, uint16_t mask, bool rtr)
{
    while(CAN->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }

    uint32_t free_mo_count = ((CAN->LIST[0] & CAN_LIST_SIZE_Msk) >> CAN_LIST_SIZE_Pos);

    if(free_mo_count < (CAN_FIFO_SIZE)) return E_OUT_OF_MEMORY;

    uint32_t fifo_base_mo = can_list_alloc_mo_static(can, can_mo_get_number_rx(can, index, 0), CAN_NODE_LIST_N); // LIST[0] - list of empty items.
    if(fifo_base_mo == CAN_MO_INVALID_INDEX) return E_OUT_OF_MEMORY;

    uint32_t dir = (rtr ? (CAN_MO_MOCTR_SETDIR_Msk) : (CAN_MO_MOCTR_RESDIR_Msk));

    CAN_MO_TypeDef* MO_Base = can_get_mo(can, fifo_base_mo);
    // Настроим базовый объект фифо.
    MO_Base->MOFCR = ((0b0001) << CAN_MO_MOFCR_MMC_Pos) |
                     ((0) << CAN_MO_MOFCR_RXIE_Pos) |
                     ((0) << CAN_MO_MOFCR_TXIE_Pos) |
                     ((0) << CAN_MO_MOFCR_OVIE_Pos) |
                     ((0) << CAN_MO_MOFCR_FRREN_Pos) |
                     ((0) << CAN_MO_MOFCR_RMM_Pos) |
                     ((0) << CAN_MO_MOFCR_SDT_Pos) |
                     ((0) << CAN_MO_MOFCR_STT_Pos) |
                     ((0) << CAN_MO_MOFCR_DLC_Pos);
    MO_Base->MOCTR = /* dir */ dir |
                     /* 0 */ CAN_MO_MOCTR_RESTXEN0_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESTXEN1_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESTXRQ_Msk |
                     /* 1 */ CAN_MO_MOCTR_SETRXEN_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESRTSEL_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESMSGVAL_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESMSGLST_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESNEWDAT_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESRXUPD_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESTXPND_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESRXPND_Msk;
    MO_Base->MOIPR = ((0) << CAN_MO_MOIPR_RXINP_Pos) |
                     ((0) << CAN_MO_MOIPR_TXINP_Pos) |
                     ((fifo_base_mo) << CAN_MO_MOIPR_MPN_Pos) |
                     ((0) << CAN_MO_MOIPR_CFCVAL_Pos);
    MO_Base->MOAMR = ((1) << CAN_MO_MOAMR_MIDE_Pos) |
                     ((mask << 18) << CAN_MO_MOAMR_AM_Pos);
    MO_Base->MOAR = ((0) << CAN_MO_MOAR_IDE_Pos) |
                    ((ident << 18) << CAN_MO_MOAR_ID_Pos) |
                    ((CAN_RX_FIFO_PRI) << CAN_MO_MOAR_PRI_Pos); // 0b01 by list order, 0b10 - by priority
    MO_Base->MODATAL = ((0) << CAN_MO_MODATAL_DB0_Pos) |
                       ((0) << CAN_MO_MODATAL_DB1_Pos) |
                       ((0) << CAN_MO_MODATAL_DB2_Pos) |
                       ((0) << CAN_MO_MODATAL_DB3_Pos);
    MO_Base->MODATAH = ((0) << CAN_MO_MODATAH_DB4_Pos) |
                       ((0) << CAN_MO_MODATAH_DB5_Pos) |
                       ((0) << CAN_MO_MODATAH_DB6_Pos) |
                       ((0) << CAN_MO_MODATAH_DB7_Pos);

    uint32_t mo_top = 0;

    // Добавим ведомые объекты.
    size_t i = 1;
    for(; i < CAN_FIFO_SIZE; i ++){
        uint32_t fifo_mo = can_list_alloc_mo_static(can, can_mo_get_number_rx(can, index, i), CAN_NODE_LIST_N);
        if(fifo_mo == CAN_MO_INVALID_INDEX) return E_OUT_OF_MEMORY;

        CAN_MO_TypeDef* MO = can_get_mo(can, fifo_mo);
        // Настроим объект фифо.
        MO->MOFCR = ((0b0000) << CAN_MO_MOFCR_MMC_Pos) |
                         ((0) << CAN_MO_MOFCR_RXIE_Pos) |
                         ((0) << CAN_MO_MOFCR_TXIE_Pos) |
                         ((0) << CAN_MO_MOFCR_OVIE_Pos) |
                         ((0) << CAN_MO_MOFCR_FRREN_Pos) |
                         ((0) << CAN_MO_MOFCR_RMM_Pos) |
                         ((0) << CAN_MO_MOFCR_SDT_Pos) |
                         ((0) << CAN_MO_MOFCR_STT_Pos) |
                         ((0) << CAN_MO_MOFCR_DLC_Pos);
        MO->MOCTR = /* dir */ dir |
                    /* 0 */ CAN_MO_MOCTR_RESTXEN0_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESTXEN1_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESTXRQ_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESRXEN_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESRTSEL_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESMSGVAL_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESMSGLST_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESNEWDAT_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESRXUPD_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESTXPND_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESRXPND_Msk;
        MO->MOIPR = ((0) << CAN_MO_MOIPR_RXINP_Pos) |
                    ((0) << CAN_MO_MOIPR_TXINP_Pos) |
                    ((fifo_mo) << CAN_MO_MOIPR_MPN_Pos) |
                    ((0) << CAN_MO_MOIPR_CFCVAL_Pos);
        MO->MOFGPR = ((0)) << CAN_MO_MOFGPR_BOT_Pos |
                     ((0)) << CAN_MO_MOFGPR_TOP_Pos |
                     ((0)) << CAN_MO_MOFGPR_CUR_Pos |
                     ((0)) << CAN_MO_MOFGPR_SEL_Pos;
        MO->MOAMR = ((0) << CAN_MO_MOAMR_MIDE_Pos) |
                    ((0) << CAN_MO_MOAMR_AM_Pos);
        MO->MOAR = ((0) << CAN_MO_MOAR_IDE_Pos) |
                   ((0) << CAN_MO_MOAR_ID_Pos) |
                   ((CAN_RX_FIFO_PRI) << CAN_MO_MOAR_PRI_Pos);
        MO->MODATAL = ((0) << CAN_MO_MODATAL_DB0_Pos) |
                      ((0) << CAN_MO_MODATAL_DB1_Pos) |
                      ((0) << CAN_MO_MODATAL_DB2_Pos) |
                      ((0) << CAN_MO_MODATAL_DB3_Pos);
        MO->MODATAH = ((0) << CAN_MO_MODATAH_DB4_Pos) |
                      ((0) << CAN_MO_MODATAH_DB5_Pos) |
                      ((0) << CAN_MO_MODATAH_DB6_Pos) |
                      ((0) << CAN_MO_MODATAH_DB7_Pos);

        if(i == (CAN_FIFO_SIZE - 1)){
            mo_top = fifo_mo;
        }
    }

    MO_Base->MOFGPR = ((fifo_base_mo)) << CAN_MO_MOFGPR_BOT_Pos |
                      ((mo_top      )) << CAN_MO_MOFGPR_TOP_Pos |
                      ((fifo_base_mo)) << CAN_MO_MOFGPR_CUR_Pos |
                      ((fifo_base_mo)) << CAN_MO_MOFGPR_SEL_Pos;

    return E_NO_ERROR;
}


err_t can_init_tx_buffer(can_t* can, size_t index, uint16_t ident, bool rtr, uint8_t noOfBytes)
{
    while(CAN->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }

    bool list_empty = (CAN->LIST[0] & CAN_LIST_EMPTY_Msk) >> CAN_LIST_EMPTY_Pos;
    if(list_empty) return E_OUT_OF_MEMORY;

    uint32_t free_mo_count = ((CAN->LIST[0] & CAN_LIST_SIZE_Msk) >> CAN_LIST_SIZE_Pos) + 1;

    if(free_mo_count < (CAN_FIFO_SIZE)) return E_OUT_OF_MEMORY;

    uint32_t fifo_base_mo = can_list_alloc_mo_static(can, can_mo_get_number_tx(can, index, 0), CAN_NODE_LIST_N); // LIST[0] - list of empty items.
    if(fifo_base_mo == CAN_MO_INVALID_INDEX) return E_OUT_OF_MEMORY;

    uint32_t dir = (rtr ? (CAN_MO_MOCTR_RESDIR_Msk) : (CAN_MO_MOCTR_SETDIR_Msk));

    CAN_MO_TypeDef* MO_Base = can_get_mo(can, fifo_base_mo);
    // Настроим базовый объект фифо.
    MO_Base->MOFCR = ((0b0010) << CAN_MO_MOFCR_MMC_Pos) |
                     ((0) << CAN_MO_MOFCR_RXIE_Pos) |
                     ((0) << CAN_MO_MOFCR_TXIE_Pos) |
                     ((0) << CAN_MO_MOFCR_OVIE_Pos) |
                     ((0) << CAN_MO_MOFCR_FRREN_Pos) |
                     ((0) << CAN_MO_MOFCR_RMM_Pos) |
                     ((0) << CAN_MO_MOFCR_SDT_Pos) |
                     ((CAN_SINGLE_TRANSMIT_TRIAL) << CAN_MO_MOFCR_STT_Pos) |
                     ((noOfBytes) << CAN_MO_MOFCR_DLC_Pos);
    MO_Base->MOCTR = /* dir */ dir |
                     /* 0 */ CAN_MO_MOCTR_RESTXEN0_Msk |
                     /* 1 */ CAN_MO_MOCTR_SETTXEN1_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESTXRQ_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESRXEN_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESRTSEL_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESMSGVAL_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESMSGLST_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESNEWDAT_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESRXUPD_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESTXPND_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESRXPND_Msk;
    MO_Base->MOIPR = ((0) << CAN_MO_MOIPR_RXINP_Pos) |
                     ((0) << CAN_MO_MOIPR_TXINP_Pos) |
                     ((0) << CAN_MO_MOIPR_MPN_Pos) |
                     ((0) << CAN_MO_MOIPR_CFCVAL_Pos);
    MO_Base->MOAMR = ((0) << CAN_MO_MOAMR_MIDE_Pos) |
                     ((0) << CAN_MO_MOAMR_AM_Pos);
    MO_Base->MOAR = ((0) << CAN_MO_MOAR_IDE_Pos) |
                    ((ident << 18) << CAN_MO_MOAR_ID_Pos) |
                    ((CAN_TX_FIFO_PRI) << CAN_MO_MOAR_PRI_Pos); // 0b01 by list order, 0b10 - by priority
    MO_Base->MODATAL = ((0) << CAN_MO_MODATAL_DB0_Pos) |
                       ((0) << CAN_MO_MODATAL_DB1_Pos) |
                       ((0) << CAN_MO_MODATAL_DB2_Pos) |
                       ((0) << CAN_MO_MODATAL_DB3_Pos);
    MO_Base->MODATAH = ((0) << CAN_MO_MODATAH_DB4_Pos) |
                       ((0) << CAN_MO_MODATAH_DB5_Pos) |
                       ((0) << CAN_MO_MODATAH_DB6_Pos) |
                       ((0) << CAN_MO_MODATAH_DB7_Pos);

    uint32_t mo_top = 0;

    // Добавим ведомые объекты.
    size_t i = 1;
    for(; i < CAN_FIFO_SIZE; i ++){
        uint32_t fifo_mo = can_list_alloc_mo_static(can, can_mo_get_number_tx(can, index, i), CAN_NODE_LIST_N);
        if(fifo_mo == CAN_MO_INVALID_INDEX) return E_OUT_OF_MEMORY;

        CAN_MO_TypeDef* MO = can_get_mo(can, fifo_mo);
        // Настроим объект фифо.
        MO->MOFCR = ((0b0011) << CAN_MO_MOFCR_MMC_Pos) |
                         ((0) << CAN_MO_MOFCR_RXIE_Pos) |
                         ((0) << CAN_MO_MOFCR_TXIE_Pos) |
                         ((0) << CAN_MO_MOFCR_OVIE_Pos) |
                         ((0) << CAN_MO_MOFCR_FRREN_Pos) |
                         ((0) << CAN_MO_MOFCR_RMM_Pos) |
                         ((0) << CAN_MO_MOFCR_SDT_Pos) |
                         ((CAN_SINGLE_TRANSMIT_TRIAL) << CAN_MO_MOFCR_STT_Pos) |
                         ((noOfBytes) << CAN_MO_MOFCR_DLC_Pos);
        MO->MOCTR = /* dir */ dir |
                    /* 0 */ CAN_MO_MOCTR_RESTXEN0_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESTXEN1_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESTXRQ_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESRXEN_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESRTSEL_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESMSGVAL_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESMSGLST_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESNEWDAT_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESRXUPD_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESTXPND_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESRXPND_Msk;
        MO->MOIPR = ((0) << CAN_MO_MOIPR_RXINP_Pos) |
                    ((0) << CAN_MO_MOIPR_TXINP_Pos) |
                    ((0) << CAN_MO_MOIPR_MPN_Pos) |
                    ((0) << CAN_MO_MOIPR_CFCVAL_Pos);
        MO->MOFGPR = ((0)) << CAN_MO_MOFGPR_BOT_Pos |
                     ((0)) << CAN_MO_MOFGPR_TOP_Pos |
                     ((fifo_base_mo)) << CAN_MO_MOFGPR_CUR_Pos |
                     ((0)) << CAN_MO_MOFGPR_SEL_Pos;
        MO->MOAMR = ((0) << CAN_MO_MOAMR_MIDE_Pos) |
                    ((0) << CAN_MO_MOAMR_AM_Pos);
        MO->MOAR = ((0) << CAN_MO_MOAR_IDE_Pos) |
                   ((ident << 18) << CAN_MO_MOAR_ID_Pos) |
                   ((CAN_TX_FIFO_PRI) << CAN_MO_MOAR_PRI_Pos);
        MO->MODATAL = ((0) << CAN_MO_MODATAL_DB0_Pos) |
                      ((0) << CAN_MO_MODATAL_DB1_Pos) |
                      ((0) << CAN_MO_MODATAL_DB2_Pos) |
                      ((0) << CAN_MO_MODATAL_DB3_Pos);
        MO->MODATAH = ((0) << CAN_MO_MODATAH_DB4_Pos) |
                      ((0) << CAN_MO_MODATAH_DB5_Pos) |
                      ((0) << CAN_MO_MODATAH_DB6_Pos) |
                      ((0) << CAN_MO_MODATAH_DB7_Pos);

        if(i == (CAN_FIFO_SIZE - 1)){
            mo_top = fifo_mo;
        }
    }

    MO_Base->MOFGPR = ((fifo_base_mo)) << CAN_MO_MOFGPR_BOT_Pos |
                      ((mo_top      )) << CAN_MO_MOFGPR_TOP_Pos |
                      ((fifo_base_mo)) << CAN_MO_MOFGPR_CUR_Pos |
                      ((fifo_base_mo)) << CAN_MO_MOFGPR_SEL_Pos;

    return E_NO_ERROR;
}

static uint32_t can_fifo_first(can_t* can, uint32_t mo_base_n)
{
    CAN_MO_TypeDef* MO_Base = can_get_mo(can, mo_base_n);

    uint32_t mo_n = (MO_Base->MOFGPR & CAN_MO_MOFGPR_CUR_Msk) >> CAN_MO_MOFGPR_CUR_Pos;

    return mo_n;
}

static uint32_t can_fifo_next(can_t* can, uint32_t mo_base_n, uint32_t mo_n)
{
    CAN_MO_TypeDef* MO_Base = can_get_mo(can, mo_base_n);

    uint32_t mo_bot = (MO_Base->MOFGPR & CAN_MO_MOFGPR_BOT_Msk) >> CAN_MO_MOFGPR_BOT_Pos;
    uint32_t mo_top = (MO_Base->MOFGPR & CAN_MO_MOFGPR_TOP_Msk) >> CAN_MO_MOFGPR_TOP_Pos;

    if(mo_n == mo_top) return mo_bot;

    CAN_MO_TypeDef* MO = can_get_mo(can, mo_n);
    uint32_t mo_next_n = (MO->MOSTAT & CAN_MO_MOSTAT_PNEXT_Msk) >> CAN_MO_MOSTAT_PNEXT_Pos;

    return mo_next_n;
}

static err_t can_send_msg_mo(can_t* can, CAN_MO_TypeDef* MO, const can_msg_t* msg)
{
    //if(MO->MOSTAT & CAN_MO_MOSTAT_TXRQ_Msk) return E_BUSY;
    if(MO->MOSTAT & CAN_MO_MOSTAT_RTSEL_Msk) return E_BUSY;

    MO->MOCTR = CAN_MO_MOCTR_RESMSGVAL_Msk;

    if(msg->rtr){
        MO->MOCTR = CAN_MO_MOCTR_RESDIR_Msk;
    }else{
        MO->MOCTR = CAN_MO_MOCTR_SETDIR_Msk;
    }

    if(msg->ide == 0){
        MO->MOAR = (MO->MOAR & ~(CAN_MO_MOAR_ID_Msk | CAN_MO_MOAR_IDE_Msk)) | ((msg->id) << (CAN_MO_MOAR_ID_Pos + 18));
    }else{
        MO->MOAR = (MO->MOAR & ~(CAN_MO_MOAR_ID_Msk)) | ((msg->id) << (CAN_MO_MOAR_ID_Pos)) | CAN_MO_MOAR_IDE_Msk;
    }

    MO->MOFCR = (MO->MOFCR & ~(CAN_MO_MOFCR_DLC_Msk)) | ((msg->dlc) << CAN_MO_MOFCR_DLC_Pos);

    if(!msg->rtr){
        MO->MODATAL = (((uint32_t)msg->data[0]) << CAN_MO_MODATAL_DB0_Pos) |
                      (((uint32_t)msg->data[1]) << CAN_MO_MODATAL_DB1_Pos) |
                      (((uint32_t)msg->data[2]) << CAN_MO_MODATAL_DB2_Pos) |
                      (((uint32_t)msg->data[3]) << CAN_MO_MODATAL_DB3_Pos);
        MO->MODATAH = (((uint32_t)msg->data[4]) << CAN_MO_MODATAH_DB4_Pos) |
                      (((uint32_t)msg->data[5]) << CAN_MO_MODATAH_DB5_Pos) |
                      (((uint32_t)msg->data[6]) << CAN_MO_MODATAH_DB6_Pos) |
                      (((uint32_t)msg->data[7]) << CAN_MO_MODATAH_DB7_Pos);
    }

    MO->MOCTR = CAN_MO_MOCTR_RESRTSEL_Msk |
                CAN_MO_MOCTR_SETNEWDAT_Msk |
                CAN_MO_MOCTR_SETTXRQ_Msk |
                CAN_MO_MOCTR_SETTXEN0_Msk |
                //CAN_MO_MOCTR_SETTXEN1_Msk |
                CAN_MO_MOCTR_SETMSGVAL_Msk;

    return E_NO_ERROR;
}

err_t can_send_msg(can_t* can, size_t index, const can_msg_t* msg)
{
    err_t err = E_AGAIN;
    uint32_t mo_base_n = can_mo_get_number_tx(can, index, 0);
    uint32_t mo_n;
    CAN_MO_TypeDef* MO;
    size_t i;
    for(i = 0; i < CAN_FIFO_SIZE; i ++){
        if(i == 0){
            mo_n = can_fifo_first(can, mo_base_n);
        }else{
            mo_n = can_fifo_next(can, mo_base_n, mo_n);
        }

        MO = can_get_mo(can, mo_n);

        if((MO->MOSTAT & CAN_MO_MOSTAT_TXRQ_Msk) == 0){
            err = can_send_msg_mo(can, MO, msg);
            if(err == E_NO_ERROR) return err;
        }
    }

    return err;
}

static err_t can_recv_msg_mo(can_t* can, CAN_MO_TypeDef* MO, can_msg_t* msg)
{
    if(MO->MOSTAT & CAN_MO_MOSTAT_RTSEL_Msk) return E_BUSY;

    do{
        MO->MOCTR = CAN_MO_MOCTR_RESNEWDAT_Msk;

        msg->rtr = (MO->MOCTR & CAN_MO_MOSTAT_TXRQ_Msk) ? true : false;

        if((MO->MOAR & CAN_MO_MOAR_IDE_Msk) == 0){
            msg->ide = 0;
            msg->id = (MO->MOAR & CAN_MO_MOAR_ID_Msk) >> (CAN_MO_MOAR_ID_Pos + 18);
        }else{
            msg->ide = 1;
            msg->id = (MO->MOAR & CAN_MO_MOAR_ID_Msk) >> CAN_MO_MOAR_ID_Pos;
        }

        MO->MOFCR = (MO->MOFCR & ~(CAN_MO_MOFCR_DLC_Msk)) | ((msg->dlc) << CAN_MO_MOFCR_DLC_Pos);

        if(!msg->rtr){
            msg->data[0] = (MO->MODATAL & CAN_MO_MODATAL_DB0_Msk) >> CAN_MO_MODATAL_DB0_Pos;
            msg->data[1] = (MO->MODATAL & CAN_MO_MODATAL_DB1_Msk) >> CAN_MO_MODATAL_DB1_Pos;
            msg->data[2] = (MO->MODATAL & CAN_MO_MODATAL_DB2_Msk) >> CAN_MO_MODATAL_DB2_Pos;
            msg->data[3] = (MO->MODATAL & CAN_MO_MODATAL_DB3_Msk) >> CAN_MO_MODATAL_DB3_Pos;
            msg->data[4] = (MO->MODATAL & CAN_MO_MODATAH_DB4_Msk) >> CAN_MO_MODATAH_DB4_Pos;
            msg->data[5] = (MO->MODATAL & CAN_MO_MODATAH_DB5_Msk) >> CAN_MO_MODATAH_DB5_Pos;
            msg->data[6] = (MO->MODATAL & CAN_MO_MODATAH_DB6_Msk) >> CAN_MO_MODATAH_DB6_Pos;
            msg->data[7] = (MO->MODATAL & CAN_MO_MODATAH_DB7_Msk) >> CAN_MO_MODATAH_DB7_Pos;
        }

    }while(MO->MOSTAT & (CAN_MO_MOSTAT_NEWDAT_Msk | CAN_MO_MOSTAT_RXUPD_Msk));

    //MO->MOCTR = CAN_MO_MOCTR_SETMSGVAL_Msk;

    return E_NO_ERROR;
}

err_t can_recv_msg(can_t* can, size_t index, can_msg_t* msg)
{
    err_t err = E_AGAIN;
    uint32_t mo_base_n = can_mo_get_number_rx(can, index, 0);
    uint32_t mo_n;
    CAN_MO_TypeDef* MO;
    size_t i;
    for(i = 0; i < CAN_FIFO_SIZE; i ++){
        if(i == 0){
            mo_n = can_fifo_first(can, mo_base_n);
        }else{
            mo_n = can_fifo_next(can, mo_base_n, mo_n);
        }

        MO = can_get_mo(can, mo_n);

        if((MO->MOSTAT & CAN_MO_MOSTAT_NEWDAT_Msk) != 0){
            err = can_recv_msg_mo(can, MO, msg);
            if(err == E_NO_ERROR) return err;
        }
    }

    return err;
}

#endif
