/**
 * \file            slog-api.c
 * \date            2025-11-04
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           SLog (Sh*tty Logging) library implementation.
 */

#include "slog-api.h"
#include "slog.h"

#include <pthread.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct SlogHandler slog_default_handler;
static pthread_mutex_t slog_mtx;

static void prv_slog_enter_cs(void) {
    pthread_mutex_lock(&slog_mtx);
}

static void prv_slog_exit_cs(void) {
    pthread_mutex_unlock(&slog_mtx);
}

// static char *prv_slog_clear_fmt(const char *fmt) {
//     char *new_fmt = calloc(strlen(fmt) + 1, 1);
//     if (NULL == new_fmt) {
//         return NULL;
//     }

//     size_t j = 0;
//     for (size_t i = 0; fmt[i]; ++i) {
//         if ('\033' == fmt[i]) {
//             while ('m' != fmt[i]) {
//                 ++i;
//             }
//         } else {
//             new_fmt[j++] = fmt[i];
//         }
//     }

//     return new_fmt;
// }

// static int prv_slog_log_impl(FILE *os, const char *fmt, va_list args) {
//     // pthread_mutex_lock(&slog_mtx);
//     prv_slog_enter_cs();

//     int ret;
//     if (!isatty(fileno(os))) {
//         char *new_fmt = prv_slog_clear_fmt(fmt);
//         ret = vfprintf(os, new_fmt, args);
//         free(new_fmt);
//     } else {
//         ret = vfprintf(os, fmt, args);
//     }

//     // pthread_mutex_unlock(&slog_mtx);
//     prv_slog_exit_cs();

//     return ret;
// }

void slog_api_init(enum SlogLevel lv) {
    slog_default_handler.stream = NULL;
    slog_default_handler.lv = lv;
    slog_default_handler.apply_colors = true;
}

enum SlogReturnCode slog_api_init_handler(struct SlogHandler *handler, enum SlogLevel lv, const char *file_path, bool apply_colors) {
    if (!handler)
        return SLOG_RC_INVALID_ARG;

    handler->lv = lv;
    handler->apply_colors = apply_colors;

    if (file_path) {
        FILE *fp = fopen(file_path, "a");
        if (!fp) {
            return SLOG_RC_IO_ERR;
        }
        handler->stream = fp;
    } else {
        handler->stream = NULL;
    }

    return SLOG_RC_OK;
}

enum SlogReturnCode slog_api_set_slog_default_handler(const struct SlogHandler *new, struct SlogHandler *old) {
    if (!new || !old)
        return SLOG_RC_INVALID_ARG;

    *old = slog_default_handler;
    slog_default_handler = *new;
    return SLOG_RC_OK;
}

const struct SlogHandler *slog_api_get_handler(void) {
    return &slog_default_handler;
}

void slog_api_deinit_handler(struct SlogHandler *handler) {
    if (!handler)
        return;

    if (handler->stream && handler->stream != stdout && handler->stream != stderr) {
        fclose(handler->stream);
        handler->stream = NULL;
    }
}

// int int_slog_log(enum SlogLevel lv, FILE *os, const char *fmt, ...) {
//     if (!(slog_lv & lv) || (NULL == os)) {
//         return OK;
//     }

//     va_list args;
//     va_start(args, fmt);

//     int ret = prv_slog_log_impl(os, fmt, args);

//     va_end(args);

//     return ret;
// }

// char *int_slog_get_time(void) {
//     static char time_buff[SLOG_TIME_BUFF_SIZE];
//     time_t now = time(NULL);
//     struct tm *ltime = localtime(&now);

//     bzero(time_buff, SLOG_TIME_BUFF_SIZE);
//     strftime(time_buff, SLOG_TIME_BUFF_SIZE, "%Y-%m-%d %H:%M:%S", ltime);

//     return time_buff;
// }
