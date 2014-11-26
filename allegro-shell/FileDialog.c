#include "FileDialog.h"
#include "../global.h"

const char* __FileDialog_get_file__(FileDialog* self) {
    if(!al_show_native_file_dialog(display -> inner_display, self -> inner_dialog)) {
        /* CANNOT CREATE FILE DIALOG EXCEPTION */
        throw(2);
    }

    if(!al_get_native_file_dialog_count(self -> inner_dialog)) {
        return "";
    }

    return al_get_native_file_dialog_path(self -> inner_dialog, 0);
}

void __FileDialog_destroy__(FileDialog** self) {
    al_destroy_native_file_dialog((*self) -> inner_dialog);
    (*self) -> inner_dialog = NULL;

    free(*self);
    *self = NULL;
}

FileDialog* new_FileDialog(const char* title, const char* patterns, int mode) {
    FileDialog* object = malloc(sizeof(FileDialog));
    object -> inner_dialog = al_create_native_file_dialog(NULL, title, patterns, mode);

    object -> get_file = __FileDialog_get_file__;

    return object;
}
