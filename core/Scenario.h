#ifndef CORE_SCENARIO_H
#define CORE_SCENARIO_H

#include <allegro5/allegro.h>
#include <stdint.h>

#include "Block.h"
#include "../allegro-shell/Display.h"

typedef uint8_t byte;

typedef struct Scenario {
    byte number_of_colors;
    byte number_of_moves;

    struct size {
        byte x;
        byte y;
    } size;

    Block* first_block;
    Display* display;

    void (*destroy)(void*);
    void (*draw_to_display)(struct Scenario*);
} Scenario;

Scenario* new_Scenario(byte columns, byte rows, byte number_of_colors, byte number_of_moves, Display* display);

#endif
