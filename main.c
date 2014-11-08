#include <setjmp.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "allegro-shell/Display.h"
#include "allegro-shell/EventQueue.h"
#include "core/constants.h"
#include "core/Scenario.h"
#include "core/Menu.h"
#include "shell/utils.h"
#include "init.h"

Display* display = NULL;
Configuration configuration;

void process_main_menu_keypresses(Menu* menu, EventQueue* queue,
                                  Scenario** scenario_to_be_created, int* kept_on_main_menu);

int main(void) {
    EventQueue* queue = NULL;
    Scenario* scenario = NULL;
    Exception exception;
    Menu* main_menu = NULL;

    if(!(exception = setjmp(__exception_buffer))) {
/*        bool is_paused = false;*/
        int is_at_main_menu = true;

        init();

        display = new_Display(800, 600);
        queue = new_EventQueue(display);

        /* scenario = new_Scenario(18,10,3,25, display); */
        main_menu = new_Menu(display, "New game", "Load game", "Highest scores", "Exit", NULL);
        display -> set_drawing_routine(display, main_menu -> draw_to_display, main_menu);

        while(true) {
            queue -> wait_for_event(queue);

            /*menu -> draw_to_display(menu);*/
            /*scenario -> draw_to_display(scenario);*/
            display -> draw(display);

            if(queue -> current_event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if(is_at_main_menu) {
                    process_main_menu_keypresses(main_menu, queue, &scenario, &is_at_main_menu);
                }
            }

            if(queue -> current_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                break;
            }
        }
    }

    /* if any exception happened */
    if(exception) {
        print_error(exception);
    }

    /* cleanup */
    if(display != NULL) {
        display -> destroy(display);
    }
    if(main_menu != NULL) {
        main_menu -> destroy(main_menu);
    }
    if(queue != NULL) {
        queue -> destroy(queue);
    }
    if(scenario != NULL) {
        scenario -> destroy(scenario);
    }

    return exception;
}



void process_main_menu_keypresses(Menu* menu, EventQueue* queue,
                                  Scenario** scenario_to_be_created, int* kept_at_main_menu) {
    switch(queue -> current_event.keyboard.keycode) {
    case ALLEGRO_KEY_UP:
        if(menu -> selected_entry > 0) {
            menu -> selected_entry -= 1;
        }
        break;

    case ALLEGRO_KEY_DOWN:
        if(menu -> selected_entry < menu -> number_of_entries - 1) {
            menu -> selected_entry += 1;
        }
        break;

    case ALLEGRO_KEY_ENTER:
        switch(menu -> selected_entry) {
        case 0:
            *scenario_to_be_created = new_Scenario(configuration.columns,configuration.rows,
                                                  configuration.colors, configuration.moves, display);
            display -> set_drawing_routine(display, (*scenario_to_be_created) -> draw_to_display, *scenario_to_be_created);
            *kept_at_main_menu = false;
            break;
        }
        break;
    }
}
