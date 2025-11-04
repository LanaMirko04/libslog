/**
 * \file            slog-api.h
 * \date            2025-11-04
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           SLog (Sh*tty Logging) library implementation.
 */

#ifndef SLOG_API
#define SLOG_API

#include "slog.h"

#ifdef __cplusplus
extern "C" {
#endif /*! __cplusplus */

/*!
 * \brief           Initialize the Slog logging system with the specified log level.
 *
 * \details         This function initializes the default logging system with the given log level.
 */
void slog_api_init(enum SlogLevel lv);

/*!
 * \brief           Initialize a SlogHandler with the specified log level and file path.
 *
 * \param           handler: Pointer to the SlogHandler structure to be initialized.
 * \param           lv: The log level to be set for the handler.
 * \param           file_path: The file path where the logs will be written. It can be NULL for
 *                  default behavior (standard output).
 * \return          SLOG_RC_OK on success, or an error code on failure:
 *                   - SLOG_RC_INVALID_ARG if the handler pointer is NULL.
 *                   - SLOG_RC_IO_ERR if there was an error opening the specified file.
 */
enum SlogReturnCode slog_api_init_handler(struct SlogHandler *handler, enum SlogLevel lv, const char *file_path, bool apply_colors);

/*!
 * \brief           Set the default handler for the logging system.
 *
 * \param new       Pointer to the new default handler to be set.
 * \param old       Pointer to a SlogHandler structure where the previous default handler will be
 *                  stored. This parameter can be NULL if the previous handler is not needed.
 * \return          SLOG_RC_OK on success, or an error code on failure:
 *                   - SLOG_RC_INVALID_ARG if the new handler is NULL.
 */
enum SlogReturnCode slog_api_set_default_handler(const struct SlogHandler *new, struct SlogHandler *old);

/*!
 * \brief           Get the current default handler for the logging system.
 *
 * \return          Pointer to the current default SlogHandler.
 */
const struct SlogHandler *slog_api_get_default_handler(void);

/*!
 * \brief           Deinitialize the SlogHandler and close any associated resources.
 */
void slog_api_deinit_handler(struct SlogHandler *handler);

#ifdef __cplusplus
}
#endif /*! __cplusplus */

/*!
 * \internal
 * \brief           The default handler.
 *
 * \attention       This variable is intended for internal use only.
 */
extern struct SlogHandler slog_default_handler;

#endif /*! SLOG_API */
