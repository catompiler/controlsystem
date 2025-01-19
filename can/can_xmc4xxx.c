#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "can_xmc4xxx.h"
#include "hardware/config.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


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

    return E_NO_ERROR;
}

void can_set_configuration_mode()
{
    CAN_NODE->NCR |= CAN_NODE_NCR_CCE_Msk | CAN_NODE_NCR_INIT_Msk;
}

void can_set_normal_mode()
{
    CAN_NODE->NCR &= ~(CAN_NODE_NCR_CCE_Msk | CAN_NODE_NCR_INIT_Msk);
}

err_t can_set_bitrate(can_bit_rate_t bit_rate)
{
    if((size_t)bit_rate >= NBTR_values_count) return E_SLCAN_INVALID_VALUE;

    CAN_NODE->NBTR = NBTR_values[(size_t)bit_rate];

    return E_NO_ERROR;
}


#endif
