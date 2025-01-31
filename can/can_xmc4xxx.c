#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "can_xmc4xxx.h"
#include "hardware/config.h"
#include <assert.h>


#define MAKE_CAN(PTR) { PTR }

static can_t cans[] = {
#ifdef CAN
        MAKE_CAN(CAN),
#endif
};
static_assert((sizeof(cans)/sizeof(cans[0])) == CANS_COUNT, "Invalid can array!");


#define MAKE_CAN_NODE(N) { &cans[0], CAN_NODE ## N, N, NULL, 0, NULL}

static can_node_t can_nodes[] = {
#ifdef CAN_NODE0
    MAKE_CAN_NODE(0),
#endif
#ifdef CAN_NODE1
    MAKE_CAN_NODE(1),
#endif
#ifdef CAN_NODE2
    MAKE_CAN_NODE(2),
#endif
#ifdef CAN_NODE3
    MAKE_CAN_NODE(3),
#endif
#ifdef CAN_NODE4
    MAKE_CAN_NODE(4),
#endif
#ifdef CAN_NODE5
    MAKE_CAN_NODE(5),
#endif
#ifdef CAN_NODE6
    MAKE_CAN_NODE(6),
#endif
#ifdef CAN_NODE7
    MAKE_CAN_NODE(7),
#endif
};
static_assert((sizeof(can_nodes)/sizeof(can_nodes[0])) == CAN_NODES_COUNT, "Invalid can nodes array!");



//! Число обработчиков прерываний CAN.
#define CAN_SR_COUNT 8
static_assert(CAN_SR_COUNT >= CAN_NODES_COUNT, "Count of SR handlers must be greater than nodes count!");



#if CAN_FREQ == 60000000
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
#else
#error Unknown NBTR values for defined CAN frequency!
#endif

const size_t NBTR_values_count = (sizeof(NBTR_values)/sizeof(NBTR_values[0]));


#define CAN_MO_INVALID_INDEX (0xffffffff)

//#define CAN_MO_FIFO_LIST ((CAN_NODES) + 1)

#define CAN_NODE_LIST_NUMBER(N) ((N) + 1)


// Очердёдность передачи сообщений.
// Rx FIFO.
#define CAN_RX_FIFO_PRI 0b001 // 0b01 by list order, 0b10 - by priority
// Tx FIFO.
#define CAN_TX_FIFO_PRI 0b001 // 0b01 by list order, 0b10 - by priority


// Число регистров MSPND.
#define CAN_MSG_PEND_REGS_COUNT 8
// Максимальный номер бита в регистре MSPND.
#define CAN_MSG_INDEX_MAX 31



/*
 * Функции получения объектов CAN по индексу (номеру).
 */


//! Получает указатель на CAN по индексу.
ALWAYS_INLINE static can_t* can_get_can(size_t index)
{
    assert(index == 0);

    // Согласно Reference Manual.
    return &cans[0];
}

//! Получает указатель на CAN_NODE по индексу.
ALWAYS_INLINE static can_node_t* can_get_node(can_t* can, size_t index)
{
    (void) can;

    assert(index < CAN_NODES_COUNT);

    return &can_nodes[index];
}

/*
 * Функции получения регистров объектов CAN по индексу (номеру).
 */

// //! Получает указатель на CAN по индексу.
//ALWAYS_INLINE static CAN_GLOBAL_TypeDef* can_get_can_device(size_t index)
//{
//    (void) index;
//
//    // Согласно Reference Manual.
//    return (CAN_GLOBAL_TypeDef*)CAN_BASE;
//}
//
// //! Получает указатель на CAN_NODE по индексу.
//ALWAYS_INLINE static CAN_NODE_TypeDef* can_get_node_device(can_t* can, size_t index)
//{
//    (void) can;
//
//    assert(index < CAN_NODES_COUNT);
//
//    // Согласно Reference Manual.
//    return (CAN_NODE_TypeDef*)(CAN_NODE0_BASE + 0x100 * index);
//}

//! Получает указатель на CAN_MO по индексу.
ALWAYS_INLINE static CAN_MO_TypeDef* can_get_mo(can_t* can, size_t index)
{
    (void) can;

    assert(index < CAN_MO_COUNT);

    // Согласно Reference Manual.
    return (CAN_MO_TypeDef*)(CAN_MO0_BASE + 0x20 * index);
}

//! Получает ноду MO.
static can_node_t* can_get_mo_node(can_t* can, CAN_MO_TypeDef* MO)
{
    (void) can;

    assert(MO != NULL);

    uint32_t list_n = (MO->MOSTAT & CAN_MO_MOSTAT_LIST_Msk) >> CAN_MO_MOSTAT_LIST_Pos;

    return ((list_n > 0) && (list_n <= CAN_NODES_COUNT)) ? &can_nodes[list_n - 1] : NULL;
}


/*
 * Функции для работы с индексами сообщений.
 */

ALWAYS_INLINE static uint32_t can_mo_n_to_pend_n(can_t* can, uint32_t mo_n)
{
    (void) can;

    return mo_n;
}

ALWAYS_INLINE static uint32_t can_pend_n_to_mo_n(can_t* can, uint32_t pend_n)
{
    (void) can;

    return pend_n;
}

/*
 * Функции добавления MO к нодам (спискам).
 */

//static uint32_t can_list_alloc_mo_static(can_t* can, uint32_t mo_n, size_t list_index)
//{
//    assert(can != NULL);
//
//    while(can->can_device->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }
//
//    can->can_device->PANCTR = ((0x2) << CAN_PANCTR_PANCMD_Pos) |
//                  ((mo_n) << CAN_PANCTR_PANAR1_Pos) |
//                  ((list_index) << CAN_PANCTR_PANAR2_Pos);
//
//    return mo_n;
//}

static uint32_t can_list_alloc_mo(can_t* can, size_t list_index)
{
    assert(can != NULL);

    while(can->can_device->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }

    can->can_device->PANCTR = ((0x3) << CAN_PANCTR_PANCMD_Pos) |
                  ((0) << CAN_PANCTR_PANAR1_Pos) |
                  ((list_index) << CAN_PANCTR_PANAR2_Pos);

    while(can->can_device->PANCTR & CAN_PANCTR_RBUSY_Msk){ __NOP(); }

    if((can->can_device->PANCTR >> CAN_PANCTR_PANAR2_Pos) & 0x80) return CAN_MO_INVALID_INDEX;

    uint32_t mo_n = (can->can_device->PANCTR & CAN_PANCTR_PANAR1_Msk) >> CAN_PANCTR_PANAR1_Pos;

    return mo_n;
}


/*
 * Функции работы с MO.
 */

//! Получает флаг события TX MO.
ALWAYS_INLINE static bool can_mo_event_is_tx(CAN_MO_TypeDef* MO)
{
    return (MO->MOSTAT & CAN_MO_MOSTAT_TXPND_Msk) >> CAN_MO_MOSTAT_TXPND_Pos;
}

//! Получает флаг события RX MO.
ALWAYS_INLINE static bool can_mo_event_is_rx(CAN_MO_TypeDef* MO)
{
    return (MO->MOSTAT & CAN_MO_MOSTAT_RXPND_Msk) >> CAN_MO_MOSTAT_RXPND_Pos;
}

// //! Получает нижний MO в fifo.
//ALWAYS_INLINE static uint32_t can_mo_fifo_bot(CAN_MO_TypeDef* MO)
//{
//    return (MO->MOFGPR & CAN_MO_MOFGPR_BOT_Msk) >> CAN_MO_MOFGPR_BOT_Pos;
//}
//
// //! Получает верхний MO в fifo.
//ALWAYS_INLINE static uint32_t can_mo_fifo_top(CAN_MO_TypeDef* MO)
//{
//    return (MO->MOFGPR & CAN_MO_MOFGPR_TOP_Msk) >> CAN_MO_MOFGPR_TOP_Pos;
//}

//! Получает текущий MO в fifo.
ALWAYS_INLINE static uint32_t can_mo_fifo_cur(CAN_MO_TypeDef* MO)
{
    return (MO->MOFGPR & CAN_MO_MOFGPR_CUR_Msk) >> CAN_MO_MOFGPR_CUR_Pos;
}

//! Получает номер главного объекта FIFO.
static uint32_t can_mo_fifo_base_mo_n(can_t* can, uint32_t mo_n)
{
    CAN_MO_TypeDef* MO = can_get_mo(can, mo_n);

    uint32_t mmc = (MO->MOFCR & CAN_MO_MOFCR_MMC_Msk) >> CAN_MO_MOFCR_MMC_Pos;

    if(mmc == 0b01 || mmc == 0b10){
        return mo_n;
    }

    return can_mo_fifo_cur(MO);
}
//    uint32_t list_n = (MO->MOSTAT & CAN_MO_MOSTAT_LIST_Msk) >> CAN_MO_MOSTAT_LIST_Pos;
//
//    if(list_n == 0 || list_n > CAN_NODES_COUNT) return CAN_MO_INVALID_INDEX;
//
//    uint32_t mo_n_begin = (can->can_device->LIST[list_n] & CAN_LIST_BEGIN_Msk) >> CAN_LIST_BEGIN_Pos;
//    uint32_t mo_n_end = (can->can_device->LIST[list_n] & CAN_LIST_END_Msk) >> CAN_LIST_END_Pos;
//
//    uint32_t mo_n_next = mo_n_begin;
//    uint32_t mo_n_cur;
//    CAN_MO_TypeDef* MO;
//
//    uint32_t mo_n_bot;
//    uint32_t mo_n_top;
//
//    uint32_t mmc;
//
//    do{
//        mo_n_cur = mo_n_next;
//
//        MO = can_get_mo(can, mo_n_cur);
//
//        mmc = (MO->MOFCR & CAN_MO_MOFCR_MMC_Msk) >> CAN_MO_MOFCR_MMC_Pos;
//
//        if(mmc == 0b01 || mmc == 0b10){
//            mo_n_bot = (MO->MOFGPR & CAN_MO_MOFGPR_BOT_Msk) >> CAN_MO_MOFGPR_BOT_Pos;
//            mo_n_top = (MO->MOFGPR & CAN_MO_MOFGPR_TOP_Msk) >> CAN_MO_MOFGPR_TOP_Pos;
//        }
//
//        mo_n_next = (MO->MOSTAT & CAN_MO_MOSTAT_PNEXT_Msk) >> CAN_MO_MOSTAT_PNEXT_Pos;
//
//    } while((mo_n_next != mo_n_end) && (mo_n_next != mo_n_cur));
//
//    return CAN_MO_INVALID_INDEX;
//}


/*
 * Обработчики прерываний.
 */


static void can_mo_irq_handler_impl(size_t can_n)
{
    can_t* can = can_get_can(can_n);

    can_node_t* can_node;
    can_node_event_t node_event;

    CAN_MO_TypeDef* MO;
    uint32_t mo_n;
    uint32_t mo_fifo_base;
    uint32_t mo_index;
    uint32_t pend_n;
    size_t i;
    for(i = 0; i < CAN_MSG_PEND_REGS_COUNT; i ++){
        can->can_device->MSIMASK = CAN_MSIMASK_IM_Msk;

        for(;;){
            mo_index = can->can_device->MSID[i] & CAN_MSID_INDEX_Msk;

            if(mo_index > CAN_MSG_INDEX_MAX) break;

            pend_n = mo_index + i * (CAN_MSG_INDEX_MAX + 1);

            mo_n = can_pend_n_to_mo_n(can, pend_n);
            mo_fifo_base = can_mo_fifo_base_mo_n(can, mo_n);
            MO = can_get_mo(can, mo_n);
            can_node = can_get_mo_node(can, MO);

            if(can_mo_event_is_tx(MO)){
                node_event.type = CAN_NODE_EVENT_MSG_SEND;
                node_event.msg_send.buf_index = mo_fifo_base;
            }else if(can_mo_event_is_rx(MO)){
                node_event.type = CAN_NODE_EVENT_MSG_RECV;
                node_event.msg_recv.buf_index = mo_fifo_base;
            }else{
                node_event.type = CAN_NODE_EVENT_UNKNOWN;
            }

            MO->MOCTR = CAN_MO_MOCTR_RESTXPND_Msk |
                        CAN_MO_MOCTR_RESRXPND_Msk/* |
                        CAN_MO_MOCTR_RESRTSEL_Msk*//* |
                        CAN_MO_MOCTR_RESTXEN0_Msk*/;

            can->can_device->MSPND[i] = ~(1 << mo_index);

            if(can_node->callback){
                can_node->callback(can_node, &node_event);
            }

        }
    }
}

static void can_node_irq_handler_impl(size_t can_n, size_t node_n)
{
    can_node_event_t node_event;

    can_t* can = can_get_can(can_n);
    can_node_t* can_node = can_get_node(can, node_n);

    CAN_NODE_TypeDef* node_device = can_node->node_device;

    // if counter overflow.
    if(node_device->NFCR & CAN_NODE_NFCR_CFCOV_Msk){
        // clear flag.
        node_device->NFCR &= ~CAN_NODE_NFCR_CFCOV_Msk;
        // increment.
        can_node->frames_counter_hi ++;
    }

    // read flags.
    uint32_t NSR = node_device->NSR;
    // clear all flags.
    node_device->NSR = 0x0;

    can_error_t can_err = (NSR & CAN_NODE_NSR_LEC_Msk) >> CAN_NODE_NSR_LEC_Pos;
    if(can_err != CAN_ERROR_NONE){

        node_event.type = CAN_NODE_EVENT_ERROR;
        node_event.error.error = can_err;

        if(can_node->callback){
            can_node->callback(can_node, &node_event);
        }
    }

    if(NSR & CAN_NODE_NSR_ALERT_Msk){

        node_event.type = CAN_NODE_EVENT_ALERT;
        node_event.alert.bus_off = (NSR & CAN_NODE_NSR_BOFF_Msk) >> CAN_NODE_NSR_BOFF_Pos;
        node_event.alert.warning_limit_reached = (NSR & CAN_NODE_NSR_EWRN_Msk) >> CAN_NODE_NSR_EWRN_Pos;
        node_event.alert.internal = (NSR & (CAN_NODE_NSR_LLE_Msk | CAN_NODE_NSR_LOE_Msk)) != 0;
        node_event.alert.init_set_by_hw = (node_device->NCR & CAN_NODE_NCR_INIT_Msk) >> CAN_NODE_NCR_INIT_Pos;

        if(can_node->callback){
            can_node->callback(can_node, &node_event);
        }
    }

}


//! Обработчик событий от MO и CAN.
void CAN0_0_IRQHandler(void)
{
    can_mo_irq_handler_impl(0);
}

#ifdef CAN_NODE0
//! Обработчик событий от NODE0
void CAN0_1_IRQHandler(void)
{
    can_node_irq_handler_impl(0, 0);
}
#endif

#ifdef CAN_NODE1
//! Обработчик событий от NODE1
void CAN0_2_IRQHandler(void)
{
    can_node_irq_handler_impl(0, 1);
}
#endif

#ifdef CAN_NODE2
//! Обработчик событий от NODE2
void CAN0_3_IRQHandler(void)
{
    can_node_irq_handler_impl(0, 2);
}
#endif

#ifdef CAN_NODE3
//! Обработчик событий от NODE3
void CAN0_4_IRQHandler(void)
{
    can_node_irq_handler_impl(0, 3);
}
#endif

#ifdef CAN_NODE4
//! Обработчик событий от NODE4
void CAN0_5_IRQHandler(void)
{
    can_node_irq_handler_impl(0, 4);
}
#endif

#ifdef CAN_NODE5
//! Обработчик событий от NODE5
void CAN0_6_IRQHandler(void)
{
    can_node_irq_handler_impl(0, 5);
}
#endif

#ifdef CAN_NODE6
//! Обработчик событий от NODE6
void CAN0_7_IRQHandler(void)
{
    can_node_irq_handler_impl(0, 6);
}
#endif

#ifdef CAN_NODE7
//! Обработчик событий от NODE7
void CAN0_8_IRQHandler(void)
{
    can_node_irq_handler_impl(0, 7);
}
#endif



can_t* can_init(can_init_t* is)
{
    if(is == NULL) return NULL;
    if(is->can_n != 0) return NULL;

    can_t* can = can_get_can(is->can_n);

    // Enable clock.
    can->can_device->CLC = can->can_device->CLC & ~(CAN_CLC_SBWE_Msk | CAN_CLC_DISR_Msk);
    // wait.
    while(can->can_device->CLC & CAN_CLC_DISS_Msk){ __NOP(); }

    // Prescaler.
    uint32_t step = SystemCoreClock / (CAN_FREQ);

    // clk.
    can->can_device->FDR = ((1) << USIC_CH_FDR_DM_Pos) |
               ((1024 - step) << USIC_CH_FDR_STEP_Pos);

    // Set MPR bit select to manual (by MOIPR_MPN).
    can->can_device->MCR = 0;

    // Wait list 0 init.
    while(can->can_device->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }

    return can;
}

void can_disable(can_t* can)
{
    assert(can != NULL);

    // Disable clock.
    can->can_device->CLC |= CAN_CLC_DISR_Msk;
    // wait.
    while((can->can_device->CLC & CAN_CLC_DISS_Msk) == 0){ __NOP(); }
}


can_node_t* can_node_init(can_node_init_t* is)
{
    if(is == NULL) return NULL;
    if(is->can == NULL) return NULL;
    if(is->can_node_n >= CAN_NODES_COUNT) return NULL;

    size_t sr_number = is->can_node_n + 1;
    if(sr_number >= CAN_SR_COUNT) return NULL;

    can_node_t* can_node = can_get_node(is->can, is->can_node_n);
    if(can_node->can != is->can) return NULL;

    can_node->callback = is->callback;
    can_node->user_data = is->user_data;

    // Set default and configuration mode.
    can_node->node_device->NCR = CAN_NODE_NCR_CCE_Msk | CAN_NODE_NCR_INIT_Msk |
                                 ((is->analyzer) << CAN_NODE_NCR_CALM_Pos);

    err_t err = can_node_set_bitrate(can_node, is->bit_rate);
    if(err != E_NO_ERROR) return NULL;

    // Count of recv & send frames.

    can_node->node_device->NFCR = ((0) << CAN_NODE_NFCR_CFMOD_Pos) |
                                  ((0b110) << CAN_NODE_NFCR_CFSEL_Pos) |
                                  CAN_NODE_NFCR_CFCIE_Msk;

    can_node->node_device->NPCR = ((is->loopback) << CAN_NODE_NPCR_LBM_Pos) |
                     ((is->sel_rx) << CAN_NODE_NPCR_RXSEL_Pos);

    can_node->node_device->NIPR = ((sr_number) << CAN_NODE_NIPR_ALINP_Pos) |
                     ((sr_number) << CAN_NODE_NIPR_CFCINP_Pos) |
                     ((sr_number) << CAN_NODE_NIPR_LECINP_Pos) |
                     ((sr_number) << CAN_NODE_NIPR_TRINP_Pos);

    // Enable TxRx interrupt.
    can_node->node_device->NCR |= CAN_NODE_NCR_LECIE_Msk |
                                  CAN_NODE_NCR_ALIE_Msk;

    if(!is->loopback){
        // gpio.
        if(!is->analyzer){
            // tx.
            gpio_set_pad_driver(is->gpio_tx, is->pin_tx_msk, is->pad_driver_tx);
            gpio_set(is->gpio_tx, is->pin_tx_msk);
            gpio_init(is->gpio_tx, is->pin_tx_msk, is->conf_tx);
        }
        // RX.
        gpio_init(is->gpio_rx, is->pin_rx_msk, is->conf_rx);
    }

    return can_node;
}

void can_node_set_configuration_mode(can_node_t* can_node)
{
    assert(can_node != NULL);

    can_node->node_device->NCR |= CAN_NODE_NCR_CCE_Msk | CAN_NODE_NCR_INIT_Msk;
}

err_t can_node_set_bitrate(can_node_t* can_node, can_bit_rate_t bit_rate)
{
    assert(can_node != NULL);

    if((size_t)bit_rate >= NBTR_values_count) return E_INVALID_VALUE;

    can_node->node_device->NBTR = NBTR_values[(size_t)bit_rate];

    return E_NO_ERROR;
}

void can_node_set_normal_mode(can_node_t* can_node)
{
    assert(can_node != NULL);

    can_node->node_device->NCR &= ~(CAN_NODE_NCR_CCE_Msk | CAN_NODE_NCR_INIT_Msk);
}

void* can_node_user_data(can_node_t* can_node)
{
    assert(can_node != NULL);

    return can_node->user_data;
}

void can_node_set_user_data(can_node_t* can_node, void* user_data)
{
    assert(can_node != NULL);

    can_node->user_data = user_data;
}

bool can_node_status_bus_off(can_node_t* can_node)
{
    return (can_node->node_device->NSR & CAN_NODE_NSR_BOFF_Msk) >> CAN_NODE_NSR_BOFF_Pos;
}

bool can_node_status_warning_limit_reached(can_node_t* can_node)
{
    return (can_node->node_device->NSR & CAN_NODE_NSR_EWRN_Msk) >> CAN_NODE_NSR_EWRN_Pos;
}

bool can_node_status_init_set_by_hw(can_node_t* can_node)
{
    return (can_node->node_device->NCR & (CAN_NODE_NCR_INIT_Msk | CAN_NODE_NCR_CCE_Msk)) == CAN_NODE_NCR_INIT_Msk;
}

bool can_node_status_internal(can_node_t* can_node)
{
    return (can_node->node_device->NSR & (CAN_NODE_NSR_LOE_Msk | CAN_NODE_NSR_LLE_Msk)) != 0;
}

can_error_t can_node_last_error(can_node_t* can_node)
{
    return (can_node->node_device->NSR & CAN_NODE_NSR_LEC_Msk) >> CAN_NODE_NSR_LEC_Pos;
}

uint8_t can_node_warning_level(can_node_t* can_node)
{
    return (can_node->node_device->NECNT & CAN_NODE_NECNT_EWRNLVL_Msk) >> CAN_NODE_NECNT_EWRNLVL_Pos;
}

void can_node_set_warning_level(can_node_t* can_node, uint8_t level)
{
    can_node->node_device->NECNT = (can_node->node_device->NECNT & ~CAN_NODE_NECNT_EWRNLVL_Msk) |
                                   ((level) << CAN_NODE_NECNT_EWRNLVL_Pos);
}

uint8_t can_node_transmit_error_counter(can_node_t* can_node)
{
    return (can_node->node_device->NECNT & CAN_NODE_NECNT_TEC_Msk) >> CAN_NODE_NECNT_TEC_Pos;
}

uint8_t can_node_receive_error_counter(can_node_t* can_node)
{
    return (can_node->node_device->NECNT & CAN_NODE_NECNT_REC_Msk) >> CAN_NODE_NECNT_REC_Pos;
}

uint64_t can_node_rxtx_count(can_node_t* can_node)
{
    uint32_t cfc_prev = (can_node->node_device->NFCR & CAN_NODE_NFCR_CFC_Msk) >> CAN_NODE_NFCR_CFC_Pos;
    uint32_t cfc_hi = can_node->frames_counter_hi;
    uint32_t cfc_cur = (can_node->node_device->NFCR & CAN_NODE_NFCR_CFC_Msk) >> CAN_NODE_NFCR_CFC_Pos;

    if(cfc_cur < cfc_prev) cfc_hi ++;

    return (uint64_t)cfc_hi << 16 | cfc_cur;
}

can_mo_index_t can_node_init_rx_buffer(can_node_t* can_node, size_t fifo_len, uint16_t ident, uint16_t mask, bool rtr)
{
    assert(can_node != NULL);

    can_t* can = can_node->can;

    while(can->can_device->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }

    bool list_empty = (can->can_device->LIST[0] & CAN_LIST_EMPTY_Msk) >> CAN_LIST_EMPTY_Pos;
    if(list_empty) return CAN_MO_INVALID_INDEX;

    uint32_t free_mo_count = ((can->can_device->LIST[0] & CAN_LIST_SIZE_Msk) >> CAN_LIST_SIZE_Pos);
    if(free_mo_count < (fifo_len)) return CAN_MO_INVALID_INDEX;

    uint32_t fifo_base_mo = can_list_alloc_mo(can, CAN_NODE_LIST_NUMBER(can_node->node_n));
    if(fifo_base_mo == CAN_MO_INVALID_INDEX) return CAN_MO_INVALID_INDEX;

    uint32_t dir = (rtr ? (CAN_MO_MOCTR_SETDIR_Msk) : (CAN_MO_MOCTR_RESDIR_Msk));

    uint32_t base_pend_n = can_mo_n_to_pend_n(can, fifo_base_mo);

    CAN_MO_TypeDef* MO_Base = can_get_mo(can, fifo_base_mo);
    // Настроим базовый объект фифо.
    MO_Base->MOFCR = ((0b0001) << CAN_MO_MOFCR_MMC_Pos) |
                     ((1) << CAN_MO_MOFCR_RXIE_Pos) |
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
                     /* 1 */ CAN_MO_MOCTR_SETMSGVAL_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESMSGLST_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESNEWDAT_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESRXUPD_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESTXPND_Msk |
                     /* 0 */ CAN_MO_MOCTR_RESRXPND_Msk;
    MO_Base->MOIPR = ((0) << CAN_MO_MOIPR_RXINP_Pos) |
                     ((0) << CAN_MO_MOIPR_TXINP_Pos) |
                     ((base_pend_n) << CAN_MO_MOIPR_MPN_Pos) |
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

    uint32_t mo_top = fifo_base_mo;

    // Добавим ведомые объекты.
    size_t i = 1;
    for(; i < fifo_len; i ++){
        uint32_t fifo_mo = can_list_alloc_mo(can, CAN_NODE_LIST_NUMBER(can_node->node_n));
        if(fifo_mo == CAN_MO_INVALID_INDEX) return CAN_MO_INVALID_INDEX;

        uint32_t pend_n = can_mo_n_to_pend_n(can, fifo_mo);

        CAN_MO_TypeDef* MO = can_get_mo(can, fifo_mo);
        // Настроим объект фифо.
        MO->MOFCR = ((0b0000) << CAN_MO_MOFCR_MMC_Pos) |
                         ((1) << CAN_MO_MOFCR_RXIE_Pos) |
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
                    /* 1 */ CAN_MO_MOCTR_SETMSGVAL_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESMSGLST_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESNEWDAT_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESRXUPD_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESTXPND_Msk |
                    /* 0 */ CAN_MO_MOCTR_RESRXPND_Msk;
        MO->MOIPR = ((0) << CAN_MO_MOIPR_RXINP_Pos) |
                    ((0) << CAN_MO_MOIPR_TXINP_Pos) |
                    ((pend_n) << CAN_MO_MOIPR_MPN_Pos) |
                    ((0) << CAN_MO_MOIPR_CFCVAL_Pos);
        MO->MOFGPR = ((0)) << CAN_MO_MOFGPR_BOT_Pos |
                     ((0)) << CAN_MO_MOFGPR_TOP_Pos |
                     ((fifo_base_mo)) << CAN_MO_MOFGPR_CUR_Pos |
                     ((0)) << CAN_MO_MOFGPR_SEL_Pos;
        MO->MOAMR = ((0) << CAN_MO_MOAMR_MIDE_Pos) | //1
                         ((0) << CAN_MO_MOAMR_AM_Pos); //mask << 18
        MO->MOAR = ((0) << CAN_MO_MOAR_IDE_Pos) |
                        ((0) << CAN_MO_MOAR_ID_Pos) | //ident << 18
                        ((CAN_RX_FIFO_PRI) << CAN_MO_MOAR_PRI_Pos); // 0b01 by list order, 0b10 - by priority
        MO->MODATAL = ((0) << CAN_MO_MODATAL_DB0_Pos) |
                      ((0) << CAN_MO_MODATAL_DB1_Pos) |
                      ((0) << CAN_MO_MODATAL_DB2_Pos) |
                      ((0) << CAN_MO_MODATAL_DB3_Pos);
        MO->MODATAH = ((0) << CAN_MO_MODATAH_DB4_Pos) |
                      ((0) << CAN_MO_MODATAH_DB5_Pos) |
                      ((0) << CAN_MO_MODATAH_DB6_Pos) |
                      ((0) << CAN_MO_MODATAH_DB7_Pos);

        if(i == (fifo_len - 1)){
            mo_top = fifo_mo;
        }
    }

    MO_Base->MOFGPR = ((fifo_base_mo)) << CAN_MO_MOFGPR_BOT_Pos |
                      ((mo_top      )) << CAN_MO_MOFGPR_TOP_Pos |
                      ((fifo_base_mo)) << CAN_MO_MOFGPR_CUR_Pos |
                      ((fifo_base_mo)) << CAN_MO_MOFGPR_SEL_Pos;

    return fifo_base_mo;
}


can_mo_index_t can_node_init_tx_buffer(can_node_t* can_node, size_t fifo_len, uint16_t ident, bool rtr, uint8_t noOfBytes)
{
    assert(can_node != NULL);

    can_t* can = can_node->can;

    while(can->can_device->PANCTR & CAN_PANCTR_BUSY_Msk){ __NOP(); }

    bool list_empty = (can->can_device->LIST[0] & CAN_LIST_EMPTY_Msk) >> CAN_LIST_EMPTY_Pos;
    if(list_empty) return CAN_MO_INVALID_INDEX;

    uint32_t free_mo_count = ((can->can_device->LIST[0] & CAN_LIST_SIZE_Msk) >> CAN_LIST_SIZE_Pos) + 1;
    if(free_mo_count < (fifo_len)) return CAN_MO_INVALID_INDEX;

    uint32_t fifo_base_mo = can_list_alloc_mo(can, CAN_NODE_LIST_NUMBER(can_node->node_n));
    if(fifo_base_mo == CAN_MO_INVALID_INDEX) return CAN_MO_INVALID_INDEX;

    uint32_t dir = (rtr ? (CAN_MO_MOCTR_RESDIR_Msk) : (CAN_MO_MOCTR_SETDIR_Msk));

    uint32_t base_pend_n = can_mo_n_to_pend_n(can, fifo_base_mo);

    CAN_MO_TypeDef* MO_Base = can_get_mo(can, fifo_base_mo);
    // Настроим базовый объект фифо.
    MO_Base->MOFCR = ((0b0010) << CAN_MO_MOFCR_MMC_Pos) |
                     ((0) << CAN_MO_MOFCR_RXIE_Pos) |
                     ((1) << CAN_MO_MOFCR_TXIE_Pos) |
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
                     ((base_pend_n) << CAN_MO_MOIPR_MPN_Pos) |
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

    uint32_t mo_top = fifo_base_mo;

    // Добавим ведомые объекты.
    size_t i = 1;
    for(; i < fifo_len; i ++){
        uint32_t fifo_mo = can_list_alloc_mo(can, CAN_NODE_LIST_NUMBER(can_node->node_n));
        if(fifo_mo == CAN_MO_INVALID_INDEX) return CAN_MO_INVALID_INDEX;

        uint32_t pend_n = can_mo_n_to_pend_n(can, fifo_mo);

        CAN_MO_TypeDef* MO = can_get_mo(can, fifo_mo);
        // Настроим объект фифо.
        MO->MOFCR = ((0b0011) << CAN_MO_MOFCR_MMC_Pos) |
                         ((0) << CAN_MO_MOFCR_RXIE_Pos) |
                         ((1) << CAN_MO_MOFCR_TXIE_Pos) |
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
                    ((pend_n) << CAN_MO_MOIPR_MPN_Pos) |
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

        if(i == (fifo_len - 1)){
            mo_top = fifo_mo;
        }
    }

    MO_Base->MOFGPR = ((fifo_base_mo)) << CAN_MO_MOFGPR_BOT_Pos |
                      ((mo_top      )) << CAN_MO_MOFGPR_TOP_Pos |
                      ((fifo_base_mo)) << CAN_MO_MOFGPR_CUR_Pos |
                      ((fifo_base_mo)) << CAN_MO_MOFGPR_SEL_Pos;

    return fifo_base_mo;
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

static err_t can_mo_send_msg(CAN_MO_TypeDef* MO_Base, CAN_MO_TypeDef* MO, const can_msg_t* msg)
{
    //if(MO->MOSTAT & CAN_MO_MOSTAT_TXRQ_Msk) return E_BUSY;
    //if(MO->MOSTAT & CAN_MO_MOSTAT_RTSEL_Msk) return E_BUSY;

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

    MO->MOCTR = CAN_MO_MOCTR_SETNEWDAT_Msk |
                CAN_MO_MOCTR_SETTXRQ_Msk |
                CAN_MO_MOCTR_SETTXEN0_Msk |
                //CAN_MO_MOCTR_SETTXEN1_Msk |
                CAN_MO_MOCTR_RESRTSEL_Msk |
                CAN_MO_MOCTR_SETMSGVAL_Msk;

    return E_NO_ERROR;
}

err_t can_node_send_msg(can_node_t* can_node, can_mo_index_t mo_index, const can_msg_t* msg)
{
    assert(can_node != NULL);

    can_t* can = can_node->can;

    uint32_t mo_base_n = mo_index;
    CAN_MO_TypeDef* MO_Base = can_get_mo(can, mo_base_n);

    can_node_t* mo_node = can_get_mo_node(can, MO_Base);
    if(/*mo_node == NULL ||*/ mo_node != can_node) return E_INVALID_VALUE;

    //uint32_t mo_bot = can_mo_fifo_top(MO_Base);
    //uint32_t mo_top = can_mo_fifo_top(MO_Base);
    uint32_t mo_cur = can_mo_fifo_cur(MO_Base);

    err_t err = E_AGAIN;

    uint32_t mo_n = mo_cur;
    CAN_MO_TypeDef* MO;
    //size_t i;
    //for(i = 0; i < CAN_FIFO_SIZE; i ++){
    do{
//        if(i == 0){
//            mo_n = can_fifo_first(can, mo_base_n);
//        }else{
//            mo_n = can_fifo_next(can, mo_base_n, mo_n);
//        }

        MO = can_get_mo(can, mo_n);

        if((MO->MOSTAT & CAN_MO_MOSTAT_TXRQ_Msk) == 0){
            err = can_mo_send_msg(MO_Base, MO, msg);
            if(err == E_NO_ERROR) break;
        }

        mo_n = can_fifo_next(can, mo_base_n, mo_n);

    } while(mo_n != mo_cur);

    if(err == E_NO_ERROR){
        //if((MO_Base->MOSTAT & CAN_MO_MOSTAT_TXRQ_Msk) == 0){
            uint32_t mo_cur_n = can_fifo_first(can, mo_base_n);
            CAN_MO_TypeDef* MO_Cur = can_get_mo(can, mo_cur_n);
            MO_Cur->MOCTR = CAN_MO_MOCTR_SETTXEN1_Msk;
            //MO->MOCTR = CAN_MO_MOCTR_SETTXEN1_Msk;
            //MO_Base->MOCTR = CAN_MO_MOCTR_SETTXRQ_Msk;
        //}
    }

    return err;
}

static err_t can_mo_recv_msg(CAN_MO_TypeDef* MO, can_msg_t* msg)
{
    //if(MO->MOSTAT & CAN_MO_MOSTAT_RTSEL_Msk) return E_BUSY;

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

        msg->dlc = (MO->MOFCR & CAN_MO_MOFCR_DLC_Msk) >> CAN_MO_MOFCR_DLC_Pos;

        if(!msg->rtr){
            msg->data[0] = (MO->MODATAL & CAN_MO_MODATAL_DB0_Msk) >> CAN_MO_MODATAL_DB0_Pos;
            msg->data[1] = (MO->MODATAL & CAN_MO_MODATAL_DB1_Msk) >> CAN_MO_MODATAL_DB1_Pos;
            msg->data[2] = (MO->MODATAL & CAN_MO_MODATAL_DB2_Msk) >> CAN_MO_MODATAL_DB2_Pos;
            msg->data[3] = (MO->MODATAL & CAN_MO_MODATAL_DB3_Msk) >> CAN_MO_MODATAL_DB3_Pos;
            msg->data[4] = (MO->MODATAH & CAN_MO_MODATAH_DB4_Msk) >> CAN_MO_MODATAH_DB4_Pos;
            msg->data[5] = (MO->MODATAH & CAN_MO_MODATAH_DB5_Msk) >> CAN_MO_MODATAH_DB5_Pos;
            msg->data[6] = (MO->MODATAH & CAN_MO_MODATAH_DB6_Msk) >> CAN_MO_MODATAH_DB6_Pos;
            msg->data[7] = (MO->MODATAH & CAN_MO_MODATAH_DB7_Msk) >> CAN_MO_MODATAH_DB7_Pos;
        }

    }while(MO->MOSTAT & (CAN_MO_MOSTAT_NEWDAT_Msk | CAN_MO_MOSTAT_RXUPD_Msk));

    //MO->MOCTR = CAN_MO_MOCTR_SETMSGVAL_Msk;

    return E_NO_ERROR;
}

err_t can_node_recv_msg(can_node_t* can_node, can_mo_index_t mo_index, can_msg_t* msg)
{
    assert(can_node != NULL);

    can_t* can = can_node->can;

    err_t err = E_AGAIN;

    uint32_t mo_base_n = mo_index;
    CAN_MO_TypeDef* MO_Base = can_get_mo(can, mo_base_n);

    can_node_t* mo_node = can_get_mo_node(can, MO_Base);
    if(/*mo_node == NULL ||*/ mo_node != can_node) return E_INVALID_VALUE;

    //uint32_t mo_bot = can_mo_fifo_top(MO_Base);
    //uint32_t mo_top = can_mo_fifo_top(MO_Base);
    uint32_t mo_cur = can_mo_fifo_cur(MO_Base);

    uint32_t mo_n = mo_cur;
    CAN_MO_TypeDef* MO;
    //size_t i;
    //for(i = 0; i < CAN_FIFO_SIZE; i ++){
    do{
//        if(i == 0){
//            mo_n = can_fifo_first(can, mo_base_n);
//        }else{
//            mo_n = can_fifo_next(can, mo_base_n, mo_n);
//        }

        MO = can_get_mo(can, mo_n);

        if((MO->MOSTAT & CAN_MO_MOSTAT_NEWDAT_Msk) != 0){
            err = can_mo_recv_msg(MO, msg);
            if(err == E_NO_ERROR) return err;
        }

        mo_n = can_fifo_next(can, mo_base_n, mo_n);

    } while(mo_n != mo_cur);

    return err;
}

#endif
