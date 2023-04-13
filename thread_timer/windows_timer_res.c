#ifndef WINDOWS_TIMER_RES_H
#define WINDOWS_TIMER_RES_H

#if defined(__WIN32__) || defined(__WIN64__) || defined(__CYGWIN__)


#include <windows.h>


// Декларация недокументированных функций WinAPI.
NTSYSAPI NTSTATUS NTAPI NtSetTimerResolution(
    IN ULONG DesiredResolution, IN BOOLEAN SetResolution, OUT PULONG CurrentResolution);
NTSYSAPI NTSTATUS NTAPI NtQueryTimerResolution(
    OUT PULONG MinimumResolution, OUT PULONG MaximumResolution, OUT PULONG CurrentResolution);


int windows_timer_set_max_res(void)
{
    NTSTATUS status = 0;
    ULONG minRes = 0, maxRes = 0, curRes = 0, settedRes = 0;

    status = NtQueryTimerResolution(&minRes, &maxRes, &curRes);
    if(status != 0){
        return (int)status;
    }
    //printf("Min res: %d Max res: %d Cur res: %d\n", (int)minRes, (int)maxRes, (int)curRes);

    status = NtSetTimerResolution(maxRes, TRUE, &settedRes);
    if(status != 0){
        return (int)status;
    }
    //printf("Setted res: %d\n", (int)settedRes);

    return 0;
}


int windows_timer_restore_res(void)
{
    NTSTATUS status = 0;
    ULONG settedRes = 0;

    status = NtSetTimerResolution(0, FALSE, &settedRes);
    if(status != 0){
        return (int)status;
    }
    //printf("Setted res: %d\n", (int)settedRes);

    return 0;
}


#endif //__WIN32__ || __WIN64__ || __CYGWIN__

#endif //WINDOWS_TIMER_RES_H
