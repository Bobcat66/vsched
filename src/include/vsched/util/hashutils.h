#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

typedef size_t (*hash_fn)(const void* key);
typedef int (*hash_eq)(const void* a, const void* b);

size_t uint_hasher(const size_t* key) {
    return *key;
}

size_t int_hasher(const ptrdiff_t* key) {
    return (size_t)*key;
}

#ifdef __cplusplus
}
#endif // __cplusplus