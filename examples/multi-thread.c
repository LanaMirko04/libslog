/*!
 * \file            multi-thread.c
 * \date            2025-11-17
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           SLog library demo: Multi-threaded logging example.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <slog.h>

#define THREAD_COUNT 5U
#define LOG_MESSAGES 10U

static pthread_mutex_t log_mutex;

static void enter_cs(void) {
    pthread_mutex_lock(&log_mutex);
}

static void exit_cs(void) {
    pthread_mutex_unlock(&log_mutex);
}

static void *thread_func(void *arg) {
    int thread_id = *((int *)arg);
    for (unsigned int i = 0; i < LOG_MESSAGES; i++) {
        SLOG_INFO("Thread %d: Log message %u", thread_id, i + 1);
    }
    return NULL;
}

int main(void) {
    struct SlogConfig config = {
        .default_logger = SLOG_INIT_DEFAULT_LOGGER,
        .enter_cs = enter_cs,
        .exit_cs = exit_cs,
    };
    slog_init(&config);

    pthread_t threads[THREAD_COUNT];
    pthread_mutex_init(&log_mutex, NULL);

    int thread_ids[THREAD_COUNT];
    for (unsigned int i = 0; i < THREAD_COUNT; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (unsigned int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&log_mutex);

    return EXIT_SUCCESS;
}
