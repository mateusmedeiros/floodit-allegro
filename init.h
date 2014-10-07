#include <allegro5/allegro.h>

#include "mtwist/mtwist.h"

void config_init(void) {
    al_init();
    al_set_new_display_flags(ALLEGRO_RESIZABLE);

    mt_seed();
}
