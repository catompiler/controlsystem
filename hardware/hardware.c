#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "hardware.h"



void hardware_init_ports(void)
{
    // reset.
    PORTS_RESET_ENABLE();
    PORTS_RESET_DISABLE();
}


void hardware_init_triacs_timers(void)
{
    // reset.
    TRIACS_TIMS_RESET_ENABLE();
    TRIACS_TIMS_RESET_DISABLE();

    // enable clock.
    TRIACS_TIMS_CLOCK_ENABLE();
}


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
}

void hardware_init_spis(void)
{
    // reset.
    SPIS_RESET_ENABLE();
    SPIS_RESET_DISABLE();
}

void hardware_init_dma(void)
{
    // reset.
    DMA_RESET_ENABLE();
    DMA_RESET_DISABLE();

    // enable clock.
    DMA_CLOCK_ENABLE();
}

void hardware_init_can(void)
{
    // reset.
    CAN_RESET_ENABLE();
    CAN_RESET_DISABLE();
}

#endif
