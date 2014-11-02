#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "mtwist/mtwist.h"

void init(void) {
    al_init();
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();

    mt_seed();
}
