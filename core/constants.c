#include "../shell/utils.h"

const float MATRIX_BOARD_SIZE = 0.8;

/* make the filepath more portable later, if possible */
const char* DEFAULT_FONT_PATH = "resources/verdana.ttf";

/* make the filepath more portable later, if possible */
const char* CONFIG_FILE_PATH = "config.dad";

const Setting SETTING_COLUMNS = { 0xC0, 1 };
const Setting SETTING_ROWS = { 0x05, 1 };
const Setting SETTING_NUMBER_OF_COLORS = { 0xC5, 1 };
const Setting SETTING_NUMBER_OF_MOVES = { 0xE0, 1 };
