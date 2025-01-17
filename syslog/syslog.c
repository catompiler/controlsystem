#include "syslog.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include "sys_counter/sys_counter.h"


#define SYSLOG_PUT_CR 1
#define SYSLOG_PUT_LF 1


void syslog_init(syslog_t* slog)
{
    assert(slog != NULL);

    memset(&slog->msg_buf, 0x0, SYSLOG_BUF_LEN);
    slog->level = 0;
    slog->putchar_callback = NULL;
    slog->msg_index = 0;
}

syslog_level_t syslog_level(syslog_t* slog)
{
    assert(slog != NULL);

    return slog->level;
}

void syslog_set_level(syslog_t* slog, syslog_level_t level)
{
    assert(slog != NULL);

    slog->level = level;
}

syslog_putchar_callback_t syslog_putchar_callback(syslog_t* slog)
{
    assert(slog != NULL);

    return slog->putchar_callback;
}

void syslog_set_putchar_callback(syslog_t* slog, syslog_putchar_callback_t putchar_callback)
{
    assert(slog != NULL);

    slog->putchar_callback = putchar_callback;
}


static size_t syslog_next_index(size_t index)
{
    size_t next_index = index + 1;
    if(next_index >= SYSLOG_BUF_LEN) next_index = 0;
    return next_index;
}


//static size_t syslog_add_index(size_t index, size_t sz)
//{
//    size_t next_index = index + sz;
//    if(next_index >= SYSLOG_BUF_LEN) next_index = next_index - SYSLOG_BUF_LEN;
//    return next_index;
//}

//! @return allocated size.
static size_t syslog_alloc_buf(syslog_t* slog, size_t needed_size)
{
    if(needed_size == 0) return 0;

    char* msg_buf = slog->msg_buf;

    size_t start_index = slog->msg_index;

    size_t end_index = slog->msg_index;
    size_t count = 0;

    while(count < SYSLOG_BUF_LEN){
        while(msg_buf[end_index]){
            end_index = syslog_next_index(end_index);
            count ++;
        }

        end_index = syslog_next_index(end_index);

        if(count >= needed_size) break;

        count ++;
    }

    slog->msg_index = end_index;

    size_t cur_index = start_index;

    do{
        msg_buf[cur_index] = 0;
        cur_index = syslog_next_index(cur_index);
    } while(cur_index != end_index);

    return count;
}

ALWAYS_INLINE static void syslog_putchar(syslog_t* slog, int c)
{
    if(slog->putchar_callback) slog->putchar_callback(c);
}

ALWAYS_INLINE static int syslog_make_timestamp(syslog_t* slog, struct timeval* tv)
{
    return snprintf(slog->time_buf, SYSLOG_TIME_BUF_LEN, "[%u.%06u] ",
            (unsigned int)tv->tv_sec, (unsigned int)tv->tv_usec);
}

static int syslog_puts_impl(syslog_t* slog, struct timeval* tv, const char* str)
{
    int time_len = syslog_make_timestamp(slog, tv);
    if(time_len < 0) return time_len;

    size_t s_len = strlen(str);
    if(s_len > SYSLOG_MAX_MSG_LEN) s_len = SYSLOG_MAX_MSG_LEN;

    size_t needed_size = (size_t)time_len + s_len;

    size_t index = slog->msg_index;
    char* msg_buf = slog->msg_buf;
    char* timer_str = slog->time_buf;

    size_t size = syslog_alloc_buf(slog, needed_size);
    if(size < needed_size) return -1;

    char c;

    while(time_len > 0){
        c = *timer_str;
        msg_buf[index] = c;
        syslog_putchar(slog, c);
        index = syslog_next_index(index);
        timer_str ++;
        time_len --;
    }

    while(s_len > 0){
        c = *str;
        msg_buf[index] = c;
        syslog_putchar(slog, c);
        index = syslog_next_index(index);
        str ++;
        s_len --;
    }

#if defined(SYSLOG_PUT_CR) && SYSLOG_PUT_CR == 1
    syslog_putchar(slog, '\r');
#endif
#if defined(SYSLOG_PUT_LF) && SYSLOG_PUT_LF == 1
    syslog_putchar(slog, '\n');
#endif

    return (int)needed_size;
}

int syslog_puts(syslog_t* slog, syslog_level_t level, const char* str)
{
    assert(slog != NULL);

    if(slog->level > level) return 0;

    if(str == NULL) return -1;

    struct timeval tv = {0, 0};
    sys_counter_value(&tv);

    return syslog_puts_impl(slog, &tv, str);
}

int syslog_printf(syslog_t* slog, syslog_level_t level, const char* fmt, ...)
{
    assert(slog != NULL);

    if(slog->level > level) return 0;

    if(fmt == NULL) return -1;

    struct timeval tv = {0, 0};
    sys_counter_value(&tv);

    va_list args;
    va_start (args, fmt);

    int n = vsnprintf (slog->printf_buf, SYSLOG_MAX_PRINTF_LEN, fmt, args);
    if(n >= 0){
        slog->printf_buf[n] = 0;
        n = syslog_puts_impl(slog, &tv, slog->printf_buf);
    }

    va_end (args);

    return n;
}

int syslog_first_message_index(syslog_t* slog)
{
    const char* msg_buf = slog->msg_buf;
    size_t index = slog->msg_index;

    size_t count = 0;
    while(msg_buf[index] == 0 && count < SYSLOG_BUF_LEN){
        index = syslog_next_index(index);
        count ++;
    }
    if(count >= SYSLOG_BUF_LEN) return -1;

    return (int)index;
}

int syslog_next_message_index(syslog_t* slog, int first_msg_index, int msg_index)
{
    if(first_msg_index < 0 || first_msg_index >= SYSLOG_BUF_LEN) return -1;
    if(msg_index < 0 || msg_index >= SYSLOG_BUF_LEN) return -1;

    const char* msg_buf = slog->msg_buf;

    size_t index = (size_t)msg_index + (size_t)first_msg_index;
    if(index >= SYSLOG_BUF_LEN) index = index - SYSLOG_BUF_LEN;

    size_t count = (size_t) msg_index;

    while(msg_buf[index] != 0 && count < SYSLOG_BUF_LEN){
        index = syslog_next_index(index);
        count ++;
    }

    while(msg_buf[index] == 0 && count < SYSLOG_BUF_LEN){
        index = syslog_next_index(index);
        count ++;
    }

    if(count >= SYSLOG_BUF_LEN) return -1;

    return (int)count;
}

int syslog_get_message(syslog_t* slog, int first_msg_index, int msg_index, char* buf, size_t buf_size)
{
    if(first_msg_index < 0 || first_msg_index >= SYSLOG_BUF_LEN) return -1;
    if(msg_index < 0 || msg_index >= SYSLOG_BUF_LEN) return -1;
    if(buf == NULL) return -1;

    const char* msg_buf = slog->msg_buf;

    size_t index = (size_t)msg_index + (size_t)first_msg_index;
    if(index >= SYSLOG_BUF_LEN) index = index - SYSLOG_BUF_LEN;

    char c;
    size_t buf_written;
    for(buf_written = 0; buf_written < buf_size; buf_written ++){
        c = msg_buf[index];
        buf[buf_written] = c;
        if(c == 0) break;
        index = syslog_next_index(index);
    }

    return (int)buf_written;
}
