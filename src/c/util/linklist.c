#include "vsched/util/linklist.h"
#include "vsched/vsdef.h"

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct linked_list_node {
    void* data;
    struct linked_list_node* next;
} llnode_t;

struct linklist {
    llnode_t* head;
    llnode_t* tail;
    size_t size;
};

linklist_t* linklist_create() {
    linklist_t* linklist = malloc(sizeof(linklist_t));
    if (VS_UNEXPECT(!linklist)) {
        return NULL; // Allocation failed, return NULL
    }
    linklist->head = NULL;
    linklist->tail = NULL;
    linklist->size = 0;
    return linklist;
}

void linklist_destroy(linklist_t* linklist) {
    assert(linklist);
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
    if (VS_UNEXPECT(!node)) {
        // allocation failed, give up
        return 1;
    }
    node->data = element;
    node->next = NULL;
    if (linklist->tail) {
        linklist->tail->next = node;
    } else {
        linklist->head = node;
    }
    linklist->tail = node;
    linklist->size++;
    return 0;
}

int linklist_push_front(linklist_t* linklist, void* element) {
    llnode_t* node = malloc(sizeof(llnode_t));
    if (VS_UNEXPECT(!node)) {
        // allocation failed, give up
        return 1;
    }
    node->data = element;
    node->next = linklist->head;
    linklist->head = node;
    if (!linklist->tail) {
        linklist->tail = node;
    }
    linklist->size++;
    return 0;
}

void linklist_reverse(linklist_t* linklist) {
    if (VS_UNEXPECT(!linklist || !linklist->head)) return;
    llnode_t* prev = NULL;
    llnode_t* curr = linklist->head;
    llnode_t* next = NULL;
    linklist->tail = curr;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    linklist->head = prev;
}

void linklist_pop_back(linklist_t* linklist) {
    assert(linklist && linklist->size > 0);
    llnode_t* prev = NULL;
    llnode_t* curr = linklist->head;
    while (curr->next) {
        prev = curr;
        curr = curr->next;
    }
    linklist->tail = prev;
    if (VS_EXPECT(prev)) {
        prev->next = NULL;
    } else {
        // If prev is null, that means the linklist has only one element
        linklist->head = NULL;
    }
    free(curr);
    linklist->size--;
}

void linklist_pop_front(linklist_t* linklist) {
    assert(linklist && linklist->head);
    llnode_t* newhead = linklist->head->next;
    free(linklist->head);
    linklist->head = newhead;
    if (VS_UNEXPECT(!newhead)) linklist->tail = NULL;
    linklist->size--;
}

void* linklist_get(linklist_t* linklist, ptrdiff_t index) {
    if (VS_EXPECT(index < (ptrdiff_t)linklist->size && -index <= (ptrdiff_t)linklist->size)) {
        if (index < 0) index = linklist->size + index;
        llnode_t* curr = linklist->head;
        for (ptrdiff_t i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->data;
    } else {
        return NULL;
    }
}

int linklist_insert(linklist_t* linklist, void* element, ptrdiff_t index) {
    if (VS_EXPECT(index <= (ptrdiff_t)linklist->size && -index <= (ptrdiff_t)linklist->size)) {
        llnode_t* node = malloc(sizeof(llnode_t));
        if (VS_UNEXPECT(!node)) {
            // allocation failed, give up
            return 1;
        }
        node->data = element;
        if (index < 0) index = linklist->size + index;
        llnode_t* prev = NULL;
        llnode_t* next = linklist->head;
        for (ptrdiff_t i = 0; i < index; i++) {
            prev = next;
            next = prev->next;
        }
        node->next = next;
        if (!prev) {
            linklist->head = node;
        } else {
            prev->next = node;
        }
        if (!next) {
            linklist->tail = node;
        }
        linklist->size++;
        return 0;
    } else {
        return 2; // Out of bounds error 
    }

}

int linklist_remove(linklist_t* linklist, ptrdiff_t index) {
    if (VS_EXPECT(index < (ptrdiff_t)linklist->size && -index <= (ptrdiff_t)linklist->size)) {
        if (index < 0) index = linklist->size + index;
        llnode_t* prev = NULL;
        llnode_t* curr = linklist->head;
        for (ptrdiff_t i = 0; i < index; i++) {
            prev = curr;
            curr = curr->next;
        }
        llnode_t** prevnext = (prev ? &prev->next : &linklist->head);
        *prevnext = curr->next;
        free(curr);
        linklist->size--;
        if (!(linklist->size)) {
            linklist->tail = NULL;
        }
        return 0;
    } else {
        return 2; // Out of bounds error 
    }
}
