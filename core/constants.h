#ifndef CORE_CONSTANTS_H
#define CORE_CONSTANTS_H

/* amount of screen for the block matrix */
extern const float MATRIX_BOARD_SIZE;

extern const char* DEFAULT_FONT_PATH;

typedef enum Exception {
    NECESSARY_RESOURCE_NOT_FOUND = 1,
    ALLEGRO_COMPONENT_INITIALIZATION_FAILED
} Exception;


#endif
