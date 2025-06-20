#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

typedef struct dynarray {
    void* data;
    size_t size;
    size_t capacity;
    size_t elemsize;
} dynarray_t;

/* 
Creates a new dynarray with enough memory preallocated to fit the given capacity. 
Returns a pointer to the dynarray if successful, and NULL if not. 
Passing a negative number as either argument is UB. Passing 0 as element size is UB, 
but passing 0 as capacity is allowed, and creates a dynarray with no preallocated
memory
*/
dynarray_t* dynarray_create(size_t capacity, size_t element_size);

/*
Destroys a dynarray. After this function is called, the dynarray pointer is in an invalid state.
do not dereference or free it
*/
void dynarray_destroy(dynarray_t* dynarray);

/*
Returns size of a dynarray
*/
size_t dynarray_size(dynarray_t* dynarray);

/*
Returns capacity of a dynarray
*/
size_t dynarray_capacity(dynarray_t* dynarray);

/*
Returns element size of a dynarray
*/
size_t dynarray_elemsize(dynarray_t* dynarray);

/*
Reallocates a dynarray's buffer to free unused memory.
Returns 0 if successful, and an error code if not
*/
int dynarray_shrink(dynarray_t* dynarray);

/*
Reallocates a dynarray's buffer to reserve enough memory for the given capacity. 
If the new capacity is lower than the current capacity, this is a no-op. Returns 0 if successful, 
or an error code if the operation fails. Passing a negative number as the new capacity is UB
*/
int dynarray_reserve(dynarray_t* dynarray, size_t new_capacity);

/*
Pushes element to the end of a dynarray, resizing if needed. 
Returns 0 if successful, and an error code if not
*/
int dynarray_push(dynarray_t* dynarray, void* element);

/*
Clears all elements of dynarray. Returns 0 if successful, and an error code if not
*/
int dynarray_clear(dynarray_t* dynarray);

/* 
Returns a pointer to the element at the specified index. 
Negative indices index the dynarray from the end. e.g., -1 would return the last element in the array
Returns NULL if the operation fails.
Note: If the element is deleted after this operation, dereferencing the pointer is UB
*/
void* dynarray_get(dynarray_t* dynarray, ptrdiff_t index);

/*
Deletes the last element of the dynarray
*/
int dynarray_del(dynarray_t* dynarray);

/*
Pops the top element off of the array and copies it to out_element. 
Returns 0 on success, error code on failure
*/
int dynarray_pop(dynarray_t* dynarray, void* out_element);

/*
Overwrites element at the given index. Returns 0 if operation was successful,
returns error code otherwise
*/
int dynarray_write(dynarray_t* dynarray, void* element, ptrdiff_t index);

#ifdef __cplusplus
}
#endif // __cplusplus