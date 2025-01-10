#include "spi.h"
#include <stddef.h>
#include "utils/utils.h"
#include "defs/defs.h"


//#define SPI_BUS_DEBUG
#ifdef SPI_BUS_DEBUG
#include <stdio.h>
#endif

// Значение по-умолчанию для мусорных данных.
#define SPI_DUMMY_DATA_DEF_VAL 0xffff

static uint16_t spi_rx_default_data = 0;


#define SPI_STATE_IDLE             0
#define SPI_STATE_READING          1
#define SPI_STATE_WRITING          2
#define SPI_STATE_READING_WRITING  3



ALWAYS_INLINE static bool spi_bus_is_duplex(spi_bus_t* spi)
{
    return true;
}

ALWAYS_INLINE static bool spi_bus_can_rx(spi_bus_t* spi)
{
    return true;
}

ALWAYS_INLINE static bool spi_bus_can_tx(spi_bus_t* spi)
{
    return true;
}

ALWAYS_INLINE static bool spi_bus_is_crc_enabled(spi_bus_t* spi)
{
    (void) spi;

    return false;
}

ALWAYS_INLINE static bool spi_bus_is_frame_16bit(spi_bus_t* spi)
{
    return ((spi->spi_device->SCTR & USIC_CH_SCTR_FLE_Msk) >> USIC_CH_SCTR_FLE_Pos) == 15;
}

ALWAYS_INLINE static bool spi_bus_is_frame_lsbfirst(spi_bus_t* spi)
{
    return (spi->spi_device->SCTR & USIC_CH_SCTR_SDIR_Msk) == 0;
}

ALWAYS_INLINE static void spi_bus_clear_tx_events(spi_bus_t* spi)
{
    spi->spi_device->PSCR = USIC_CH_PSCR_CTSIF_Msk | USIC_CH_PSCR_CTBIF_Msk;
}

ALWAYS_INLINE static void spi_bus_clear_rx_events(spi_bus_t* spi)
{
    spi->spi_device->PSCR = USIC_CH_PSCR_CRSIF_Msk | USIC_CH_PSCR_CRIF_Msk | USIC_CH_PSCR_CAIF_Msk;
}

ALWAYS_INLINE static void spi_bus_clear_rxtx_events(spi_bus_t* spi)
{
    spi_bus_clear_tx_events(spi);
    spi_bus_clear_rx_events(spi);
}

ALWAYS_INLINE static void spi_bus_wait_can_tx(spi_bus_t* spi)
{
    WAIT_WHILE_TRUE((spi->spi_device->PSR & USIC_CH_PSR_SSCMode_TBIF_Msk) == 0);
}

ALWAYS_INLINE static void spi_bus_wait_can_rx(spi_bus_t* spi)
{
    WAIT_WHILE_TRUE((spi->spi_device->PSR & (USIC_CH_PSR_SSCMode_RIF_Msk | USIC_CH_PSR_SSCMode_AIF_Msk)) == 0);
}


ALWAYS_INLINE static bool spi_bus_tx_it_enabled(spi_bus_t* spi)
{
    return (spi->spi_device->CCR & USIC_CH_CCR_TBIEN_Msk) != 0;
}

ALWAYS_INLINE static void spi_bus_tx_it_enable(spi_bus_t* spi)
{
    spi->spi_device->CCR |= USIC_CH_CCR_TBIEN_Msk;
}

ALWAYS_INLINE static void spi_bus_tx_it_disable(spi_bus_t* spi)
{
    spi->spi_device->CCR &= ~USIC_CH_CCR_TBIEN_Msk;
}

ALWAYS_INLINE static void spi_bus_tx_it_set_enabled(spi_bus_t* spi, bool enabled)
{
    if(enabled) spi_bus_tx_it_enable(spi);
    else spi_bus_tx_it_disable(spi);
}

ALWAYS_INLINE static bool spi_bus_rx_it_enabled(spi_bus_t* spi)
{
    return (spi->spi_device->CCR & (USIC_CH_CCR_RIEN_Msk | USIC_CH_CCR_AIEN_Msk)) != 0;
}

ALWAYS_INLINE static void spi_bus_rx_it_enable(spi_bus_t* spi)
{
    spi->spi_device->CCR |= (USIC_CH_CCR_RIEN_Msk | USIC_CH_CCR_AIEN_Msk);
}

ALWAYS_INLINE static void spi_bus_rx_it_disable(spi_bus_t* spi)
{
    spi->spi_device->CCR &= ~(USIC_CH_CCR_RIEN_Msk | USIC_CH_CCR_AIEN_Msk);
}

ALWAYS_INLINE static void spi_bus_rx_it_set_enabled(spi_bus_t* spi, bool enabled)
{
    if(enabled) spi_bus_rx_it_enable(spi);
    else spi_bus_rx_it_disable(spi);
}


ALWAYS_INLINE static bool spi_bus_er_it_enabled(spi_bus_t* spi)
{
    return ((spi->spi_device->CCR & USIC_CH_CCR_DLIEN_Msk) != 0) || ((spi->spi_device->PCR_SSCMode & USIC_CH_PCR_SSCMode_DX2TIEN_Msk) != 0);
}

ALWAYS_INLINE static void spi_bus_er_it_enable(spi_bus_t* spi)
{
    spi->spi_device->CCR |= USIC_CH_CCR_DLIEN_Msk;
    spi->spi_device->PCR_SSCMode |= USIC_CH_PCR_SSCMode_DX2TIEN_Msk;
}

ALWAYS_INLINE static void spi_bus_er_it_disable(spi_bus_t* spi)
{
    spi->spi_device->CCR &= ~USIC_CH_CCR_DLIEN_Msk;
    spi->spi_device->PCR_SSCMode &= ~USIC_CH_PCR_SSCMode_DX2TIEN_Msk;
}

ALWAYS_INLINE static void spi_bus_er_it_set_enabled(spi_bus_t* spi, bool enabled)
{
    if(enabled) spi_bus_er_it_enable(spi);
    else spi_bus_er_it_disable(spi);
}


err_t spi_bus_init(spi_bus_t* spi, spi_bus_init_t* init)
{
    if(init == NULL) return E_NULL_POINTER;
    
    spi->spi_device = init->spi_device;
    spi->dma_rx_channel = init->dma_rx_channel;
    spi->dma_tx_channel = init->dma_tx_channel;
    spi->messages = NULL;
    spi->messages_count = 0;
    spi->message_index = 0;
    spi->status = SPI_STATUS_IDLE;
    spi->errors = SPI_NO_ERROR;
    spi->transfer_id = SPI_BUS_DEFAULT_TRANSFER_ID;
    spi->callback = NULL;
    
    spi->state = SPI_STATE_IDLE;
    spi->dma_rx_locked = false;
    spi->dma_tx_locked = false;
    
    spi->tx_default = SPI_DUMMY_DATA_DEF_VAL;

    spi_bus_er_it_enable(spi);
    
    return E_NO_ERROR;
}

static void spi_bus_dma_rxtx_config(spi_bus_t* spi, void* rx_address, const void* tx_address, size_t size)
{
    uint32_t ccr = DMA_CCR1_PL_0 | DMA_CCR1_TEIE | DMA_CCR1_TCIE;
    
    if(spi_bus_is_frame_16bit(spi)){
        ccr |= DMA_CCR1_MSIZE_0 | DMA_CCR1_PSIZE_0;
        size >>= 1;
    }

    // RX.
    if(spi->dma_rx_locked){
        
        spi->dma_rx_channel->CCR = 0;
        
        spi->dma_rx_channel->CNDTR = size;
        
        spi->dma_rx_channel->CPAR = (uint32_t)&spi->spi_device->DR;
        
        if(rx_address){
            spi->dma_rx_channel->CMAR = (uint32_t)rx_address;
            spi->dma_rx_channel->CCR = ccr | DMA_CCR1_MINC;
        }else{
            spi->dma_rx_channel->CMAR = (uint32_t)&spi_rx_default_data;
            spi->dma_rx_channel->CCR = ccr;
        }
    }
    
    // TX.
    if(spi->dma_tx_locked){
        
        spi->dma_tx_channel->CCR = 0;
        
        spi->dma_tx_channel->CNDTR = size;
        
        spi->dma_tx_channel->CPAR = (uint32_t)&spi->spi_device->DR;
        
        if(tx_address){
            spi->dma_tx_channel->CMAR = (uint32_t)tx_address;
            spi->dma_tx_channel->CCR = ccr | DMA_CCR1_DIR | DMA_CCR1_MINC;
        }else{
            spi->dma_tx_channel->CMAR = (uint32_t)&spi->tx_default;
            spi->dma_tx_channel->CCR = ccr | DMA_CCR1_DIR;
        }
    }
}

ALWAYS_INLINE static void spi_bus_dma_start(spi_bus_t* spi)
{
    if(spi->dma_rx_locked){
        spi->spi_device->CR2 |= SPI_CR2_RXDMAEN;
        spi->dma_rx_channel->CCR |= DMA_CCR1_EN;
    }
    if(spi->dma_tx_locked){
        spi->spi_device->CR2 |= SPI_CR2_TXDMAEN;
        spi->dma_tx_channel->CCR |= DMA_CCR1_EN;
    }
}


ALWAYS_INLINE static void spi_bus_dma_stop_rx(spi_bus_t* spi)
{
    if(spi->dma_rx_locked){
        spi->dma_rx_channel->CCR &= ~DMA_CCR1_EN;
        spi->spi_device->CR2 &= ~SPI_CR2_RXDMAEN;
    }
}

ALWAYS_INLINE static void spi_bus_dma_stop_tx(spi_bus_t* spi)
{
    if(spi->dma_tx_locked){
        spi->dma_tx_channel->CCR &= ~DMA_CCR1_EN;
        spi->spi_device->CR2 &= ~SPI_CR2_TXDMAEN;
    }
}

ALWAYS_INLINE static void spi_bus_dma_stop(spi_bus_t* spi)
{
    spi_bus_dma_stop_rx(spi);
    spi_bus_dma_stop_tx(spi);
}

static bool spi_bus_dma_lock_channels(spi_bus_t* spi, bool lock_rx, bool lock_tx)
{
    if(lock_rx){
        spi->dma_rx_locked = dma_channel_trylock(spi->dma_rx_channel);
        if(!spi->dma_rx_locked) return false;
    }
    if(lock_tx){
        spi->dma_tx_locked = dma_channel_trylock(spi->dma_tx_channel);
        if(!spi->dma_tx_locked){
            if(spi->dma_rx_locked){
                dma_channel_unlock(spi->dma_rx_channel);
                spi->dma_rx_locked = false;
            }
            return false;
        }
    }
    return true;
}

static void spi_bus_dma_unlock_channels(spi_bus_t* spi)
{
    if(spi->dma_rx_locked){
        dma_channel_deinit(spi->dma_rx_channel);
        dma_channel_unlock(spi->dma_rx_channel);
        spi->dma_rx_locked = false;
    }
    if(spi->dma_tx_locked){
        dma_channel_deinit(spi->dma_tx_channel);
        dma_channel_unlock(spi->dma_tx_channel);
        spi->dma_tx_locked = false;
    }
}

static void spi_bus_setup_message(spi_bus_t* spi)
{
    spi_message_t* msg = &spi->messages[spi->message_index];
    switch(msg->direction){
        case SPI_WRITE:
            spi->state = SPI_STATE_WRITING;
            spi_bus_dma_rxtx_config(spi, NULL, msg->tx_data, msg->data_size);
            break;
        case SPI_READ:
            spi->state = SPI_STATE_READING;
            spi_bus_dma_rxtx_config(spi, msg->rx_data, NULL, msg->data_size);
            break;
        case SPI_READ_WRITE:
            spi->state = SPI_STATE_READING_WRITING;
            spi_bus_dma_rxtx_config(spi, msg->rx_data, msg->tx_data, msg->data_size);
            break;
    }
}

static ALWAYS_INLINE void spi_bus_on_message_sent(spi_bus_t* spi)
{
    if(spi->messages[spi->message_index].callback != NULL){
        spi->messages[spi->message_index].callback(&spi->messages[spi->message_index]);
    }
}

static bool spi_bus_setup_next_message(spi_bus_t* spi)
{
    spi_bus_on_message_sent(spi);
    if(++ spi->message_index >= spi->messages_count) return false;
    spi_bus_setup_message(spi);
    return true;
}

static ALWAYS_INLINE bool spi_bus_done(spi_bus_t* spi)
{
    if(spi->callback) spi->callback();
    return spi->state == SPI_STATE_IDLE;
}

static void spi_bus_transfer_done(spi_bus_t* spi)
{
    if(spi_bus_setup_next_message(spi)){
        spi_bus_dma_start(spi);
    }else{
        spi_bus_dma_stop(spi);
        spi_bus_dma_unlock_channels(spi);

        spi->state = SPI_STATE_IDLE;
        spi->status = SPI_STATUS_TRANSFERED;

        spi_bus_done(spi);
    }
}

static void spi_bus_transfer_error(spi_bus_t* spi)
{
    spi_bus_dma_stop(spi);
    spi_bus_dma_unlock_channels(spi);

    spi->state = SPI_STATE_IDLE;
    spi->status = SPI_STATUS_ERROR;
    
    spi_bus_done(spi);
}

static uint16_t spi_bus_read_received_data(spi_bus_t* spi)
{
    return spi->spi_device->OUTR;
}

void spi_bus_irq_handler(spi_bus_t* spi)
{
#ifdef SPI_BUS_DEBUG
    printf("[SPI] ERR\r\n");
#endif
    
    uint16_t PSR = spi->spi_device->PSR;
    
    if(PSR & USIC_CH_PSR_SSCMode_DLIF_Msk){
        // Clear flag.
        spi->spi_device->PSCR = USIC_CH_PSCR_CDLIF_Msk;
        
        spi->errors |= SPI_ERROR_OVERRUN;

    }
    if(PSR & USIC_CH_PSR_SSCMode_DX2TEV_Msk){
        spi->spi_device->PSCR = USIC_CH_PSCR_CST3_Msk;
        
        spi->errors |= SPI_ERROR_MASTER_MODE_FAULT;
    }
//    if(PSR & SPI_SR_CRCERR){
//        // Clear flag.
//
//        spi->errors |= SPI_ERROR_CRC;
//    }

    if(PSR & (USIC_CH_PSR_SSCMode_RIF_Msk | USIC_CH_PSR_SSCMode_AIF_Msk)){
        // Clear flag.
        spi_bus_clear_rx_events(spi);
        // Disable interrupt.
        spi_bus_rx_it_disable(spi);
        
    }else if(PSR & USIC_CH_PSR_SSCMode_TBIF_Msk){
        // Clear flag.
        spi_bus_clear_tx_events(spi);
        // Disable interrupt.
        spi_bus_tx_it_disable(spi);
    }
    
    if(spi->errors == SPI_NO_ERROR){
        spi_bus_transfer_done(spi);
    }else{
        spi_bus_transfer_error(spi);
    }
}

bool spi_bus_dma_rx_channel_irq_handler(spi_bus_t* spi)
{
    //bool duplex = spi_bus_is_duplex(spi);
    bool can_rx = spi_bus_can_rx(spi);
    //bool can_tx = spi_bus_can_tx(spi);
    
#ifdef SPI_BUS_DEBUG
    printf("[SPI] DMA RX\r\n");
#endif
    
    // Если мы не можем принимать - возврат.
    if(!can_rx || !spi->dma_rx_locked) return false;
        
    uint32_t dma_tc_flag = dma_channel_it_flag(spi->dma_rx_channel, DMA_IT_TC);
    uint32_t dma_te_flag = dma_channel_it_flag(spi->dma_tx_channel, DMA_IT_TE);

    if(dma_channel_it_flag_status(dma_tc_flag)){

        dma_channel_it_flag_clear(dma_tc_flag);
        
        if(!spi_bus_is_crc_enabled(spi)){
            spi_bus_transfer_done(spi);
        }else{
            spi_bus_rx_it_enable(spi);
        }

    }else if(dma_channel_it_flag_status(dma_te_flag)){

        dma_channel_it_flag_clear(dma_te_flag);
        
        spi->errors |= SPI_ERROR_DMA;
        spi_bus_transfer_error(spi);
    }

    return true;
}

bool spi_bus_dma_tx_channel_irq_handler(spi_bus_t* spi)
{
    //bool duplex = spi_bus_is_duplex(spi);
    bool can_rx = spi_bus_can_rx(spi);
    bool can_tx = spi_bus_can_tx(spi);
    
#ifdef SPI_BUS_DEBUG
    printf("[SPI] DMA TX\r\n");
#endif
    
    // Если мы не можем передавать - возврат.
    if(!can_tx || !spi->dma_tx_locked) return false;
        
    uint32_t dma_tc_flag = dma_channel_it_flag(spi->dma_tx_channel, DMA_IT_TC);
    uint32_t dma_te_flag = dma_channel_it_flag(spi->dma_tx_channel, DMA_IT_TE);

    if(dma_channel_it_flag_status(dma_tc_flag)){

        dma_channel_it_flag_clear(dma_tc_flag);

        if(!can_rx){
            if(!spi_bus_is_crc_enabled(spi)){
                spi_bus_transfer_done(spi);
            }else{
                spi_bus_tx_it_enable(spi);
            }
        }

    }else if(dma_channel_it_flag_status(dma_te_flag)){

        dma_channel_it_flag_clear(dma_te_flag);
        
        spi->errors |= SPI_ERROR_DMA;
        spi_bus_transfer_error(spi);
    }
    return true;
}

bool spi_bus_busy(spi_bus_t* spi)
{
    return (spi->spi_device->TCSR & USIC_CH_TCSR_TDVTR_Msk) != 0;// && spi->state != SPI_STATE_IDLE;
}

void spi_bus_wait(spi_bus_t* spi)
{
    WAIT_WHILE_TRUE(spi_bus_busy(spi));
}

bool spi_bus_enabled(spi_bus_t* spi)
{
    return ((spi->spi_device->CCR & USIC_CH_CCR_MODE_Msk) >> USIC_CH_CCR_MODE_Pos) != 0; // == 0b01
}

bool spi_bus_set_enabled(spi_bus_t* spi, bool enabled)
{
    if(spi_bus_busy(spi)) return false;
    
    if(enabled){
        uint32_t mode = ((spi->spi_device->CCR & USIC_CH_CCR_MODE_Msk) >> USIC_CH_CCR_MODE_Pos);
        if((mode != 0b01) && (mode != 0b00)){
            spi->spi_device->CCR &= ~USIC_CH_CCR_MODE_Msk;
        }
        spi->spi_device->CCR = (spi->spi_device->CCR & ~USIC_CH_CCR_MODE_Msk) | (0b01 << USIC_CH_CCR_MODE_Pos);
    }else{
        spi->spi_device->CCR &= ~USIC_CH_CCR_MODE_Msk;
    }
    
    return true;
}

spi_callback_t spi_bus_callback(spi_bus_t* spi)
{
    return spi->callback;
}

void spi_bus_set_callback(spi_bus_t* spi, spi_callback_t callback)
{
    spi->callback = callback;
}

spi_transfer_id_t spi_bus_transfer_id(spi_bus_t* spi)
{
    return spi->transfer_id;
}

bool spi_bus_set_transfer_id(spi_bus_t* spi, spi_transfer_id_t id)
{
    if(spi_bus_busy(spi)) return false;
    
    spi->transfer_id = id;
    
    return true;
}

void spi_bus_set_tx_default_value(spi_bus_t* spi, uint16_t value)
{
    spi->tx_default = value;
}

bool spi_bus_crc_enabled(spi_bus_t* spi)
{
    return spi_bus_is_crc_enabled(spi);
}

bool spi_bus_set_crc_enabled(spi_bus_t* spi, bool enabled)
{
    (void) spi;
    (void) enabled;

    return false;
}

uint16_t spi_bus_crc_polynomial(spi_bus_t* spi)
{
    (void) spi;

    return 0;
}

bool spi_bus_set_crc_polynomial(spi_bus_t* spi, uint16_t polynomial)
{
    (void) spi;
    (void) polynomial;

    return false;
}

uint16_t spi_bus_tx_crc(spi_bus_t* spi)
{
    (void) spi;

    return 0;
}

uint16_t spi_bus_rx_crc(spi_bus_t* spi)
{
    (void) spi;

    return 0;
}

bool spi_bus_reset_crc(spi_bus_t* spi)
{
    (void) spi;
    
    return false;
}

spi_data_frame_format_t spi_bus_data_frame_format(spi_bus_t* spi)
{
    if(spi_bus_is_frame_16bit(spi)){
        return SPI_DATA_FRAME_FORMAT_16BIT;
    }
    return SPI_DATA_FRAME_FORMAT_8BIT;
}

bool spi_bus_set_data_frame_format(spi_bus_t* spi, spi_data_frame_format_t format)
{
    if(spi_bus_busy(spi)) return false;

    if(format == SPI_DATA_FRAME_FORMAT_8BIT){
        spi->spi_device->SCTR = (spi->spi_device->SCTR & ~USIC_CH_SCTR_FLE_Msk) | (7 << USIC_CH_SCTR_FLE_Pos);
    }else{
        spi->spi_device->SCTR = (spi->spi_device->SCTR & ~USIC_CH_SCTR_FLE_Msk) | (15 << USIC_CH_SCTR_FLE_Pos);
    }

    return true;
}

spi_frame_format_t spi_bus_frame_format(spi_bus_t* spi)
{
    if(spi_bus_is_frame_lsbfirst(spi)){
        return SPI_FRAME_FORMAT_LSBFIRST;
    }
    return SPI_FRAME_FORMAT_MSBFIRST;
}

bool spi_bus_set_frame_format(spi_bus_t* spi, spi_frame_format_t format)
{
    if(spi_bus_busy(spi)) return false;

    if(format == SPI_FRAME_FORMAT_MSBFIRST){
        spi->spi_device->SCTR |= USIC_CH_SCTR_SDIR_Msk;
    }else{
        spi->spi_device->SCTR &= ~USIC_CH_SCTR_SDIR_Msk;
    }

    return true;
}

spi_status_t spi_bus_status(spi_bus_t* spi)
{
    return spi->status;
}

spi_errors_t spi_bus_errors(spi_bus_t* spi)
{
    return spi->errors;
}

err_t spi_message_init(spi_message_t* message, spi_direction_t direction, const void* tx_data, void* rx_data, size_t data_size)
{
    if(data_size == 0) return E_INVALID_VALUE;
    
    switch(direction){
        case SPI_READ:
            if(rx_data == NULL) return E_NULL_POINTER;
            if(tx_data != NULL) return E_INVALID_VALUE;
            break;
        case SPI_WRITE:
            if(tx_data == NULL) return E_NULL_POINTER;
            if(rx_data != NULL) return E_INVALID_VALUE;
            break;
        case SPI_READ_WRITE:
            if(tx_data == NULL || rx_data == NULL) return E_NULL_POINTER;
            break;
    }
    
    message->direction = direction;
    message->tx_data = tx_data;
    message->rx_data = rx_data;
    message->data_size = data_size;
    message->callback = NULL;
    message->sender_data = NULL;
    
    return E_NO_ERROR;
}

err_t spi_bus_transfer(spi_bus_t* spi, spi_message_t* messages, size_t messages_count)
{
    if(spi_bus_busy(spi)) return E_BUSY;
    if(messages == NULL) return E_NULL_POINTER;
    if(messages_count == 0) return E_INVALID_VALUE;
    
    bool need_rx_channel = false;
    bool need_tx_channel = false;
    
    size_t i = 0;
    
    bool duplex = spi_bus_is_duplex(spi);
    
    spi_message_t* msg = NULL;
    // Если режим передачи по обоим линиям.
    if(duplex){
        need_rx_channel = true;
        need_tx_channel = true;
    // Иначе.
    }else{
        // Возможность передачи и приёма.
        bool can_rx = spi_bus_can_rx(spi);
        bool can_tx = spi_bus_can_tx(spi);
        // Проверим все сообщения.
        for(; i < messages_count; i ++){
            msg = &messages[i];
            switch(msg->direction){
                case SPI_READ:
                    // Принимать данные можно только при BIDIOE == 0.
                    if(!can_rx) return E_SPI_INVALID_MESSAGE;
                    need_rx_channel = true;
                    break;
                case SPI_WRITE:
                    // Передавать данные можно только при BIDIOE == 1.
                    if(!can_tx) return E_SPI_INVALID_MESSAGE;
                    need_tx_channel = true;
                    break;
                case SPI_READ_WRITE:
                    // Передавать и принимать данные одновременно нельзя
                    // в режиме однопроводной шины.
                    return E_SPI_INVALID_MESSAGE;
            }
            if(need_rx_channel && need_tx_channel) break;
        }
    }
    
    if(!spi_bus_dma_lock_channels(spi, need_rx_channel, need_tx_channel)) return E_BUSY;
    
    spi->messages = messages;
    spi->messages_count = messages_count;
    spi->message_index = 0;
    spi->errors = E_NO_ERROR;
    spi->status = SPI_STATUS_TRANSFERING;
    
    spi_bus_setup_message(spi);
    
    spi_bus_dma_start(spi);
    
    return E_NO_ERROR;
}

err_t spi_bus_transmit(spi_bus_t* spi, uint16_t tx_data, uint16_t* rx_data)
{
    if(spi_bus_busy(spi)) return E_BUSY;

    spi_bus_clear_rxtx_events(spi);

    spi->spi_device->TBUF[0] = tx_data;

    // Подождать отправки.
    spi_bus_wait_can_tx(spi);
    // Подождать получения.
    spi_bus_wait_can_rx(spi);

    // Очистим RXNE flag.
    uint16_t data = spi_bus_read_received_data(spi);
    if(rx_data) *rx_data = data;

    return E_NO_ERROR;
}
