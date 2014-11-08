#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdlib.h>

#include "Scenario.h"
#include "constants.h"
#include "../global.h"
#include "../shell/utils.h"
#include "../mtwist/mtwist.h"
#include "../shell/colors.h"
#include "../allegro-shell/Display.h"


void __Scenario_draw_to_display__(void* self) {
    int board_pos_x;
    Block* current_block;
    int i;

    int pixels_per_block_x = ((((Scenario*)self) -> display -> width(((Scenario*)self) -> display) * MATRIX_BOARD_SIZE) / ((Scenario*)self) -> size.x) + 1;
    int pixels_per_block_y = ((((Scenario*)self) -> display -> height(((Scenario*)self) -> display) / ((Scenario*)self) -> size.y)) + 1;

    al_set_target_backbuffer(((Scenario*)self) -> display -> inner_display);

    /* interface */
    al_set_clipping_rectangle(0, 0, (1 - MATRIX_BOARD_SIZE + 0.01) * ((Scenario*)self) -> display -> width(((Scenario*)self) -> display), ((Scenario*)self) -> display -> height(((Scenario*)self) -> display));
    al_clear_to_color(al_map_rgba(39,40,34,0));

    al_draw_text(((Scenario*)self) -> font, get_allegro_color(WHITE),
                 (((Scenario*)self)-> display -> width(((Scenario*)self) -> display) * (1.0 - MATRIX_BOARD_SIZE) * 0.9), 15, ALLEGRO_ALIGN_RIGHT, "281080");

    al_draw_text(((Scenario*)self) -> font, get_allegro_color(WHITE),
                 (((Scenario*)self)-> display -> width(((Scenario*)self) -> display) * (1.0 - MATRIX_BOARD_SIZE) * 0.4), 15, ALLEGRO_ALIGN_RIGHT, "12/25");


    for(i = 0; i < configuration.colors; i++) {
        al_set_clipping_rectangle(((((Scenario*)self)-> display -> width(((Scenario*)self) -> display) * (1.0 - MATRIX_BOARD_SIZE) - pixels_per_block_x) / 2),
                                  (pixels_per_block_y + 20) * (1 + i), pixels_per_block_x, pixels_per_block_y);
        al_clear_to_color(get_allegro_color(Colors[i]));
    }



    board_pos_x = ((Scenario*)self) -> display -> width(((Scenario*)self) -> display) - (((Scenario*)self) -> display -> width(((Scenario*)self) -> display) * MATRIX_BOARD_SIZE);

    current_block = ((Scenario*)self) -> first_block;

    for(i = 0; i < ((Scenario*)self) -> size.y; i++) {
        Block* current_column = current_block;
        int j;
        for(j = 0; j < ((Scenario*)self) -> size.x; j++) {
            al_set_clipping_rectangle(board_pos_x + pixels_per_block_x * j,
                                      pixels_per_block_y * i,
                                      pixels_per_block_x,
                                      pixels_per_block_y);
            al_clear_to_color(current_column -> color);
            current_column = current_column -> right;
        }

        current_block = current_block -> down;
    }

    al_acknowledge_resize(((Scenario*)self) -> display -> inner_display);
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
    self = NULL;
}


Scenario* new_Scenario(uint8 columns, uint8 rows, uint8 number_of_colors, uint8 number_of_moves, Display* display) {
    Scenario* object = malloc(sizeof(Scenario));
    Block* current_block;
    ALLEGRO_FONT* font;
    int i;

    object -> number_of_colors = number_of_colors;
    object -> number_of_moves = number_of_moves;
    object -> size.x = columns;
    object -> size.y = rows;

    if(!file_exists(DEFAULT_FONT_PATH)){
        throw(NECESSARY_RESOURCE_NOT_FOUND);
    }

    font = al_load_font(DEFAULT_FONT_PATH, 16, 0);

    if(font == NULL) {
        throw(ALLEGRO_COMPONENT_INITIALIZATION_FAILED);
    }

    object -> first_block = new_Block(Colors[mt_lrand() % number_of_colors], NULL, NULL, NULL, NULL);
    object -> display = display;
    object -> font = font;

    current_block = object -> first_block;

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
