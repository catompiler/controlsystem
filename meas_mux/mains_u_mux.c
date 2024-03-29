#include "mains_u_mux.h"
#include "utils/utils.h"


METHOD_INIT_IMPL(M_mains_u_mux, mux)
{
}

METHOD_DEINIT_IMPL(M_mains_u_mux, mux)
{
}

METHOD_CALC_IMPL(M_mains_u_mux, mux)
{
    uint32_t sel = MIN(mux->p_sel, MAINS_U_MUX_INPUTS-1);

    mux->out_Ua = mux->in_Ua[sel];
    mux->out_Ub = mux->in_Ub[sel];
    mux->out_Uc = mux->in_Uc[sel];
}
