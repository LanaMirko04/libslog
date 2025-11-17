/*!
 * \file            file-logging.c
 * \date            2025-11-17
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           SLog library demo: File logging example.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <slog.h>

/*!
 * \brief           Write log message to a file.
 *
 * \param[in]       ctx: Context pointer (FILE *).
 * \param[in]       fmt: Format string.
 * \param[in]       ...: Additional arguments.
 * \return          SLOG_RC_OK on success, error code otherwise.
 */
static enum SlogReturnCode write_to_file(const void *ctx, const char *fmt, ...) {
    if (!fmt) {
        return SLOG_RC_INVALID_ARG;
    }

    va_list args;
    va_start(args, fmt);

    FILE *os = (FILE *)ctx;
    vfprintf(os, fmt, args);

    va_end(args);

    return SLOG_RC_OK;
}

int main(void) {
    /*! First, we define the configuration for the slog library and initialize it. */
    struct SlogConfig config = {
        .default_logger = SLOG_INIT_DEFAULT_LOGGER,
        .enter_cs = NULL,
        .exit_cs = NULL,
    };
    slog_init(&config);

    /*! Now, we open a file to log messages into it. */
    FILE *log_file = fopen("output.log", "a");
    if (!log_file) {
        perror("Failed to open log file");
        return EXIT_FAILURE;
    }

    /*! We create a custom logger that writes to the file. */
    struct Slogger file_logger = {
        .write_fn = write_to_file,
        .flush_fn = NULL,
        .ctx = log_file,
        .lv = SLOG_LEVEL_ALL,
        .apply_colors = false,
    };

    /*! Set the file logger as the default logger. */
    slog_set_default_logger(&file_logger, NULL);

    /*! Now we can log messages that will be written to the file. */
    SLOG_INFO("This is an informational message logged to a file.");
    SLOG_ERROR("This is an error message logged to a file.");
    SLOG_WARN("This is a warning message logged to a file.");
    SLOG_DEBUG("This is a debug message logged to a file.");

    /*! Close the log file when done. */
    fclose(log_file);

    return EXIT_SUCCESS;
}
