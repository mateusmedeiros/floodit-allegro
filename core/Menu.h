#ifndef CORE_MENU_H
#define CORE_MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>

#include "Block.h"
#include "../shell/utils.h"
#include "../allegro-shell/Display.h"

typedef struct Menu {
    uint8 number_of_entries;
    uint8 selected_entry;
    char** entries;
    ALLEGRO_FONT* font;

    Display* display;

    void (*destroy)(void*);
    void (*draw_to_display)(struct Menu*);
} Menu;

Menu* new_Menu(Display* display, ...);

#endif
