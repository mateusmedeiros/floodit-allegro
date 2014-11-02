#ifndef GLOBAL_H
#define GLOBAL_H

#include <setjmp.h>
#include "allegro-shell/Display.h"

extern jmp_buf global_buffer;
extern Display* display;

#endif
