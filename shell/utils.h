#ifndef CORE_UTILS_H
#define CORE_UTILS_H

#include <limits.h>
#include "../core/constants.h"

#if UCHAR_MAX == 255
    typedef unsigned char uint8;
#elif USHRT_MAX == 255
    typedef unsigned short uint8;
#elif UINT_MAX == 255
    typedef unsigned int uint8;
#elif ULONG_MAX == 255
    typedef unsigned long uint8;
#endif

#if UCHAR_MAX == 65535
    typedef unsigned char uint16;
#elif USHRT_MAX == 65535
    typedef unsigned short uint16;
#elif UINT_MAX == 65535
    typedef unsigned int uint16;
#elif ULONG_MAX == 65535
    typedef unsigned long uint16;
#endif

#if UCHAR_MAX == 4294967295
    typedef unsigned char uint32;
#elif USHRT_MAX == 4294967295
    typedef unsigned short uint32;
#elif UINT_MAX == 4294967295
    typedef unsigned int uint32;
#elif ULONG_MAX == 4294967295
    typedef unsigned long uint32;
#endif

ALLEGRO_COLOR get_allegro_color(Color color);
void print_error(Exception ex);
int file_exists(const char* path);

#endif
