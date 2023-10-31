#include "phase_ampl.h"
#include "bits/bits.h"
#include "iqmath/iqmath.h"
#include "phase_ampl_cmplx_sin_table.h"


//
// Возможно, в случае необходимости,
// реализовать алгоритм Гёрцеля.
// https://ru.dsplib.org/content/goertzel/goertzel.html
//


METHOD_INIT_IMPL(M_phase_ampl, pa)
{
    pa->m_count = 0;
    pa->m_get_index = 0;
    pa->m_put_index = 0;
}

METHOD_DEINIT_IMPL(M_phase_ampl, pa)
{
}

#define USE_64BIT_LOAD 0

#if defined(USE_64BIT_LOAD) && USE_64BIT_LOAD == 1
ALWAYS_INLINE static void phase_ampl_move_blocks(M_phase_ampl* pa)
{
    uint64_t* ptr_wr = (uint64_t*)&pa->m_data[0];
    uint64_t* ptr_rd = (uint64_t*)&pa->m_data[PHASE_AMPL_BLOCK_LEN];

    int i;
    #pragma GCC unroll 8
    for(i = 0; i < (PHASE_AMPL_SAMPLES_COUNT / PHASE_AMPL_BLOCK_LEN); i ++){
        *ptr_wr ++ = *ptr_rd ++;
    }
}
#else  //USE_64BIT_LOAD
ALWAYS_INLINE static void phase_ampl_move_blocks(M_phase_ampl* pa)
{
    uint32_t* ptr_wr = (uint32_t*)&pa->m_data[0];
    uint32_t* ptr_rd = (uint32_t*)&pa->m_data[PHASE_AMPL_BLOCK_LEN];

    int i;
    #pragma GCC unroll 8
    for(i = 0; i < (PHASE_AMPL_SAMPLES_COUNT / PHASE_AMPL_BLOCK_LEN); i ++){
        *ptr_wr ++ = *ptr_rd ++;
#if PHASE_AMPL_BLOCK_SIZE >= 8
        *ptr_wr ++ = *ptr_rd ++;
#endif
#if PHASE_AMPL_BLOCK_SIZE >= 12
        *ptr_wr ++ = *ptr_rd ++;
#endif
#if PHASE_AMPL_BLOCK_SIZE >= 16
        *ptr_wr ++ = *ptr_rd ++;
#endif
    }
}
#endif  //USE_64BIT_LOAD


static void calc_phase_ampl(M_phase_ampl* pa)
{
#if defined(USE_64BIT_LOAD) && USE_64BIT_LOAD == 1

    const int64_t* pcmplx_sin = (int64_t*)&phase_ampl_cmplx_sin_table[0];
    int32_t* pvalues = (int32_t*)&pa->m_data[pa->m_get_index];

    union _U_64 {
        struct _S_64 {
            int32_t lo;
            int32_t hi;
        } w;
        int64_t all;
    } cdw;
    int32_t xw;

    int64_t acc_r = 0;
    int64_t acc_i = 0;

    int i;
    #pragma GCC unroll 8
    for(i = 0; i < (PHASE_AMPL_SAMPLES_COUNT / PHASE_AMPL_BLOCK_LEN); i ++){
        // x0, x1
        cdw.all = *pcmplx_sin ++;
        xw = *pvalues ++;
        acc_r = __SMLALD(cdw.w.lo, xw, acc_r);
        acc_i = __SMLALD(cdw.w.hi, xw, acc_i);
        // x2, x3
        cdw.all = *pcmplx_sin ++;
        xw = *pvalues ++;
        acc_r = __SMLALD(cdw.w.lo, xw, acc_r);
        acc_i = __SMLALD(cdw.w.hi, xw, acc_i);
    }

#else  //USE_64BIT_LOAD

    const int32_t* pcmplx_sin = (int32_t*)&phase_ampl_cmplx_sin_table[0];
    int32_t* pvalues = (int32_t*)&pa->m_data[pa->m_get_index];

    int32_t crw;
    int32_t ciw;
    int32_t xw;

    int64_t acc_r = 0;
    int64_t acc_i = 0;

    int i;
    #pragma GCC unroll 8
    for(i = 0; i < (PHASE_AMPL_SAMPLES_COUNT / PHASE_AMPL_BLOCK_LEN); i ++){
        // x0, x1
        crw = *pcmplx_sin ++;
        ciw = *pcmplx_sin ++;
        xw = *pvalues ++;

        acc_r = __SMLALD(crw, xw, acc_r);
        acc_i = __SMLALD(ciw, xw, acc_i);

        // x1, x2
        crw = *pcmplx_sin ++;
        ciw = *pcmplx_sin ++;
        xw = *pvalues ++;

        acc_r = __SMLALD(crw, xw, acc_r);
        acc_i = __SMLALD(ciw, xw, acc_i);
    }

#endif  //USE_64BIT_LOAD

#if IS_POW2(PHASE_AMPL_SAMPLES_COUNT/2)
    // iq(PHASE_AMPL_DATA_SAT_BIT + PHASE_AMPL_CMPLX_SIN_TABLE_FRACT_BITS) -> iq24 and / (L/2).
    acc_r >>= (PHASE_AMPL_DATA_FRACT_BITS + PHASE_AMPL_CMPLX_SIN_TABLE_FRACT_BITS - IQ24_FRACT_BITS + GET_POW2(PHASE_AMPL_SAMPLES_COUNT/2));
    acc_i >>= (PHASE_AMPL_DATA_FRACT_BITS + PHASE_AMPL_CMPLX_SIN_TABLE_FRACT_BITS - IQ24_FRACT_BITS + GET_POW2(PHASE_AMPL_SAMPLES_COUNT/2));
#else //IS_POW2(PHASE_AMPL_SAMPLES_COUNT)
    // iq(PHASE_AMPL_DATA_SAT_BIT + PHASE_AMPL_CMPLX_SIN_TABLE_FRACT_BITS) -> iq24.
    acc_r >>= (PHASE_AMPL_DATA_FRACT_BITS + PHASE_AMPL_CMPLX_SIN_TABLE_FRACT_BITS - IQ24_FRACT_BITS);
    acc_i >>= (PHASE_AMPL_DATA_FRACT_BITS + PHASE_AMPL_CMPLX_SIN_TABLE_FRACT_BITS - IQ24_FRACT_BITS);
    // acc / (L/2)
    acc_r /= (PHASE_AMPL_SAMPLES_COUNT/2);
    acc_i /= (PHASE_AMPL_SAMPLES_COUNT/2);
#endif //IS_POW2(PHASE_AMPL_SAMPLES_COUNT)

    //printf("%d, %d\n", (int)acc_r, (int)acc_i);

    iq24_t x = (iq24_t)acc_r;
    iq24_t y = (iq24_t)acc_i;

    iq24_t angle = 0;
    iq24_t hyp = 0;

    iq24_cordic_atan2_hyp_pu(x, y, &angle, &hyp);

    // Коррекция на фазу между двумя точками.
    angle -= IQ24_2PI_PU / PHASE_AMPL_SAMPLES_COUNT;

    // Приведение к интервалу [0; 2*pi).
    if(angle > IQ24_2PI_PU) angle -= IQ24_2PI_PU;
    if(angle < 0) angle += IQ24_2PI_PU;

    pa->out_phase = angle;
    pa->out_ampl = hyp;
}

METHOD_CALC_IMPL(M_phase_ampl, pa)
{
    if(!(pa->control & CONTROL_ENABLE)) return;

    iq14l_t iq_pa_val = __SSAT_ASR(pa->in_value,
                                     PHASE_AMPL_DATA_SAT_BIT,
                                     IQ24_FRACT_BITS - PHASE_AMPL_DATA_FRACT_BITS);

    /*static iq15_t angle = 0;
    iq_pa_val = iq15_sin_pu(angle);
    angle += IQ15_2PI_PU / PHASE_AMPL_SAMPLES_COUNT;*/
    //pa->out_value = iq_pa_val << (IQ24_FRACT_BITS - PHASE_AMPL_DATA_FRACT_BITS);

    pa->m_data[pa->m_put_index] = (phase_ampl_data_t)iq_pa_val;

    // Индекс записи в конце буфера.
    if(pa->m_put_index == (PHASE_AMPL_LEN - 1)){
        // Перемещаем блоки буфера.
        phase_ampl_move_blocks(pa);
        pa->m_get_index = 0;
        pa->m_put_index = PHASE_AMPL_SAMPLES_COUNT;
    }else{
        pa->m_put_index ++;

        if(pa->m_put_index > PHASE_AMPL_SAMPLES_COUNT){
            pa->m_get_index ++;
        }
    }

    if(pa->m_count < PHASE_AMPL_SAMPLES_COUNT) pa->m_count ++;

    // calc.
    calc_phase_ampl(pa);

    if(pa->m_count == PHASE_AMPL_SAMPLES_COUNT){
        pa->status = STATUS_VALID;
    }
}
