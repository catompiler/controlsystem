#include "armature_u_mux.h"
#include "utils/utils.h"


METHOD_INIT_IMPL(M_armature_u_mux, mux)
{
}

METHOD_DEINIT_IMPL(M_armature_u_mux, mux)
{
}

METHOD_CALC_IMPL(M_armature_u_mux, mux)
{
    uint32_t sel = CLAMP(mux->p_sel, 0, ARMATURE_U_MUX_INPUTS);

    mux->out_Uarm = mux->in_Uarm[sel];
}
