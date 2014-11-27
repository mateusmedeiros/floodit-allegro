#ifndef SHELL_IOUTILS
#define SHELL_IOUTILS

#include "../core/Scenario.h"

/* This function writes a file with data of a Scenario, to be restored late (load game / save game). */
void write_scenario_to_file(const char* file_path, Scenario* scenario);

/* This function creates a new Scenario and set the options to the ones of the file passed as argument. */
Scenario* read_scenario_from_file(const char* file_path);

/* Reads a config.dad into the memory / global config of the game */
void read_config_file_to_global_config(void);

#endif
