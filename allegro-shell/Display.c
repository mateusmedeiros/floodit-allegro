#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdlib.h>
#include "../shell/exceptions.h"

#include "Display.h"


void __Display_draw__(Display* self) {
    if(self -> drawing_routine == NULL || self -> object_to_be_drawn == NULL) {
        al_show_native_message_box(self -> inner_display, "Error", "Error",
                                   "Not possible to draw without a drawing routine set and an object to call this routine",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        throw(NULL_POINTER_EXCEPTION);
    }

    self -> drawing_routine(self -> object_to_be_drawn);
    al_flip_display();
}

void __Display_set_drawing_routine__(Display* self, DrawingRoutine drawing_function, void* object_to_be_drawn) {
    self -> drawing_routine = drawing_function;
    self -> object_to_be_drawn = object_to_be_drawn;
}

int __Display_height__(Display* self) {
    return al_get_display_height(self -> inner_display);
}

int __Display_width__(Display* self) {
    return al_get_display_width(self -> inner_display);
}

void __Display_destroy__(Display** self) {
    al_destroy_display((*self) -> inner_display);
    (*self) -> inner_display = NULL;

    free(*self);
    *self = NULL;
}


Display* new_Display(int width, int height) {
    Display* object = malloc(sizeof(Display));
    object -> height_value = height;
    object -> width_value = width;
    object -> inner_display = al_create_display(width, height);

    if(object -> inner_display == NULL) {
        throw(ALLEGRO_COMPONENT_INITIALIZATION_FAILED);
    }

    object -> height = __Display_height__;
    object -> width = __Display_width__;
    object -> destroy = __Display_destroy__;
    object -> set_drawing_routine = __Display_set_drawing_routine__;
    object -> draw = __Display_draw__;
    object -> drawing_routine = NULL;
    object -> object_to_be_drawn = NULL;
    object -> current_state = MAIN_MENU;

    return object;
}
