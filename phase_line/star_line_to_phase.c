#include "star_line_to_phase.h"
#include "iqmath/iqmath.h"


// Косинус и синус угла pi/6.
#define COS_PI6 (0xDDB3D7)
#define SIN_PI6 (0x800000)


METHOD_INIT_IMPL(M_star_line_to_phase, lp)
{
    INIT(lp->m_clarke);
    INIT(lp->m_park);
    INIT(lp->m_clarke_inv);
}

METHOD_DEINIT_IMPL(M_star_line_to_phase, lp)
{
    DEINIT(lp->m_clarke);
    DEINIT(lp->m_park);
    DEINIT(lp->m_clarke_inv);
}

METHOD_CALC_IMPL(M_star_line_to_phase, lp)
{
    iq24_t AB, BC, CA;
    iq24_t A, B, C;
    iq24_t alpha, beta;
    iq24_t alpha_rot, beta_rot;

    AB = lp->in_A;
    BC = lp->in_B;
    CA = lp->in_C;

    lp->m_clarke.in_A = AB;
    lp->m_clarke.in_B = BC;
    lp->m_clarke.in_C = CA;
    CALC(lp->m_clarke);

    alpha = lp->m_clarke.out_A;
    beta  = lp->m_clarke.out_B;

    lp->m_park.in_A = alpha;
    lp->m_park.in_B = beta;
    lp->m_park.in_cos_angle = COS_PI6;
    lp->m_park.in_sin_angle = SIN_PI6;
    CALC(lp->m_park);

    alpha_rot = lp->m_park.out_A;
    beta_rot  = lp->m_park.out_B;

    alpha_rot = iq24_mul(alpha_rot, IQ24_INV_SQRT3);
    beta_rot  = iq24_mul(beta_rot, IQ24_INV_SQRT3);

    lp->m_clarke_inv.in_A = alpha_rot;
    lp->m_clarke_inv.in_B = beta_rot;
    CALC(lp->m_clarke_inv);

    A = lp->m_clarke_inv.out_A;
    B = lp->m_clarke_inv.out_B;
    C = lp->m_clarke_inv.out_C;

    lp->out_A = A;
    lp->out_B = B;
    lp->out_C = C;
}
