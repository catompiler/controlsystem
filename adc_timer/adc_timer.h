#ifndef ADC_TIMER_H
#define ADC_TIMER_H

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "adc_timer_xmc4xxx.h"
#endif

#if defined(PORT_POSIX)
#include "adc_timer_thread.h"
#endif

#endif /* ADC_TIMER_H */
