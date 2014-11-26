#ifndef SHELL_IOUTILS
#define SHELL_IOUTILS

#include "../core/Scenario.h"

void write_scenario_to_file(const char* file_path, Scenario* scenario);
Scenario* read_scenario_from_file(const char* file_path);
void read_config_file_to_global_config(void);

#endif
