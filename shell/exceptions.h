#ifndef SHELL_EXCEPTIONS_H
#define SHELL_EXCEPTIONS_H

#include <setjmp.h>

extern jmp_buf __exception_buffer;

typedef enum Exception {
    NECESSARY_RESOURCE_NOT_FOUND = 1,
    ALLEGRO_COMPONENT_INITIALIZATION_FAILED,
    KEYBOARD_NOT_PRESENT,
    NULL_POINTER_EXCEPTION,
    WRONG_FILETYPE_EXCEPTION
} Exception;

#define try(exception) if(!(exception = setjmp(__exception_buffer)))
#define throw(exception) longjmp(__exception_buffer, exception);

#endif
