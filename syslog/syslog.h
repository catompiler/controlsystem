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
#define SYSLOG_BUF_LEN 128

//! Размер буфера для метки времени.
#define SYSLOG_TIME_BUF_LEN 20

//! Размер буфера для получения сообщений.
#define SYSLOG_MAX_FULL_MSG_LEN ((SYSLOG_MAX_MSG_LEN) + (SYSLOG_TIME_BUF_LEN))

#define SYSLOG_MAX_PRINTF_LEN 255

//! Структура сислога.
typedef struct _S_Syslog {
    char msg_buf[SYSLOG_BUF_LEN]; //!< Буфер для сообщений.
    char time_buf[SYSLOG_TIME_BUF_LEN]; //!< Буфер для отметки времени.
    char printf_buf[SYSLOG_MAX_PRINTF_LEN + 1]; //!< Буфер для printf + гарантированный символ окончания строки.
    syslog_level_t level; //!< Уровень приёма сообщений в буфер.
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


#endif /* SYSLOG_SYSLOG_H_ */
