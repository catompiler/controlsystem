#include "thread_timer.h"
#include <stdio.h>
#include <stddef.h>
#include <errno.h>


//! Складывает две отметки времени.
#define timespecadd(a, b, res)\
            do{\
                (res)->tv_sec = (a)->tv_sec + (b)->tv_sec;\
                (res)->tv_nsec = (a)->tv_nsec + (b)->tv_nsec;\
                if((res)->tv_nsec >= 1000000000){\
                    (res)->tv_sec += 1;\
                    (res)->tv_nsec -= 1000000000;\
                }\
            }while(0);

//! Сравнивает две отметки времени.
#define timespeccmp(lhs, rhs, cmp)\
            (((lhs)->tv_sec == (rhs)->tv_sec) ?\
            ((lhs)->tv_nsec cmp (rhs)->tv_nsec) :\
            ((lhs)->tv_sec cmp (rhs)->tv_sec))


//! Функция потока таймера.
static void* thread_timer_thread_proc(void* arg)
{
    if(arg == NULL){
        #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
        printf("thread arg == NULL\n");
        #endif
        pthread_exit((void*)-1);
    }

    thread_timer_t* thr_tim = (thread_timer_t*)arg;

    int res = 0;
    int end = 0;

    thr_tim->state = THREAD_TIMER_STATE_IDLE;
    //thr_tim->cmd = THREAD_TIMER_CMD_START;

    struct timespec ts = {0, 0};
    struct timespec ts_end = {0, 0};
    #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
    struct timespec ts_start = {0, 0};
    #endif

    #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
    printf("thread begin\n");
    #endif

    for(;end == 0;){
        #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 4
        printf("thread lock mutex\n");
        #endif

        res = pthread_mutex_lock(&thr_tim->cond_mutex);
        if(res != 0){
            #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
            printf("pthread_mutex_lock() == %d\n", res);
            #endif
        }

        switch(thr_tim->cmd){
            default:
            case THREAD_TIMER_CMD_NONE:
                break;

            case THREAD_TIMER_CMD_END:
                #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 2
                printf("thread cmd end\n");
                #endif
                end = 1;
                thr_tim->state = THREAD_TIMER_STATE_NONE;
                break;

            case THREAD_TIMER_CMD_START:
                res = clock_gettime(CLOCK_MONOTONIC, &ts);
                if(res != 0){
                    #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
                    printf("clock_gettime() == %d\n", res);
                    #endif
                }
                #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 2
                printf("thread cmd start\n");
                #endif
                #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
                ts_start.tv_sec = ts.tv_sec;
                ts_start.tv_nsec = ts.tv_nsec;
                #endif
                timespecadd(&ts, &thr_tim->ts_period, &ts_end);
                thr_tim->state = THREAD_TIMER_STATE_RUN;
                break;

            case THREAD_TIMER_CMD_STOP:
                #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 2
                printf("thread cmd stop\n");
                #endif
                thr_tim->state = THREAD_TIMER_STATE_IDLE;
                break;
        }
        thr_tim->cmd = THREAD_TIMER_CMD_NONE;

        #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 4
        printf("thread unlock mutex\n");
        #endif

        res = pthread_mutex_unlock(&thr_tim->cond_mutex);
        if(res != 0){
            #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
            printf("pthread_mutex_unlock() == %d\n", res);
            #endif
        }

        switch(thr_tim->state){
            default:
            case THREAD_TIMER_STATE_NONE:
                break;

            case THREAD_TIMER_STATE_IDLE:
                #if defined(THREAD_TIMER_THREAD_USE_COND_WAIT) && THREAD_TIMER_THREAD_USE_COND_WAIT == 1
                res = clock_gettime(CLOCK_MONOTONIC, &ts);
                if(res != 0){
                    #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
                    printf("clock_gettime() == %d\n", res);
                    #endif
                }
                ts_end.tv_sec = THREAD_TIMER_THREAD_COND_WAIT_TIME_S;
                ts_end.tv_nsec = THREAD_TIMER_THREAD_COND_WAIT_TIME_NS;
                timespecadd(&ts, &ts_end, &ts_end);

                #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 4
                printf("thread lock mutex\n");
                #endif

                res = pthread_mutex_lock(&thr_tim->cond_mutex);
                if(res != 0){
                    #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
                    printf("pthread_mutex_lock() == %d\n", res);
                    #endif
                }

                #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 3
                printf("thread cond timedwait\n");
                #endif

                res = pthread_cond_timedwait(&thr_tim->cond_var, &thr_tim->cond_mutex, &ts_end);
                if(res != 0 && res != ETIMEDOUT){
                    #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 3
                    printf("pthread_cond_timedwait() == %d\n", res);
                    #endif
                }

                #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 4
                printf("thread unlock mutex\n");
                #endif

                res = pthread_mutex_unlock(&thr_tim->cond_mutex);
                if(res != 0){
                    #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
                    printf("pthread_mutex_unlock() == %d\n", res);
                    #endif
                }
                #endif //THREAD_TIMER_THREAD_USE_COND_WAIT
                break;

            case THREAD_TIMER_STATE_RUN:
                res = clock_gettime(CLOCK_MONOTONIC, &ts);
                if(res != 0){
                    #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
                    printf("clock_gettime() == %d\n", res);
                    #endif
                }
                if(timespeccmp(&ts, &ts_end, >=)){
                    #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
                    printf("thread time %ld us\n", (ts.tv_nsec - ts_start.tv_nsec) / 1000);
                    ts_start.tv_sec = ts.tv_sec;
                    ts_start.tv_nsec = ts.tv_nsec;
                    #endif
                    if(!(thr_tim->flags & THREAD_TIMER_FLAG_ONE_SHOT)){
                        #if defined(THREAD_TIMER_RELOAD_RELATIVE_END_TIME) && THREAD_TIMER_RELOAD_RELATIVE_END_TIME == 1
                        timespecadd(&ts_end, &thr_tim->ts_period, &ts_end);
                        #else
                        timespecadd(&ts, &thr_tim->ts_period, &ts_end);
                        #endif
                    }
                    if(thr_tim->callback){
                        thr_tim->callback(thr_tim->callback_arg);
                    }
                    if(thr_tim->flags & THREAD_TIMER_FLAG_ONE_SHOT){
                        #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
                        printf("thread one shot done");
                        #endif
                        thr_tim->state = THREAD_TIMER_STATE_IDLE;
                    }
                }
                break;
        }
    }

    #if defined(THREAD_TIMER_THREAD_DEBUG) && THREAD_TIMER_THREAD_DEBUG >= 1
    printf("thread end\n");
    #endif

    return 0;
}


int thread_timer_init(thread_timer_t* thr_tim)
{
    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
    printf("main timer init\n");
    #endif

    thr_tim->cmd = THREAD_TIMER_CMD_NONE;
    thr_tim->state = THREAD_TIMER_STATE_NONE;
    thr_tim->ts_period.tv_sec = 0;
    thr_tim->ts_period.tv_nsec = 0;
    thr_tim->flags = 0;
    thr_tim->callback = NULL;
    thr_tim->callback_arg = NULL;

    int res = 0;

    res = pthread_mutex_init(&thr_tim->cond_mutex, NULL);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_init() == %d\n", res);
        #endif
        return res;
    }

    #if defined(THREAD_TIMER_THREAD_USE_COND_WAIT) && THREAD_TIMER_THREAD_USE_COND_WAIT == 1
    res = pthread_condattr_init(&thr_tim->cond_attr);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_condattr_init() == %d\n", res);
        #endif
        return res;
    }

    res = pthread_condattr_setclock(&thr_tim->cond_attr, CLOCK_MONOTONIC);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_condattr_setclock() == %d\n", res);
        #endif
        return res;
    }


    res = pthread_cond_init(&thr_tim->cond_var, &thr_tim->cond_attr);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_cond_init() == %d\n", res);
        #endif
        return res;
    }
    #endif //THREAD_TIMER_THREAD_USE_COND_WAIT

    res = pthread_attr_init(&thr_tim->thread_attr);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_attr_init() == %d\n", res);
        #endif
        return res;
    }

    res = pthread_attr_setdetachstate(&thr_tim->thread_attr, PTHREAD_CREATE_JOINABLE);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_attr_setdetachstate() == %d\n", res);
        #endif
        return res;
    }

    res = pthread_create(&thr_tim->thread, &thr_tim->thread_attr, thread_timer_thread_proc, (void*)thr_tim);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_create() == %d\n", res);
        #endif
        return res;
    }

    return 0;
}


int thread_timer_deinit(thread_timer_t* thr_tim)
{
    int res = 0;

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
    printf("main timer deinit\n");
    #endif

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main lock mutex\n");
    #endif
    res = pthread_mutex_lock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_lock() == %d\n", res);
        #endif
        return res;
    }

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 2
    printf("main set end\n");
    #endif
    thr_tim->cmd = THREAD_TIMER_CMD_END;

    #if defined(THREAD_TIMER_THREAD_USE_COND_WAIT) && THREAD_TIMER_THREAD_USE_COND_WAIT == 1
/*
    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main unlock mutex\n");
    #endif
    res = pthread_mutex_unlock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_unlock() == %d\n", res);
        #endif
        return res;
    }


    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main lock mutex\n");
    #endif
    res = pthread_mutex_lock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_lock() == %d\n", res);
        #endif
        return res;
    }
//*/

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 3
    printf("main cond signal\n");
    #endif
    res = pthread_cond_signal(&thr_tim->cond_var);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_cond_signal() == %d\n", res);
        #endif
        return res;
    }
    #endif //THREAD_TIMER_THREAD_USE_COND_WAIT

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main unlock mutex\n");
    #endif
    res = pthread_mutex_unlock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_unlock() == %d\n", res);
        #endif
        return res;
    }


    res = pthread_join(thr_tim->thread, NULL);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_join() == %d\n", res);
        #endif
        return res;
    }

    #if defined(THREAD_TIMER_THREAD_USE_COND_WAIT) && THREAD_TIMER_THREAD_USE_COND_WAIT == 1
    res = pthread_cond_destroy(&thr_tim->cond_var);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_cond_destroy() == %d\n", res);
        #endif
        return res;
    }
    res = pthread_condattr_destroy(&thr_tim->cond_attr);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_condattr_destroy() == %d\n", res);
        #endif
        return res;
    }
    #endif //THREAD_TIMER_THREAD_USE_COND_WAIT

    res = pthread_mutex_destroy(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_destroy() == %d\n", res);
        #endif
        return res;
    }
    res = pthread_attr_destroy(&thr_tim->thread_attr);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_attr_destroy() == %d\n", res);
        #endif
        return res;
    }

    return 0;
}


void thread_timer_set_callback(thread_timer_t* thr_tim, thread_timer_callback_t callback, void* callback_arg)
{
    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
    printf("main timer set callback\n");
    #endif
    thr_tim->callback = callback;
    thr_tim->callback_arg = callback_arg;
}


void thread_timer_set_period(thread_timer_t* thr_tim, struct timespec* tv_period)
{
    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
    printf("main timer set period\n");
    #endif
    if(tv_period == NULL){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("tv_period == NULL\n");
        #endif
        return;
    }

    thr_tim->ts_period.tv_sec = tv_period->tv_sec;
    thr_tim->ts_period.tv_nsec = tv_period->tv_nsec;
}


void thread_timer_set_flags(thread_timer_t* thr_tim, thread_timer_flags_t flags)
{
    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
    printf("main timer set flags\n");
    #endif

    thr_tim->flags = flags;
}


int thread_timer_running(thread_timer_t* thr_tim)
{
    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
    printf("main timer running\n");
    #endif

    if(thr_tim->state == THREAD_TIMER_STATE_RUN
       //|| thr_tim->cmd == THREAD_TIMER_CMD_START
    ){
        return 1;
    }
    return 0;
}


void thread_timer_wait_thread_begin(thread_timer_t* thr_tim)
{
    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
    printf("main timer wait thread begin\n");
    #endif

    for(;;){
        if(thr_tim->state == THREAD_TIMER_STATE_IDLE){
            break;
        }
    }
}


void thread_timer_wait_start(thread_timer_t* thr_tim)
{
    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
    printf("main timer wait start\n");
    #endif

    for(;;){
        if(thr_tim->cmd != THREAD_TIMER_CMD_START){
            break;
        }
        if(thr_tim->state == THREAD_TIMER_STATE_RUN){
            break;
        }
    }
}


void thread_timer_wait_stop(thread_timer_t* thr_tim)
{
    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
    printf("main timer wait stop\n");
    #endif

    for(;;){
        if(thr_tim->cmd != THREAD_TIMER_CMD_STOP){
            break;
        }
        if(thr_tim->state != THREAD_TIMER_STATE_RUN){
            break;
        }
    }
}


int thread_timer_start(thread_timer_t* thr_tim)
{
    int res = 0;

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
    printf("main timer start\n");
    #endif

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main lock mutex\n");
    #endif
    res = pthread_mutex_lock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_lock() == %d\n", res);
        #endif
        return res;
    }

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 2
    printf("main set start\n");
    #endif
    thr_tim->cmd = THREAD_TIMER_CMD_START;

    #if defined(THREAD_TIMER_THREAD_USE_COND_WAIT) && THREAD_TIMER_THREAD_USE_COND_WAIT == 1
/*
    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main unlock mutex\n");
    #endif
    res = pthread_mutex_unlock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_unlock() == %d\n", res);
        #endif
        return res;
    }


    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main lock mutex\n");
    #endif
    res = pthread_mutex_lock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_lock() == %d\n", res);
        #endif
        return res;
    }
//*/

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 3
    printf("main cond signal\n");
    #endif
    res = pthread_cond_signal(&thr_tim->cond_var);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_cond_signal() == %d\n", res);
        #endif
        return res;
    }
    #endif //THREAD_TIMER_THREAD_USE_COND_WAIT

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main unlock mutex\n");
    #endif
    res = pthread_mutex_unlock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_unlock() == %d\n", res);
        #endif
        return res;
    }

    return 0;
}


int thread_timer_stop(thread_timer_t* thr_tim)
{
    int res = 0;

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
    printf("main timer stop\n");
    #endif

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main lock mutex\n");
    #endif
    res = pthread_mutex_lock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_lock() == %d\n", res);
        #endif
        return res;
    }

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 2
    printf("main set stop\n");
    #endif
    thr_tim->cmd = THREAD_TIMER_CMD_STOP;

    #if defined(THREAD_TIMER_THREAD_USE_COND_WAIT) && THREAD_TIMER_THREAD_USE_COND_WAIT == 1
/*
    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main unlock mutex\n");
    #endif
    res = pthread_mutex_unlock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_unlock() == %d\n", res);
        #endif
        return res;
    }


    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main lock mutex\n");
    #endif
    res = pthread_mutex_lock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_lock() == %d\n", res);
        #endif
        return res;
    }
//*/

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 3
    printf("main cond signal\n");
    #endif
    res = pthread_cond_signal(&thr_tim->cond_var);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_cond_signal() == %d\n", res);
        #endif
        return res;
    }
    #endif //THREAD_TIMER_THREAD_USE_COND_WAIT

    #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 4
    printf("main unlock mutex\n");
    #endif
    res = pthread_mutex_unlock(&thr_tim->cond_mutex);
    if(res != 0){
        #if defined(THREAD_TIMER_DEBUG) && THREAD_TIMER_DEBUG >= 1
        printf("pthread_mutex_unlock() == %d\n", res);
        #endif
        return res;
    }

    return 0;
}
