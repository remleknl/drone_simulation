#include "simulator.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void controller_task(void *args) {
    while (1) {
        /* Task for controller - it will handle drones and survivors */
        sleep(1); // Placeholder for operations
    }
}

int main() {
    List *survivors = create_list(sizeof(Survivor), 10);

    // Create some test survivors and add them to the list
    Survivor s1 = {IDLE, {0, 0}, {0}, "Test Survivor 1"};
    survivors->add(survivors, &s1);

    Survivor s2 = {IDLE, {1, 1}, {0}, "Test Survivor 2"};
    survivors->add(survivors, &s2);

    // Start controller task
    controller_task(NULL);

    return 0;
}
