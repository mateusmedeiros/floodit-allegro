#ifndef CORE_CONSTANTS_H
#define CORE_CONSTANTS_H

#include "../shell/utils.h"

/* The size in float notation to dedicate to the board itself (with the blocks) */
extern const float MATRIX_BOARD_SIZE;

extern const char* DEFAULT_FONT_PATH;
extern const char* CONFIG_FILE_PATH;

extern const Setting SETTING_COLUMNS;
extern const Setting SETTING_ROWS;
extern const Setting SETTING_NUMBER_OF_COLORS;
extern const Setting SETTING_NUMBER_OF_MOVES;

typedef enum DisplayState { MAIN_MENU, SCENARIO, CONFIG_MENU, PAUSE_MENU} DisplayState;

#endif
