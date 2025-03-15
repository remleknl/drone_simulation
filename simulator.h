#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <time.h>
#include <semaphore.h>
#include "list.h"

#define IDLE 0
#define EMPTY_COORD {0, 0}

/* Coordinate structure */
typedef struct coord {
    int x;
    int y;
} Coord;

/* Survivor structure */
typedef struct survivor {
    int status;
    Coord coord;
    struct tm discovery_time;  /* Discovery time of survivor */
    struct tm helped_time;     /* Time when helped */
    char info[25];             /* Info about survivor */
} Survivor;

/* Map cell structure */
typedef struct mapcell {
    Coord coord;              /* Coordinates in the map */
    List *survivors;          /* Survivors in this cell */
} MapCell;

/* Map structure */
typedef struct map {
    int height;               /* Map height */
    int width;                /* Map width */
    MapCell **cells;          /* 2D array of map cells */
} Map;

/* Drone structure */
typedef struct drone {
    int status;
    int numberofhelped;
    Coord destination;
    Coord coord;
    struct tm stime;
    char info[30];            /* Info about the drone */
} Drone;

extern Map map;

/* Lists */
extern List *survivors;      /* List of survivors waiting for help */
extern List *helpedsurvivors; /* List of helped survivors */
extern List *drones;         /* List of drones */

/* Model functions */
void init_map(int height, int width);
void freemap();
Survivor *create_survivor(Coord *coord, char *info, struct tm *discovery_time);
void survivor_generator(void *args);
void drone_controller(void *args);

/* View functions */
int init_sdl_window(Map map);
int draw_map();
int check_events();
int quit_all();

#endif /* SIMULATOR_H */
