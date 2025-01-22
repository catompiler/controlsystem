#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "can_xmc4xxx.h"
#include "hardware/config.h"


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


err_t can_init()
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

    // Set default and configuration mode.
    CAN_NODE->NCR = CAN_NODE_NCR_CCE_Msk | CAN_NODE_NCR_INIT_Msk;

    err = can_set_bitrate(CAN_BIT_RATE_DEFAULT);
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

void can_set_configuration_mode()
{
    CAN_NODE->NCR |= CAN_NODE_NCR_CCE_Msk | CAN_NODE_NCR_INIT_Msk;
}

err_t can_set_bitrate(can_bit_rate_t bit_rate)
{
    if((size_t)bit_rate >= NBTR_values_count) return E_SLCAN_INVALID_VALUE;

    CAN_NODE->NBTR = NBTR_values[(size_t)bit_rate];

    return E_NO_ERROR;
}

void can_set_normal_mode()
{
    CAN_NODE->NCR &= ~(CAN_NODE_NCR_CCE_Msk | CAN_NODE_NCR_INIT_Msk);
}

ALWAYS_INLINE static CAN_MO_TypeDef* can_get_mo(size_t index)
{
    // Согласно Reference Manual.
    return &CAN_MO0[index];
}

//! Получает номер объекта для приёма сообщения по индексу буфера и номеру в fifo.
static uint32_t can_mo_get_number_rx(size_t buf_index, size_t fifo_n)
{
    return buf_index * CAN_FIFO_SIZE + fifo_n;
}

static uint32_t can_list_alloc_mo_static(uint32_t mo_n, size_t list_index)
{
    while(CAN->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }

    CAN->PANCTR = ((0x2) << CAN_PANCTR_PANCMD_Pos) |
                  ((mo_n) << CAN_PANCTR_PANAR1_Pos) |
                  ((list_index) << CAN_PANCTR_PANAR2_Pos);

    return mo_n;
}

//static uint32_t can_list_alloc_mo(size_t list_index)
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

err_t can_init_rx_buffer(size_t index, uint16_t ident, uint16_t mask, bool rtr)
{
    while(CAN->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }

    uint32_t free_mo_count = ((CAN->LIST[0] & CAN_LIST_SIZE_Msk) >> CAN_LIST_SIZE_Pos);

    if(free_mo_count < (CAN_FIFO_SIZE)) return E_OUT_OF_MEMORY;

    uint32_t fifo_base_mo = can_list_alloc_mo_static(can_mo_get_number_rx(index, 0), CAN_NODE_LIST_N); // LIST[0] - list of empty items.
    if(fifo_base_mo == CAN_MO_INVALID_INDEX) return E_OUT_OF_MEMORY;

    uint32_t dir = (rtr ? (CAN_MO_MOCTR_SETDIR_Msk) : (CAN_MO_MOCTR_RESDIR_Msk));

    CAN_MO_TypeDef* MO_Base = can_get_mo(fifo_base_mo);
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
                     ((0) << CAN_MO_MOIPR_MPN_Pos) |
                     ((0) << CAN_MO_MOIPR_CFCVAL_Pos);
    MO_Base->MOAMR = ((1) << CAN_MO_MOAMR_MIDE_Pos) |
                     ((mask << 18) << CAN_MO_MOAMR_AM_Pos);
    MO_Base->MOAR = ((0) << CAN_MO_MOAR_IDE_Pos) |
                    ((ident << 18) << CAN_MO_MOAR_ID_Pos) |
                    ((0b10) << CAN_MO_MOAR_PRI_Pos); // 0b01 by list order, 0b10 - by priority
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
    size_t i = 0;
    for(; i < CAN_FIFO_SIZE; i ++){
        uint32_t fifo_mo = can_list_alloc_mo_static(can_mo_get_number_rx(index, i + 1), CAN_NODE_LIST_N);
        if(fifo_mo == CAN_MO_INVALID_INDEX) return E_OUT_OF_MEMORY;

        CAN_MO_TypeDef* MO = can_get_mo(fifo_mo);
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
                    ((0) << CAN_MO_MOIPR_MPN_Pos) |
                    ((0) << CAN_MO_MOIPR_CFCVAL_Pos);
        MO->MOFGPR = ((0)) << CAN_MO_MOFGPR_BOT_Pos |
                     ((0)) << CAN_MO_MOFGPR_TOP_Pos |
                     ((0)) << CAN_MO_MOFGPR_CUR_Pos |
                     ((0)) << CAN_MO_MOFGPR_SEL_Pos;
        MO->MOAMR = ((0) << CAN_MO_MOAMR_MIDE_Pos) |
                    ((0) << CAN_MO_MOAMR_AM_Pos);
        MO->MOAR = ((0) << CAN_MO_MOAR_IDE_Pos) |
                   ((0) << CAN_MO_MOAR_ID_Pos) |
                   ((0) << CAN_MO_MOAR_PRI_Pos);
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
}


#endif
