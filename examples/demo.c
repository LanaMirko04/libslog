/*!
 * \file            demo.c
 * \date            2025-11-17
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           SLog library demo: File logging example.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        puts("Usage: demo [FILE]");
        return EXIT_FAILURE;
    }

    /*! First, we define the configuration for the slog library and initialize it. */
    struct SlogConfig config = {
        .default_logger = SLOG_INIT_DEFAULT_LOGGER,
        .enter_cs = NULL,
        .exit_cs = NULL,
    };
    slog_init(&config);

    /*! Now, we open the specified file as a log file. */
    SLOG_INFO("Opening log file: %s", argv[1]);
    FILE *file = fopen(argv[1], "a");
    if (!file) {
        SLOG_ERROR("Unable to open the file: %s", strerror(errno));
    }
    SLOG_INFO("File opened correctly!");

    /*! After opening the file, we create a SLog logger that writes to the file. */
    struct Slogger file_logger = {
        .write_fn = write_to_file,
        .flush_fn = NULL,
        .ctx = file,
        .lv = SLOG_LEVEL_ALL,
        .apply_colors = false,
    };

    SLOG_INFO("This informational message starts here...");
    SLOG_EMIT(&file_logger, SLOG_LEVEL_INFO, "and goes to '%s'! (info)", argv[1]);
    sleep(1);
    SLOG_ERROR("This error message starts here...");
    SLOG_EMIT(&file_logger, SLOG_LEVEL_ERROR, "and goes to '%s'! (error)", argv[1]);
    sleep(1);
    SLOG_WARN("This warning message starts here...");
    SLOG_EMIT(&file_logger, SLOG_LEVEL_WARN, "and goes to '%s'! (warn)", argv[1]);
    sleep(1);
    SLOG_DEBUG("This debug message starts here...");
    SLOG_EMIT(&file_logger, SLOG_LEVEL_DEBUG, "and goes to '%s'! (debug)", argv[1]);
    sleep(1);

    SLOG_INFO("Exiting demo...");
    SLOG_INFO("Closing '%s'", argv[1]);
    fclose(file);

    return EXIT_SUCCESS;
}
