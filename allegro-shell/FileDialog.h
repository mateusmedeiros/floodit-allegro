#ifndef ALLEGRO_SHELL_FILEDIALOG_H
#define ALLEGRO_SHELL_FILEDIALOG_H

#include <allegro5/allegro_native_dialog.h>
#include "../core/constants.h"

typedef struct FileDialog {
    ALLEGRO_FILECHOOSER* inner_dialog;

    void (*destroy)(struct FileDialog**);
    const char* (*get_file)(struct FileDialog*);
} FileDialog;

FileDialog* new_FileDialog(const char*, const char*, int);

#endif
