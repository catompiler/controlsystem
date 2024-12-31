#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "hardware.h"



void hardware_init_periodic_timers(void)
{
    // reset.
    PERIODIC_TIMS_RESET_ENABLE();
    PERIODIC_TIMS_RESET_DISABLE();

    // enable clock.
    PERIODIC_TIMS_CLOCK_ENABLE();
}


void hardware_init_counting_timers(void)
{
    // reset.
    COUNTING_TIMS_RESET_ENABLE();
    COUNTING_TIMS_RESET_DISABLE();

    // enable clock.
    COUNTING_TIMS_CLOCK_ENABLE();
}

void hardware_init_usarts(void)
{
    // reset.
    USARTS_RESET_ENABLE();
    USARTS_RESET_DISABLE();

    // enable clock.
    COUNTING_TIMS_CLOCK_ENABLE();
}

#endif
