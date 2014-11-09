#ifndef SHELL_COLORS_H
#define SHELL_COLORS_H

#include <allegro5/allegro.h>

typedef enum Color {
                               /*R G B A*/
    RED                 = (int)0xF0322F00,
    BLUE                = (int)0x268BF200,
    GREEN               = (int)0x16AF0E00,
    YELLOW              = (int)0xEEEE0000,
    GRAY                = (int)0x66666600,
    WHITE               = (int)0xDDDDDD00,
    WHEAT               = (int)0xEFB57100,
    PURPLE              = (int)0xB177B900,
    BACKGROUND_COLOR    = (int)0x27282200
} Color;

extern const Color Colors[];

#endif
