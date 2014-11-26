#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "../core/Scenario.h"
#include "../core/constants.h"
#include "../shell/exceptions.h"
#include "../shell/colors.h"
#include "../global.h"

ALLEGRO_COLOR get_allegro_color(Color color) {
    return al_map_rgba((color & 0xFF000000) >> 24, /* R */
                       (color & 0x00FF0000) >> 16, /* G */
                       (color & 0x0000FF00) >> 8,  /* B */
                       (color & 0x000000FF) >> 0); /* A */
}

/*uint32_t to_little_endian(uint32_t bytes) {
//    uint8_t b1 = (bytes & 0xFF000000) >> 24;
//    uint8_t b2 = (bytes & 0x00FF0000) >> 16;
//    uint8_t b3 = (bytes & 0x0000FF00) >> 8;
//    uint8_t b4 = (bytes & 0x000000FF);

//    return b1 | (((uint32_t) b2) << 8) | (((uint32_t) b3) << 16) | (((uint32_t) b4) << 24);
//}*/

int file_exists(const char* path) {
    FILE* file;

    file = fopen(path, "r");
    if(file != NULL) {
        fclose(file);
        return 1;
    }

    return 0;
}

void print_error(Exception ex) {
    ALLEGRO_DISPLAY* exception_display = NULL;
    if(display != NULL) {
        exception_display = display -> inner_display;
    }
    switch(ex) {
        case NECESSARY_RESOURCE_NOT_FOUND:
            al_show_native_message_box(exception_display, "Error!", "Flood-it has failed to initialize!",
                                       "A necessary resource was not found. (font/sound/bitmap/config.dad)?",
                                       NULL, ALLEGRO_MESSAGEBOX_ERROR);
            break;

        case ALLEGRO_COMPONENT_INITIALIZATION_FAILED:
            al_show_native_message_box(exception_display, "Error!", "Flood-it has failed to initialize!",
                                       "Allegro or one of it's components failed on initialization",
                                       NULL, ALLEGRO_MESSAGEBOX_ERROR);
            break;

        case KEYBOARD_NOT_PRESENT:
            al_show_native_message_box(exception_display, "Error!", "Flood-it has failed to initialize!",
                                       "Couldn't find a keyboard.",
                                       NULL, ALLEGRO_MESSAGEBOX_ERROR);
            break;

        default:
            al_show_native_message_box(exception_display, "Error!", "Flood-it has failed to initialize!",
                                       "Unindentified exception",
                                       NULL, ALLEGRO_MESSAGEBOX_ERROR);
            break;
    }
}
