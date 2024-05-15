#include "park.h"


METHOD_INIT_IMPL(M_park, pk)
{
}

METHOD_DEINIT_IMPL(M_park, pk)
{
}

METHOD_CALC_IMPL(M_park, pk)
{
//    pk->out_A =   pk->in_A * pk->in_cos_angle + pk->in_B * pk->in_sin_angle;
//    pk->out_B = - pk->in_A * pk->in_sin_angle + pk->in_B * pk->in_cos_angle;

    iq24_t A, B;
    iq24_t cos_angle, sin_angle;

    iq24_t A_cos, A_sin;
    iq24_t B_cos, B_sin;

    iq24_t res_A, res_B;

    A = pk->in_A;
    B = pk->in_B;
    cos_angle = pk->in_cos_angle;
    sin_angle = pk->in_sin_angle;

    A_cos = iq24_mul(A, cos_angle);
    A_sin = iq24_mul(A, sin_angle);
    B_cos = iq24_mul(B, cos_angle);
    B_sin = iq24_mul(B, sin_angle);

    res_A = iq24_add(A_cos, B_sin);
    res_B = iq24_sub(B_cos, A_sin);

    pk->out_A = res_A;
    pk->out_B = res_B;
}
