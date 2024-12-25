#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include "sys_counter.h"


#if !__BSD_VISIBLE
#ifndef _KERNEL         /* NetBSD/OpenBSD compatible interfaces */

#define timerclear(tvp)     ((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define timerisset(tvp)     ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp)                 \
    (((tvp)->tv_sec == (uvp)->tv_sec) ?             \
        ((tvp)->tv_usec cmp (uvp)->tv_usec) :           \
        ((tvp)->tv_sec cmp (uvp)->tv_sec))
#define timeradd(tvp, uvp, vvp)                     \
    do {                                \
        (vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec;      \
        (vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec;   \
        if ((vvp)->tv_usec >= 1000000) {            \
            (vvp)->tv_sec++;                \
            (vvp)->tv_usec -= 1000000;          \
        }                           \
    } while (0)
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
#endif /* __BSD_VISIBLE */




void sys_counter_init(void)
{
}

void sys_counter_irq_set_enabled(bool enabled)
{
}

bool sys_counter_irq_enabled(void)
{
    return false;
}

void sys_counter_irq_enable(void)
{
}

void sys_counter_irq_disable(void)
{
}

void sys_counter_set_running(bool running)
{
    (void) running;
}

bool sys_counter_running(void)
{
    return true;
}

void sys_counter_start(void)
{
}

void sys_counter_stop(void)
{
}

void sys_counter_reset(void)
{
}

__attribute__((noinline))
void sys_counter_value(struct timeval* tv)
{
    if(tv == NULL) return;
    
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    
    tv->tv_sec = tp.tv_sec;
    tv->tv_usec = tp.tv_nsec / 1000;
}

void sys_counter_delay(struct timeval* tv)
{
	struct timeval tv_cur;
    struct timeval tv_dt;
    struct timeval tv_end;

    tv_dt.tv_sec = tv->tv_sec;
    tv_dt.tv_usec = tv->tv_usec;

    sys_counter_value(&tv_cur);
    timeradd(&tv_cur, &tv_dt, &tv_end);

    for(;;){
		if(timercmp(&tv_cur, &tv_end, >=)){
			break;
		}
    	sys_counter_value(&tv_cur);
    }
}

#if defined(SYS_COUNTER_CLOCK_GETTIME) && SYS_COUNTER_CLOCK_GETTIME == 1

int clock_gettime (clockid_t clock_id, struct timespec *tp)
{
    if(clock_id != CLOCK_MONOTONIC){
        errno = EINVAL;
        return -1;
    }
    if(tp == NULL){
        errno = EFAULT;
        return -1;
    }

    struct timeval tv;
    sys_counter_value(&tv);

    tp->tv_sec = tv.tv_sec;
    tp->tv_nsec = tv.tv_usec * 1000;

    return 0;
}

#endif
