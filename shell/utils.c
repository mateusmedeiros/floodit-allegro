#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "../core/constants.h"
#include <allegro5/allegro.h>
#include "../shell/colors.h"

ALLEGRO_COLOR get_allegro_color(Color color) {
    return al_map_rgba((color & 0xFF000000) >> 24, /* R */
                       (color & 0x00FF0000) >> 16, /* G */
                       (color & 0x0000FF00) >> 8,  /* B */
                       (color & 0x000000FF) >> 0); /* A */
}

uint32_t to_little_endian(uint32_t bytes) {
    uint8_t b1 = (bytes & 0xFF000000) >> 24;
    uint8_t b2 = (bytes & 0x00FF0000) >> 16;
    uint8_t b3 = (bytes & 0x0000FF00) >> 8;
    uint8_t b4 = (bytes & 0x000000FF);

    return b1 | (((uint32_t) b2) << 8) | (((uint32_t) b3) << 16) | (((uint32_t) b4) << 24);
}

void print_error(Exception ex) {
    switch(ex) {
        case NECESSARY_RESOURCE_NOT_FOUND:
            printf("%s", "A necessary resource was not found. (font/sound/bitmap)?");
            break;
        default:
            printf("%s", "Undefined exception");
            break;
    }
}
