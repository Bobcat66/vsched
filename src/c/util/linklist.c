#include "vsched/util/linklist.h"

#include <assert.h>

typedef struct linked_list_node {
    void* data;
    llnode_t* next;
} llnode_t;

struct linklist {
    llnode_t* head;
    llnode_t* tail;
    size_t size;
};

linklist_t* linklist_create() {
    linklist_t* linklist = malloc(sizeof(linklist_t));
    if (!linklist) {
        return NULL; // Allocation failed, return NULL
    }
    linklist->head = NULL;
    linklist->tail = NULL;
    linklist->size = 0;
    return linklist;
}

void linklist_destroy(linklist_t* linklist) {
    llnode_t* current = linklist->head;
    while (current) {
        llnode_t* next = current->next;
        free(current);
        current = next;
    }
    free(linklist);
}

void* linklist_head(linklist_t* linklist){
    return linklist->head->data;
}

void* linklist_tail(linklist_t* linklist){
    return linklist->tail->data;
}

size_t linklist_size(linklist_t* linklist){
    return linklist->size;
}

int linklist_push_back(linklist_t* linklist, void* element) {
    llnode_t* node = malloc(sizeof(llnode_t));
    if (!node) {
        // allocation failed, give up
        return 1;
    }
    node->data = element;
    node->next = NULL;
    linklist->tail->next = node;
    linklist->tail = node;
    return 0;
}

int linklist_push_front(linklist_t* linklist, void* element) {
    llnode_t* node = malloc(sizeof(llnode_t));
    if (!node) {
        // allocation failed, give up
        return 1;
    }
    node->data = element;
    node->next = linklist->head;
    linklist->head = node;
    return 0;
}

void linklist_reverse(linklist_t* linklist);

void linklist_pop_back(linklist_t* linklist);

void linklist_pop_front(linklist_t* linklist);

void* linklist_get(linklist_t* linklist, ptrdiff_t index);

int linklist_insert(linklist_t* linklist, void* element, ptrdiff_t index);

int linklist_remove(linklist_t* linklist, ptrdiff_t index);
