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


void __Menu_draw_to_display__(void* self) {
    int i;
    ALLEGRO_COLOR color;

    al_clear_to_color(get_allegro_color(BACKGROUND_COLOR));

    for(i = 0; i < (((Menu*)self) -> number_of_entries); i++) {
        if(i == ((Menu*)self) -> selected_entry) {
            color = get_allegro_color(YELLOW);
        } else {
            color = get_allegro_color(WHITE);
        }

        al_draw_text(((Menu*)self) -> font, color, 150, i * 50, ALLEGRO_ALIGN_LEFT, ((Menu*)self) -> entries[i]);
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
        entries = realloc(entries, i * sizeof(char**));
        entries[i - 1] = arg;
        arg = va_arg(arguments, char*);
    }

    object -> entries = entries;
    object -> number_of_entries = i - 1;
    object -> selected_entry = 0;

    if(!file_exists(DEFAULT_FONT_PATH)){
        va_end(arguments);
        throw(NECESSARY_RESOURCE_NOT_FOUND);
    }

    font = al_load_font(DEFAULT_FONT_PATH, 35, 0);

    if(font == NULL) {
        va_end(arguments);
        throw(ALLEGRO_COMPONENT_INITIALIZATION_FAILED);
    }

    object -> font = font;
    object -> display = display;

    object -> draw_to_display = __Menu_draw_to_display__;
    object -> destroy = __Menu_destroy__;

    va_end(arguments);

    return object;
}
