#include <allegro5/allegro.h>
#include <stdlib.h>
#include "../shell/exceptions.h"

#include "EventQueue.h"
#include "Display.h"

void __EventQueue_wait_for_event__(EventQueue* self) {
    al_wait_for_event(self -> inner_queue, &(self -> current_event));
}

void __EventQueue_add_source__(EventQueue* self, ALLEGRO_EVENT_SOURCE* source) {
    al_register_event_source(self -> inner_queue, source);
}

void __EventQueue_destroy__(EventQueue** self) {
    al_destroy_timer((*self) -> refresh_rate_timer);
    (*self) -> refresh_rate_timer = NULL;

    al_destroy_event_queue((*self) -> inner_queue);
    (*self) -> inner_queue = NULL;

    free(*self);
    *self = NULL;
}

/* The EventQueue will automatically add the keyboard event source and the timer (synchronized with the display refresh rate) */
EventQueue* new_EventQueue(Display* display) {
    EventQueue* object = malloc(sizeof(EventQueue));
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_SOURCE* keyboard_source;
    int refresh_rate;

    object -> inner_queue = al_create_event_queue();

    if(object -> inner_queue == NULL) {
        longjmp(__exception_buffer, ALLEGRO_COMPONENT_INITIALIZATION_FAILED);
    }

    object -> wait_for_event = __EventQueue_wait_for_event__;
    object -> add_source = __EventQueue_add_source__;
    object -> destroy = __EventQueue_destroy__;

    object -> add_source(object, al_get_display_event_source(display -> inner_display));

    keyboard_source = al_get_keyboard_event_source();
    if(keyboard_source == NULL) {
        throw(KEYBOARD_NOT_PRESENT);
    }
    object -> add_source(object, keyboard_source);

    refresh_rate = al_get_display_refresh_rate(display -> inner_display);
    timer = al_create_timer(1.0 / refresh_rate);

    if(timer == NULL) {
        longjmp(__exception_buffer, ALLEGRO_COMPONENT_INITIALIZATION_FAILED);
    }

    object -> add_source(object, al_get_timer_event_source(timer));
    al_start_timer(timer);
    object -> refresh_rate_timer = timer;

    return object;
}

