#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

typedef struct dlinklist dlinklist_t;

/*
Iterator API
------------
Use `dlinklist_head()` to begin iteration, and `dlliter_next()` to advance.
Use `dlliter_data()` to access the element.
Use `dlinklist_tail()` and `dlliter_prev()` to iterate backwards.
Iterators are invalidated by `dlliter_remove`, but it returns
a new iterator which is valid for list traversal, as long as
the nodes before and after the removed node are still valid and in their
same relative positions. However, this new iterator is not valid for data retrieval
*/
typedef struct dlliter {
    void* prev;
    void* node;
    void* next;
} dlliter_t;

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
dlliter_t dlinklist_head(dlinklist_t* dlinklist);

/*
Returns the element at the end of the dlinklist. UB if the list is empty
*/
dlliter_t dlinklist_tail(dlinklist_t* dlinklist);

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
int dlinklist_insert(dlinklist_t* dlinklist, void* element, ptrdiff_t index);

/*
Removes element at the given index.
*/
int dlinklist_remove(dlinklist_t* dlinklist, ptrdiff_t index);

/*
Accesses element from iterator
*/
void* dlliter_data(dlliter_t dlliter);

/*
Returns next iterator
*/
dlliter_t dlliter_next(dlliter_t dlliter);

/*
Returns previous iterator
*/
dlliter_t dlliter_prev(dlliter_t dlliter);

/*
Removes element at iterator.
*/
dlliter_t dlliter_remove(dlinklist_t* dlinklist, dlliter_t dlliter);


#ifdef __cplusplus
}
#endif // __cplusplus
