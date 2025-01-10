#ifndef DMA_DMA_H_
#define DMA_DMA_H_

#include "cpu.h"
#include "defs/defs.h"
#include <stdint.h>
#include <stddef.h>


//! Число каналов DMA1.
#define DMA1_CHANNELS_COUNT 8

//! Число каналов DMA2.
#define DMA2_CHANNELS_COUNT 4

//! Число каналов DMA.
#define DMA_CHANNELS_COUNT ((DMA1_CHANNELS_COUNT)+(DMA2_CHANNELS_COUNT))


//! Тип коллбэка DMA.
typedef void (*dma_callback_t)(void* user_data);


//! Тип передачи DMA.
typedef enum _E_Dma_Transfer_Type {
    DMA_MEM_MEM,
    DMA_MEM_PER,
    DMA_PER_MEM,
    DMA_PER_PER
} dma_transfer_type_t;

//! Тип линии источника запроса.
typedef size_t dma_line_t;

//! Тип источника запроса.
typedef size_t dma_request_t;

//! Тип ширины одного элемента передачи.
typedef enum _E_Dma_Transfer_Width {
    DMA_TRANSFER_8_BIT,
    DMA_TRANSFER_16_BIT,
    DMA_TRANSFER_32_BIT,
} dma_transfer_width_t;


//! Тип инкремента адреса.
typedef enum _E_Dma_Addr_Inc {
    DMA_ADDR_INC,
    DMA_ADDR_DEC,
    DMA_ADDR_FIX
} dma_addr_inc_t;


err_t dma_setup_transfer_basic(dma_line_t line, dma_request_t req, dma_transfer_type_t type,
                               void* src, dma_transfer_width_t src_width, dma_addr_inc_t src_inc,
                               void* dst, dma_transfer_width_t dst_width, dma_addr_inc_t dst_inc, size_t count);


#endif /* DMA_DMA_H_ */
