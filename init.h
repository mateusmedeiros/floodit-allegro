#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <setjmp.h>
#include "core/constants.h"
#include "global.h"

#include "mtwist/mtwist.h"

void init(void) {
    if(!al_init()) { longjmp(global_buffer, ALLEGRO_COMPONENT_INITIALIZATION_FAILED); }
    if(!al_install_keyboard()) { longjmp(global_buffer, ALLEGRO_COMPONENT_INITIALIZATION_FAILED); }

    al_init_font_addon();
    if(!al_init_ttf_addon()) { longjmp(global_buffer, ALLEGRO_COMPONENT_INITIALIZATION_FAILED); }

    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    mt_seed();
}
