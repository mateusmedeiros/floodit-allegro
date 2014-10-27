#include <allegro5/allegro.h>
#include <stdlib.h>


#include "Scenario.h"
#include "constants.h"
#include "../mtwist/mtwist.h"
#include "../shell/colors.h"
#include "../allegro-shell/Display.h"


void __Scenario_draw_to_display__(Scenario* self) {
    al_set_target_backbuffer(self -> display -> inner_display);

    int pixels_per_block_x = (self -> display -> width(self -> display) * MATRIX_BOARD_SIZE) / self -> size.x;
    int pixels_per_block_y = (self -> display -> height(self -> display) / self -> size.y);

    //interface
    al_set_clipping_rectangle(0, 0, (1 - MATRIX_BOARD_SIZE) * self -> display -> width(self -> display), self -> display -> height(self -> display));
    al_clear_to_color(al_map_rgba(0,0,0,0));
    //

    int board_pos_x = self -> display -> width(self -> display) - (self -> display -> width(self -> display) * MATRIX_BOARD_SIZE);

    Block* current_block = self -> first_block;
    int i;
    for(i = 0; i < self -> size.y; i++) {
        Block* current_column = current_block;
        int j;
        for(j = 0; j < self -> size.x; j++) {
            al_set_clipping_rectangle(board_pos_x + pixels_per_block_x * j,
                                      pixels_per_block_y * i,
                                      pixels_per_block_x,
                                      pixels_per_block_y);
            al_clear_to_color(current_column -> color);
            current_column = current_column -> right;
        }

        current_block = current_block -> down;
    }

    al_acknowledge_resize(self -> display -> inner_display);
}


void __Scenario_destroy__(void* self) {
    int i;
    for(i = 0; i < ((Scenario*)self) -> size.y; i++) {
        Block* current_column = ((Scenario*)self) -> first_block;

        Block* first_block_below_current_column = current_column -> down;
        int j;
        for(j = 0; j < ((Scenario*)self) -> size.x - 1; j++) {
            current_column = current_column -> right;
            current_column -> left -> destroy(current_column);
        }
        current_column -> destroy(current_column);

        current_column = first_block_below_current_column;
    }

    free((Scenario*)self);
}


Scenario* new_Scenario(byte columns, byte rows, byte number_of_colors, byte number_of_moves, Display* display) {
    Scenario* object = malloc(sizeof(Scenario));
    object -> number_of_colors = number_of_colors;
    object -> number_of_moves = number_of_moves;
    object -> size.x = columns;
    object -> size.y = rows;

    object -> first_block = new_Block(Colors[mt_lrand() % number_of_colors], NULL, NULL, NULL, NULL);
    object -> display = display;

    Block* current_block = object -> first_block;
    int i;
    for(i = 0; i < rows; i++) {
        Block* current_column = current_block;
        int j;
        for(j = 0; j < columns - 1; j++) {
            current_column -> right = new_Block (Colors[mt_lrand() % number_of_colors], NULL, NULL, NULL, NULL);
            current_column = current_column -> right;
        }
        if(i != rows - 1) {
            current_block -> down = new_Block (Colors[mt_lrand() % number_of_colors], NULL, NULL, NULL, NULL);
            current_block = current_block -> down;
        }
    }

    object -> draw_to_display = __Scenario_draw_to_display__;
    object -> destroy = __Scenario_destroy__;

    return object;
}
