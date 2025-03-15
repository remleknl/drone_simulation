#ifndef LIST_H
#define LIST_H

#include <semaphore.h>
#include <stddef.h>  // For size_t

typedef struct node {
    struct node *prev;
    struct node *next;
    char occupied;
    char data[];  // Flexible array member for data storage
} Node;

typedef struct list {
    Node *head;
    Node *tail;
    int number_of_elements; /* Current number of elements in the list */
    sem_t sem_number_of_elements; /* Semaphore for number_of_elements */
    int capacity; /* Maximum capacity of the list */
    sem_t sem_capacity; /* Semaphore for capacity */
    int datasize; /* Size of the data in each node (e.g. sizeof(Survivor)) */
    int nodesize; /* Total size of a node, including prev and next pointers */
    char *startaddress; /* Starting address of the list */
    char *endaddress; /* End address of the list */
    Node *lastprocessed; /* Points to the last processed node */
    
    /* Operations on the list */
    Node *(*add)(struct list *list, void *data);  // Add a new node with data
    int  (*removedata)(struct list *list, void *data);  // Remove node by data
    int (*removenode)(struct list *list, Node *node);  // Remove a specific node
    void *(*pop)(struct list *list, void *dest);  // Pop (remove and return) the first node
    void *(*peek)(struct list *list);  // Peek at the first node's data
    void (*destroy)(struct list *list);  // Destroy the list
    void (*printlist)(struct list *list, void (*print)(void*));  // Print the list
    void (*printlistfromtail)(struct list *list, void (*print)(void*));  // Print the list from tail
    
    struct list *self;  // Self-reference to the list for recursive operations
} List;

/* Function Prototypes */
List *create_list(size_t datasize, int capacity);  // Create a new list
int removenode(List *list, Node *node);  // Remove a node
Node *add(List *list, void *data);  // Add a node to the list
int removedata(List *list, void *data);  // Remove a node by its data
void *pop(List *list, void *dest);  // Pop a node from the list
void *peek(List *list);  // Peek at the first node's data
void destroy(List *list);  // Destroy the list and free memory
void printlist(List *list, void (*print)(void*));  // Print the list's data
void printlistfromtail(List *list, void (*print)(void*));  // Print the list's data from tail

#endif /* LIST_H */
