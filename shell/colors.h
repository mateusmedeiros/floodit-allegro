#ifndef SHELL_COLORS_H
#define SHELL_COLORS_H

#include <allegro5/allegro.h>

//#define GET_COLOR(r, g, b, a) r << 12 + g << 8 + b << 4 + a
typedef uint8_t byte;

//typedef enum Color {
//    //                       R       G       B       A
//    RED =       GET_COLOR(0x00F , 0     , 0     , 0     ),
//    BLUE =      GET_COLOR(0     , 0     , 0x00F , 0     ),
//    GREEN =     GET_COLOR(0     , 0x00F , 0     , 0     )
//} Color;

typedef enum Color {
                  //R/G/B/A
    RED         = 0xFF000000,
    BLUE        = 0x0000FF00,
    GREEN       = 0x00FF0000
} Color;

//typedef struct Colors {
//    Color color[] = { RED, BLUE, GREEN };
//    byte size = 3;
//} Colors;

extern const Color Colors[];

#endif
