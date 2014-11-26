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
    ALLEGRO_USTR* moves_string;
    int i;

    /* calculate size of each block based on the display size and the MATRIX_BOARD_SIZE
     * constant (that defines the width of the black bar in float notation)            */
    int pixels_per_block_x = ((((Scenario*)self) -> display -> width(((Scenario*)self) -> display) * MATRIX_BOARD_SIZE) / ((Scenario*)self) -> size.x) + 1;
    int pixels_per_block_y = ((((Scenario*)self) -> display -> height(((Scenario*)self) -> display) / ((Scenario*)self) -> size.y)) + 1;

    /* set draw target to be the display */
    al_set_target_backbuffer(((Scenario*)self) -> display -> inner_display);

    /* draw black bar */
    al_set_clipping_rectangle(0, 0, (1 - MATRIX_BOARD_SIZE + 0.01) * ((Scenario*)self) -> display -> width(((Scenario*)self) -> display), ((Scenario*)self) -> display -> height(((Scenario*)self) -> display));
    al_clear_to_color(get_allegro_color(BACKGROUND_COLOR));

    /* draw score */
    al_draw_text(((Scenario*)self) -> font, get_allegro_color(WHITE),
                 (((Scenario*)self)-> display -> width(((Scenario*)self) -> display) * (1.0 - MATRIX_BOARD_SIZE) * 0.9), 15, ALLEGRO_ALIGN_RIGHT, "281080");

    /* draw number of moves */
    moves_string = al_ustr_newf("%d/%d", ((Scenario*)self) -> current_move - 1, ((Scenario*)self) -> number_of_moves);
    al_draw_ustr(((Scenario*)self) -> font, get_allegro_color(WHITE),
                 (((Scenario*)self)-> display -> width(((Scenario*)self) -> display) * (1.0 - MATRIX_BOARD_SIZE) * 0.4), 15, ALLEGRO_ALIGN_RIGHT, moves_string);
    al_ustr_free(moves_string);

    /* draw blocks in the black bar (including selection box) */
    for(i = 0; i < configuration.colors; i++) {
        uint16 x = ((((Scenario*)self)-> display -> width(((Scenario*)self) -> display) * (1.0 - MATRIX_BOARD_SIZE) - pixels_per_block_x) / 2);
        uint16 y = (pixels_per_block_y + 20) * (1 + i);

        if(i == ((Scenario*) self) -> selected_color) {
            al_set_clipping_rectangle(x - 3, y - 3, pixels_per_block_x + 6, pixels_per_block_y + 6);
            al_clear_to_color(get_allegro_color(YELLOW));
            al_set_clipping_rectangle(x - 1, y - 1, pixels_per_block_x + 2, pixels_per_block_y + 2);
            al_clear_to_color(get_allegro_color(BACKGROUND_COLOR));
        }
        al_set_clipping_rectangle(x, y, pixels_per_block_x, pixels_per_block_y);
        al_clear_to_color(get_allegro_color(Colors[i]));
    }

    /* draw the block matrix / board */
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

    /* acknowledge resize is needed for the display to update width and height info at resizing */
    al_acknowledge_resize(((Scenario*)self) -> display -> inner_display);
}

void __Scenario_flood_colors__(Block* block, Color original, Color desired) {
    if(block == NULL || block -> color_code != original) {
        return;
    }

    block -> color = get_allegro_color(desired);
    block -> color_code = desired;

    __Scenario_flood_colors__(block -> right, original, desired);
    __Scenario_flood_colors__(block -> left, original, desired);
    __Scenario_flood_colors__(block -> up, original, desired);
    __Scenario_flood_colors__(block -> down, original, desired);
}

void __Scenario_flood__(Scenario* self, Color color) {
    Block* current_column_block;
    Block* current_row_block;

    Color first_color = self -> first_block -> color_code;
    __Scenario_flood_colors__(self -> first_block, first_color, color);

    if((self -> current_move) > (self -> number_of_moves)) {
        self -> state = STATE_LOST;
        return;
    }

    for(current_column_block = self -> first_block; current_column_block != NULL; current_column_block = current_column_block -> right) {
        for(current_row_block = current_column_block; current_row_block != NULL; current_row_block = current_row_block -> down) {
            if(current_row_block -> color_code != first_color) {
                return;
            }
        }
    }

    self -> state = STATE_WON;
}


void __Scenario_destroy__(Scenario** self) {
    Block* current_row = (*self) -> first_block;
    while(current_row != NULL) {
        Block* temp = current_row;
        Block* current_col = temp;
        current_row = current_row -> down;

        while(current_col != NULL) {
            Block* block_to_be_destroyed = current_col;
            current_col = current_col -> right;
            block_to_be_destroyed -> destroy(&block_to_be_destroyed);
        }
    }

    free(*self);
    *self = NULL;
}


Scenario* new_Scenario(uint8 columns, uint8 rows, uint8 number_of_colors, uint8 number_of_moves, Display* display) {
    Scenario* object = malloc(sizeof(Scenario));
    Block* first_on_current_row;
    ALLEGRO_FONT* font;
    uint8 row_it;

    object -> number_of_colors = number_of_colors;
    object -> number_of_moves = number_of_moves;
    object -> size.x = columns;
    object -> size.y = rows;
    object -> selected_color = 0;
    object -> current_move = 1;

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

    first_on_current_row = object -> first_block;

    for(row_it = 0; row_it < rows; row_it++, first_on_current_row = first_on_current_row -> down) {
        Block* above_next_column_block;
        Block* current_column = first_on_current_row;
        uint8 column_it;

        for(column_it = 0; column_it < columns - 1; column_it++, current_column = current_column -> right) {
            if(row_it == 0) {
                current_column -> right = new_Block (Colors[mt_lrand() % number_of_colors], NULL, NULL, NULL, current_column);
            } else {
                uint8 k;
                above_next_column_block = first_on_current_row -> up;

                for(k = 0; k <= column_it; k++) {
                    above_next_column_block = above_next_column_block -> right;
                }
                current_column -> right = new_Block (Colors[mt_lrand() % number_of_colors], above_next_column_block, NULL, NULL, current_column);
                above_next_column_block -> down = current_column -> right;
            }

            if(column_it == 0 && row_it != rows - 1) {
                first_on_current_row -> down = new_Block (Colors[mt_lrand() % number_of_colors], first_on_current_row, NULL, NULL, NULL);
            }
        }
    }

    object -> flood = __Scenario_flood__;
    object -> draw_to_display = __Scenario_draw_to_display__;
    object -> destroy = __Scenario_destroy__;

    return object;
}
