#include "listtest.h"
#include "list.h"
#include "simulator.h"
#include <assert.h>
#include <stdio.h>

/* Test function to create a new list */
void test_create_list() {
    List *list = create_list(sizeof(Survivor), 10);
    assert(list != NULL);
    assert(list->number_of_elements == 0);
    assert(list->capacity == 10);
    printf("test_create_list passed.\n");
}

/* Test function to add a new survivor to the list */
void test_add() {
    List *list = create_list(sizeof(Survivor), 10);
    Survivor s1 = {IDLE, {0, 0}, {0}, "Test Survivor 1"};
    Node *node = list->add(list, &s1);
    assert(node != NULL);
    assert(list->number_of_elements == 1);
    printf("test_add passed.\n");
}

/* Test function to remove a node by data */
void test_remove_data() {
    List *list = create_list(sizeof(Survivor), 10);
    Survivor s1 = {IDLE, {0, 0}, {0}, "Test Survivor 1"};
    list->add(list, &s1);
    int result = list->removedata(list, &s1);
    assert(result == 0);
    assert(list->number_of_elements == 0);
    printf("test_remove_data passed.\n");
}

/* Test function to remove a node */
void test_remove_node() {
    List *list = create_list(sizeof(Survivor), 10);
    Survivor s1 = {IDLE, {0, 0}, {0}, "Test Survivor 1"};
    Node *node = list->add(list, &s1);
    int result = list->removenode(list, node);
    assert(result == 0);
    assert(list->number_of_elements == 0);
    printf("test_remove_node passed.\n");
}

/* Test function to pop a node */
void test_pop() {
    List *list = create_list(sizeof(Survivor), 10);
    Survivor s1 = {IDLE, {0, 0}, {0}, "Test Survivor 1"};
    list->add(list, &s1);
    Survivor popped;
    list->pop(list, &popped);
    assert(list->number_of_elements == 0);
    printf("test_pop passed.\n");
}

/* Test function to peek the first node */
void test_peek() {
    List *list = create_list(sizeof(Survivor), 10);
    Survivor s1 = {IDLE, {0, 0}, {0}, "Test Survivor 1"};
    list->add(list, &s1);
    Survivor *peeked = (Survivor *)list->peek(list);
    assert(peeked != NULL);
    assert(peeked->status == IDLE);
    printf("test_peek passed.\n");
}

/* Test function to print the list */
void test_printlist() {
    List *list = create_list(sizeof(Survivor), 10);
    Survivor s1 = {IDLE, {0, 0}, {0}, "Test Survivor 1"};
    list->add(list, &s1);
    
    // Simple print function for testing
    list->printlist(list, [](void *data) {
        Survivor *s = (Survivor *)data;
        printf("Survivor: %s at (%d,%d)\n", s->info, s->coord.x, s->coord.y);
    });
    
    printf("test_printlist passed.\n");
}

int main() {
    test_create_list();
    test_add();
    test_remove_data();
    test_remove_node();
    test_pop();
    test_peek();
    test_printlist();

    printf("All tests passed.\n");
    return 0;
}
