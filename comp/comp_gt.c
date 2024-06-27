#include "comp_gt.h"


METHOD_INIT_IMPL(M_comp_gt, cmp)
{
}

METHOD_DEINIT_IMPL(M_comp_gt, cmp)
{
}

METHOD_CALC_IMPL(M_comp_gt, cmp)
{
    cmp->out_value = (cmp->in_A > cmp->in_B) ? FLAG_ACTIVE : FLAG_NONE;
}
