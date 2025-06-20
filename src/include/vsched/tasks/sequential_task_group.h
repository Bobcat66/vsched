#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "vsched/tasks/task.h"

typedef struct sequential_task_group {
    task_t task;
} sequential_task_group_t;

#ifdef __cplusplus
}
#endif // __cplusplus
