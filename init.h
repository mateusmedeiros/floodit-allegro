#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "shell/exceptions.h"
#include "shell/utils.h"

#include "mtwist/mtwist.h"

void init(void) {
    if(!al_init()) { throw(ALLEGRO_COMPONENT_INITIALIZATION_FAILED); }
    if(!al_install_keyboard()) { throw(ALLEGRO_COMPONENT_INITIALIZATION_FAILED); }

    al_init_font_addon();
    if(!al_init_ttf_addon()) { throw(ALLEGRO_COMPONENT_INITIALIZATION_FAILED); }

    al_set_new_display_flags(ALLEGRO_RESIZABLE);

    read_config_file_to_global_config();

    mt_seed();
}
