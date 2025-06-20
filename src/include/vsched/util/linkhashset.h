#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include "vsched/util/hashutils.h"
#include "vsched/util/dlinklist.h"

typedef struct linkhashset linkhashset_t;

linkhashset_t* linkhashset_create(size_t capacity, hash_fn hasher, hash_eq comparator);

void linkhashset_destroy(linkhashset_t* linkhashset);



#ifdef __cplusplus
}
#endif // __cplusplus