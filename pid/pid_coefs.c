#include "pid_coefs.h"


METHOD_INIT_IMPL(M_pid_coefs, coefs)
{
    IDLE((*coefs));
}

METHOD_DEINIT_IMPL(M_pid_coefs, coefs)
{
}

METHOD_IDLE_IMPL(M_pid_coefs, coefs)
{
    iq24_t Kp, Ki, Kd, Kf;
    iq24_t Ts, Ti, Td, Tf;

    iq24_t tmp, Tf_Ts;

    Kp = coefs->p_kp;
    Ts = coefs->r_Ts;
    Ti = coefs->p_Ti;
    Td = coefs->p_Td;
    Tf = coefs->p_Tf;

    Ki = 0;
    Kd = 0;
    Kf = 0;

    Tf_Ts = iq24_add(Tf, Ts);

    // Kp = Kp.
    // Kp = Kp;

    if(Ts != 0){
        if(Ti != 0){
            // Ki = Kp * Ts / Ti.
            tmp = iq24_mul_sat(Kp, Ts);
            Ki  = iq24_div_sat(tmp, Ti);
        }

        if(Td != 0){
            // Kd = Kp * Td / (Tf + Ts).
            tmp = iq24_div_sat(Td, Tf_Ts);
            Kd  = iq24_mul_sat(Kp, tmp);

            if(Tf != 0){
                // Kf = Kp * Tf / (Tf + Ts).
                tmp = iq24_div_sat(Tf, Tf_Ts);
                Kf  = iq24_mul_sat(Kp, tmp);
            }
        }
    }

    coefs->out_kp = Kp;
    coefs->out_ki = Ki;
    coefs->out_kd = Kd;
    coefs->out_kf = Kf;
}
