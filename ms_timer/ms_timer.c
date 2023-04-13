#include "ms_timer.h"
#include <assert.h>
#include <stddef.h>


static void timer_callback(void* arg)
{
    M_ms_timer* ms_tmr = (M_ms_timer*)arg;

    assert(ms_tmr != NULL);

    ms_tmr->out_counter ++;

    CALLBACK_CALL(ms_tmr->on_timeout);
}

static int timer_init_impl(M_ms_timer* ms_tmr)
{
    int res = 0;

    res = thread_timer_init(&ms_tmr->m_thr_tim);
    if(res != 0) return res;

    thread_timer_set_callback(&ms_tmr->m_thr_tim, timer_callback, ms_tmr);

    struct timespec ts_val;
    ts_val.tv_sec = 0;
    ts_val.tv_nsec = MS_TIMER_TICKS_PERIOD_US * 1000;
    thread_timer_set_period(&ms_tmr->m_thr_tim, &ts_val);

    thread_timer_wait_thread_begin(&ms_tmr->m_thr_tim);

    return 0;
}

static int timer_start_impl(M_ms_timer* ms_tmr)
{
    int res = 0;

    res = thread_timer_start(&ms_tmr->m_thr_tim);
    if(res != 0) return res;

    thread_timer_wait_start(&ms_tmr->m_thr_tim);

    return 0;
}

static int timer_stop_impl(M_ms_timer* ms_tmr)
{
    int res = 0;

    res = thread_timer_stop(&ms_tmr->m_thr_tim);
    if(res != 0) return res;

    thread_timer_wait_stop(&ms_tmr->m_thr_tim);

    return 0;
}

static int timer_isrunning_impl(M_ms_timer* ms_tmr)
{
    return thread_timer_running(&ms_tmr->m_thr_tim);
}

static void timer_deinit_impl(M_ms_timer* ms_tmr)
{
    thread_timer_deinit(&ms_tmr->m_thr_tim);
}


METHOD_INIT_IMPL(M_ms_timer, ms_tmr)
{
    ms_tmr->control = 0;
    ms_tmr->status = 0;
    ms_tmr->out_counter = 0;

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
