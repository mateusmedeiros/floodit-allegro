#include <allegro5/allegro.h>
#include <stdlib.h>

#include "EventQueue.h"
#include "Display.h"

void __EventQueue_wait_for_event__(EventQueue* self) {
    al_wait_for_event(self -> inner_queue, &(self -> current_event));
}

void __EventQueue_add_source__(EventQueue* self, ALLEGRO_EVENT_SOURCE* source) {
    al_register_event_source(self -> inner_queue, source);
}

void __EventQueue_destroy__(void* self) {
    al_destroy_timer(((EventQueue*)self) -> refresh_rate_timer);
    ((EventQueue*)self) -> refresh_rate_timer = NULL;

    al_destroy_event_queue(((EventQueue*)self) -> inner_queue);
    ((EventQueue*)self) -> inner_queue = NULL;

    free((EventQueue*)self);
    self = NULL;
}

EventQueue* new_EventQueue(Display* display) {
    EventQueue* object = malloc(sizeof(EventQueue));
    ALLEGRO_TIMER* timer;
    int refresh_rate;

    object -> inner_queue = al_create_event_queue();

    object -> wait_for_event = __EventQueue_wait_for_event__;
    object -> add_source = __EventQueue_add_source__;
    object -> destroy = __EventQueue_destroy__;

    al_register_event_source(object -> inner_queue, al_get_display_event_source(display -> inner_display));

    refresh_rate = al_get_display_refresh_rate(display -> inner_display);
    timer = al_create_timer(1.0 / refresh_rate);
    al_register_event_source(object -> inner_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    object -> refresh_rate_timer = timer;

    return object;
}

