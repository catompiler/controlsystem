#include "timer.h"
#include "modules/modules.h"


METHOD_INIT_IMPL(M_timer, tim)
{
}

METHOD_DEINIT_IMPL(M_timer, tim)
{
}

static void timer_control(M_timer* tim)
{
    //    if((tim->status & STATUS_RUN) && (tim->control & CONTROL_RESET)){
    //        tim->m_ref_counter = sys_time.r_counter_ms;
    //    }
    if(tim->control & CONTROL_START){
        tim->out_expired = FLAG_NONE;
        tim->out_timeout = STROBE_NONE;
        tim->m_ref_counter = sys_time.r_counter_ms;

        tim->status = STATUS_RUN;
    }
    if(tim->control & CONTROL_STOP){
        tim->out_expired = FLAG_NONE;
        tim->out_timeout = STROBE_NONE;

        tim->status = STATUS_NONE;
    }

    tim->control = CONTROL_NONE;
}

static uint32_t timer_calc_diff(uint32_t ref, uint32_t cur)
{
    // Текущее значение больше опорного - счётчик не переполнился.
    if(cur >= ref) return cur - ref;
    // Иначе cur < ref - счётчик переполнился.
    return UINT32_MAX - ref + cur + 1;
}

METHOD_CALC_IMPL(M_timer, tim)
{
    tim->out_timeout = STROBE_NONE;

    timer_control(tim);

    if(tim->status & STATUS_RUN){
        // Пройденное время с начала счёта.
        uint32_t elapsed_time = timer_calc_diff(tim->m_ref_counter, sys_time.r_counter_ms);
        // Если времени прошло больше чем интервал таймера.
        if(elapsed_time >= tim->r_interval){
            tim->status = STATUS_NONE;

            tim->out_expired = FLAG_ACTIVE;
            tim->out_timeout = STROBE_ACTIVE;
        }
    }
}

METHOD_CONTROL_IMPL(M_timer, tim)
{
    timer_control(tim);
}
