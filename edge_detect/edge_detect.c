#include "edge_detect.h"


METHOD_INIT_IMPL(M_edge_detect, ed)
{
}

METHOD_DEINIT_IMPL(M_edge_detect, ed)
{
}

METHOD_CALC_IMPL(M_edge_detect, ed)
{
    flag_t b0 = (ed->in_value & FLAG_ACTIVE);
    flag_t b1 = ed->m_b0_z1;

    ed->m_b0_z1 = b0;
    ed->out_value = ((b1 << 1) | b0);
}
