#ifndef CORE_MATRIX_H
#define CORE_MATRIX_H

#include <allegro5/allegro.h>

#include "../shell/colors.h"

/* The matrix is made with the pointers. There's NO matrix on Scenario ! */
typedef struct Block {
    ALLEGRO_COLOR color;
    Color color_code;
    struct Block* up;
    struct Block* right;
    struct Block* left;
    struct Block* down;

    void (*set_color)(struct Block*, Color);
    void (*destroy)(struct Block**);
} Block;

Block* new_Block(Color color, Block* up, Block* down, Block* right, Block* left);

#endif
