#include "simulator.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

Map map;
List *survivors = NULL;
List *helpedsurvivors = NULL;
List *drones = NULL;

/* Initializes the map with given height and width */
void init_map(int height, int width) {
    map.height = height;
    map.width = width;
    map.cells = (MapCell **)malloc(sizeof(MapCell *) * height);

    for (int i = 0; i < height; i++) {
        map.cells[i] = (MapCell *)malloc(sizeof(MapCell) * width);
        for (int j = 0; j < width; j++) {
            map.cells[i][j].coord.x = j;
            map.cells[i][j].coord.y = i;
            map.cells[i][j].survivors = create_list(sizeof(Survivor), 10);
        }
    }
}

/* Frees the map */
void freemap() {
    for (int i = 0; i < map.height; i++) {
        free(map.cells[i]);
    }
    free(map.cells);
}

/* Creates a new survivor and returns a pointer to it */
Survivor *create_survivor(Coord *coord, char *info, struct tm *discovery_time) {
    Survivor *surv = (Survivor *)malloc(sizeof(Survivor));
    surv->coord = *coord;
    surv->status = IDLE;
    strcpy(surv->info, info);
    surv->discovery_time = *discovery_time;
    return surv;
}

/* Generates survivors at random coordinates */
void survivor_generator(void *args) {
    while (1) {
        // Simulate survivor generation at random coordinates
        Coord coord = {rand() % map.width, rand() % map.height};
        char info[25];
        snprintf(info, sizeof(info), "Survivor at (%d,%d)", coord.x, coord.y);

        struct tm discovery_time;
        time_t t = time(NULL);
        localtime_r(&t, &discovery_time);

        Survivor *new_survivor = create_survivor(&coord, info, &discovery_time);
        map.cells[coord.y][coord.x].survivors->add(map.cells[coord.y][coord.x].survivors, new_survivor);

        sleep(1); // Simulate time delay
    }
}

/* Drone controller function that simulates drone operations */
void drone_controller(void *args) {
    while (1) {
        // Simulate drone actions like moving and helping survivors
        // This is a placeholder for future drone-related logic
        sleep(1);
    }
}
