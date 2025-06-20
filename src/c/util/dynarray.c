#include "vsched/util/dynarray.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Returns a pointer to the end of a dynarray (not to the end of its allocated memory, just the end of the used buffer)
static void* dynarray_end(dynarray_t* dynarray) {
    assert(dynarray);
    return (void*)((char*)dynarray->data + (dynarray->size * dynarray->elemsize));
}

// Returns the size of a dynarray's allocated memory block
static size_t dynarray_memsize(dynarray_t* dynarray) {
    assert(dynarray);
    return dynarray->capacity * dynarray->elemsize;
}

dynarray_t* dynarray_create(size_t capacity, size_t element_size) {
    size_t dynarray_memsize = capacity * element_size;
    void* pdata = malloc(dynarray_memsize);
    if (!pdata) {
        return NULL; // Buffer allocation failed, give up
    }
    dynarray_t* dynarray = malloc(sizeof(dynarray_t));
    if (!dynarray) {
        free(pdata);
        return NULL; // dynarray struct allocation failed, give up
    }
    dynarray->data = pdata;
    dynarray->size = 0;
    dynarray->capacity = capacity;
    dynarray->elemsize = element_size;
    return dynarray;
};

void dynarray_destroy(dynarray_t* dynarray) {
    assert(dynarray);
    free(dynarray->data);
    free(dynarray);
}

size_t dynarray_size(dynarray_t* dynarray) {
    assert(dynarray);
    return dynarray->size;
}

size_t dynarray_capacity(dynarray_t* dynarray){
    assert(dynarray);
    return dynarray->capacity;
}

size_t dynarray_elemsize(dynarray_t* dynarray) {
    assert(dynarray);
    return dynarray->elemsize;
}

int dynarray_shrink(dynarray_t* dynarray) {
    assert(dynarray);
    size_t new_memsize = dynarray->elemsize * dynarray->size;
    void* newdata = realloc(dynarray->data,new_memsize);
    if (!newdata && new_memsize) {
        // If new_memsize is 0, then returning NULL is intended behavior
        // reallocation failed, return 1. old data pointer is still valid
        return 1;
    }
    // reallocation was successful, reassign data pointer
    dynarray->data = newdata;
    dynarray->capacity = dynarray->size;
    return 0;
}

int dynarray_reserve(dynarray_t* dynarray, size_t new_capacity) {
    assert(dynarray);
    if (new_capacity <= dynarray->capacity) {
        return 0;
    }
    size_t new_memsize = new_capacity * dynarray->elemsize;
    void* newdata = realloc(dynarray->data,new_memsize);
    if (!newdata) {
        // Allocation failed. Element is not added, old data is still valid, return error code
        return 1;
    }
    // Allocation successful
    dynarray->data = newdata;
    dynarray->capacity = new_capacity;
    return 0;
}

int dynarray_push(dynarray_t* dynarray, void* element) {
    assert(dynarray);
    size_t newsize = dynarray->size + 1;
    if (newsize > dynarray->capacity) {
        // adding element would exceed capacity, reallocate
        // doubles current capacity if current capacity is not zero, otherwise sets new capacity to 1
        size_t new_capacity = dynarray->capacity ? dynarray->capacity * 2 : 1;

        // Reallocate dynarray buffer
        int error_code = dynarray_reserve(dynarray,new_capacity);

        if (error_code) {
            // Allocation failed, give up
            return error_code;
        }
    }
    // append element to the end of the dynarray
    memcpy(dynarray_end(dynarray),element,dynarray->elemsize);
    dynarray->size = newsize;
    return 0;
}

int dynarray_clear(dynarray_t* dynarray) {
    assert(dynarray);
    dynarray->size = 0;
    return 0;
}

void* dynarray_get(dynarray_t* dynarray, ptrdiff_t index) {
    assert(dynarray);
    if (index < dynarray->size && index > -dynarray->size) {
        char* base = (char*)(index >= 0 ? dynarray->data : dynarray_end(dynarray));
        return (void*)(base + (index * dynarray->elemsize));
    } else {
        return NULL; // Out-of-range
    }
}

int dynarray_del(dynarray_t* dynarray) {
    assert(dynarray);
    if (dynarray->size == 0) {
        return 1; // dynarray size is 0, error
    }
    dynarray->size--;
    return 0;
}

int dynarray_pop(dynarray_t* dynarray, void* out_element) {
    assert(dynarray && out_element);
    if (dynarray->size == 0) return 1; // empty

    void* last = dynarray_get(dynarray, -1);
    memcpy(out_element, last, dynarray->elemsize);
    dynarray->size--;
    return 0;
}

int dynarray_write(dynarray_t* dynarray, void* element, ptrdiff_t index) {
    assert(element && dynarray);
    void* pelem = dynarray_get(dynarray,index);
    if (!pelem) {
        return 1; // dynarray access failed, give up
    }
    memcpy(pelem,element,dynarray->elemsize);
    return 0;
}