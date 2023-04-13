#include "adc_timer.h"
#include <assert.h>
#include <stddef.h>


static void timer_callback(void* arg)
{
    M_adc_timer* adc_tmr = (M_adc_timer*)arg;

    assert(adc_tmr != NULL);

    adc_tmr->out_counter ++;

    CALLBACK_CALL(adc_tmr->on_timeout);
}

static int timer_init_impl(M_adc_timer* adc_tmr)
{
    int res = 0;

    res = thread_timer_init(&adc_tmr->m_thr_tim);
    if(res != 0) return res;

    thread_timer_set_callback(&adc_tmr->m_thr_tim, timer_callback, adc_tmr);

    struct timespec ts_val;
    ts_val.tv_sec = 0;
    ts_val.tv_nsec = ADC_TIMER_TICKS_PERIOD_US * 1000;
    thread_timer_set_period(&adc_tmr->m_thr_tim, &ts_val);

    thread_timer_wait_thread_begin(&adc_tmr->m_thr_tim);

    return 0;
}

static int timer_start_impl(M_adc_timer* adc_tmr)
{
    int res = 0;

    res = thread_timer_start(&adc_tmr->m_thr_tim);
    if(res != 0) return res;

    thread_timer_wait_start(&adc_tmr->m_thr_tim);

    return 0;
}

static int timer_stop_impl(M_adc_timer* adc_tmr)
{
    int res = 0;

    res = thread_timer_stop(&adc_tmr->m_thr_tim);
    if(res != 0) return res;

    thread_timer_wait_stop(&adc_tmr->m_thr_tim);

    return 0;
}

static int timer_isrunning_impl(M_adc_timer* adc_tmr)
{
    return thread_timer_running(&adc_tmr->m_thr_tim);
}

static void timer_deinit_impl(M_adc_timer* adc_tmr)
{
    thread_timer_deinit(&adc_tmr->m_thr_tim);
}


METHOD_INIT_IMPL(M_adc_timer, adc_tmr)
{
    adc_tmr->control = 0;
    adc_tmr->status = 0;
    adc_tmr->out_counter = 0;

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
