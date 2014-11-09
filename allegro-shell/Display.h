#ifndef ALLEGRO_SHELL_DISPLAY_H
#define ALLEGRO_SHELL_DISPLAY_H

#include "../core/constants.h"

typedef void (*DrawingRoutine)(void*);

typedef struct Display {
    ALLEGRO_DISPLAY* inner_display;
    DrawingRoutine drawing_routine;
    void* object_to_be_drawn;
    int height_value;
    int width_value;
    DisplayState current_state;

    void (*destroy)(void*);
    void (*draw)(struct Display*);

    void (*set_drawing_routine)(struct Display* self, void (*drawing_function)(void*), void* object_to_be_drawn);
    int (*height)(struct Display*);
    int (*width)(struct Display*);
} Display;

Display* new_Display(int, int);

#endif
