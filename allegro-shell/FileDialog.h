#ifndef ALLEGRO_SHELL_FILEDIALOG_H
#define ALLEGRO_SHELL_FILEDIALOG_H

#include <allegro5/allegro_native_dialog.h>
#include "../core/constants.h"

/* This should just encapsulate and abstract an equivalent struct in allegro (ALLEGRO_FILECHOOSER) */
typedef struct FileDialog {
    ALLEGRO_FILECHOOSER* inner_dialog;

    void (*destroy)(struct FileDialog**);
    const char* (*get_file)(struct FileDialog*);
} FileDialog;

FileDialog* new_FileDialog(const char*, const char*, int);

#endif
