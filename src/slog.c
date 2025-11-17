/**
 * \file            slog.h
 * \date            2023-05-30
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           SLog (Sh*tty Logging) library.
 */

#include "slog.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

/*!
 * \brief           Internal SLog handler structure.
 */
struct SlogHandler {
    struct Slogger default_logger; /*!< Default logger instance. */
    enum SlogLevel emit_level;     /*!< Current emit log level. */
    void (*enter_cs)(void);        /*!< Enter critical section function pointer. */
    void (*exit_cs)(void);         /*!< Exit critical section function pointer. */
};

static const char *SLOG_LEVEL_COLOR_CODES[SLOG_LEVEL_ALL] = {
    SLOG_ANSI_GREEN,
    SLOG_ANSI_RED,
    SLOG_ANSI_YELLOW,
    SLOG_ANSI_CYAN,
}; /*!< Color codes for each log level. */
static const char *SLOG_LEVEL_STRINGS[SLOG_LEVEL_ALL] = {
    "INFO",
    "ERROR",
    "WARN",
    "DEBUG",
}; /*!< String representations for each log level. */

static struct SlogHandler slog; /*!< Internal SLog handler instance. */

/*! Check if logging has to be disabled or not (functions become no-ops) */
#ifndef SLOG_DISABLE_LOGGING_SYSTEM

/*!
 * \brief           Dummy critical section function.
 */
static void prv_slog_cs_dummy(void) {
}

/*!
 * \brief           Get current time as string.
 *
 * \return          Pointer to static string buffer containing current time.
 */
static const char *prv_slog_get_curr_time_str(void) {
    static char buffer[20U];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    memset(buffer, 0U, 20U);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);

    return buffer;
}

enum SlogReturnCode int_slog_default_write(const void *ctx, const char *fmt, ...) {
    if (!fmt) {
        return SLOG_RC_INVALID_ARG;
    }

    (void)ctx;
    va_list args;
    va_start(args, fmt);

    FILE *os = slog.emit_level == SLOG_LEVEL_ERROR ? stderr : stdout;
    vfprintf(os, fmt, args);

    va_end(args);

    return SLOG_RC_OK;
}

enum SlogReturnCode int_slog_default_flush(const void *ctx) {
    (void)ctx;
    return SLOG_RC_OK;
}

enum SlogReturnCode int_slog_emit(const struct Slogger *logger, enum SlogLevel lv, const char *fmt, ...) {
    static char buffer[SLOG_EMIT_BUFFER_SIZE];

    if (!logger || !fmt) {
        return SLOG_RC_INVALID_ARG;
    }

    if (!(logger->lv & lv)) {
        return SLOG_RC_OK;
    }

    va_list args;
    va_start(args, fmt);

    slog.enter_cs();
    slog.emit_level = lv;
    memset(buffer, 0U, SLOG_EMIT_BUFFER_SIZE);

    if (logger->apply_colors) {
        snprintf(buffer,
                 SLOG_EMIT_BUFFER_SIZE,
                 "%s%s %s%s[%s]%s",
                 SLOG_ANSI_GRAY,
                 prv_slog_get_curr_time_str(),
                 SLOG_ANSI_BOLD,
                 SLOG_LEVEL_COLOR_CODES[__builtin_ctz(lv)],
                 SLOG_LEVEL_STRINGS[__builtin_ctz(lv)],
                 SLOG_ANSI_RESET);
    } else {
        snprintf(buffer,
                 SLOG_EMIT_BUFFER_SIZE,
                 "%s [%s]",
                 prv_slog_get_curr_time_str(),
                 SLOG_LEVEL_STRINGS[lv]);
    }
    vsnprintf(buffer + strlen(buffer), SLOG_EMIT_BUFFER_SIZE - strlen(buffer), fmt, args);

    va_end(args);

    enum SlogReturnCode ret = logger->write_fn(logger->ctx, "%s", buffer);
    if (ret != SLOG_RC_OK) {
        slog.exit_cs();
        return ret;
    }

    ret = logger->flush_fn(logger->ctx);
    slog.exit_cs();

    return ret;
}

void slog_init(const struct SlogConfig *cfg) {
    slog.default_logger = cfg->default_logger;
    slog.enter_cs = !cfg->enter_cs ? prv_slog_cs_dummy : cfg->enter_cs;
    slog.exit_cs = !cfg->exit_cs ? prv_slog_cs_dummy : cfg->exit_cs;
    slog.emit_level = SLOG_LEVEL_NONE;
}

enum SlogReturnCode slog_set_default_logger(const struct Slogger *logger, struct Slogger *old_logger) {
    if (!logger) {
        return SLOG_RC_INVALID_ARG;
    }

    if (old_logger)
        *old_logger = slog.default_logger;

    slog.default_logger = *logger;

    return SLOG_RC_OK;
}

const struct Slogger *slog_get_default_logger(void) {
    return &slog.default_logger;
}

enum SlogLevel slog_get_emit_level(void) {
    return slog.emit_level;
}

#endif /*! SLOG_DISABLE_LOGGING_SYSTEM */

const char *slog_level_to_string(enum SlogLevel lv) {
    if (!lv)
        return "";

    int idx = __builtin_ctz(lv);
    return idx >= __builtin_ctz(SLOG_LEVEL_ALL) ? "" : SLOG_LEVEL_STRINGS[idx];
}
