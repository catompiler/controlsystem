#include "mux_abc.h"
#include <stddef.h>
#include "bits/bits.h"
#include "utils/utils.h"



METHOD_INIT_IMPL(M_mux_abc, mux)
{
}

METHOD_DEINIT_IMPL(M_mux_abc, mux)
{
}

METHOD_CALC_IMPL(M_mux_abc, mux)
{
    size_t sel = mux->p_sel;

    iql_t A, B, C;

#if IS_POW2(MUX_ABC_INPUTS)
    sel = sel & ((1 << GET_POW2(MUX_ABC_INPUTS)) - 1);
#else //IS_POW2(MUX_ABC_INPUTS)
    sel = MIN(sel, MUX_ABC_INPUTS-1);
#endif

    A = mux->in_A[sel];
    B = mux->in_B[sel];
    C = mux->in_C[sel];

    mux->out_A = A;
    mux->out_B = B;
    mux->out_C = C;
}
