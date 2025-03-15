#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static Node *create_node(size_t datasize) {
    Node *node = (Node *)malloc(sizeof(Node) + datasize);
    node->next = NULL;
    node->prev = NULL;
    node->occupied = 0;
    return node;
}

/* Creates a new list */
List *create_list(size_t datasize, int capacity) {
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->number_of_elements = 0;
    sem_init(&list->sem_number_of_elements, 0, 1);
    list->capacity = capacity;
    sem_init(&list->sem_capacity, 0, 1);
    list->datasize = datasize;
    list->nodesize = sizeof(Node);
    list->startaddress = NULL;
    list->endaddress = NULL;
    list->lastprocessed = NULL;
    list->add = add;
    list->removedata = removedata;
    list->removenode = removenode;
    list->pop = pop;
    list->peek = peek;
    list->destroy = destroy;
    list->printlist = printlist;
    list->printlistfromtail = printlistfromtail;
    list->self = list;
    return list;
}

/* Add a new node to the list */
Node *add(List *list, void *data) {
    if (list->number_of_elements >= list->capacity) {
        return NULL;
    }

    Node *new_node = create_node(list->datasize);
    memcpy(new_node->data, data, list->datasize);

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }

    list->number_of_elements++;
    return new_node;
}

/* Remove node by data */
int removedata(List *list, void *data) {
    Node *node = list->head;
    while (node != NULL) {
        if (memcmp(node->data, data, list->datasize) == 0) {
            removenode(list, node);
            return 0;
        }
        node = node->next;
    }
    return -1;
}

/* Remove a specific node */
int removenode(List *list, Node *node) {
    if (node == NULL) {
        return -1;
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    if (node == list->head) {
        list->head = node->next;
    }
    if (node == list->tail) {
        list->tail = node->prev;
    }

    free(node);
    list->number_of_elements--;
    return 0;
}

/* Pop (remove and return) the first node */
void *pop(List *list, void *dest) {
    if (list->head == NULL) {
        return NULL;
    }

    Node *node = list->head;
    list->head = node->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    }

    memcpy(dest, node->data, list->datasize);
    free(node);
    list->number_of_elements--;

    return dest;
}

/* Peek at the first node's data */
void *peek(List *list) {
    if (list->head == NULL) {
        return NULL;
    }
    return list->head->data;
}

/* Destroy the list */
void destroy(List *list) {
    Node *node = list->head;
    while (node != NULL) {
        Node *next = node->next;
        free(node);
        node = next;
    }

    free(list);
}

/* Print the list */
void printlist(List *list, void (*print)(void*)) {
    Node *node = list->head;
    while (node != NULL) {
        print(node->data);
        node = node->next;
    }
}

/* Print the list from tail */
void printlistfromtail(List *list, void (*print)(void*)) {
    Node *node = list->tail;
    while (node != NULL) {
        print(node->data);
        node = node->prev;
    }
}
