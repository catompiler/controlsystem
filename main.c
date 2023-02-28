#include <stdio.h>
#include <stddef.h>

#include <math.h>

#include "iqmath/iq.h"
#include "iqmath/iq24.h"
#include "iqmath/iq24_math.h"
#include "iqmath/iq15.h"
#include "iqmath/iq15_math.h"
#include "iqmath/iq24_cordic.h"
#include "iqmath/q15.h"
#include "iqmath/q15_math.h"

#ifndef __arm__
#include "test_main.h"
#endif

/*

#include <signal.h>
#include <time.h>


#define COUNTER_TOP 1
timer_t timerid;
int counter = 0;

void timer_notify_function(union sigval arg)
{
    (void) arg;
    printf("%d\n", ++counter);
    fflush(stdout);
}

int init_timer(void)
{
    int res = 0;

    struct sigevent sigev;

    sigev.sigev_notify = SIGEV_THREAD;
    sigev.sigev_signo = 0;
    sigev.sigev_notify_attributes = 0;
    sigev.sigev_notify_function = timer_notify_function;
    sigev.sigev_value.sival_ptr = NULL;

    res = timer_create(CLOCK_REALTIME, &sigev, &timerid);
    if(res != 0) return res;

    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = 100000000;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = 100000000;

    res = timer_settime(timerid, 0, &t, NULL);
    if(res != 0) return res;

    return res;
}

int deinit_timer(void)
{
    int res = 0;

    res = timer_delete(timerid);

    return res;
}
*/
#ifdef __arm__
int printf(const char* __restrict, ...)
{
    return 0;
}
#endif



int main(void)
{
/*
    int res = 0;

    res = init_timer();
    if(res != 0){
        printf("Error init timer!\n");
        return res;
    }

    while(counter < COUNTER_TOP);

    deinit_timer();
*/
#ifndef __arm__
    test_main();
#endif

    /*iq24_t sin_val = iq24_sin(IQ24_PI/4);
    printf("sin(pi/4): 0x%x\n", sin_val);*/

    /*iq24_t sqrt_val = iq24_sqrt(IQ24I(2));
    printf("sqrt(2): 0x%x\n", sqrt_val);*/

    /*iq15_t sqrt_val = iq15_sqrt(IQ15I(2));
    printf("sqrt(2): 0x%x\n", sqrt_val);*/

    /*iq24_t x, y, angle, hyp;
    x = IQ24(0);
    y = IQ24(1);
    iq24_cordic_atan2_hyp_pu(x, y, &angle, &hyp);
    printf("atan 0x%x hyp 0x%x\n", angle, hyp);

    angle = IQ24(0.0);
    iq24_cordic_sincos_pu(angle, &y, &x);
    printf("sin 0x%x cos 0x%x\n", y, x);*/

    //print_iq15_cordic_atan2_pu();

    /*q15_t sin_val = q15_sin_pu(Q15(0.125));
    printf("sin(pi/4): 0x%x\n", sin_val);*/

    /*q15_t sin_val = q15_sin_pu(0xdfa4);
    printf("sin(pi/4): 0x%x\n", sin_val);*/

#ifndef __arm__

    //print_iq24_sqrt();

#endif

    return 0;
}
