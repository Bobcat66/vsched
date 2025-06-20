#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

typedef struct linklist linklist_t;

/*
Creates a linklist
*/
linklist_t* linklist_create();

/*
Destroys a linklist. Note: does not destroy the elements
*/
void linklist_destroy(linklist_t* linklist);

/*
Returns the element at the beginning of the linklist. UB if the list is empty
*/
void* linklist_head(linklist_t* linklist);

/*
Returns the element at the end of the linklist. UB if the list is empty
*/
void* linklist_tail(linklist_t* linklist);

/*
Returns the size of the linklist
*/
size_t linklist_size(linklist_t* linklist);

/*
Inserts an element at the end of the linklist. Returns 0 if successful
*/
int linklist_push_back(linklist_t* linklist, void* element);

/*
Inserts an element at the beginning of the linklist. Returns 0 if successful
*/
int linklist_push_front(linklist_t* linklist, void* element);

/*
Reverses the linklist
*/
void linklist_reverse(linklist_t* linklist);

/*
Removes the last element of the linklist
*/
void linklist_pop_back(linklist_t* linklist);

/*
Removes the first element of the linklist
*/
void linklist_pop_front(linklist_t* linklist);

/*
Retrieves element at the given index.
*/
void* linklist_get(linklist_t* linklist, ptrdiff_t index);

/*
Inserts element at the given index.
*/
int linklist_insert(linklist_t* linklist, void* element, ptrdiff_t index);

/*
Removes element at the given index.
*/
int linklist_remove(linklist_t* linklist, ptrdiff_t index);

#ifdef __cplusplus
}
#endif // __cplusplus