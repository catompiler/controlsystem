#include "port.h"

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef DMA_DMA_XMC4XXX_H_
#define DMA_DMA_XMC4XXX_H_

#include "cpu.h"
#include "defs/defs.h"
#include "bits/bits.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


//! Число каналов DMA1.
#define DMA1_CHANNELS_COUNT 8

//! Число каналов DMA2.
#define DMA2_CHANNELS_COUNT 4

//! Число каналов DMA.
#define DMA_CHANNELS_COUNT ((DMA1_CHANNELS_COUNT)+(DMA2_CHANNELS_COUNT))


//! Тип коллбэка DMA.
typedef void (*dma_callback_t)(void* user_data);


//! Тип канала ПДП.
typedef void dma_channel_t;

//! Макрос приведения типа канала ПДП.
#define DMA_CHANNEL(CH) ((GPDMA0_CH_TypeDef*)(CH))


//! Тип ПДП.
typedef void dma_t;

//! Макрос приведения типа ПДП.
#define DMA(D) ((GPDMA0_GLOBAL_TypeDef*)(D))

//! Тип источника запроса.
typedef size_t dma_req_line_source_t;


//! Ращрешение прерываний канала.
typedef enum _E_Dma_Int_State {
    DMA_INT_DISABLE = 0,
    DMA_INT_ENABLE = 1
} dma_int_state_t;


//! Тип ширины одного элемента передачи.
typedef enum _E_Dma_Transfer_Width {
    DMA_TRANSFER_WIDTH_8_BIT = 0b000,
    DMA_TRANSFER_WIDTH_16_BIT = 0b001,
    DMA_TRANSFER_WIDTH_32_BIT = 0b010,
} dma_transfer_width_t;


//! Тип инкремента адреса.
typedef enum _E_Dma_Addr_Inc {
    DMA_ADDR_INC = 0b00,
    DMA_ADDR_DEC = 0b01,
    DMA_ADDR_NO_CHANGE = 0b10
} dma_addr_inc_t;

//! Длина burst-передачи.
typedef enum _E_Dma_Burst_trans_Len {
    DMA_BURST_TRANS_LEN_1 = 0b000,
    DMA_BURST_TRANS_LEN_4 = 0b001,
    DMA_BURST_TRANS_LEN_8 = 0b010,
} dma_burst_trans_len_t;

//! Тип передачи DMA.
typedef enum _E_Dma_Transfer_Type {
    DMA_TRANSFER_MEM_TO_MEM_FC_DMA = 0b000,
    DMA_TRANSFER_MEM_TO_PER_FC_DMA = 0b001,
    DMA_TRANSFER_PER_TO_MEM_FC_DMA = 0b010,
    DMA_TRANSFER_PER_TO_PER_FC_DMA = 0b011,
    DMA_TRANSFER_PER_TO_MEM_FC_PER = 0b100,
    DMA_TRANSFER_PER_TO_PER_FC_SRC_PER = 0b101,
    DMA_TRANSFER_MEM_TO_PER_FC_PER = 0b110,
    DMA_TRANSFER_PER_TO_PER_FC_DST_PER = 0b111,
} dma_transfer_type_t;

//! Режим управления потоком.
typedef enum _E_Dma_Flow_Control_Mode {
    DMA_FLOW_CONTROL_PREFETCH_ENABLED = 0,
    DMA_FLOW_CONTROL_PREFETCH_DISABLED = 1
} dma_flow_control_mode_t;

//! Режим FIFO.
typedef enum _E_Dma_Fifo_Mode {
    DMA_FIFO_SINGLE_DATA_FOR_BURST = 0,
    DMA_FIFO_HALF_DEPTH_FOR_BURST = 1
} dma_fifo_mode_t;


// //! Тип автоперезагрузки адреса.
//typedef enum _E_Dma_Auto_Relod {
//    DMA_NO_AUTO_RELOAD = 0,
//    DMA_AUTO_RELOAD = 1
//} dma_auto_reload_t;


//! Тип приоритета канала.
typedef uint32_t dma_channel_priority_t;


//! Тип рукопожатия.
typedef enum _E_Dma_Hs_Type {
    DMA_HS_HARDWARE = 0,
    DMA_HS_SOFTWARE = 1
} dma_hs_type_t;

//! Полярность сигнала рукопожатия.
typedef enum _E_Dma_Hs_Polarity {
    DMA_HS_ACTIVE_HIGH = 0,
    DMA_HS_ACTIVE_LOW = 1
} dma_hs_polarity_t;


//! Безлимит burst передачи.
#define DMA_BURST_LEN_NO_LIMIT 0

//! Приоритет по-умолчанию.
#define DMA_PRIOR_DEFAULT 0


/*
 *
 * Handlers data & callbacks.
 *
 */

EXTERN void dma_set_int_callback(size_t ch_n, dma_callback_t callback, void* user_data);


/*
 *
 * Lock/Unlock channels.
 *
 */

//! Try lock channel stub.
ALWAYS_INLINE static bool dma_channel_trylock(size_t ch_n)
{
    (void) ch_n;
    return true;
}

//! Lock channel stub.
ALWAYS_INLINE static bool dma_channel_lock(size_t ch_n)
{
    (void) ch_n;
    return true;
}

//! Unlock channel stub.
ALWAYS_INLINE static void dma_channel_unlock(size_t ch_n)
{
    (void) ch_n;
}


/*
 *
 * DLR
 *
 */

//! Получает статус overrun.
ALWAYS_INLINE static bool dma_request_line_overrun_status(size_t rl_n)
{
    if(rl_n < DMA_CHANNELS_COUNT)
        return BIT_TEST(DLR->OVRSTAT, rl_n);
    return false;
}

//! Очищает статус overrun.
ALWAYS_INLINE static void dma_request_line_overrun_clear(size_t rl_n)
{
    if(rl_n < DMA_CHANNELS_COUNT) DLR->OVRCLR = BIT(rl_n);
}

//! Получает разрешённость линии запроса ПДП.
ALWAYS_INLINE static bool dma_request_line_enabled(size_t rl_n)
{
    if(rl_n < DMA_CHANNELS_COUNT)
        return BIT_TEST(DLR->LNEN, rl_n);
    return false;
}

//! Разрешает линию запроса ПДП.
ALWAYS_INLINE static void dma_request_line_enable(size_t rl_n)
{
    if(rl_n < DMA_CHANNELS_COUNT) BIT_ON(DLR->LNEN, rl_n);
}

//! Запрещает линию запроса ПДП.
ALWAYS_INLINE static void dma_request_line_disable(size_t rl_n)
{
    if(rl_n < DMA_CHANNELS_COUNT) BIT_OFF(DLR->LNEN, rl_n);
}

//! Разрешает или запрещает линию запроса ПДП.
ALWAYS_INLINE static void dma_request_line_set_enabled(size_t rl_n, bool enabled)
{
    if(enabled) dma_request_line_enable(rl_n);
    else dma_request_line_disable(rl_n);
}

//! Получает источник запроса линии ПДП.
ALWAYS_INLINE static dma_req_line_source_t dma_request_line_source(size_t rl_n)
{
    if(rl_n < DMA1_CHANNELS_COUNT){
        uint32_t shift = (DLR_SRSEL0_RS1_Pos - DLR_SRSEL0_RS0_Pos) * rl_n;
        return (DLR->SRSEL0 >> shift) & DLR_SRSEL0_RS0_Msk;
    }else if(rl_n < DMA_CHANNELS_COUNT){
        uint32_t shift = (DLR_SRSEL1_RS9_Pos - DLR_SRSEL1_RS8_Pos) * (rl_n - DMA1_CHANNELS_COUNT);
        return (DLR->SRSEL1 >> shift) & DLR_SRSEL1_RS8_Msk;
    }
    return 0;
}

//! Устанавливает источник запроса линии ПДП.
ALWAYS_INLINE static void dma_request_line_set_source(size_t rl_n, dma_req_line_source_t req_source)
{
    if(rl_n < DMA1_CHANNELS_COUNT){
        uint32_t shift = (DLR_SRSEL0_RS1_Pos - DLR_SRSEL0_RS0_Pos) * rl_n;
        DLR->SRSEL0 = (DLR->SRSEL0 & ~(DLR_SRSEL0_RS0_Msk << shift)) | ((req_source & DLR_SRSEL0_RS0_Msk) << shift);
    }
    else if(rl_n < DMA_CHANNELS_COUNT){
        uint32_t shift = (DLR_SRSEL1_RS9_Pos - DLR_SRSEL1_RS8_Pos) * (rl_n - DMA1_CHANNELS_COUNT);
        DLR->SRSEL1 = (DLR->SRSEL1 & ~(DLR_SRSEL1_RS8_Msk << shift)) | ((req_source & DLR_SRSEL1_RS8_Msk) << shift);
    }
}


/*
 *
 * GPDMA
 *
 */

/**
 * Получает канал ПДП по номеру.
 * @param ch_n Номер канала.
 * @return Адрес канала ПДП или NULL.
 */
ALWAYS_INLINE static dma_channel_t* dma_get_channel(size_t ch_n)
{
    if(ch_n < DMA1_CHANNELS_COUNT)
        return (dma_channel_t*)(GPDMA0_CH0_BASE + (GPDMA0_CH1_BASE - GPDMA0_CH0_BASE) * ch_n);
    else if(ch_n < DMA_CHANNELS_COUNT)
        return (dma_channel_t*)(GPDMA1_CH0_BASE + (GPDMA1_CH1_BASE - GPDMA1_CH0_BASE) * (ch_n - DMA1_CHANNELS_COUNT));
    return NULL;
}

//! Сбрасывает канал.
ALWAYS_INLINE static void dma_channel_deinit(dma_channel_t* ch)
{
    DMA_CHANNEL(ch)->CTLH = 0;
    DMA_CHANNEL(ch)->CTLL = 0;
    DMA_CHANNEL(ch)->CFGH = 0;
    DMA_CHANNEL(ch)->CFGL = 0;
    DMA_CHANNEL(ch)->DAR = 0;
    DMA_CHANNEL(ch)->SAR = 0;
}


/*
 * SAR
 */

//! Получает адрес источника.
ALWAYS_INLINE static void* dma_channel_source_address(dma_channel_t* ch)
{
    return (void*)DMA_CHANNEL(ch)->SAR;
}

//! Устанавливает адрес источника.
ALWAYS_INLINE static void dma_channel_set_source_address(dma_channel_t* ch, const void* addr)
{
    DMA_CHANNEL(ch)->SAR = (uint32_t)addr;
}

/*
 * DAR
 */

//! Получает адрес приёмника.
ALWAYS_INLINE static void* dma_channel_dest_address(dma_channel_t* ch)
{
    return (void*)DMA_CHANNEL(ch)->DAR;
}

//! Устанавливает адрес приёмника.
ALWAYS_INLINE static void dma_channel_set_dest_address(dma_channel_t* ch, void* addr)
{
    DMA_CHANNEL(ch)->DAR = (uint32_t)addr;
}

/*
 * CTLH
 */

//! Получает размер блока передачи.
ALWAYS_INLINE static size_t dma_channel_block_transfer_size(dma_channel_t* ch)
{
    return DMA_CHANNEL(ch)->CTLH & GPDMA0_CH_CTLH_BLOCK_TS_Msk;
}

//! Устанавливает размер блока передачи.
//! Очищает флаг завершения передачи блока.
ALWAYS_INLINE static void dma_channel_set_block_transfer_size(dma_channel_t* ch, size_t ts)
{
    //DMA_CHANNEL(ch)->CTLH = (DMA_CHANNEL(ch)->CTLH & ~GPDMA0_CH_CTLH_BLOCK_TS_Msk) | (ts & GPDMA0_CH_CTLH_BLOCK_TS_Msk);
    DMA_CHANNEL(ch)->CTLH = ts & GPDMA0_CH_CTLH_BLOCK_TS_Msk;
}

//! Получает флаг завершения передачи блока.
ALWAYS_INLINE static bool dma_channel_block_transfer_done(dma_channel_t* ch)
{
    return DMA_CHANNEL(ch)->CTLH & GPDMA0_CH_CTLH_DONE_Msk;
}

//! Сбрасывает флаг завершения передачи блока.
ALWAYS_INLINE static void dma_channel_block_transfer_done_clear(dma_channel_t* ch)
{
    DMA_CHANNEL(ch)->CTLH &= ~GPDMA0_CH_CTLH_DONE_Msk;
}

//! Устанавливает флаг завершения передачи блока.
ALWAYS_INLINE static void dma_channel_block_transfer_done_set(dma_channel_t* ch)
{
    DMA_CHANNEL(ch)->CTLH |= GPDMA0_CH_CTLH_DONE_Msk;
}

//! Устанавливает или сбрасывает флаг завершения передачи блока.
ALWAYS_INLINE static void dma_channel_set_block_transfer_done(dma_channel_t* ch, bool done)
{
    if(done) dma_channel_block_transfer_done_set(ch);
    else dma_channel_block_transfer_done_clear(ch);
}

/*
 * CTLL
 */

//! Настраивает параметры управления.
ALWAYS_INLINE static void dma_channel_control(dma_channel_t* ch, dma_int_state_t int_en,
                                              dma_transfer_width_t dst_tr_w, dma_transfer_width_t src_tr_w,
                                              dma_addr_inc_t dinc, dma_addr_inc_t sinc,
                                              dma_burst_trans_len_t dest_msize, dma_burst_trans_len_t src_msize,
                                              dma_transfer_type_t tt_fc)
{
    DMA_CHANNEL(ch)->CTLL = ((int_en) << GPDMA0_CH_CTLL_INT_EN_Pos) |
                            ((dst_tr_w) << GPDMA0_CH_CTLL_DST_TR_WIDTH_Pos) |
                            ((src_tr_w) << GPDMA0_CH_CTLL_SRC_TR_WIDTH_Pos) |
                            ((dinc) << GPDMA0_CH_CTLL_DINC_Pos) |
                            ((sinc) << GPDMA0_CH_CTLL_SINC_Pos) |
                            ((dest_msize) << GPDMA0_CH_CTLL_DEST_MSIZE_Pos) |
                            ((src_msize) << GPDMA0_CH_CTLL_SRC_MSIZE_Pos) |
                            ((tt_fc) << GPDMA0_CH_CTLL_TT_FC_Pos);
}

/*
 * CFGH
 * CFGL
 */

//! Получает флаг приостановки передачи.
ALWAYS_INLINE static bool dma_channel_suspended(dma_channel_t* ch)
{
    return DMA_CHANNEL(ch)->CFGL & GPDMA0_CH_CFGL_CH_SUSP_Msk;
}

//! Приостанавливает передачу.
ALWAYS_INLINE static void dma_channel_suspend(dma_channel_t* ch)
{
    DMA_CHANNEL(ch)->CFGL |= GPDMA0_CH_CFGL_CH_SUSP_Msk;
}

//! Возобновляет передачу.
ALWAYS_INLINE static void dma_channel_resume(dma_channel_t* ch)
{
    DMA_CHANNEL(ch)->CFGL &= ~GPDMA0_CH_CFGL_CH_SUSP_Msk;
}

//! Приостанавливает или возобновляет передачу.
ALWAYS_INLINE static void dma_channel_set_suspended(dma_channel_t* ch, bool suspended)
{
    if(suspended) dma_channel_suspend(ch);
    else dma_channel_resume(ch);
}

//! Получает флаг опустошённости FIFO.
ALWAYS_INLINE static bool dma_channel_fifo_empty(dma_channel_t* ch)
{
    return DMA_CHANNEL(ch)->CFGL & GPDMA0_CH_CFGL_FIFO_EMPTY_Msk;
}

//! Настраивает параметры канала.
ALWAYS_INLINE static void dma_channel_config(dma_channel_t* ch,
                                             // CFGH
                                             dma_flow_control_mode_t fc_mode, dma_fifo_mode_t fifo_mode,
                                             size_t dst_req_line, size_t src_req_line,
                                             // CFGL
                                             size_t ch_prior, dma_hs_type_t dst_hs, dma_hs_type_t src_hs,
                                             dma_hs_polarity_t dst_hs_pol, dma_hs_polarity_t src_hs_pol,
                                             size_t max_burst_len)
{
    DMA_CHANNEL(ch)->CFGH = ((fc_mode) << GPDMA0_CH_CFGH_FCMODE_Pos) |
                            ((fifo_mode) << GPDMA0_CH_CFGH_FIFO_MODE_Pos) |
                            ((src_req_line) << GPDMA0_CH_CFGH_SRC_PER_Pos) |
                            ((dst_req_line) << GPDMA0_CH_CFGH_DEST_PER_Pos);

    DMA_CHANNEL(ch)->CFGL = ((ch_prior) << GPDMA0_CH_CFGL_CH_PRIOR_Pos) |
                            ((dst_hs) << GPDMA0_CH_CFGL_HS_SEL_DST_Pos) |
                            ((src_hs) << GPDMA0_CH_CFGL_HS_SEL_SRC_Pos) |
                            ((dst_hs_pol) << GPDMA0_CH_CFGL_DST_HS_POL_Pos) |
                            ((src_hs_pol) << GPDMA0_CH_CFGL_SRC_HS_POL_Pos) |
                            ((max_burst_len) << GPDMA0_CH_CFGL_MAX_ABRST_Pos);
}

//err_t dma_setup_transfer_basic(size_t rl_n, dma_line_request_t req, dma_transfer_type_t type,
//                               void* src, dma_transfer_width_t src_width, dma_addr_inc_t src_inc,
//                               void* dst, dma_transfer_width_t dst_width, dma_addr_inc_t dst_inc, size_t count);


/*
 * Int flags
 */

/*
 * Clear pending.
 */

ALWAYS_INLINE static void dma_int_clear_pending_requests(size_t ch_n)
{
    uint32_t mask;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        mask = BIT(ch_n);
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        mask = BIT(ch_n - DMA1_CHANNELS_COUNT);
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->CLEARTFR = mask;
    DMA(dma)->CLEARBLOCK = mask;
    DMA(dma)->CLEARSRCTRAN = mask;
    DMA(dma)->CLEARDSTTRAN = mask;
    DMA(dma)->CLEARERR = mask;
}

/*
 * Raw
 */

//! Transfer Complete
ALWAYS_INLINE static bool dma_int_raw_status_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->RAWTFR) >> shift) & GPDMA0_RAWTFR_CH0_Msk;
}

//! Block Transfer Complete
ALWAYS_INLINE static bool dma_int_raw_status_block_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->RAWBLOCK) >> shift) & GPDMA0_RAWBLOCK_CH0_Msk;
}

//! Source Transaction Complete
ALWAYS_INLINE static bool dma_int_raw_status_src_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->RAWSRCTRAN) >> shift) & GPDMA0_RAWSRCTRAN_CH0_Msk;
}

//! Destination Transaction Complete
ALWAYS_INLINE static bool dma_int_raw_status_dst_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->RAWDSTTRAN) >> shift) & GPDMA0_RAWDSTTRAN_CH0_Msk;
}

//! Error
ALWAYS_INLINE static bool dma_int_raw_status_error(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->RAWERR) >> shift) & GPDMA0_RAWERR_CH0_Msk;
}

/*
 * Status
 */

//! Transfer Complete
ALWAYS_INLINE static bool dma_int_status_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->STATUSTFR) >> shift) & GPDMA0_STATUSTFR_CH0_Msk;
}

//! Block Transfer Complete
ALWAYS_INLINE static bool dma_int_status_block_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->STATUSBLOCK) >> shift) & GPDMA0_STATUSBLOCK_CH0_Msk;
}

//! Source Transaction Complete
ALWAYS_INLINE static bool dma_int_status_src_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->STATUSSRCTRAN) >> shift) & GPDMA0_STATUSSRCTRAN_CH0_Msk;
}

//! Destination Transaction Complete
ALWAYS_INLINE static bool dma_int_status_dst_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->STATUSDSTTRAN) >> shift) & GPDMA0_STATUSDSTTRAN_CH0_Msk;
}

//! Error
ALWAYS_INLINE static bool dma_int_status_error(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->STATUSERR) >> shift) & GPDMA0_STATUSERR_CH0_Msk;
}

/*
 * Mask - get
 */

//! Transfer Complete
ALWAYS_INLINE static bool dma_int_masked_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->MASKTFR) >> shift) & GPDMA0_MASKTFR_CH0_Msk;
}

//! Block Transfer Complete
ALWAYS_INLINE static bool dma_int_masked_block_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->MASKBLOCK) >> shift) & GPDMA0_MASKBLOCK_CH0_Msk;
}

//! Source Transaction Complete
ALWAYS_INLINE static bool dma_int_masked_src_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->MASKSRCTRAN) >> shift) & GPDMA0_MASKSRCTRAN_CH0_Msk;
}

//! Destination Transaction Complete
ALWAYS_INLINE static bool dma_int_masked_dst_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->MASKDSTTRAN) >> shift) & GPDMA0_MASKDSTTRAN_CH0_Msk;
}

//! Error
ALWAYS_INLINE static bool dma_int_masked_error(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->MASKERR) >> shift) & GPDMA0_MASKERR_CH0_Msk;
}

/*
 * Mask - set
 */

//! Transfer Complete
ALWAYS_INLINE static void dma_int_mask_set_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->MASKTFR = (GPDMA0_MASKTFR_WE_CH0_Msk | GPDMA0_MASKTFR_CH0_Msk) << shift;
}

//! Block Transfer Complete
ALWAYS_INLINE static void dma_int_mask_set_block_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->MASKBLOCK = (GPDMA0_MASKBLOCK_WE_CH0_Msk | GPDMA0_MASKBLOCK_CH0_Msk) << shift;
}

//! Source Transaction Complete
ALWAYS_INLINE static void dma_int_mask_set_src_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->MASKSRCTRAN = (GPDMA0_MASKSRCTRAN_WE_CH0_Msk | GPDMA0_MASKSRCTRAN_CH0_Msk) << shift;
}

//! Destination Transaction Complete
ALWAYS_INLINE static void dma_int_mask_set_dst_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->MASKDSTTRAN = (GPDMA0_MASKDSTTRAN_WE_CH0_Msk | GPDMA0_MASKDSTTRAN_CH0_Msk) << shift;
}

//! Error
ALWAYS_INLINE static void dma_int_mask_set_error(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->MASKERR = (GPDMA0_MASKERR_WE_CH0_Msk | GPDMA0_MASKERR_CH0_Msk) << shift;
}

/*
 * Mask - clear
 */

//! Transfer Complete
ALWAYS_INLINE static void dma_int_mask_clear_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->MASKTFR = GPDMA0_MASKTFR_WE_CH0_Msk << shift;
}

//! Block Transfer Complete
ALWAYS_INLINE static void dma_int_mask_clear_block_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->MASKBLOCK = GPDMA0_MASKBLOCK_WE_CH0_Msk << shift;
}

//! Source Transaction Complete
ALWAYS_INLINE static void dma_int_mask_clear_src_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->MASKSRCTRAN = GPDMA0_MASKSRCTRAN_WE_CH0_Msk << shift;
}

//! Destination Transaction Complete
ALWAYS_INLINE static void dma_int_mask_clear_dst_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->MASKDSTTRAN = GPDMA0_MASKDSTTRAN_WE_CH0_Msk << shift;
}

//! Error
ALWAYS_INLINE static void dma_int_mask_clear_error(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->MASKERR = GPDMA0_MASKERR_WE_CH0_Msk << shift;
}

/*
 * Mask
 */

//! Transfer Complete
ALWAYS_INLINE static void dma_int_mask_transfer_complete(size_t ch_n, bool mask)
{
    if(mask) dma_int_mask_set_transfer_complete(ch_n);
    else dma_int_mask_clear_transfer_complete(ch_n);
}

//! Block Transfer Complete
ALWAYS_INLINE static void dma_int_mask_block_transfer_complete(size_t ch_n, bool mask)
{
    if(mask) dma_int_mask_set_block_transfer_complete(ch_n);
    else dma_int_mask_clear_block_transfer_complete(ch_n);
}

//! Source Transaction Complete
ALWAYS_INLINE static void dma_int_mask_src_transaction_complete(size_t ch_n, bool mask)
{
    if(mask) dma_int_mask_set_src_transaction_complete(ch_n);
    else dma_int_mask_clear_src_transaction_complete(ch_n);
}

//! Destination Transaction Complete
ALWAYS_INLINE static void dma_int_mask_dst_transaction_complete(size_t ch_n, bool mask)
{
    if(mask) dma_int_mask_set_dst_transaction_complete(ch_n);
    else dma_int_mask_clear_dst_transaction_complete(ch_n);
}

//! Error
ALWAYS_INLINE static void dma_int_mask_error(size_t ch_n, bool mask)
{
    if(mask) dma_int_mask_set_error(ch_n);
    else dma_int_mask_clear_error(ch_n);
}

/*
 * Clear
 */

//! Transfer Complete
ALWAYS_INLINE static void dma_int_clear_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->CLEARTFR = GPDMA0_CLEARTFR_CH0_Msk << shift;
}

//! Block Transfer Complete
ALWAYS_INLINE static void dma_int_clear_block_transfer_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->CLEARBLOCK = GPDMA0_CLEARBLOCK_CH0_Msk << shift;
}

//! Source Transaction Complete
ALWAYS_INLINE static void dma_int_clear_src_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->CLEARSRCTRAN = GPDMA0_CLEARSRCTRAN_CH0_Msk << shift;
}

//! Destination Transaction Complete
ALWAYS_INLINE static void dma_int_clear_dst_transaction_complete(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->CLEARDSTTRAN = GPDMA0_CLEARDSTTRAN_CH0_Msk << shift;
}

//! Error
ALWAYS_INLINE static void dma_int_clear_error(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->CLEARERR = GPDMA0_CLEARERR_CH0_Msk << shift;
}

/*
 * Combined status
 */

//! Transfer Complete
ALWAYS_INLINE static bool dma_int_combined_status_transfer_complete(size_t ch_n)
{
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        dma = GPDMA1;
    }else{
        return false;
    }
    return DMA(dma)->STATUSINT & GPDMA0_STATUSINT_TFR_Msk;
}

//! Block Transfer Complete
ALWAYS_INLINE static bool dma_int_combined_status_block_transfer_complete(size_t ch_n)
{
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        dma = GPDMA1;
    }else{
        return false;
    }
    return DMA(dma)->STATUSINT & GPDMA0_STATUSINT_BLOCK_Msk;
}

//! Source Transaction Complete
ALWAYS_INLINE static bool dma_int_combined_status_src_transaction_complete(size_t ch_n)
{
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        dma = GPDMA1;
    }else{
        return false;
    }
    return DMA(dma)->STATUSINT & GPDMA0_STATUSINT_SRCT_Msk;
}

//! Destination Transaction Complete
ALWAYS_INLINE static bool dma_int_combined_status_dst_transaction_complete(size_t ch_n)
{
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        dma = GPDMA1;
    }else{
        return false;
    }
    return DMA(dma)->STATUSINT & GPDMA0_STATUSINT_DSTT_Msk;
}

//! Error
ALWAYS_INLINE static bool dma_int_combined_status_error(size_t ch_n)
{
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        dma = GPDMA1;
    }else{
        return false;
    }
    return DMA(dma)->STATUSINT & GPDMA0_STATUSINT_ERR_Msk;
}


/*
 *
 * Software handshaking.
 *
 */

/*
 * Requested.
 */

//! Source Software Transaction
ALWAYS_INLINE static bool dma_requested_src_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->REQSRCREG) >> shift) & GPDMA0_REQSRCREG_CH0_Msk;
}

//! Destination Software Transaction
ALWAYS_INLINE static bool dma_requested_dst_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->REQDSTREG) >> shift) & GPDMA0_REQDSTREG_CH0_Msk;
}

//! Single Source Software Transaction
ALWAYS_INLINE static bool dma_requested_single_src_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->SGLREQSRCREG) >> shift) & GPDMA0_SGLREQSRCREG_CH0_Msk;
}

//! Single Destination Software Transaction
ALWAYS_INLINE static bool dma_requested_single_dst_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->SGLREQDSTREG) >> shift) & GPDMA0_SGLREQDSTREG_CH0_Msk;
}

//! Last Source Software Transaction
ALWAYS_INLINE static bool dma_requested_last_src_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->LSTSRCREG) >> shift) & GPDMA0_LSTSRCREG_CH0_Msk;
}

//! Last Destination Software Transaction
ALWAYS_INLINE static bool dma_requested_last_dst_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->LSTDSTREG) >> shift) & GPDMA0_LSTDSTREG_CH0_Msk;
}

/*
 * Request - set.
 */

//! Source Software Transaction
ALWAYS_INLINE static void dma_set_request_src_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->REQSRCREG = (GPDMA0_REQSRCREG_WE_CH0_Msk | GPDMA0_REQSRCREG_CH0_Msk) << shift;
}

//! Destination Software Transaction
ALWAYS_INLINE static void dma_set_request_dst_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->REQDSTREG = (GPDMA0_REQDSTREG_WE_CH0_Msk | GPDMA0_REQDSTREG_CH0_Msk) << shift;
}

//! Single Source Software Transaction
ALWAYS_INLINE static void dma_set_request_single_src_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->SGLREQSRCREG = (GPDMA0_SGLREQSRCREG_WE_CH0_Msk | GPDMA0_SGLREQSRCREG_CH0_Msk) << shift;
}

//! Single Destination Software Transaction
ALWAYS_INLINE static void dma_set_request_single_dst_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->SGLREQDSTREG = (GPDMA0_SGLREQDSTREG_WE_CH0_Msk | GPDMA0_SGLREQDSTREG_CH0_Msk) << shift;
}

//! Last Source Software Transaction
ALWAYS_INLINE static void dma_set_request_last_src_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->LSTSRCREG = (GPDMA0_LSTSRCREG_WE_CH0_Msk | GPDMA0_LSTSRCREG_CH0_Msk) << shift;
}

//! Last Destination Software Transaction
ALWAYS_INLINE static void dma_set_request_last_dst_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->LSTDSTREG = (GPDMA0_LSTDSTREG_WE_CH0_Msk | GPDMA0_LSTDSTREG_CH0_Msk) << shift;
}

/*
 * Request - clear.
 */

//! Source Software Transaction
ALWAYS_INLINE static void dma_clear_request_src_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->REQSRCREG = GPDMA0_REQSRCREG_WE_CH0_Msk << shift;
}

//! Destination Software Transaction
ALWAYS_INLINE static void dma_clear_request_dst_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->REQDSTREG = GPDMA0_REQDSTREG_WE_CH0_Msk << shift;
}

//! Single Source Software Transaction
ALWAYS_INLINE static void dma_clear_request_single_src_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->SGLREQSRCREG = GPDMA0_SGLREQSRCREG_WE_CH0_Msk << shift;
}

//! Single Destination Software Transaction
ALWAYS_INLINE static void dma_clear_request_single_dst_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->SGLREQDSTREG = GPDMA0_SGLREQDSTREG_WE_CH0_Msk << shift;
}

//! Last Source Software Transaction
ALWAYS_INLINE static void dma_clear_request_last_src_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->LSTSRCREG = GPDMA0_LSTSRCREG_WE_CH0_Msk << shift;
}

//! Last Destination Software Transaction
ALWAYS_INLINE static void dma_clear_request_last_dst_sw_transaction(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->LSTDSTREG = GPDMA0_LSTDSTREG_WE_CH0_Msk << shift;
}

/*
 * Request - set/reset.
 */

//! Source Software Transaction
ALWAYS_INLINE static void dma_request_src_sw_transaction(size_t ch_n, bool req)
{
    if(req) dma_set_request_src_sw_transaction(ch_n);
    else dma_clear_request_src_sw_transaction(ch_n);
}

//! Destination Software Transaction
ALWAYS_INLINE static void dma_request_dst_sw_transaction(size_t ch_n, bool req)
{
    if(req) dma_set_request_dst_sw_transaction(ch_n);
    else dma_clear_request_dst_sw_transaction(ch_n);
}

//! Single Source Software Transaction
ALWAYS_INLINE static void dma_request_single_src_sw_transaction(size_t ch_n, bool req)
{
    if(req) dma_set_request_single_src_sw_transaction(ch_n);
    else dma_clear_request_single_src_sw_transaction(ch_n);
}

//! Single Destination Software Transaction
ALWAYS_INLINE static void dma_request_single_dst_sw_transaction(size_t ch_n, bool req)
{
    if(req) dma_set_request_single_dst_sw_transaction(ch_n);
    else dma_clear_request_single_dst_sw_transaction(ch_n);
}

//! Last Source Software Transaction
ALWAYS_INLINE static void dma_request_last_src_sw_transaction(size_t ch_n, bool req)
{
    if(req) dma_set_request_last_src_sw_transaction(ch_n);
    else dma_clear_request_last_src_sw_transaction(ch_n);
}

//! Last Destination Software Transaction
ALWAYS_INLINE static void dma_request_last_dst_sw_transaction(size_t ch_n, bool req)
{
    if(req) dma_set_request_last_dst_sw_transaction(ch_n);
    else dma_clear_request_last_dst_sw_transaction(ch_n);
}



/*
 *
 * DMA & DMA ch en/dis.
 *
 */

/*
 * DMA en/dis
 */

//! Enabled
ALWAYS_INLINE static bool dma_enabled(dma_t* dma)
{
    return DMA(dma)->DMACFGREG & GPDMA0_DMACFGREG_DMA_EN_Msk;
}

//! Enable
ALWAYS_INLINE static void dma_enable(dma_t* dma)
{
    DMA(dma)->DMACFGREG |= GPDMA0_DMACFGREG_DMA_EN_Msk;
}

//! Disable
ALWAYS_INLINE static void dma_disable(dma_t* dma)
{
    DMA(dma)->DMACFGREG &= ~GPDMA0_DMACFGREG_DMA_EN_Msk;
}

//! Set enabled
ALWAYS_INLINE static void dma_set_enabled(dma_t* dma, bool enabled)
{
    if(enabled) dma_enable(dma);
    else dma_disable(dma);
}


/*
 * Channel en/dis
 */

//! Enabled
ALWAYS_INLINE static bool dma_channel_enabled(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return false;
    }
    return ((DMA(dma)->CHENREG) >> shift) & BIT(GPDMA0_CHENREG_CH_Pos);
}

//! Enable
ALWAYS_INLINE static void dma_channel_enable(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->CHENREG = (BIT(GPDMA0_CHENREG_WE_CH_Pos) | BIT(GPDMA0_CHENREG_CH_Pos)) << shift;
}

//! Disable
ALWAYS_INLINE static void dma_channel_disable(size_t ch_n)
{
    uint32_t shift;
    dma_t* dma;

    if(ch_n < DMA1_CHANNELS_COUNT){
        shift = ch_n;
        dma = GPDMA0;
    }else if(ch_n < DMA_CHANNELS_COUNT){
        shift = ch_n - DMA1_CHANNELS_COUNT;
        dma = GPDMA1;
    }else{
        return;
    }
    DMA(dma)->CHENREG = BIT(GPDMA0_CHENREG_WE_CH_Pos) << shift;
}

//! Set enabled
ALWAYS_INLINE static void dma_channel_set_enabled(size_t ch_n, bool enabled)
{
    if(enabled) dma_channel_enable(ch_n);
    else dma_channel_disable(ch_n);
}


#endif /* DMA_DMA_XMC4XXX_H_ */

#endif
