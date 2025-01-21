#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef CAN_CAN_XMC4XXX_H_
#define CAN_CAN_XMC4XXX_H_

#include "cpu.h"
#include "defs/defs.h"
#include "errors/errors.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


//! Частота тактирования блока CAN.
#define CAN_FREQ 60000000


//! Перечисление стандартных битрейтов.
typedef enum _E_Can_Bit_Rate {
    CAN_BIT_RATE_10kbit = 0,
    CAN_BIT_RATE_20kbit = 1,
    CAN_BIT_RATE_50kbit = 2,
    CAN_BIT_RATE_100kbit = 3,
    CAN_BIT_RATE_125kbit = 4,
    CAN_BIT_RATE_250kbit = 5,
    CAN_BIT_RATE_500kbit = 6,
    CAN_BIT_RATE_800kbit = 7,
    CAN_BIT_RATE_1000kbit = 8
} can_bit_rate_t;


//! Битрейт по-умолчанию.
#define CAN_BIT_RATE_DEFAULT CAN_BIT_RATE_125kbit


//! Режим замыкания на себя.
#define CAN_LOOPBACK 0


//! Число элементов в FIFO буфера.
#define CAN_FIFO_SIZE 4


// //! Тип CAN.
//typedef struct _S_Can {
//} can_t;


//! Инициализирует CAN.
EXTERN err_t can_init();

//! Устанавливает режим конфигурации.
EXTERN void can_set_configuration_mode();

//! Устанавливает битрейт.
EXTERN err_t can_set_bitrate(can_bit_rate_t bit_rate);

//! Устанавливает нормальный режим.
EXTERN void can_set_normal_mode();

//! Инициализирует буфер приёма с заданным индексом.
EXTERN err_t can_init_rx_buffer(size_t index, uint16_t ident, uint16_t mask, bool rtr);

#endif /* CAN_CAN_XMC4XXX_H_ */

#endif
