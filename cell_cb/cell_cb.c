#include "cell_cb.h"


METHOD_INIT_IMPL(M_cell_cb, cb)
{
}

METHOD_DEINIT_IMPL(M_cell_cb, cb)
{
}

METHOD_CALC_IMPL(M_cell_cb, cb)
{
    flag_t no, nc;
    cell_cb_state_t res;

    no = cb->in_no_state & FLAG_ACTIVE;
    nc = cb->in_nc_state & FLAG_ACTIVE;

    res = (nc << 1) | no;

    cb->out_state = res;
}
