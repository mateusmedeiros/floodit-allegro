#include <allegro5/allegro.h>
#include <stdlib.h>


#include "Block.h"

void __Block_destroy__(void* self) {
    ((Block*)self) -> up = NULL;
    ((Block*)self) -> down = NULL;
    ((Block*)self) -> left = NULL;
    ((Block*)self) -> right = NULL;
    free((Block*)self);
    self = NULL;
}


Block* new_Block(Color color, Block* up, Block* down, Block* right, Block* left) {
    Block* object = malloc(sizeof(Block));

    ALLEGRO_COLOR allegro_color = al_map_rgba((color & 0xFF000000) >> 24, /* R */
                                              (color & 0x00FF0000) >> 16, /* G */
                                              (color & 0x0000FF00) >> 8,  /* B */
                                              (color & 0x000000FF) >> 0); /* A */
    object -> color = allegro_color;
    object -> color_code = color;
    object -> up = up;
    object -> down = down;
    object -> right = right;
    object -> left = left;

    object -> destroy = __Block_destroy__;

    return object;
}
