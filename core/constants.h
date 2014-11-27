#ifndef CORE_CONSTANTS_H
#define CORE_CONSTANTS_H

#include "../shell/utils.h"

/* The size in float notation to dedicate to the board itself (with the blocks) */
extern const float MATRIX_BOARD_SIZE;

/* The default font path */
extern const char* DEFAULT_FONT_PATH;

/* The place to look for config.dad (or whichever name it is set) */
extern const char* CONFIG_FILE_PATH;

/* These constants are to define what byte will be considered the byte for a specific configuration on the .dad file */
extern const Setting SETTING_COLUMNS;
extern const Setting SETTING_ROWS;
extern const Setting SETTING_NUMBER_OF_COLORS;
extern const Setting SETTING_NUMBER_OF_MOVES;

/* Enum for the state of the display. This should encompass every different "screen" on the game */
typedef enum DisplayState { MAIN_MENU, SCENARIO, CONFIG_MENU, PAUSE_MENU} DisplayState;

#endif
