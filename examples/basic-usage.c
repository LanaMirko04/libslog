/*!
 * \file            basic-usage.c
 * \date            2025-11-17
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           SLog library example: Basic usage.
 */

#include <stdlib.h>
#include <slog.h>

int main(void) {
    /*! First, we define the configuration for the slog library and initialize it. */
    struct SlogConfig config = {
        .default_logger = SLOG_INIT_DEFAULT_LOGGER,
        .enter_cs = NULL,
        .exit_cs = NULL,
    };
    slog_init(&config);

    /*! Now, we can log messages at different levels. */
    SLOG_INFO("This is an informational message.");
    SLOG_ERROR("This is an error message.");
    SLOG_WARN("This is a warning message.");
    SLOG_DEBUG("This is a debug message.");

    return EXIT_SUCCESS;
}
