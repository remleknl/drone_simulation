#include "SDL2/SDL.h"
#include "simulator.h"
#include <assert.h>

void test_init_sdl_window() {
    Map test_map = {10, 10, NULL};
    test_map.cells = (MapCell **)malloc(sizeof(MapCell *) * test_map.height);
    for (int i = 0; i < test_map.height; i++) {
        test_map.cells[i] = (MapCell *)malloc(sizeof(MapCell) * test_map.width);
    }

    assert(init_sdl_window(test_map) == 0);

    quit_all();
}

void test_draw_map() {
    Map test_map = {10, 10, NULL};
    test_map.cells = (MapCell **)malloc(sizeof(MapCell *) * test_map.height);
    for (int i = 0; i < test_map.height; i++) {
        test_map.cells[i] = (MapCell *)malloc(sizeof(MapCell) * test_map.width);
    }

    init_sdl_window(test_map);
    assert(draw_map() == 0);

    quit_all();
}

int main() {
    test_init_sdl_window();
    test_draw_map();

    printf("SDL tests passed.\n");
    return 0;
}
