#include "sys_timer.h"
#include <assert.h>
#include <stddef.h>


static void timer_notify_function(union sigval arg)
{
    M_sys_timer* sys_tmr = (M_sys_timer*)arg.sival_ptr;

    assert(sys_tmr != NULL);

    sys_tmr->out_counter ++;

    CALLBACK_CALL(sys_tmr->on_timeout);
}

static int timer_init_impl(M_sys_timer* sys_tmr)
{
    int res = 0;

    struct sigevent sigev;

    sigev.sigev_notify = SIGEV_THREAD;
    sigev.sigev_signo = 0;
    sigev.sigev_notify_attributes = 0;
    sigev.sigev_notify_function = timer_notify_function;
    sigev.sigev_value.sival_ptr = (void*)sys_tmr;

    res = timer_create(CLOCK_MONOTONIC, &sigev, &sys_tmr->m_timerid);
    if(res != 0) return res;

    // reset timer value
    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = 0;

    res = timer_settime(sys_tmr->m_timerid, 0, &t, NULL);
    if(res != 0) return res;

    return res;
}

static int timer_start_impl(M_sys_timer* sys_tmr)
{
    int res = 0;

    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = SYS_TIMER_TICKS_PERIOD_US * 1000;
#if defined(SYS_TIMER_ONE_SHOT) && SYS_TIMER_ONE_SHOT == 1
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = 0;
#else
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = SYS_TIMER_TICKS_PERIOD_US * 1000;
#endif

    res = timer_settime(sys_tmr->m_timerid, 0, &t, NULL);
    if(res != 0) return res;

    return res;
}

static int timer_stop_impl(M_sys_timer* sys_tmr)
{
    int res = 0;

    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = 0;

    res = timer_settime(sys_tmr->m_timerid, 0, &t, NULL);
    if(res != 0) return res;

    return res;
}

static int timer_isrunning_impl(M_sys_timer* sys_tmr)
{
    int res = 0;

    struct itimerspec t;
    t.it_value.tv_sec = 0;
    t.it_value.tv_nsec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_nsec = 0;

    res = timer_gettime(sys_tmr->m_timerid, &t);
    if(res != 0) return 0;

    if(t.it_value.tv_sec == 0 && t.it_value.tv_nsec == 0){
        return 0;
    }

    return 1;
}

static void timer_deinit_impl(M_sys_timer* sys_tmr)
{
    timer_delete(sys_tmr->m_timerid);
}


METHOD_INIT_IMPL(M_sys_timer, sys_tmr)
{
    sys_tmr->control = 0;
    sys_tmr->status = 0;
    sys_tmr->out_counter = 0;
    sys_tmr->m_timerid = 0;

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
