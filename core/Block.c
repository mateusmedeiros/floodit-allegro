#include <allegro5/allegro.h>
#include <stdlib.h>


#include "Block.h"

void __Block_destroy__(Block** self) {
    (*self) -> up = NULL;
    (*self) -> down = NULL;
    (*self) -> left = NULL;
    (*self) -> right = NULL;
    free(*self);
    *self = NULL;
}

void __Block_set_color__(Block* self, Color color) {
    ALLEGRO_COLOR allegro_color = al_map_rgba((color & 0xFF000000) >> 24, /* R */
                                              (color & 0x00FF0000) >> 16, /* G */
                                              (color & 0x0000FF00) >> 8,  /* B */
                                              (color & 0x000000FF) >> 0); /* A */
    self -> color = allegro_color;
    self -> color_code = color;
}


Block* new_Block(Color color, Block* up, Block* down, Block* right, Block* left) {
    Block* object = malloc(sizeof(Block));

    __Block_set_color__(object, color);
    object -> up = up;
    object -> down = down;
    object -> right = right;
    object -> left = left;

    object -> destroy = __Block_destroy__;
    object -> set_color = __Block_set_color__;

    return object;
}
