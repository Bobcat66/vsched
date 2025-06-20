#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "vsched/tasks/task.h"
#include "vsched/util/dynarray.h"

typedef struct sequential_task_group {
    task_t task;
    dynarray_t* tasks;
} sequential_task_group_t;

int sequential_task_group_add_task(
    sequential_task_group_t* sequential_task_group,
    task_t* task
);

#ifdef __cplusplus
}
#endif // __cplusplus
