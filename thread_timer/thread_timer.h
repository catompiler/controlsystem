#ifndef THREAD_TIMER_H
#define THREAD_TIMER_H

#include <pthread.h>
#include <time.h>


//! Использовать ли ожидание условной переменной.
//! 1 - да.
//! 0, либо не определено - нет.
#define THREAD_TIMER_THREAD_USE_COND_WAIT 1
//! Время ожидания условной переменной, секунды.
#define THREAD_TIMER_THREAD_COND_WAIT_TIME_S 1
//! Время ожидания условной переменной, наносекунды.
#define THREAD_TIMER_THREAD_COND_WAIT_TIME_NS 0
//! Перезагружать время следующего срабатывания
//! 1 - относительно планируемого времени срабатывания.
//! 0, либо не определено - относительно текущего времени.
#define THREAD_TIMER_RELOAD_RELATIVE_END_TIME 0
//! Отладка потока.
//! 0, либо не опрелелено - ничего.
//! от 1 до 4 - уровни подробностей вывода отладки.
#define THREAD_TIMER_THREAD_DEBUG 0
//! Отладка управления.
//! 0, либо не опрелелено - ничего.
//! от 1 до 4 - уровни подробностей вывода отладки.
#define THREAD_TIMER_DEBUG 0


//! Тип функции обратного вызова.
typedef void (*thread_timer_callback_t)(void* arg);

//! Тип команды потока таймера.
typedef enum _E_Thread_Timer_Cmd {
    THREAD_TIMER_CMD_NONE = 0, //!< Ничего.
    THREAD_TIMER_CMD_END = 1, //!< Завершить работу.
    THREAD_TIMER_CMD_START = 2, //!< Запуск.
    THREAD_TIMER_CMD_STOP = 3, //!< Останов.
} thread_timer_cmd_t;

//! Тип состояния потока.
typedef enum _E_Thread_Timer_State {
    THREAD_TIMER_STATE_NONE = 0, //!< Ничего.
    THREAD_TIMER_STATE_IDLE = 1, //!< Простой.
    THREAD_TIMER_STATE_RUN = 2, //!< Работа.
} thread_timer_state_t;

//! Флаги таймера.
typedef enum _E_Thread_Timer_Flags {
    THREAD_TIMER_FLAG_NONE = 0, //!< Ничего.
    THREAD_TIMER_FLAG_ONE_SHOT = 1, //!< Однократное срабатывание.
} thread_timer_flag_t;

// Тип флагов таймера.
typedef uint32_t thread_timer_flags_t;

//! Тип таймера.
typedef struct _S_Thread_Timer {
    // Работа с потоком таймера.
    pthread_mutex_t cond_mutex;
    #if defined(THREAD_TIMER_THREAD_USE_COND_WAIT) && THREAD_TIMER_THREAD_USE_COND_WAIT == 1
    pthread_condattr_t cond_attr;
    pthread_cond_t cond_var;
    #endif //THREAD_TIMER_THREAD_USE_COND_WAIT
    pthread_attr_t thread_attr;
    pthread_t thread;
    //! Команда.
    thread_timer_cmd_t cmd;
    //! Состояние.
    thread_timer_state_t state;
    //! Заданный период.
    struct timespec ts_period;
    //! Флаги.
    thread_timer_flags_t flags;
    //! Коллбэк.
    thread_timer_callback_t callback;
    //! Аргумент коллбэка.
    void* callback_arg;
} thread_timer_t;


//! Определение EXTERN.
#ifndef EXTERN
 #ifndef __cplusplus
  #define EXTERN extern
 #else
  #define EXTERN extern "C"
 #endif
#endif


/**
 * Инициализирует таймер.
 * @param thr_tim Таймер.
 * @return 0 в случае успеха, иначе код ошибки.
 */
EXTERN int thread_timer_init(thread_timer_t* thr_tim);

/**
 * Деинициализирует таймер.
 * @param thr_tim Таймер.
 * @return 0 в случае успеха, иначе код ошибки.
 */
EXTERN int thread_timer_deinit(thread_timer_t* thr_tim);

/**
 * Устанавливает коллбэк и аргумент коллбэка таймера.
 * @param thr_tim Таймер.
 * @param callback Коллбэк.
 * @param callback_arg Аргумент коллбэка.
 */
EXTERN void thread_timer_set_callback(thread_timer_t* thr_tim, thread_timer_callback_t callback, void* callback_arg);

/**
 * Устанавливает период таймера.
 * @param thr_tim Таймер.
 * @param tv_period Период.
 */
EXTERN void thread_timer_set_period(thread_timer_t* thr_tim, struct timespec* tv_period);

/**
 * Устанавливает флаги таймера.
 * @param thr_tim Таймер.
 * @param flags Флаги.
 */
EXTERN void thread_timer_set_flags(thread_timer_t* thr_tim, thread_timer_flags_t flags);

/**
 * Получает флаг работы таймера.
 * @param thr_tim Таймер.
 * @return 1 - работа, 0 - простой.
 */
EXTERN int thread_timer_running(thread_timer_t* thr_tim);

/**
 * Ожидает запуска потока таймера.
 * @param thr_tim Таймер.
 */
EXTERN void thread_timer_wait_thread_begin(thread_timer_t* thr_tim);

/**
 * Ожидает запуска таймера.
 * @param thr_tim Таймер.
 */
EXTERN void thread_timer_wait_start(thread_timer_t* thr_tim);

/**
 * Ожидает останова таймера.
 * @param thr_tim Таймер.
 */
EXTERN void thread_timer_wait_stop(thread_timer_t* thr_tim);

/**
 * Запускает таймер.
 * @param thr_tim Таймер.
 * @return 0 в случае успеха, иначе код ошибки.
 */
EXTERN int thread_timer_start(thread_timer_t* thr_tim);

/**
 * Останавливает таймер таймер.
 * @param thr_tim Таймер.
 * @return 0 в случае успеха, иначе код ошибки.
 */
EXTERN int thread_timer_stop(thread_timer_t* thr_tim);


#endif //THREAD_TIMER_H
