/**
 * \file            slog.h
 * \date            2023-05-30
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           SLog (Sh*tty Logging) library.
 */

#ifndef SLOG_H
#define SLOG_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

/*!
 * \defgroup        ansi_codes ANSI escape sequences.
 * @{
 */

#define SLOG_ANSI_RESET "\033[0m"     /*!< ANSI escape code for reset. */
#define SLOG_ANSI_BOLD "\033[1m"      /*!< ANSI escape code for bold text. */
#define SLOG_ANSI_RED "\033[0;31m"    /*!< ANSI escape code for red foreground color. */
#define SLOG_ANSI_GREEN "\033[0;32m"  /*!< ANSI escape code for green foreground color. */
#define SLOG_ANSI_YELLOW "\033[0;33m" /*!< ANSI escape code for yellow foreground color. */
#define SLOG_ANSI_CYAN "\033[0;36m"   /*!< ANSI escape code for cyan foreground color. */
#define SLOG_ANSI_GRAY "\033[0;37m"   /*!< ANSI escape code for gray foreground color. */

/*!
 * @}
 */

#ifndef SLOG_EMIT_BUFFER_SIZE

/*!
 * \brief           Size of the internal buffer used for log message formatting.
 *
 * \note            This value can be overridden by defining SLOG_EMIT_BUFFER_SIZE
 *                  before including this header file or during compilation (-d flag).
 */
#define SLOG_EMIT_BUFFER_SIZE 1024

#endif /*! SLOG_EMIT_BUFFER_SIZE */

#define SLOG_INIT_DEFAULT_LOGGER {         \
    .write_fn = int_slog_default_write,    \
    .flush_fn = int_slog_default_flush,    \
    .ctx = NULL,                           \
    .lv = SLOG_LEVEL_ALL,                  \
    .apply_colors = isatty(fileno(stdout)) \
} /*!< Default Slogger initializer. */

/*!
 * \defgroup        log_macros Logging macros.
 * @{
 */

/*!
  * \brief           Enumeration containing all possible return codes.
  */
enum SlogReturnCode {
    SLOG_RC_FAIL = -1,   /*!< An error occurred. */
    SLOG_RC_OK,          /*!< Everything is fine. */
    SLOG_RC_INVALID_ARG, /*!< Invalid argument. */
    SLOG_RC_IO_ERR       /*!< I/O error occurred. */
};

/**
  * \brief           Enumeration representing different log levels.
  */
enum SlogLevel {
    SLOG_LEVEL_NONE = 0x00,  /*!< No logging messages. */
    SLOG_LEVEL_INFO = 0x01,  /*!< Informational messages. */
    SLOG_LEVEL_ERROR = 0x02, /*!< Error messages. */
    SLOG_LEVEL_WARN = 0x04,  /*!< Warning messages. */
    SLOG_LEVEL_DEBUG = 0x08, /*!< Debugging messages. */
    SLOG_LEVEL_ALL = 0x0F    /*!< All messages. */
};

/*!
  * \brief           The SLog logger structure.
  */
struct Slogger {
    enum SlogReturnCode (*write_fn)(const void *ctx, const char *fmt, ...); /*!< Write function pointer. */
    enum SlogReturnCode (*flush_fn)(const void *ctx);                       /*!< Flush function pointer. */
    void *ctx;                                                              /*!< User-defined context pointer. */
    uint8_t lv;                                                             /*!< Log level for this logger. */
    bool apply_colors;                                                      /*!< Flag to apply colors to the log messages. */
};

/*!
  * \brief           Configuration structure for initializing the SLog system.
  */
struct SlogConfig {
    struct Slogger default_logger; /*!< Default logger configuration. */
    void (*enter_cs)(void);        /*!< Function pointer to enter critical section. */
    void (*exit_cs)(void);         /*!< Function pointer to exit critical section. */
};

#ifdef __cplusplus
extern "C" {
#endif /*! __cplusplus */

/*!
 * \brief           Emit a log message using the specified logger.
 *
 * \param[in]       logger: Pointer to the Slogger to use.
 * \param[in]       lv: Log level of the message.
 * \param[in]       fmt: Format string.
 * \param[in]       ...: Variable arguments.
 * \return          SLOG_RC_OK on success, otherwise an error code.
 */
#define SLOG_EMIT(logger, lv, fmt, ...) \
    int_slog_emit((logger), (lv), " %s:%d -> " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

/*!
 * \brief           Emit an informational log message.
 *
 * \param[in]       fmt: Format string.
 * \param[in]       ...: Variable arguments.
 * \return          SLOG_RC_OK on success, otherwise an error code.
 */
#define SLOG_INFO(fmt, ...) \
    SLOG_EMIT(slog_get_default_logger(), SLOG_LEVEL_INFO, fmt, ##__VA_ARGS__)

/*!
 * \brief           Emit an error log message.
 *
 * \param[in]       fmt: Format string.
 * \param[in]       ...: Variable arguments.
 * \return          SLOG_RC_OK on success, otherwise an error code.
 */
#define SLOG_ERROR(fmt, ...) \
    SLOG_EMIT(slog_get_default_logger(), SLOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)

/*!
 * \brief           Emit a warning log message.
 *
 * \param[in]       fmt: Format string.
 * \param[in]       ...: Variable arguments.
 * \return          SLOG_RC_OK on success, otherwise an error code.
 */
#define SLOG_WARN(fmt, ...) \
    SLOG_EMIT(slog_get_default_logger(), SLOG_LEVEL_WARN, fmt, ##__VA_ARGS__)

/*!
 * \brief           Emit a debug log message.
 *
 * \param[in]       fmt: Format string.
 * \param[in]       ...: Variable arguments.
 * \return          SLOG_RC_OK on success, otherwise an error code.
 */
#define SLOG_DEBUG(fmt, ...) \
    SLOG_EMIT(slog_get_default_logger(), SLOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)

/*!
 * @}
 */

/*!
 * \brief           Default write function.
 *
 * \param[in]       ctx: User-defined context pointer.
 * \param[in]       fmt: Format string.
 * \param[in]       ...: Variable arguments.
 * \return          SLOG_RC_OK on success, otherwise an error code.
 */
enum SlogReturnCode int_slog_default_write(const void *ctx, const char *fmt, ...);

/*!
 * \brief           Default (dummy) flush function.
 *
 * \param[in]       ctx: User-defined context pointer.
 * \return          SLOG_RC_OK every time.
 */
enum SlogReturnCode int_slog_default_flush(const void *ctx);

/*!
 * \brief           Emit a log message using the default logger.
 *
 * \param[in]       level: Log level of the message.
 * \param[in]       fmt: Format string.
 * \param[in]       ...: Variable arguments.
 * \return          SLOG_RC_OK on success, otherwise an error code.
 */
enum SlogReturnCode int_slog_emit(const struct Slogger *logger, enum SlogLevel level, const char *fmt, ...);

/*!
 * \brief           Initialize the SLog logging system.
 *
 * \param[in]       cfg: Pointer to the SlogConfig structure.
 */
void slog_init(const struct SlogConfig *cfg);

/*!
 * \brief           Set the default logger for the logging system.
 *
 * \param[in]       logger: Pointer to the Slogger to set as default.
 * \param[out]      old_logger: Pointer to store the previous default logger (can be NULL).
 * \return          SLOG_RC_OK on success, or an error code on failure.
 */
enum SlogReturnCode slog_set_default_logger(const struct Slogger *logger, struct Slogger *old_logger);

/*!
 * \brief           Get the current default logger for the logging system.
 *
 * \return          Pointer to the current default Slogger.
 */
const struct Slogger *slog_get_default_logger(void);

/*!
 * \brief           Get the current log emit level.
 *
 * \return          Current log emit level as an enum SlogLevel.
 *
 * \note            This level is the last level set by the SLOG_EMIT macro.
 */
enum SlogLevel slog_get_emit_level(void);

/*!
 * \brief           Convert SlogLevel enum to string representation.
 */
const char *slog_level_to_str(enum SlogLevel level);

#ifdef __cplusplus
}
#endif /*! __cplusplus */

#endif /*! SLOG_H */
