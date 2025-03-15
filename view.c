#include "SDL2/SDL.h"
#include "simulator.h"

#define CSIZE 20 /* Cell size in SDL-grid */

/* Window management variables */
SDL_bool done = 1;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;

int windowheight = 0;
int windowwidth = 0;

/* Initializes the SDL window and renderer */
int init_sdl_window(Map map) {
    windowheight = map.height * CSIZE; /* Height of the window */
    windowwidth = map.width * CSIZE;   /* Width of the window */
    printf("height: %d, width:%d\n", windowheight, windowwidth);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
        return 1;
    }

    /* Creates SDL window */
    window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowwidth, windowheight, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer != NULL) {
        SDL_SetWindowTitle(window, "Medeniyet Drone Simulator");
        done = 0;
    } else {
        perror("Renderer Error");
    }

    return done;
}

/* Draw rectangles for map cells */
static void draw_rectangles() {
    for (int i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            SDL_Rect rect = {CSIZE * j, CSIZE * i, CSIZE, CSIZE};

            if (map.cells[i][j].survivors != NULL && map.cells[i][j].survivors->number_of_elements != 0) {
                int r = map.cells[i][j].survivors->number_of_elements;
                r = (r % 15);
                SDL_SetRenderDrawColor(renderer, 100 + r * 10, 255 - r * 10, 0, SDL_ALPHA_OPAQUE);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            }

            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

/* Draw the entire map */
int draw_map() {
    draw_rectangles();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (int i = 0; i <= windowheight; i = i + CSIZE) {
        SDL_RenderDrawLine(renderer, 0, i, windowwidth, i);
    }

    SDL_SetRenderDrawColor(renderer, 255, 155, 155, SDL_ALPHA_OPAQUE);

    for (int j = 0; j <= windowwidth; j = j + CSIZE) {
        SDL_RenderDrawLine(renderer, j, 0, j, windowheight);
    }

    SDL_RenderPresent(renderer);

    return 0;
}

/* Check for quit events */
int check_events() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
            done = 1;
        }
    }

    return done;
}

/* Quit SDL and clean up */
int quit_all() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();

    return 0;
}
