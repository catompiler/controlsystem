/**
 * @file sys_counter.h Библиотека таймера высокого разрешения.
 */

#ifndef SYSTEM_COUNTER_POSIX_H
#define SYSTEM_COUNTER_POSIX_H

#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>
#include "defs/defs.h"


// Параметры таймера.
//! Период таймера в тиках.
#define SYS_COUNTER_PERIOD_TICKS 1000000



/**
 * Инициализирует высокоточный таймер привода.
 * @param TIM Периферия таймера.
 * @return Код ошибки.
 */
EXTERN void sys_counter_init(void);

/**
 * Устанавливает разрешение прерывания переполнения таймера.
 * @param enabled Флаг разрешения прерывания.
 */
EXTERN void sys_counter_irq_set_enabled(bool enabled);

/**
 * Получает разрешение прерывания переполнения таймера.
 * @return Флаг разрешения прерывания.
 */
EXTERN bool sys_counter_irq_enabled(void);

/**
 * Включает прерывание таймера.
 */
EXTERN void sys_counter_irq_enable(void);

/**
 * Выключает прерывание таймера.
 */
EXTERN void sys_counter_irq_disable(void);

/**
 * Устанавливает флаг работы таймера.
 * @param running Флаг работы таймера.
 */
EXTERN void sys_counter_set_running(bool running);

/**
 * Получает флаг работы таймера.
 * @return Флаг работы таймера.
 */
EXTERN bool sys_counter_running(void);

/**
 * Запускает таймер.
 */
EXTERN void sys_counter_start(void);

/**
 * Останавливает таймер.
 */
EXTERN void sys_counter_stop(void);

/**
 * Сбрасывает счётчик таймера.
 */
EXTERN void sys_counter_reset(void);

/**
 * Получает время работы таймера.
 * Переполняется каждые 4294967296 секунд.
 * @param tv Время.
 */
EXTERN void sys_counter_value(struct timeval* tv);

/**
 * Функция задержки
 * @param sec Время задержки в секундах.
 * @param usec Время задержки в микросекундах.
 */
EXTERN void sys_counter_delay(struct timeval* tv);


#if defined(SYS_COUNTER_CLOCK_GETTIME) && SYS_COUNTER_CLOCK_GETTIME == 1

#include <time.h>

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

EXTERN int clock_gettime (clockid_t clock_id, struct timespec *tp);

#endif // SYS_COUNTER_CLOCK_GETTIME

#endif /* SYSTEM_COUNTER_POSIX_H */

