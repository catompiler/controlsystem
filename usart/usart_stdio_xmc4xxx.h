#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef USART_STDIO_XMC4XXX_H
#define USART_STDIO_XMC4XXX_H

#include "defs/defs.h"
#include "errors/errors.h"

//! Скорость обмена данными.
#define USART_STDIO_BAUD 115200

//! Размер буфера для передачи.
#define USART_STDIO_TX_BUFFER_LEN 128
//! Размер буфера для приёма.
#define USART_STDIO_RX_BUFFER_LEN 128


EXTERN err_t usart_stdio_init(void);

#endif /* USART_STDIO_XMC4XXX_H */

#endif
