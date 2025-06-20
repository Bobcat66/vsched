#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "vsched/tasks/task.h"

typedef struct scheduler scheduler_t;

scheduler_t* scheduler_create();

void scheduler_run(scheduler_t* scheduler);

void scheduler_add_task(task_t* task);

#ifdef __cplusplus
}
#endif // __cplusplus