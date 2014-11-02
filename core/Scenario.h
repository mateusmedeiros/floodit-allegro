#ifndef CORE_SCENARIO_H
#define CORE_SCENARIO_H

#include <allegro5/allegro.h>
#include <stdint.h>

#include "Block.h"
#include "../shell/utils.h"
#include "../allegro-shell/Display.h"

typedef struct Scenario {
    uint8 number_of_colors;
    uint8 number_of_moves;

    struct size {
        uint8 x;
        uint8 y;
    } size;

    Block* first_block;
    Display* display;

    void (*destroy)(void*);
    void (*draw_to_display)(struct Scenario*);
} Scenario;

Scenario* new_Scenario(uint8 columns, uint8 rows, uint8 number_of_colors, uint8 number_of_moves, Display* display);

#endif
