#ifndef ALLEGRO_SHELL_DISPLAY_H
#define ALLEGRO_SHELL_DISPLAY_H

typedef struct Display {
    ALLEGRO_DISPLAY* inner_display;
    int height_value;
    int width_value;

    void (*destroy)(void*);
    int (*height)(struct Display*);
    int (*width)(struct Display*);
} Display;

Display* new_Display(int, int);

#endif
