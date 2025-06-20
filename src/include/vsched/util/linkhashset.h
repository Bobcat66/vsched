#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <stdbool.h>
#include "vsched/util/hashutils.h"
#include "vsched/util/dlinklist.h"

typedef struct linkhashset linkhashset_t;

linkhashset_t* linkhashset_create(size_t capacity, hash_fn hasher, hash_eq comparator);

void linkhashset_destroy(linkhashset_t* linkhashset);

/*
Inserts an element. Returns 1 if inserted, 0 if already present, or -1 on allocation failure.
*/
int linkhashset_insert(linkhashset_t* set, void* element);

/*
Removes an element. Returns 1 if removed, 0 if not found.
*/
int linkhashset_remove(linkhashset_t* set, const void* element);

/*
Returns true if the element exists in the set.
*/
bool linkhashset_contains(linkhashset_t* set, const void* element);

/*
Returns the number of elements in the set.
*/
size_t linkhashset_size(linkhashset_t* set);

/*
These methods provide iterators to the underlying dlinklist
Begin with `linkhashset_head()`, traverse with `dlliter_next()`, and access via `dlliter_data()`.
Removal by iterator is not supported
*/

dlliter_t linkhashset_iter_head(linkhashset_t* set);
dlliter_t linkhashset_iter_tail(linkhashset_t* set);

#ifdef __cplusplus
}
#endif // __cplusplus