#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef USART_STDIO_XMC4XXX_H
#define USART_STDIO_XMC4XXX_H

#include "defs/defs.h"


#define USART_STDIO_BAUD 115200


EXTERN void usart_stdio_init(void);

#endif /* USART_STDIO_XMC4XXX_H */

#endif
