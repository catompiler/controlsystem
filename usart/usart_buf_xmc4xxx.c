#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "usart_buf_xmc4xxx.h"
#include "utils/utils.h"
#include "defs/defs.h"
#include <stdbool.h>



ALWAYS_INLINE static bool usart_tx_it_enabled(USIC_CH_TypeDef* usart)
{
    if(usart->CCR & USIC_CH_CCR_TBIEN_Msk) return true;
    return false;
}

ALWAYS_INLINE static void usart_tx_it_enable(USIC_CH_TypeDef* usart)
{
    usart->CCR |= USIC_CH_CCR_TBIEN_Msk;
}

ALWAYS_INLINE static void usart_tx_it_disable(USIC_CH_TypeDef* usart)
{
    usart->CCR &= ~USIC_CH_CCR_TBIEN_Msk;
}

ALWAYS_INLINE static void usart_tx_it_set_enabled(USIC_CH_TypeDef* usart, bool enabled)
{
    if(enabled) usart_tx_it_enable(usart);
    else usart_tx_it_disable(usart);
}

ALWAYS_INLINE static bool usart_rx_it_enabled(USIC_CH_TypeDef* usart)
{
    if(usart->CCR & USIC_CH_CCR_RIEN_Msk) return true;
    return false;
}

ALWAYS_INLINE static void usart_rx_it_enable(USIC_CH_TypeDef* usart)
{
    usart->CCR |= USIC_CH_CCR_RIEN_Msk;
}

ALWAYS_INLINE static void usart_rx_it_disable(USIC_CH_TypeDef* usart)
{
    usart->CCR &= ~USIC_CH_CCR_RIEN_Msk;
}

ALWAYS_INLINE static void usart_rx_it_set_enabled(USIC_CH_TypeDef* usart, bool enabled)
{
    if(enabled) usart_rx_it_enable(usart);
    else usart_rx_it_disable(usart);
}


ALWAYS_INLINE static bool usart_rx_event(USIC_CH_TypeDef* usart)
{
    return usart->PSR_ASCMode & USIC_CH_PSR_ASCMode_RIF_Msk;
}

ALWAYS_INLINE static void usart_rx_event_clear(USIC_CH_TypeDef* usart)
{
    usart->PSCR = USIC_CH_PSCR_CRIF_Msk;
}


ALWAYS_INLINE static bool usart_tx_event(USIC_CH_TypeDef* usart)
{
    return usart->PSR_ASCMode & USIC_CH_PSR_ASCMode_TBIF_Msk;
}

ALWAYS_INLINE static void usart_tx_event_clear(USIC_CH_TypeDef* usart)
{
    usart->PSCR = USIC_CH_PSCR_CTBIF_Msk;
}


ALWAYS_INLINE static void usart_send_data(USIC_CH_TypeDef* usart, uint8_t data)
{
    usart->TBUF[0] = data;
}

ALWAYS_INLINE static uint8_t usart_recv_data(USIC_CH_TypeDef* usart)
{
    return usart->RBUF & 0xff;
}


err_t usart_buf_init(usart_buf_t* usart_buf, usart_buf_init_t* usart_buf_init)
{
    // Адрес периферии не может быть нулём.
    if(usart_buf_init->usart == NULL) return E_NULL_POINTER;
    
    // Если буфера нет.
    if(usart_buf_init->write_buffer == NULL){
        // То и его размер должен быть нулём.
        if(usart_buf_init->write_buffer_size != 0) return E_NULL_POINTER;
    }else{
        // Иначе размер не может буть нулевым.
        if(usart_buf_init->write_buffer_size == 0) return E_INVALID_VALUE;
    }
    
    // Если буфера нет.
    if(usart_buf_init->read_buffer == NULL){
        // То и его размер должен быть нулём.
        if(usart_buf_init->read_buffer_size != 0) return E_NULL_POINTER;
    }else{
        // Иначе размер не может буть нулевым.
        if(usart_buf_init->read_buffer_size == 0) return E_INVALID_VALUE;
    }
    
    usart_buf->usart = usart_buf_init->usart;
    
    usart_buf->data_overrun = false;
    
    circular_buffer_init(&usart_buf->write_buffer, (uint8_t*)usart_buf_init->write_buffer, usart_buf_init->write_buffer_size);
    circular_buffer_init(&usart_buf->read_buffer,  (uint8_t*)usart_buf_init->read_buffer,  usart_buf_init->read_buffer_size);
    
    usart_rx_it_enable(usart_buf->usart);
    
    return E_NO_ERROR;
}

void usart_buf_irq_handler(usart_buf_t* usart_buf)
{
    USIC_CH_TypeDef* usart = usart_buf->usart;

    if(usart_rx_event(usart)){
        usart_rx_event_clear(usart);
        
        uint8_t data = usart_recv_data(usart);
        if(!circular_buffer_put(&usart_buf->read_buffer, data)){
            usart_buf->data_overrun = true;
        }
    }

    if(usart_tx_event(usart)){
        usart_tx_event_clear(usart);
        
        uint8_t data;
        if(circular_buffer_get(&usart_buf->write_buffer, &data)){
            usart_send_data(usart, data);
        }else{
            usart_tx_it_disable(usart);
        }
    }
}

bool usart_buf_data_overrun(usart_buf_t* usart_buf)
{
    return usart_buf->data_overrun;
}

void usart_buf_flush(usart_buf_t* usart_buf)
{
    while(circular_buffer_avail_size(&usart_buf->write_buffer) != 0);
}

size_t usart_buf_data_avail(usart_buf_t* usart_buf)
{
    return circular_buffer_avail_size(&usart_buf->read_buffer);
}

size_t usart_buf_put(usart_buf_t* usart_buf, uint8_t data)
{
    USIC_CH_TypeDef* usart = usart_buf->usart;

    size_t res;
    
    if(!circular_buffer_valid(&usart_buf->write_buffer)) return 0;
    
    while(circular_buffer_free_size(&usart_buf->write_buffer) == 0);
    
    bool tx_it_enabled = usart_tx_it_enabled(usart);
    usart_tx_it_disable(usart);
    
    res = circular_buffer_put(&usart_buf->write_buffer, data);
    
    if(res != 0){
        usart_tx_it_enable(usart);
    }else{
        usart_tx_it_set_enabled(usart, tx_it_enabled);
    }
    
    return res;
}

size_t usart_buf_get(usart_buf_t* usart_buf, uint8_t* data)
{
    USIC_CH_TypeDef* usart = usart_buf->usart;

    size_t res;
    
    if(!circular_buffer_valid(&usart_buf->read_buffer)) return 0;
    
    bool rx_it_enabled = usart_rx_it_enabled(usart);
    usart_rx_it_disable(usart);
    
    res = circular_buffer_get(&usart_buf->read_buffer, data);
    
    usart_rx_it_set_enabled(usart, rx_it_enabled);
    
    if(res != 0){
        usart_buf->data_overrun = false;
    }
    
    return res;
}

size_t usart_buf_write(usart_buf_t* usart_buf, const void* data, size_t size)
{
    USIC_CH_TypeDef* usart = usart_buf->usart;

    if(size == 0 || data == NULL) return 0;
    if(!circular_buffer_valid(&usart_buf->write_buffer)) return 0;
    
    size_t res_size = 0;
    size_t n;
    size_t free_size;
    
    do{

        do{
            free_size = circular_buffer_free_size(&usart_buf->write_buffer);
            n = MIN(free_size, size);
        }while(n == 0);

        bool tx_it_enabled = usart_tx_it_enabled(usart);
        usart_tx_it_disable(usart);

        n = circular_buffer_write(&usart_buf->write_buffer, data, n);

        if(n != 0){
            usart_tx_it_enable(usart);
        }else{
            usart_tx_it_set_enabled(usart, tx_it_enabled);
            break;
        }
        
        res_size += n;
        data += n;
        size -= n;
    
    }while(size > 0);
    
    return res_size;
}

size_t usart_buf_read(usart_buf_t* usart_buf, void* data, size_t size)
{
    USIC_CH_TypeDef* usart = usart_buf->usart;

    if(size == 0 || data == NULL) return 0;
    if(!circular_buffer_valid(&usart_buf->read_buffer)) return 0;
    
    size_t res_size = 0;
    
    bool rx_it_enabled = usart_rx_it_enabled(usart);
    usart_rx_it_disable(usart);
    
    res_size = circular_buffer_read(&usart_buf->read_buffer, data, size);
    
    usart_rx_it_set_enabled(usart, rx_it_enabled);
    
    if(res_size != 0){
        usart_buf->data_overrun = false;
    }
    
    return res_size;
}

#endif
