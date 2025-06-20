#include "vsched/util/dlinklist.h"
#include "vsched/vsdef.h"

#include <stdbool.h>
#include <assert.h>

typedef struct dlinklist_node {
    void* data;
    struct dlinklist_node* prev;
    struct dlinklist_node* next;
} dllnode_t;

struct dlinklist {
    dllnode_t* head;
    dllnode_t* tail;
    size_t size;
};

static dllnode_t* dlinklist_node_at(dlinklist_t* dlinklist, ptrdiff_t index) {
    if (VS_EXPECT(index < (ptrdiff_t)dlinklist->size && -index <= (ptrdiff_t)dlinklist->size)) {
        if (index < 0) index = dlinklist->size + index;
        dllnode_t* curr;
        if (index < (ptrdiff_t)dlinklist->size / 2) {
            curr = dlinklist->head;
            for (ptrdiff_t i = 0; i < index; i++) {
                curr = curr->next;
            }
        } else {
            curr = dlinklist->tail;
            ptrdiff_t i = dlinklist->size-1
            for (ptrdiff_t i = (ptrdiff_t)dlinklist->size; i >= index; i--) {
                curr = curr->prev;
            }
        }
        return curr;
    } else {
        return NULL;
    }
}

dlinklist_t* dlinklist_create() {
    dlinklist_t* dlinklist = malloc(sizeof(dlinklist_t));
    if (VS_UNEXPECT(!dlinklist)) {
        return NULL; // Allocation failed, return NULL
    }
    dlinklist->head = NULL;
    dlinklist->tail = NULL;
    dlinklist->size = 0;
    return dlinklist;
}

void dlinklist_destroy(dlinklist_t* dlinklist) {
    assert(dlinklist);
    dllnode_t* current = dlinklist->head;
    while (current) {
        dllnode_t* next = current->next;
        free(current);
        current = next;
    }
    free(dlinklist);
}

void* dlinklist_head(dlinklist_t* dlinklist){
    return dlinklist->head->data;
}

void* dlinklist_tail(dlinklist_t* dlinklist){
    return dlinklist->tail->data;
}

size_t dlinklist_size(dlinklist_t* dlinklist){
    return dlinklist->size;
}

int dlinklist_push_back(dlinklist_t* dlinklist, void* element) {
    dllnode_t* node = malloc(sizeof(dllnode_t));
    if (VS_UNEXPECT(!node)) {
        // allocation failed, give up
        return 1;
    }
    node->data = element;
    node->next = NULL;
    if (dlinklist->tail) {
        node->prev = dlinklist->tail;
        dlinklist->tail->next = node;
    } else {
        dlinklist->head = node;
    }
    dlinklist->tail = node;
    dlinklist->size++;
    return 0;
}

int dlinklist_push_front(dlinklist_t* dlinklist, void* element) {
    dllnode_t* node = malloc(sizeof(dllnode_t));
    if (VS_UNEXPECT(!node)) {
        // allocation failed, give up
        return 1;
    }
    node->data = element;
    node->next = dlinklist->head;
    node->prev = NULL;
    dlinklist->head = node;
    if (!dlinklist->tail) {
        dlinklist->tail = node;
    }
    dlinklist->size++;
    return 0;
}

void dlinklist_reverse(dlinklist_t* dlinklist) {
    if (VS_UNEXPECT(!dlinklist || !dlinklist->head)) return;
    dllnode_t* curr = dlinklist->head;
    dllnode_t* next = NULL;
    dlinklist->head = dlinklist->tail;
    dlinklist->tail = curr;
    while (curr) {
        next = curr->next;
        curr->next = curr->prev;
        curr->prev = next;
        curr = next;
    }
}

void dlinklist_pop_back(dlinklist_t* dlinklist) {
    assert(dlinklist && dlinklist->size > 0);
    dllnode_t* newtail = dlinklist->tail->prev;
    free(dlinklist->tail);
    dlinklist->tail = newtail;
    if (VS_EXPECT(newtail)) {
        newtail->next = NULL;
    } else {
        // If newtail is null, that means the dlinklist had only one element prior to the pop
        dlinklist->head = NULL;
    }
    dlinklist->size--;
}

void dlinklist_pop_front(dlinklist_t* dlinklist) {
    assert(dlinklist && dlinklist->head);
    dllnode_t* newhead = dlinklist->head->next;
    free(dlinklist->head);
    dlinklist->head = newhead;
    if (VS_EXPECT(newhead)){
        newhead->prev = NULL;
    } else {
        // If newhead is null, that means the dlinklist had only one element prior to the pop
        dlinklist->tail = NULL;
    }
    dlinklist->size--;
}

void* dlinklist_get(dlinklist_t* dlinklist, ptrdiff_t index) {
    dllnode_t* node = dlinklist_node_at(dlinklist,index);
    if (VS_EXPECT(node)) {
        return node->data;
    } else {
        return NULL;
    }
}

int dlinklist_insert(dlinklist_t* dlinklist, void* element, ptrdiff_t index) {
    if (index == dlinklist->size) return dlinklist_push_back(dlinklist,element);
    dllnode_t* node = malloc(sizeof(dllnode_t));
    if (VS_UNEXPECT(!node)) {
        // allocation failed, give up
        return 1;
    }
    dllnode_t* nextnode = dlinklist_node_at(dlinklist, index);
    if (VS_UNEXPECT(!nextnode)) {
        return 2; // oob error
    }
    dllnode_t* prevnode = nextnode->prev;
    node->prev = prevnode;
    node->next = nextnode;
    if (prevnode) {
        prevnode->next = node;
    }
    if (nextnode) {
        nextnode->prev = node;
    }
    dlinklist->size++;
    return 0;

}

int dlinklist_remove(dlinklist_t* dlinklist, ptrdiff_t index) {
    dllnode_t* node = dlinklist_node_at(dlinklist,index);
    if (VS_UNEXPECT(!node)) {
        return 2; // oob error
    }
    dllnode_t** prevnext = (node->prev ? &node->prev->next : &dlinklist->head);
    *prevnext = node->next;
    dllnode_t** nextprev = (node->next ? &node->next->prev : &dlinklist->tail);
    *nextprev = node->prev;
    free(node);
    dlinklist->size--;
    return 0;
}
