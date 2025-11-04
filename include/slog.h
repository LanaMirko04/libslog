/**
 * \file            slog.h
 * \date            2023-05-30
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           SLog (Sh*tty Logging) library.
 */

#ifndef SLOG_H
#define SLOG_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

/*!
 * \defgroup        colors ANSI escape sequences.
 * @{
 */

#define SLOG_RED "\033[0;31m"    /*!< ANSI escape code for red foreground color. */
#define SLOG_GREEN "\033[0;32m"  /*!< ANSI escape code for green foreground color. */
#define SLOG_YELLOW "\033[0;33m" /*!< ANSI escape code for yellow foreground color. */
#define SLOG_BLUE "\033[0;34m"   /*!< ANSI escape code for blue foreground color. */
#define SLOG_RESET "\033[0m"     /*!< ANSI escape code for reset. */
#define SLOG_CYAN "\033[0;36m"   /*!< ANSI escape code for cyan foreground color. */

/*!
 * @}
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
 * \brief           The SLog handler structure.
 *
 * \attention       This structure should not be used directly.
 */
struct SlogHandler {
    FILE *stream;
    enum SlogLevel lv;
    bool apply_colors;
};

#endif /*! SLOG_H */
