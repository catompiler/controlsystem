#if defined(PORT_POSIX)

/**
 * @file sys_counter.h Библиотека таймера высокого разрешения.
 */

#ifndef SYSTEM_COUNTER_POSIX_H
#define SYSTEM_COUNTER_POSIX_H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
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


// From time.h

/* Operations on timespecs */
#ifndef timespecclear
#define timespecclear(tvp)  ((tvp)->tv_sec = (tvp)->tv_nsec = 0)
#endif

#ifndef timespecisset
#define timespecisset(tvp)  ((tvp)->tv_sec || (tvp)->tv_nsec)
#endif

#ifndef timespeccmp
#define timespeccmp(tvp, uvp, cmp)                  \
    (((tvp)->tv_sec == (uvp)->tv_sec) ?             \
        ((tvp)->tv_nsec cmp (uvp)->tv_nsec) :           \
        ((tvp)->tv_sec cmp (uvp)->tv_sec))
#endif

#ifndef timespecadd
#define timespecadd(tsp, usp, vsp)                  \
    do {                                \
        (vsp)->tv_sec = (tsp)->tv_sec + (usp)->tv_sec;      \
        (vsp)->tv_nsec = (tsp)->tv_nsec + (usp)->tv_nsec;   \
        if ((vsp)->tv_nsec >= 1000000000L) {            \
            (vsp)->tv_sec++;                \
            (vsp)->tv_nsec -= 1000000000L;          \
        }                           \
    } while (0)
#endif

#ifndef timespecsub
#define timespecsub(tsp, usp, vsp)                  \
    do {                                \
        (vsp)->tv_sec = (tsp)->tv_sec - (usp)->tv_sec;      \
        (vsp)->tv_nsec = (tsp)->tv_nsec - (usp)->tv_nsec;   \
        if ((vsp)->tv_nsec < 0) {               \
            (vsp)->tv_sec--;                \
            (vsp)->tv_nsec += 1000000000L;          \
        }                           \
    } while (0)
#endif

/* Operations on timeval */
#ifndef timerclear
#define timerclear(tvp)     ((tvp)->tv_sec = (tvp)->tv_usec = 0)
#endif

#ifndef timerisset
#define timerisset(tvp)     ((tvp)->tv_sec || (tvp)->tv_usec)
#endif

#ifndef timercmp
#define timercmp(tvp, uvp, cmp)                 \
    (((tvp)->tv_sec == (uvp)->tv_sec) ?             \
        ((tvp)->tv_usec cmp (uvp)->tv_usec) :           \
        ((tvp)->tv_sec cmp (uvp)->tv_sec))
#endif

#ifndef timeradd
#define timeradd(tvp, uvp, vvp)                     \
    do {                                \
        (vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec;      \
        (vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec;   \
        if ((vvp)->tv_usec >= 1000000) {            \
            (vvp)->tv_sec++;                \
            (vvp)->tv_usec -= 1000000;          \
        }                           \
    } while (0)
#endif

#ifndef timersub
#define timersub(tvp, uvp, vvp)                     \
    do {                                \
        (vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;      \
        (vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;   \
        if ((vvp)->tv_usec < 0) {               \
            (vvp)->tv_sec--;                \
            (vvp)->tv_usec += 1000000;          \
        }                           \
    } while (0)
#endif

#endif /* SYSTEM_COUNTER_POSIX_H */

#endif
