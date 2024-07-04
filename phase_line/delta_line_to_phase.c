#include "delta_line_to_phase.h"



METHOD_INIT_IMPL(M_delta_line_to_phase, lp)
{
}

METHOD_DEINIT_IMPL(M_delta_line_to_phase, lp)
{
}

METHOD_CALC_IMPL(M_delta_line_to_phase, lp)
{
    iql_t AB, BC, CA;
    iql_t A, B, C;

    AB = lp->in_A;
    BC = lp->in_B;
    CA = lp->in_C;

    A = AB - CA;
    B = BC - AB;
    C = CA - BC;

    lp->out_A = A;
    lp->out_B = B;
    lp->out_C = C;
}
