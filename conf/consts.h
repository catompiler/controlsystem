#ifndef CONF_CONSTS_H_
#define CONF_CONSTS_H_

/*
 * Конфигурационные константы.
 */

//! Частота сети.
#define CONF_MAINS_FREQ (50)

//! Число семплов за период сети.
#define CONF_PERIOD_SAMPLES (72)

//! Частота дискретизации.
#define CONF_SAMPLE_RATE (CONF_MAINS_FREQ * CONF_PERIOD_SAMPLES)


#endif /* CONF_CONSTS_H_ */
