#include "mains_i_mux.h"
#include "utils/utils.h"


METHOD_INIT_IMPL(M_mains_i_mux, mux)
{
}

METHOD_DEINIT_IMPL(M_mains_i_mux, mux)
{
}

METHOD_CALC_IMPL(M_mains_i_mux, mux)
{
    uint32_t sel = MIN(mux->p_sel, MAINS_I_MUX_INPUTS-1);

    mux->out_Ia = mux->in_Ia[sel];
    mux->out_Ib = mux->in_Ib[sel];
    mux->out_Ic = mux->in_Ic[sel];
}
