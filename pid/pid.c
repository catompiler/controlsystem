#include "pid.h"
#include "utils/utils.h"


METHOD_INIT_IMPL(M_pid, pid)
{
}

METHOD_DEINIT_IMPL(M_pid, pid)
{
}

static void pid_control(M_pid* pid)
{
    if(pid->control & CONTROL_RESET){
        pid->out_value = 0;
        pid->m_I = 0;
        pid->m_D_z1 = 0;
        pid->m_e_z1 = 0;

        pid->control &= ~CONTROL_RESET;
    }
}

METHOD_CALC_IMPL(M_pid, pid)
{
    iq24_t ref, fbk, e, de;
    iq24_t Kp, Ki, Kd, Kf;
    iq24_t maxval, minval;
    iq24_t I_z1, D_z1, e_z1;
    iq24_t P, I, D;
    iq24_t res, tmp;

    pid_control(pid);

    if(!(pid->control & CONTROL_ENABLE)){
        return;
    }

    ref = pid->in_ref;
    fbk = pid->in_fbk;

    Kp = pid->r_kp;
    Ki = pid->r_ki;
    Kd = pid->r_kd;
    Kf = pid->r_kf;

    minval = pid->r_min;
    maxval = pid->r_max;

    I_z1 = pid->m_I;
    D_z1 = pid->m_D_z1;
    e_z1 = pid->m_e_z1;

    res = 0;

    // e = ref - fbk.
    e = iq24_sub_sat(ref, fbk);

    if(Kp != 0){
        // P = Kp * e.
        P = iq24_mul_sat(Kp, e);
        res = iq24_add_sat(res, P);
    }

    if(Ki != 0){
        // I = Ki * e + I_z1.
        I = iq24_mul_sat(Ki, e);
        I = iq24_add_sat(I, I_z1);
        I = CLAMP(I, minval, maxval);
        res = iq24_add_sat(res, I);
    }

    if(Kd != 0){
        // de = e - e_z1.
        de  = iq24_sub_sat(e, e_z1);
        // D = Kd * de + Kf * D_z1.
        D   = iq24_mul_sat(Kd, de);
        if(Kf != 0){
            tmp = iq24_mul_sat(Kf, D_z1);
            D   = iq24_add_sat(D, tmp);
        }
        res = iq24_add_sat(res, D);
    }

    res = CLAMP(res, minval, maxval);

    pid->out_value = res;

    pid->m_I = I;
    pid->m_e_z1 = e;
    pid->m_D_z1 = D;
}

METHOD_CONTROL_IMPL(M_pid, pid)
{
    pid_control(pid);
}
