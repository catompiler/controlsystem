#include "prot.h"


static status_t recalc_values(M_prot* prot)
{
    status_t res_status = STATUS_READY;

    return res_status;
}


METHOD_INIT_IMPL(M_prot, prot)
{
    IDLE((*prot));
}

METHOD_DEINIT_IMPL(M_prot, prot)
{
}

METHOD_CALC_IMPL(M_prot, prot)
{
}

METHOD_IDLE_IMPL(M_prot, prot)
{
    recalc_values(prot);
}
