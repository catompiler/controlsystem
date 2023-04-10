#include "ms_timer.h"
#include <assert.h>
#include <stddef.h>


static void timer_notify_function(union sigval arg)
{
    M_ms_timer* ms_tmr = (M_ms_timer*)arg.sival_ptr;

    assert(ms_tmr != NULL);

    ms_tmr->out_counter ++;

    CALLBACK_CALL(ms_tmr->on_timeout);
}

static int timer_init_impl(M_ms_timer* ms_tmr)
{
    int res = 0;

    struct sigevent sigev;

    sigev.sigev_notify = SIGEV_THREAD;
    sigev.sigev_signo = 0;
    sigev.sigev_notify_attributes = 0;
    sigev.sigev_notify_function = timer_notify_function;
    sigev.sigev_value.sival_ptr = (void*)ms_tmr;

    res = timer_create(CLOCK_MONOTONIC, &sigev, &ms_tmr->m_timerid);
    if(res != 0) return res;

    // reset timer value
    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = 0;

    res = timer_settime(ms_tmr->m_timerid, 0, &t, NULL);
    if(res != 0) return res;

    return res;
}

static int timer_start_impl(M_ms_timer* ms_tmr)
{
    int res = 0;

    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = MS_TIMER_TICKS_PERIOD_US * 1000;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = MS_TIMER_TICKS_PERIOD_US * 1000;

    res = timer_settime(ms_tmr->m_timerid, 0, &t, NULL);
    if(res != 0) return res;

    return res;
}

static int timer_stop_impl(M_ms_timer* ms_tmr)
{
    int res = 0;

    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = 0;

    res = timer_settime(ms_tmr->m_timerid, 0, &t, NULL);
    if(res != 0) return res;

    return res;
}

static int timer_isrunning_impl(M_ms_timer* ms_tmr)
{
    int res = 0;

    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = 0;

    res = timer_gettime(ms_tmr->m_timerid, &t);
    if(res != 0) return 0;

    if(t.it_value.tv_sec == 0 && t.it_value.tv_nsec == 0){
        return 0;
    }

    return 1;
}

static void timer_deinit_impl(M_ms_timer* ms_tmr)
{
    timer_delete(ms_tmr->m_timerid);
}


METHOD_INIT_IMPL(M_ms_timer, ms_tmr)
{
    ms_tmr->control = 0;
    ms_tmr->status = 0;
    ms_tmr->out_counter = 0;
    ms_tmr->m_timerid = 0;

    int res = timer_init_impl(ms_tmr);

    if(res == 0){
        ms_tmr->status = MS_TIMER_STATUS_READY;
    }else{
        ms_tmr->status = MS_TIMER_STATUS_ERROR;
    }
}

METHOD_DEINIT_IMPL(M_ms_timer, ms_tmr)
{
    timer_deinit_impl(ms_tmr);

    ms_tmr->status = MS_TIMER_STATUS_NONE;
}

METHOD_CONTROL_IMPL(M_ms_timer, ms_tmr)
{
    if(!(ms_tmr->status & MS_TIMER_STATUS_READY)){
        return;
    }

    if(ms_tmr->control & MS_TIMER_CONTROL_ENABLE){
        //if(!(ms_tmr->status & MS_TIMER_STATUS_RUN)){
        if(!timer_isrunning_impl(ms_tmr)){
            int res = timer_start_impl(ms_tmr);
            if(res == 0){
                ms_tmr->status = MS_TIMER_STATUS_READY | MS_TIMER_STATUS_RUN;
            }else{
                ms_tmr->status = MS_TIMER_STATUS_ERROR;
            }
        }
    }else{ // !(ms_tmr->control & MS_TIMER_CONTROL_ENABLE)
        //if(ms_tmr->status & MS_TIMER_STATUS_RUN){
        if(timer_isrunning_impl(ms_tmr)){
            int res = timer_stop_impl(ms_tmr);
            if(res == 0){
                ms_tmr->status = MS_TIMER_STATUS_READY;
            }else{
                ms_tmr->status = MS_TIMER_STATUS_ERROR;
            }
        }
    }
}
