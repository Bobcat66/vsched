#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "vsched/tasks/task.h"
#include "vsched/util/dynarray.h"

typedef struct sequential_task_group sequential_task_group_t;

sequential_task_group_t* sequential_task_group_create(task_t*[]);

#ifdef __cplusplus
}
#endif // __cplusplus
