#ifndef GPIO_H
#define GPIO_H

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "gpio_xmc4xxx.h"
#endif

#if defined(PORT_POSIX)
#endif

#endif /* GPIO_H */
