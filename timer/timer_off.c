#include "timer_off.h"


METHOD_INIT_IMPL(M_timer_off, tmr)
{
}

METHOD_DEINIT_IMPL(M_timer_off, tmr)
{
}

METHOD_CALC_IMPL(M_timer_off, tmr)
{
    tmr->m_ed.in_value = tmr->in_value;
    CALC(tmr->m_ed);

    flag_t res = FLAG_NONE;
    flag_t cur = FLAG_NONE;

    switch(tmr->m_ed.out_value){
    default:
    case EDGE_DETECT_LOW:
        break;
    case EDGE_DETECT_HIGH:
        cur = FLAG_ACTIVE;
        break;
    case EDGE_DETECT_LEADING:
        tmr->r_tmr.control = CONTROL_STOP;
        //CONTROL(tmr->r_tmr);
        break;
    case EDGE_DETECT_FALLING:
        tmr->r_tmr.control = CONTROL_START;
        //CONTROL(tmr->r_tmr);
        break;
    }
    CALC(tmr->r_tmr);

    res = (cur | ((tmr->r_tmr.status & STATUS_RUN) ? (FLAG_ACTIVE) : (FLAG_NONE)));

    tmr->out_value = res;
}
