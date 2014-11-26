#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "../core/Scenario.h"
#include "../core/constants.h"
#include "../shell/exceptions.h"
#include "../shell/colors.h"
#include "../global.h"
/*
 * Read a file specified by a null-terminated string and creates a Scenario from the file
 * returns the newly-created Scenario
 */
Scenario* read_scenario_from_file(const char* file_path) {
    FILE* file_ptr;
    Scenario* scenario;
    uint8 header[6];
    uint8 rows;
    uint8 columns;
    uint8 total_of_moves;
    uint8 current_move;
    uint8 number_of_colors;
    uint16 score;
    Color current_color;
    Block* current_row;
    Block* current_column;

    file_ptr = fopen(file_path, "rb");

    if(file_ptr == NULL) {
        throw(NECESSARY_RESOURCE_NOT_FOUND);
    }

    fread(header, sizeof(header), 1, file_ptr);

    if(header[0] != 0x44 || header[1] != 0x4F || header[2] != 0x4F
            || header[3] != 0x53 || header[4] != 0x41 || header[5] != 0x55) {
        fclose(file_ptr);
        throw(WRONG_FILETYPE_EXCEPTION);
    }

    fread(&columns, sizeof(columns), 1, file_ptr);
    fread(&rows, sizeof(rows), 1, file_ptr);
    fread(&number_of_colors, sizeof(number_of_colors), 1, file_ptr);
    fread(&total_of_moves, sizeof(total_of_moves), 1, file_ptr);
    fread(&current_move, sizeof(current_move), 1, file_ptr);
    fread(&score, sizeof(score), 1, file_ptr);

    if(feof(file_ptr)) {
        fclose(file_ptr);
        /* change to CORRUPTED_FILE_EXCEPTION */
        throw(WRONG_FILETYPE_EXCEPTION);
    }

    scenario = new_Scenario(columns, rows, number_of_colors, total_of_moves, display);
    scenario -> current_move = current_move;

    for(current_column = scenario -> first_block; current_column != NULL; current_column = current_column -> right) {
        for(current_row = current_column; current_row != NULL; current_row = current_row -> down) {
            fread(&current_color, sizeof(Color), 1, file_ptr);
            current_row -> set_color(current_row, current_color);
        }
    }

    fclose(file_ptr);

    return scenario;
}

/*
 * Writes a Scenario to a file for reading later
 */
void write_scenario_to_file(const char* file_path, Scenario* scenario) {
    FILE* file_ptr;
    Block* current_row;
    Block* current_column;

    file_ptr = fopen(file_path, "wb");

    if(file_ptr == NULL) {
        /* INVALID PATH */
        throw(NECESSARY_RESOURCE_NOT_FOUND);
    }

    fputc(0x44, file_ptr);
    fputc(0x4F, file_ptr);
    fputc(0x4F, file_ptr);
    fputc(0x53, file_ptr);
    fputc(0x41, file_ptr);
    fputc(0x55, file_ptr);

    fwrite(&(scenario -> size.x), sizeof(scenario -> size.x), 1, file_ptr);
    fwrite(&(scenario -> size.y), sizeof(scenario -> size.y), 1, file_ptr);
    fwrite(&(scenario -> number_of_colors), sizeof(scenario -> number_of_colors), 1, file_ptr);
    fwrite(&(scenario -> number_of_moves), sizeof(scenario -> number_of_moves), 1, file_ptr);
    fwrite(&(scenario -> current_move), sizeof(scenario -> current_move), 1, file_ptr);
    fputc(0x0F, file_ptr);
    fputc(0x0F, file_ptr);

    for(current_column = scenario -> first_block; current_column != NULL; current_column = current_column -> right) {
        for(current_row = current_column; current_row != NULL; current_row = current_row -> down) {
            fwrite(&(current_row -> color_code), sizeof(Color), 1, file_ptr);
        }
    }

    fclose(file_ptr);
}

void read_config_file_to_global_config(void) {
    FILE* file_ptr;
    int i = 0;
    uint8 header[6];
    uint8 number_of_configs;

    file_ptr = fopen(CONFIG_FILE_PATH, "rb");

    if(file_ptr == NULL) {
        throw(NECESSARY_RESOURCE_NOT_FOUND);
    }

    fread(header, sizeof(header), 1, file_ptr);

    if(header[0] != 0x44 || header[1] != 0x4F || header[2] != 0x4F
            || header[3] != 0x44 || header[4] != 0x41 || header[5] != 0x44) {
        fclose(file_ptr);
        throw(WRONG_FILETYPE_EXCEPTION);
    }

    fread(&number_of_configs, sizeof(number_of_configs), 1, file_ptr);

    /* exception work needed here */
    for(i = 0; i < number_of_configs; i++) {
        uint8 config_code;
        fread(&config_code, sizeof(config_code), 1, file_ptr);

        if(config_code == SETTING_COLUMNS.code) {
            int j;
            void* value = malloc(SETTING_COLUMNS.value_size);
            fread(value, SETTING_COLUMNS.value_size, 1, file_ptr);
            for(j = 0; j < SETTING_COLUMNS.value_size; j++) {
                *((&configuration.columns) + j) = *(((uint8*)value) + j);
            }
            free(value);
            value = NULL;
        } else if (config_code == SETTING_ROWS.code) {
            int j;
            void* value = malloc(SETTING_ROWS.value_size);
            fread(value, SETTING_ROWS.value_size, 1, file_ptr);
            for(j = 0; j < SETTING_ROWS.value_size; j++) {
                *((&configuration.rows) + j) = *(((uint8*)value) + j);
            }
            free(value);
            value = NULL;
        } else if(config_code == SETTING_NUMBER_OF_COLORS.code) {
            int j;
            void* value = malloc(SETTING_NUMBER_OF_COLORS.value_size);
            fread(value, SETTING_NUMBER_OF_COLORS.value_size, 1, file_ptr);
            for(j = 0; j < SETTING_NUMBER_OF_COLORS.value_size; j++) {
                *((&configuration.colors) + j) = *(((uint8*)value) + j);
            }
            free(value);
            value = NULL;
        } else if(config_code == SETTING_NUMBER_OF_MOVES.code) {
            int j;
            void* value = malloc(SETTING_NUMBER_OF_MOVES.value_size);
            fread(value, SETTING_NUMBER_OF_MOVES.value_size, 1, file_ptr);
            for(j = 0; j < SETTING_NUMBER_OF_MOVES.value_size; j++) {
                *((&configuration.moves) + j) = *(((uint8*)value) + j);
            }
            free(value);
            value = NULL;
        } else {
            fclose(file_ptr);
            throw(WRONG_FILETYPE_EXCEPTION);
        }

    }
}
