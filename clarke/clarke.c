#include "clarke.h"
#include "iqmath/iqmath.h"


METHOD_INIT_IMPL(M_clarke, cl)
{
}

METHOD_DEINIT_IMPL(M_clarke, cl)
{
}

METHOD_CALC_IMPL(M_clarke, cl)
{
//    INV_SQRT3 = 1.0/sqrt(3);
//
//    cl->out_A = cl->in_A;
//    cl->out_B = (cl->in_B - cl->in_C) * INV_SQRT3;

    iq24_t A, B, C;
    iq24_t res_A, res_B;

    A = cl->in_A;
    B = cl->in_B;
    C = cl->in_C;

    res_A = A;
    res_B = iq24_sub(B, C);
    res_B = iq24_mul(res_B, IQ24_INV_SQRT3);

    cl->out_A = res_A;
    cl->out_B = res_B;
}
