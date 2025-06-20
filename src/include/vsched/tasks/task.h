#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>
#include <stdbool.h>

typedef struct task task_t;

task_t* task_create(
    void* context,
    void (*init)(void* ctx),
    void (*run)(void* ctx),
    void (*end)(void* ctx),
    bool (*isfinished)(void* ctx)
);

void task_init(task_t task);

void task_run(task_t task);

void task_end(task_t task);

#ifdef __cplusplus
}
#endif // __cplusplus