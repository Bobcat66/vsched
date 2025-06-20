#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>
#include <stdbool.h>

typedef struct task {
    unsigned int id;
    void* context;
    void* composition; // task composition this task is a part of
    void (*init)(void* ctx);
    void (*run)(void* ctx);
    void (*end)(void* ctx);
    bool (*isfinished)(void* ctx);
} task_t;

void task_init(task_t task);

void task_run(task_t task);

void task_end(task_t task);

#ifdef __cplusplus
}
#endif // __cplusplus