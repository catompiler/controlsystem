#include "adc_timer.h"
#include <assert.h>
#include <stddef.h>


static void timer_notify_function(union sigval arg)
{
    M_adc_timer* adc_tmr = (M_adc_timer*)arg.sival_ptr;

    assert(adc_tmr != NULL);

    adc_tmr->out_counter ++;

    CALLBACK_CALL(adc_tmr->on_timeout);
}

static int timer_init_impl(M_adc_timer* adc_tmr)
{
    int res = 0;

    struct sigevent sigev;

    sigev.sigev_notify = SIGEV_THREAD;
    sigev.sigev_signo = 0;
    sigev.sigev_notify_attributes = 0;
    sigev.sigev_notify_function = timer_notify_function;
    sigev.sigev_value.sival_ptr = (void*)adc_tmr;

    res = timer_create(CLOCK_MONOTONIC, &sigev, &adc_tmr->m_timerid);
    if(res != 0) return res;

    // reset timer value
    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = 0;

    res = timer_settime(adc_tmr->m_timerid, 0, &t, NULL);
    if(res != 0) return res;

    return res;
}

static int timer_start_impl(M_adc_timer* adc_tmr)
{
    int res = 0;

    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = ADC_TIMER_TICKS_PERIOD_US * 1000;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = ADC_TIMER_TICKS_PERIOD_US * 1000;

    res = timer_settime(adc_tmr->m_timerid, 0, &t, NULL);
    if(res != 0) return res;

    return res;
}

static int timer_stop_impl(M_adc_timer* adc_tmr)
{
    int res = 0;

    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = 0;

    res = timer_settime(adc_tmr->m_timerid, 0, &t, NULL);
    if(res != 0) return res;

    return res;
}

static int timer_isrunning_impl(M_adc_timer* adc_tmr)
{
    int res = 0;

    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = 0;

    res = timer_gettime(adc_tmr->m_timerid, &t);
    if(res != 0) return 0;

    if(t.it_value.tv_sec == 0 && t.it_value.tv_nsec == 0){
        return 0;
    }

    return 1;
}

static void timer_deinit_impl(M_adc_timer* adc_tmr)
{
    timer_delete(adc_tmr->m_timerid);
}


METHOD_INIT_IMPL(M_adc_timer, adc_tmr)
{
    adc_tmr->control = 0;
    adc_tmr->status = 0;
    adc_tmr->out_counter = 0;
    adc_tmr->m_timerid = 0;

    int res = timer_init_impl(adc_tmr);

    if(res == 0){
        adc_tmr->status = ADC_TIMER_STATUS_READY;
    }else{
        adc_tmr->status = ADC_TIMER_STATUS_ERROR;
    }
}

METHOD_DEINIT_IMPL(M_adc_timer, adc_tmr)
{
    timer_deinit_impl(adc_tmr);

    adc_tmr->status = ADC_TIMER_STATUS_NONE;
}

METHOD_CONTROL_IMPL(M_adc_timer, adc_tmr)
{
    if(!(adc_tmr->status & ADC_TIMER_STATUS_READY)){
        return;
    }

    if(adc_tmr->control & ADC_TIMER_CONTROL_ENABLE){
        //if(!(adc_tmr->status & ADC_TIMER_STATUS_RUN)){
        if(!timer_isrunning_impl(adc_tmr)){
            int res = timer_start_impl(adc_tmr);
            if(res == 0){
                adc_tmr->status = ADC_TIMER_STATUS_READY | ADC_TIMER_STATUS_RUN;
            }else{
                adc_tmr->status = ADC_TIMER_STATUS_ERROR;
            }
        }
    }else{ // !(adc_tmr->control & ADC_TIMER_CONTROL_ENABLE)
        //if(adc_tmr->status & ADC_TIMER_STATUS_RUN){
        if(timer_isrunning_impl(adc_tmr)){
            int res = timer_stop_impl(adc_tmr);
            if(res == 0){
                adc_tmr->status = ADC_TIMER_STATUS_READY;
            }else{
                adc_tmr->status = ADC_TIMER_STATUS_ERROR;
            }
        }
    }
}
