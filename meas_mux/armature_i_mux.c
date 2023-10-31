#include "armature_i_mux.h"
#include "utils/utils.h"


METHOD_INIT_IMPL(M_armature_i_mux, mux)
{
}

METHOD_DEINIT_IMPL(M_armature_i_mux, mux)
{
}

METHOD_CALC_IMPL(M_armature_i_mux, mux)
{
    uint32_t sel = CLAMP(mux->p_sel, 0, ARMATURE_I_MUX_INPUTS);

    mux->out_Iarm = mux->in_Iarm[sel];
}
