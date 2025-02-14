#include "port.h"

#if defined(PORT_POSIX)

#include "sys_timer.h"
#include <assert.h>
#include <stddef.h>


static void timer_callback(void* arg)
{
    M_sys_timer* sys_tmr = (M_sys_timer*)arg;

    assert(sys_tmr != NULL);

//    #if defined(SYS_TIMER_ONE_SHOT) && SYS_TIMER_ONE_SHOT == 1
//    thread_timer_stop(&sys_tmr->m_thr_tim);
//    #endif

    sys_tmr->out_counter ++;

    CALLBACK_CALL(sys_tmr->on_timeout);
}

static int timer_init_impl(M_sys_timer* sys_tmr)
{
    int res = 0;

    res = thread_timer_init(&sys_tmr->m_thr_tim);
    if(res != 0) return res;

    #if defined(SYS_TIMER_ONE_SHOT) && SYS_TIMER_ONE_SHOT == 1
    thread_timer_set_flags(&sys_tmr->m_thr_tim, THREAD_TIMER_FLAG_ONE_SHOT);
    #endif

    thread_timer_set_callback(&sys_tmr->m_thr_tim, timer_callback, sys_tmr);

    struct timespec ts_val;
    ts_val.tv_sec = 0;
    ts_val.tv_nsec = SYS_TIMER_TICKS_PERIOD_US * 1000;
    thread_timer_set_period(&sys_tmr->m_thr_tim, &ts_val);

    thread_timer_wait_thread_begin(&sys_tmr->m_thr_tim);

    return 0;
}

static int timer_start_impl(M_sys_timer* sys_tmr)
{
    int res = 0;

    res = thread_timer_start(&sys_tmr->m_thr_tim);
    if(res != 0) return res;

    thread_timer_wait_start(&sys_tmr->m_thr_tim);

    return 0;
}

static int timer_stop_impl(M_sys_timer* sys_tmr)
{
    int res = 0;

    res = thread_timer_stop(&sys_tmr->m_thr_tim);
    if(res != 0) return res;

    thread_timer_wait_stop(&sys_tmr->m_thr_tim);

    return 0;
}

static int timer_isrunning_impl(M_sys_timer* sys_tmr)
{
    return thread_timer_running(&sys_tmr->m_thr_tim);
}

static void timer_deinit_impl(M_sys_timer* sys_tmr)
{
    thread_timer_deinit(&sys_tmr->m_thr_tim);
}


METHOD_INIT_IMPL(M_sys_timer, sys_tmr)
{
    sys_tmr->control = 0;
    sys_tmr->status = 0;
    sys_tmr->out_counter = 0;

    int res = timer_init_impl(sys_tmr);

    if(res == 0){
        sys_tmr->status = SYS_TIMER_STATUS_READY;
    }else{
        sys_tmr->status = SYS_TIMER_STATUS_ERROR;
    }
}

METHOD_DEINIT_IMPL(M_sys_timer, sys_tmr)
{
    timer_deinit_impl(sys_tmr);

    sys_tmr->status = SYS_TIMER_STATUS_NONE;
}

METHOD_CONTROL_IMPL(M_sys_timer, sys_tmr)
{
    if(!(sys_tmr->status & SYS_TIMER_STATUS_READY)){
        return;
    }

    if(sys_tmr->control & SYS_TIMER_CONTROL_ENABLE){
        //if(!(sys_tmr->status & SYS_TIMER_STATUS_RUN)){
        if(!timer_isrunning_impl(sys_tmr)){
            int res = timer_start_impl(sys_tmr);
            if(res == 0){
                sys_tmr->status = SYS_TIMER_STATUS_READY | SYS_TIMER_STATUS_RUN;
            }else{
                sys_tmr->status = SYS_TIMER_STATUS_ERROR;
            }
        }
    }else{ // !(sys_tmr->control & SYS_TIMER_CONTROL_ENABLE)
        //if(sys_tmr->status & SYS_TIMER_STATUS_RUN){
        if(timer_isrunning_impl(sys_tmr)){
            int res = timer_stop_impl(sys_tmr);
            if(res == 0){
                sys_tmr->status = SYS_TIMER_STATUS_READY;
            }else{
                sys_tmr->status = SYS_TIMER_STATUS_ERROR;
            }
        }
    }
}

#endif
