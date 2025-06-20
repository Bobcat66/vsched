#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

typedef struct dlinklist dlinklist_t;

/*
Creates a dlinklist
*/
dlinklist_t* dlinklist_create();

/*
Destroys a linklist. Note: does not destroy the elements
*/
void dlinklist_destroy(dlinklist_t* dlinklist);

/*
Returns the element at the beginning of the dlinklist. UB if the list is empty
*/
void* dlinklist_head(dlinklist_t* dlinklist);

/*
Returns the element at the end of the dlinklist. UB if the list is empty
*/
void* linklist_tail(dlinklist_t* dlinklist);

/*
Returns the size of the dlinklist
*/
size_t dlinklist_size(dlinklist_t* dlinklist);

/*
Inserts an element at the end of the linklist. Returns 0 if successful
*/
int dlinklist_push_back(dlinklist_t* dlinklist, void* element);

/*
Inserts an element at the beginning of the linklist. Returns 0 if successful
*/
int dlinklist_push_front(dlinklist_t* dlinklist, void* element);

/*
Reverses the linklist
*/
void dlinklist_reverse(dlinklist_t* dlinklist);

/*
Removes the last element of the linklist
*/
void dlinklist_pop_back(dlinklist_t* dlinklist);

/*
Removes the first element of the linklist
*/
void dlinklist_pop_front(dlinklist_t* dlinklist);

/*
Retrieves element at the given index.
*/
void* dlinklist_get(dlinklist_t* dlinklist, ptrdiff_t index);

/*
Inserts element at the given index.
*/
int dlinklist_insert(dlinklist_t* linklist, void* element, ptrdiff_t index);

/*
Removes element at the given index.
*/
int dlinklist_remove(dlinklist_t* dlinklist, ptrdiff_t index);

#ifdef __cplusplus
}
#endif // __cplusplus
