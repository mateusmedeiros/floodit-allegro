#include "allegro5/allegro.h"
#include "../shell/colors.h"

ALLEGRO_COLOR get_allegro_color(Color color) {
    return al_map_rgba((color & 0xFF000000) >> 24, // R
                       (color & 0x00FF0000) >> 16, // G
                       (color & 0x0000FF00) >> 8,  // B
                       (color & 0x000000FF) >> 0); // A
}
