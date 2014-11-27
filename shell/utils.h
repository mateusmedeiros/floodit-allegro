#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H

#include <limits.h>

/* Not really necessary, but just to be hackish. Great excuse, I know. */

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

#include "colors.h"
#include "../shell/exceptions.h"


/* Will return an ALLEGRO_COLOR of the color especified on the argument */
ALLEGRO_COLOR get_allegro_color(Color color);

/* Show native dialog messages when something goes wrong. */
void print_error(Exception ex);
int file_exists(const char* path);

/* Abstract a setting, including how much bytes it should use on the config.dad */
typedef struct {
    const uint8 code;
    const uint8 value_size;
} Setting;

/* This is the global configuration, note the difference between the current configuration and a single setting.*/
typedef struct {
    uint8 columns;
    uint8 rows;
    uint8 colors;
    uint8 moves;
} Configuration;

/* An enum to abstract the state of the game */
typedef enum RunningState {
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_WON,
    STATE_LOST

} RunningState;


#endif
