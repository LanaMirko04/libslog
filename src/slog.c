/**
 * \file            slog.h
 * \date            2023-05-30
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           SLog (Sh*tty Logging) library.
 */

#include "slog.h"

#include <pthread.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static uint8_t slog_lv;
static pthread_mutex_t slog_mtx;
FILE *slog_file;

static char *prv_slog_clear_fmt(const char *fmt) {
    char *new_fmt = calloc(strlen(fmt) + 1, 1);
    if (NULL == new_fmt) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; fmt[i]; ++i) {
        if ('\033' == fmt[i]) {
            while ('m' != fmt[i]) {
                ++i;
            }
        } else {
            new_fmt[j++] = fmt[i];
        }
    }

    return new_fmt;
}

static int prv_slog_log_impl(FILE *os, const char *fmt, va_list args) {
    pthread_mutex_lock(&slog_mtx);

    int ret;
    if (!isatty(fileno(os))) {
        char *new_fmt = prv_slog_clear_fmt(fmt);
        ret = vfprintf(os, new_fmt, args);
        free(new_fmt);
    } else {
        ret = vfprintf(os, fmt, args);
    }

    pthread_mutex_unlock(&slog_mtx);

    return ret;
}

void slog_init(uint8_t lv) {
    slog_file = NULL;
    slog_lv = lv;
}

int slog_open_file(const char *filepath) {
    if (!filepath) {
        return ERR;
    }

    if (slog_file) {
        return ERR;
    }

    slog_file = fopen(filepath, "a");
    if (NULL == slog_file) {
        return ERR;
    }

    return OK;
}

void slog_close_file(void) {
    if (NULL != slog_file) {
        fclose(slog_file);
        slog_file = NULL;
    }
}

int int_slog_log(enum SlogLevel lv, FILE *os, const char *fmt, ...) {
    if (!(slog_lv & lv) || (NULL == os)) {
        return OK;
    }

    va_list args;
    va_start(args, fmt);

    int ret = prv_slog_log_impl(os, fmt, args);

    va_end(args);

    return ret;
}

int int_slog_log_all(enum SlogLevel lv, const char *fmt, ...) {
    if (!(slog_lv & lv)) {
        return OK;
    }

    va_list args;
    va_start(args, fmt);

    int ret = prv_slog_log_impl((LV_ERROR == lv) ? stderr : stdout, fmt, args);
    if (ERR == ret) {
        va_end(args);
        return ERR;
    }

    if (NULL == slog_file) {
        va_end(args);
        return ret;
    }

    ret = prv_slog_log_impl(slog_file, fmt, args);
    if (ERR == ret) {
        va_end(args);
        return ERR;
    }

    va_end(args);

    return ret;
}

char *int_slog_get_time(void) {
    static char time_buff[SLOG_TIME_BUFF_SIZE];
    time_t now = time(NULL);
    struct tm *ltime = localtime(&now);

    bzero(time_buff, SLOG_TIME_BUFF_SIZE);
    strftime(time_buff, SLOG_TIME_BUFF_SIZE, "%Y-%m-%d %H:%M:%S", ltime);

    return time_buff;
}
