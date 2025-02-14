#include "port.h"

#if defined(PORT_POSIX)

#include "net_timer.h"
#include <assert.h>
#include <stddef.h>


static void timer_callback(void* arg)
{
    M_net_timer* net_tmr = (M_net_timer*)arg;

    assert(net_tmr != NULL);

    net_tmr->out_counter ++;

    CALLBACK_CALL(net_tmr->on_timeout);
}

static int timer_init_impl(M_net_timer* net_tmr)
{
    int res = 0;

    res = thread_timer_init(&net_tmr->m_thr_tim);
    if(res != 0) return res;

    thread_timer_set_callback(&net_tmr->m_thr_tim, timer_callback, net_tmr);

    struct timespec ts_val;
    ts_val.tv_sec = 0;
    ts_val.tv_nsec = NET_TIMER_TICKS_PERIOD_US * 1000;
    thread_timer_set_period(&net_tmr->m_thr_tim, &ts_val);

    thread_timer_wait_thread_begin(&net_tmr->m_thr_tim);

    return 0;
}

static int timer_start_impl(M_net_timer* net_tmr)
{
    int res = 0;

    res = thread_timer_start(&net_tmr->m_thr_tim);
    if(res != 0) return res;

    thread_timer_wait_start(&net_tmr->m_thr_tim);

    return 0;
}

static int timer_stop_impl(M_net_timer* net_tmr)
{
    int res = 0;

    res = thread_timer_stop(&net_tmr->m_thr_tim);
    if(res != 0) return res;

    thread_timer_wait_stop(&net_tmr->m_thr_tim);

    return 0;
}

static int timer_isrunning_impl(M_net_timer* net_tmr)
{
    return thread_timer_running(&net_tmr->m_thr_tim);
}

static void timer_deinit_impl(M_net_timer* net_tmr)
{
    thread_timer_deinit(&net_tmr->m_thr_tim);
}


METHOD_INIT_IMPL(M_net_timer, net_tmr)
{
    net_tmr->control = 0;
    net_tmr->status = 0;
    net_tmr->out_counter = 0;

    int res = timer_init_impl(net_tmr);

    if(res == 0){
        net_tmr->status = NET_TIMER_STATUS_READY;
    }else{
        net_tmr->status = NET_TIMER_STATUS_ERROR;
    }
}

METHOD_DEINIT_IMPL(M_net_timer, net_tmr)
{
    timer_deinit_impl(net_tmr);

    net_tmr->status = NET_TIMER_STATUS_NONE;
}

METHOD_CONTROL_IMPL(M_net_timer, net_tmr)
{
    if(!(net_tmr->status & NET_TIMER_STATUS_READY)){
        return;
    }

    if(net_tmr->control & NET_TIMER_CONTROL_ENABLE){
        //if(!(net_tmr->status & NET_TIMER_STATUS_RUN)){
        if(!timer_isrunning_impl(net_tmr)){
            int res = timer_start_impl(net_tmr);
            if(res == 0){
                net_tmr->status = NET_TIMER_STATUS_READY | NET_TIMER_STATUS_RUN;
            }else{
                net_tmr->status = NET_TIMER_STATUS_ERROR;
            }
        }
    }else{ // !(net_tmr->control & NET_TIMER_CONTROL_ENABLE)
        //if(net_tmr->status & NET_TIMER_STATUS_RUN){
        if(timer_isrunning_impl(net_tmr)){
            int res = timer_stop_impl(net_tmr);
            if(res == 0){
                net_tmr->status = NET_TIMER_STATUS_READY;
            }else{
                net_tmr->status = NET_TIMER_STATUS_ERROR;
            }
        }
    }
}

#endif
