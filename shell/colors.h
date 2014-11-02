#ifndef SHELL_COLORS_H
#define SHELL_COLORS_H

#include <allegro5/allegro.h>

typedef enum Color {
                       /*R/G/B/A*/
    RED         = (int)0xFF000000,
    BLUE        = (int)0x0000FF00,
    GREEN       = (int)0x00FF0000
} Color;

extern const Color Colors[];

#endif
