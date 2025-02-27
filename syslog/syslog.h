#ifndef SYSLOG_SYSLOG_H_
#define SYSLOG_SYSLOG_H_

#include <stdint.h>
#include <stddef.h>
#include "defs/defs.h"


//! Тип уровня сообщения.
typedef enum _E_Syslog_Level {
    SYSLOG_DEBUG = 0,
    SYSLOG_INFO = 1,
    SYSLOG_WARNING = 2,
    SYSLOG_ERROR = 3,
    SYSLOG_FATAL = 4,
    SYSLOG_DISABLE = INT32_MAX
} syslog_level_t;


//! Максимальный размер сообщения (без завершающего нуля и без отметки времени).
#define SYSLOG_MAX_MSG_LEN 32

//! Размер буфера сообщений.
#define SYSLOG_BUF_LEN 256

//! Размер буфера для метки времени.
#define SYSLOG_TIME_BUF_LEN 20

//! Размер буфера для получения сообщений.
#define SYSLOG_MAX_FULL_MSG_LEN ((SYSLOG_MAX_MSG_LEN) + (SYSLOG_TIME_BUF_LEN))

//! Размер буфера для printf.
#define SYSLOG_MAX_PRINTF_LEN 255

//! Тип функции печати символа.
typedef int (*syslog_putchar_callback_t)(int);

//! Структура сислога.
typedef struct _S_Syslog {
    char msg_buf[SYSLOG_BUF_LEN]; //!< Буфер для сообщений.
    char time_buf[SYSLOG_TIME_BUF_LEN]; //!< Буфер для отметки времени.
    char printf_buf[SYSLOG_MAX_PRINTF_LEN + 1]; //!< Буфер для printf + гарантированный символ окончания строки.
    syslog_level_t level; //!< Уровень приёма сообщений в буфер.
    syslog_putchar_callback_t putchar_callback; //!< Функция вывода строки.
    size_t msg_index; //!< Индекс начала сообщений.
} syslog_t;

/**
 * Инициализирует системный лог.
 * @param slog Системный лог.
 */
EXTERN void syslog_init(syslog_t* slog);

/**
 * Получает текущий уровень логгирования.
 * @param slog Системный лог.
 * @return Уровень логгирования.
 */
EXTERN syslog_level_t syslog_level(syslog_t* slog);

/**
 * Устанавливает текущий уровень логгирования.
 * @param slog Системный лог.
 * @param level Уровень логгирования.
 */
EXTERN void syslog_set_level(syslog_t* slog, syslog_level_t level);

/**
 * Получает функцию вывода.
 * @param slog Системный лог.
 * @return Функция вывода.
 */
EXTERN syslog_putchar_callback_t syslog_putchar_callback(syslog_t* slog);

/**
 * Устанавливает функцию вывода.
 * @param slog Системный лог.
 * @param putchar_callback Функция вывода.
 */
EXTERN void syslog_set_putchar_callback(syslog_t* slog, syslog_putchar_callback_t putchar_callback);

/**
 * Помещает сообщение в системный лог.
 * @param slog Системный лог.
 * @param level Уровень логгирования.
 * @param str Сообщение.
 * @return Число помещённых символов, отрицательное число в случае ошибки.
 */
EXTERN int syslog_puts(syslog_t* slog, syslog_level_t level, const char* str);

/**
 * Помещает сообщение в системный лог.
 * @param slog Системный лог.
 * @param level Уровень логгирования.
 * @param fmt Строка.
 * @return Число помещённых символов, отрицательное число в случае ошибки.
 */
EXTERN int syslog_printf(syslog_t* slog, syslog_level_t level, const char* fmt, ...);

/**
 * Получает индекс первого сообщения.
 * @param slog Системный лог.
 * @return Индекс первого сообщения, отрицательное число если нет сообщений.
 */
EXTERN int syslog_first_message_index(syslog_t* slog);

/**
 * Получает индекс следующего сообщения.
 * @param slog Системный лог.
 * @param first_msg_index Индекс первого сообщения.
 * @param msg_index Индекс текущего сообщения.
 * @return Индекс следующего сообщения, отрицательное число если больше нет сообщений.
 */
EXTERN int syslog_next_message_index(syslog_t* slog, int first_msg_index, int msg_index);

/**
 * Получает сообщение.
 * @param slog Системный лог.
 * @param first_msg_index Индекс первого сообщения.
 * @param msg_index Индекс текущего сообщения.
 * @param buf Буфер для сообщения.
 * @param buf_size Размер буфера.
 * @return Число помещённых символов, кроме 0, отрицательное число в случае ошибки.
 */
EXTERN int syslog_get_message(syslog_t* slog, int first_msg_index, int msg_index, char* buf, size_t buf_size);


#ifdef SYSLOG_GLOBAL

#ifndef SYSLOG_NAME
#define SYSLOG_NAME syslog
#endif

//! Глобальный системный лог.
EXTERN syslog_t SYSLOG_NAME;

//! Глобальная функция вывода строки в системный лог.
#define SYSLOG_MSG(LEVEL, MSG) syslog_puts(&SYSLOG_NAME, LEVEL, MSG)
//! Глобальная функция форматированного вывода в системный лог.
#define SYSLOG_MSGF(LEVEL, FMT, ...) syslog_printf(&SYSLOG_NAME, LEVEL, FMT, ##__VA_ARGS__)
//! Глобальная функция вывода в лог по-умолчанию.
#define SYSLOG(LEVEL, MSG, ...) syslog_printf(&SYSLOG_NAME, LEVEL, MSG, ##__VA_ARGS__)

#endif

#endif /* SYSLOG_SYSLOG_H_ */
