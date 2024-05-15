#include "clarke_inv.h"
#include "iqmath/iqmath.h"


#define HALF_SQRT3 (IQ24_SQRT3 >> 1)


METHOD_INIT_IMPL(M_clarke_inv, cl)
{
}

METHOD_DEINIT_IMPL(M_clarke_inv, cl)
{
}

METHOD_CALC_IMPL(M_clarke_inv, cl)
{
//    SQRT3 = sqrt(3);
//
//    cl->out_A = cl->in_A;
//    cl->out_B =  0.5 * (SQRT3 * cl->in_B - cl->in_A);
//    cl->out_C = -0.5 * (SQRT3 * cl->in_B + cl->in_A);

    iq24_t A, B;
    iq24_t res_A, res_B, res_C;

    A = cl->in_A;
    B = cl->in_B;

    iq24_t half_sqrt3_in_B = iq24_mul(HALF_SQRT3, B);
    iq24_t half_in_A = A >> 1;

    res_A =  A;
    res_B =  iq24_sub(half_sqrt3_in_B, half_in_A);
    res_C = -iq24_add(half_sqrt3_in_B, half_in_A);

    cl->out_A = res_A;
    cl->out_B = res_B;
    cl->out_C = res_C;
}
