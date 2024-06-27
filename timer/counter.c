#include "counter.h"
#include "modules/modules.h"
#include "utils/counter.h"


METHOD_INIT_IMPL(M_counter, cnt)
{
}

METHOD_DEINIT_IMPL(M_counter, cnt)
{
}

static void counter_control(M_counter* cnt)
{
    if(cnt->control & CONTROL_START){
        cnt->out_value = 0;
        cnt->m_ref_counter = sys_time.r_counter_ms;

        cnt->status = STATUS_RUN;
    }
    if(cnt->control & CONTROL_STOP){

        cnt->status = STATUS_NONE;
    }

    cnt->control = CONTROL_NONE;
}

METHOD_CALC_IMPL(M_counter, cnt)
{
    counter_control(cnt);

    if(cnt->status & STATUS_RUN){
        // Пройденное время с начала счёта.
        cnt->out_value = counter_calc_diff(sys_time.r_counter_ms, cnt->m_ref_counter);
    }
}

METHOD_CONTROL_IMPL(M_counter, cnt)
{
    counter_control(cnt);
}
