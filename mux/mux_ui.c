#include "mux_ui.h"
#include <stddef.h>
#include "bits/bits.h"
#include "utils/utils.h"



METHOD_INIT_IMPL(M_mux_ui, mux)
{
}

METHOD_DEINIT_IMPL(M_mux_ui, mux)
{
}

METHOD_CALC_IMPL(M_mux_ui, mux)
{
    size_t sel = mux->p_sel;

    iql_t U, I;

#if IS_POW2(MUX_UI_INPUTS)
    sel = sel & ((1 << GET_POW2(MUX_UI_INPUTS)) - 1);
#else //IS_POW2(MUX_UI_INPUTS)
    sel = MIN(sel, MUX_UI_INPUTS-1);
#endif

    U = mux->in_U[sel];
    I = mux->in_I[sel];

    mux->out_U = U;
    mux->out_I = I;
}
