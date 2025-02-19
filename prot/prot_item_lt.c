#include "prot_item_lt.h"


METHOD_INIT_IMPL(M_prot_item_lt, pi)
{
    INIT(pi->r_threshold);
    INIT(pi->r_timer);
}

METHOD_DEINIT_IMPL(M_prot_item_lt, pi)
{
    DEINIT(pi->r_timer);
    DEINIT(pi->r_threshold);
}

METHOD_CALC_IMPL(M_prot_item_lt, pi)
{
    pi->r_threshold.in_value = pi->in_value;
    CALC(pi->r_threshold);

    pi->r_timer.in_value = pi->r_threshold.out_value;
    CALC(pi->r_timer);

    pi->out_value = pi->r_timer.out_value;
}
