#ifndef FAKE_ADC_H
#define FAKE_ADC_H


#define ADC_AC_FREQ (50)
#define ADC_SAMPLES_PER_PERIOD (32)
#define ADC_SAMPLES_FREQ (ADC_AC_FREQ * ADC_SAMPLES_PER_PERIOD)
#define ADC_SAMPLES_PERIOD_US (1000000 / ADC_SAMPLES_FREQ)
#define ADC_SAMPLES_PERIOD_NS (ADC_SAMPLES_PERIOD_US * 1000)


typedef struct _FAKE_ADC FAKE_ADC;

struct _FAKE_ADC {
};


#endif //FAKE_ADC_H
