#include "dac.h"
#include "cpu.h"
#include "utils/utils.h"


//! Средняя точка.
#define DAC_OFFSET 2048
//! Амплитуда.
#define DAC_AMPL 2048
//! Минимальное значение.
#define DAC_MIN 0
//! Максимальное значение.
#define DAC_MAX 4095


METHOD_INIT_IMPL(M_dac, dac)
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#if (defined(DAC_CHANNEL0_ENABLED) && DAC_CHANNEL0_ENABLED == 1) ||\
    (defined(DAC_CHANNEL1_ENABLED) && DAC_CHANNEL1_ENABLED == 1)
    DAC->DAC01DATA = 0;
#endif
#if defined(DAC_CHANNEL0_ENABLED) && DAC_CHANNEL0_ENABLED == 1
    DAC->DAC0CFG0 = ((0b001) << DAC_DAC0CFG0_MODE_Pos) | // Single value.
                    ((0) << DAC_DAC0CFG0_SIGN_Pos); // Unsigned, 1 - signed input data.

    DAC->DAC0CFG1 = ((0b00) << DAC_DAC0CFG1_TRIGMOD_Pos) | // Internal.
                    ((1) << DAC_DAC0CFG1_ANAEN_Pos); // Enable.
    DAC->DAC0DATA = 0;
#endif
#if defined(DAC_CHANNEL1_ENABLED) && DAC_CHANNEL1_ENABLED == 1
    DAC->DAC1CFG0 = ((0b001) << DAC_DAC1CFG0_MODE_Pos) | // Single value.
                    ((0) << DAC_DAC1CFG0_SIGN_Pos); // Unsigned, 1 - signed input data.

    DAC->DAC1CFG1 = ((0b00) << DAC_DAC1CFG1_TRIGMOD_Pos) | // Internal.
                    ((1) << DAC_DAC1CFG1_ANAEN_Pos); // Enable.
    DAC->DAC1DATA = 0;
#endif
#endif
}

METHOD_DEINIT_IMPL(M_dac, dac)
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#if defined(DAC_CHANNEL0_ENABLED) && DAC_CHANNEL0_ENABLED == 1
    DAC->DAC0CFG1 = 0;
    DAC->DAC0CFG0 = 0;
#endif
#if defined(DAC_CHANNEL1_ENABLED) && DAC_CHANNEL1_ENABLED == 1
    DAC->DAC1CFG1 = 0;
    DAC->DAC1CFG0 = 0;
#endif
#endif
}

METHOD_CALC_IMPL(M_dac, dac)
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#if (defined(DAC_CHANNEL0_ENABLED) && DAC_CHANNEL0_ENABLED == 1) ||\
    (defined(DAC_CHANNEL1_ENABLED) && DAC_CHANNEL1_ENABLED == 1)
    iq24_t val;
    int32_t dacval;
#endif

#if defined(DAC_CHANNEL0_ENABLED) && DAC_CHANNEL0_ENABLED == 1
    val = dac->in_value[0];

    dacval = iq24_mul(val, DAC_AMPL);
    dacval = dacval + DAC_OFFSET;
    dacval = CLAMP(dacval, DAC_MIN, DAC_MAX);

    DAC->DAC0DATA = (uint32_t)dacval;
#endif
#if defined(DAC_CHANNEL1_ENABLED) && DAC_CHANNEL1_ENABLED == 1
    val = dac->in_value[1];

    dacval = iq24_mul(val, DAC_AMPL);
    dacval = dacval + DAC_OFFSET;
    dacval = CLAMP(dacval, DAC_MIN, DAC_MAX);

    DAC->DAC1DATA = (uint32_t)dacval;
#endif
#endif
}
