#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/* Node type for linked list */
typedef struct node {
    void *data;
    struct node *next;
} Node;

/* Linked list type */
typedef struct list {
    Node *head;
    int number_of_elements;
} List;

/* Function prototypes for list operations */
List* create_list();
void free_list(List *list);
int add_to_list(List *list, void *data);
void* remove_from_list(List *list);
int list_is_empty(List *list);

#endif /* LIST_H */
