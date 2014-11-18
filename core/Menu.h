#ifndef CORE_MENU_H
#define CORE_MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "Block.h"
#include "../shell/utils.h"
#include "../allegro-shell/Display.h"

typedef struct Menu {
    uint8 number_of_entries;
    uint8 selected_entry;
    char** entries;
    ALLEGRO_FONT* font;

    Display* display;

    void (*destroy)(struct Menu**);
    void (*draw_to_display)(void*);
} Menu;

Menu* new_Menu(Display* display, ...);

#endif
