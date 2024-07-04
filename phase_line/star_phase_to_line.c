#include "star_phase_to_line.h"


METHOD_INIT_IMPL(M_star_phase_to_line, pl)
{
}

METHOD_DEINIT_IMPL(M_star_phase_to_line, pl)
{
}

METHOD_CALC_IMPL(M_star_phase_to_line, pl)
{
    iql_t A, B, C;
    iql_t AB, BC, CA;

    A = pl->in_A;
    B = pl->in_B;
    C = pl->in_C;

    AB = A - B;
    BC = B - C;
    CA = C - A;

    pl->out_A = AB;
    pl->out_B = BC;
    pl->out_C = CA;
}
