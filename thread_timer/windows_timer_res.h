#if defined(PORT_POSIX)

#ifndef WINDOWS_TIMER_RES_H
#define WINDOWS_TIMER_RES_H

#if defined(__WIN32__) || defined(__WIN64__) || defined(__CYGWIN__)


// Макрос для удобства использования.
#ifndef WINDOWS_TIMER
#define WINDOWS_TIMER 1
#endif

//! Определение EXTERN.
#ifndef EXTERN
 #ifndef __cplusplus
  #define EXTERN extern
 #else
  #define EXTERN extern "C"
 #endif
#endif


/**
 * Устанавливает максимальное доступное разрешение системного таймера.
 * @return 0 в случае успеха, иначе код ошибки.
 */
EXTERN int windows_timer_set_max_res(void);


/**
 * Возвращает разрешение системного таймера.
 * @return 0 в случае успеха, иначе код ошибки.
 */
EXTERN int windows_timer_restore_res(void);


#endif //__WIN32__ || __WIN64__ || __CYGWIN__


#endif //WINDOWS_TIMER_RES_H

#endif
