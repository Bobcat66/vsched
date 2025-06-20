#include "vsched/tasks/task.h"

static unsigned long task_counter = 0;
struct task {
    unsigned long id;
    void* context;
    void* composition; // task composition this task is a part of
    void (*init)(void* ctx);
    void (*run)(void* ctx);
    void (*end)(void* ctx);
    bool (*isfinished)(void* ctx);
};