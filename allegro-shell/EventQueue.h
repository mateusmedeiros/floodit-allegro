#ifndef ALLEGRO_SHELL_EVENTQUEUE_H
#define ALLEGRO_SHELL_EVENTQUEUE_H

#include "Display.h"

typedef struct EventQueue {
    ALLEGRO_EVENT_QUEUE* inner_queue;
    ALLEGRO_EVENT current_event;
    ALLEGRO_TIMER* refresh_rate_timer;

    void (*add_source)(struct EventQueue*, ALLEGRO_EVENT_SOURCE*);
    void (*wait_for_event)(struct EventQueue*);
    void (*destroy)(void*);
} EventQueue;

EventQueue* new_EventQueue(Display*);

#endif
