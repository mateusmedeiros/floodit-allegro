#include <allegro5/allegro.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <setjmp.h>


#include "Menu.h"
#include "constants.h"
#include "../mtwist/mtwist.h"
#include "../shell/colors.h"
#include "../shell/utils.h"
#include "../allegro-shell/Display.h"
#include "../global.h"


void __Menu_draw_to_display__(Menu* self) {
    int i;
    ALLEGRO_COLOR color;

    al_clear_to_color(al_map_rgba(0,0,0,0));

    for(i = 0; i < (self -> number_of_entries); i++) {
        if(i == self -> selected_entry) {
            color = al_map_rgba(220, 220, 0, 0);
        } else {
            color = al_map_rgba(255, 255, 255, 0);
        }

        al_draw_text(self -> font, color, 150, i * 50, ALLEGRO_ALIGN_LEFT, self -> entries[i]);
    }
}


void __Menu_destroy__(void* self) {
    free(((Menu*) self) -> entries);
    ((Menu*) self) -> entries = NULL;

    al_destroy_font(((Menu*) self) -> font);

    free((Menu*) self);
    self = NULL;
}


Menu* new_Menu(Display* display, ...) {

    va_list arguments;
    Menu* object = malloc(sizeof(Menu));
    ALLEGRO_FONT* font;

    char* arg;
    char** entries = NULL;
    int i;
    va_start(arguments, display);
    arg = va_arg(arguments, char*);

    for(i = 1; arg != NULL; i++) {
        entries = realloc(entries, i * sizeof(char*));
        entries[i - 1] = arg;
        arg = va_arg(arguments, char*);
    }

    object -> entries = entries;
    object -> number_of_entries = i - 1;
    object -> selected_entry = 0;

    if(!file_exists(DEFAULT_FONT_PATH)){
        va_end(arguments);
        longjmp(global_buffer, NECESSARY_RESOURCE_NOT_FOUND);
    }

    font = al_load_font(DEFAULT_FONT_PATH, 35, 0);

    if(font == NULL) {
        va_end(arguments);
        longjmp(global_buffer, ALLEGRO_COMPONENT_INITIALIZATION_FAILED);
    }

    object -> font = font;
    object -> display = display;

    object -> draw_to_display = __Menu_draw_to_display__;
    object -> destroy = __Menu_destroy__;

    va_end(arguments);

    return object;
}
