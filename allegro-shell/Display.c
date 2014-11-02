#include <allegro5/allegro.h>
#include <stdlib.h>


#include "Display.h"

int __Display_height__(Display* self) {
    al_get_display_height(self -> inner_display);
}

int __Display_width__(Display* self) {
    al_get_display_width(self -> inner_display);
}

void __Display_destroy__(void* self) {
    al_destroy_display(((Display*)self) -> inner_display);
    ((Display*)self) -> inner_display = NULL;

    free((Display*)self);
    self = NULL;
}


Display* new_Display(int width, int height) {
    Display* object = malloc(sizeof(Display));
    object -> height_value = height;
    object -> width_value = width;
    object -> inner_display = al_create_display(width, height);

    object -> height = __Display_height__;
    object -> width = __Display_width__;
    object -> destroy = __Display_destroy__;

    return object;
}
