#include <dma/dma_xmc4xxx.h>
#include "hardware/config.h"



typedef struct _Dma_Handler_Data {
    dma_callback_t callback;
    void* user_data;
} dma_handler_data_t;


static dma_handler_data_t handlers[DMA_CHANNELS_COUNT] = {
        {NULL, NULL}, // 1
        {NULL, NULL}, // 2
        {NULL, NULL}, // 3
        {NULL, NULL}, // 4
        {NULL, NULL}, // 5
        {NULL, NULL}, // 6
        {NULL, NULL}, // 7
        {NULL, NULL}, // 8
        {NULL, NULL}, // 9
        {NULL, NULL}, // 10
        {NULL, NULL}, // 11
        {NULL, NULL}  // 12
};


void dma_set_int_callback(size_t ch_n, dma_callback_t callback, void* user_data)
{
    if(ch_n >= DMA_CHANNELS_COUNT) return;

    dma_handler_data_t* handler = &handlers[ch_n];
    handler->callback = callback;
    handler->user_data = user_data;
}



void DMA1_IRQ_Handler(void)
{
    uint32_t irq_stat = GPDMA0->STATUSTFR |
                        GPDMA0->STATUSBLOCK |
                        GPDMA0->STATUSSRCTRAN |
                        GPDMA0->STATUSDSTTRAN |
                        GPDMA0->STATUSERR;

    uint32_t ch_mask = 1;
    size_t ch_n = 0;
    for(; ch_n < DMA1_CHANNELS_COUNT; ch_n ++, ch_mask <<= 1){
        if(irq_stat & ch_mask){
            // Handler data.
            dma_handler_data_t* handler = &handlers[ch_n];
            // Callback.
            dma_callback_t callback = handler->callback;
            // If callback is not NULL - call handler with user data.
            if(callback){
                callback(handler->user_data);
            } // Else - clear all interrupt flags.
            //else{
                GPDMA0->CLEARTFR = ch_mask;
                GPDMA0->CLEARBLOCK = ch_mask;
                GPDMA0->CLEARSRCTRAN = ch_mask;
                GPDMA0->CLEARDSTTRAN = ch_mask;
                GPDMA0->CLEARERR = ch_mask;
            //}
        }
    }
}


void DMA2_IRQ_Handler(void)
{
    uint32_t irq_stat = GPDMA1->STATUSTFR |
                        GPDMA1->STATUSBLOCK |
                        GPDMA1->STATUSSRCTRAN |
                        GPDMA1->STATUSDSTTRAN |
                        GPDMA1->STATUSERR;

    uint32_t ch_mask = 1;
    size_t ch_n = DMA1_CHANNELS_COUNT;
    for(; ch_n < DMA_CHANNELS_COUNT; ch_n ++, ch_mask <<= 1){
        if(irq_stat & ch_mask){
            // Handler data.
            dma_handler_data_t* handler = &handlers[ch_n];
            // Callback.
            dma_callback_t callback = handler->callback;
            // If callback is not NULL - call handler with user data.
            if(callback){
                callback(handler->user_data);
            } // Else - clear all interrupt flags.
            //else{
                GPDMA1->CLEARTFR = ch_mask;
                GPDMA1->CLEARBLOCK = ch_mask;
                GPDMA1->CLEARSRCTRAN = ch_mask;
                GPDMA1->CLEARDSTTRAN = ch_mask;
                GPDMA1->CLEARERR = ch_mask;
            //}
        }
    }
}

