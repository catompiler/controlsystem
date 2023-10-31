#include "sys_time.h"
#include "modules/modules.h"


METHOD_INIT_IMPL(M_sys_time, t)
{
}

METHOD_DEINIT_IMPL(M_sys_time, t)
{
}

METHOD_CALC_IMPL(M_sys_time, t)
{
    t->r_counter_ms ++;

    if(++ t->m_counter_ms >= 1000){
        t->m_counter_ms = 0;
        t->r_counter_s ++;
    }

    if(sys.status & STATUS_RUN){
        if(++ t->m_run_counter_ms >= 1000){
            t->m_run_counter_ms = 0;
            t->r_run_counter_s ++;
        }
    }
}
