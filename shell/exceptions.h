#ifndef SHELL_EXCEPTIONS_H
#define SHELL_EXCEPTIONS_H

#include <setjmp.h>

/* A global jmp_buf, to be used internally with the macros. Should not ever be touched directly. */
extern jmp_buf __exception_buffer;

/* An enum for the different kind of exceptions. The Exception number here is also returned as the end code if any exception occurs */
typedef enum Exception {
    NECESSARY_RESOURCE_NOT_FOUND = 1,
    ALLEGRO_COMPONENT_INITIALIZATION_FAILED,
    KEYBOARD_NOT_PRESENT,
    NULL_POINTER_EXCEPTION,
    WRONG_FILETYPE_EXCEPTION
} Exception;

/* Two macros for try and throw */
#define try(exception) if(!(exception = setjmp(__exception_buffer)))
#define throw(exception) longjmp(__exception_buffer, exception);

#endif
