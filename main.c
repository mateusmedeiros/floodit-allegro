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

int process_main_menu_keypresses(Menu*, EventQueue*, Scenario**);
int process_scenario_keypresses(Scenario*, EventQueue*);

int main(void) {
    EventQueue* queue = NULL;
    Scenario* scenario = NULL;
    Exception exception;
    Menu* main_menu = NULL;

    if(!(exception = setjmp(__exception_buffer))) {
        init();

        display = new_Display(800, 600);
        queue = new_EventQueue(display);

        /* scenario = new_Scenario(18,10,3,25, display); */
        main_menu = new_Menu(display, "New game", "Load game", "Highest scores", "Exit", NULL);
        display -> set_drawing_routine(display, main_menu -> draw_to_display, main_menu);

        while(true) {
            queue -> wait_for_event(queue);

            if(queue -> current_event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if(display -> current_state == MAIN_MENU) {
                    if(process_main_menu_keypresses(main_menu, queue, &scenario)) { break; }
                } else if(display -> current_state == SCENARIO) {
                    if(process_scenario_keypresses(scenario, queue)) { break; }
                }
            }

            if(queue -> current_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                break;
            }

            display -> draw(display);
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

int process_main_menu_keypresses(Menu* menu, EventQueue* queue, Scenario** scenario_to_be_created) {
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
        /* new game */
        case 0:
            *scenario_to_be_created = new_Scenario(configuration.columns,configuration.rows,
                                                  configuration.colors, configuration.moves, display);
            display -> set_drawing_routine(display, (*scenario_to_be_created) -> draw_to_display, *scenario_to_be_created);
            display -> current_state = SCENARIO;
            break;

        /* exit */
        case 3:
            return 1;
        }
        break;
    }

    return 0;
}

int process_scenario_keypresses(Scenario* scenario, EventQueue* queue) {
    switch(queue -> current_event.keyboard.keycode) {
    case ALLEGRO_KEY_UP:
        if(scenario -> selected_color > 0) {
            scenario -> selected_color -= 1;
        }
        break;

    case ALLEGRO_KEY_DOWN:
        if(scenario -> selected_color < scenario -> number_of_colors - 1) {
            scenario -> selected_color += 1;
        }
        break;

    case ALLEGRO_KEY_ENTER:
        switch(scenario -> selected_color) {
        case 0:
            if(scenario -> first_block -> color_code != Colors[0]) {
                scenario -> flood(scenario, Colors[0]);
                scenario -> current_move += 1;
            }
            break;

        case 1:
            if(scenario -> first_block -> color_code != Colors[1]) {
                scenario -> flood(scenario, Colors[1]);
                scenario -> current_move += 1;
            }
            break;

        case 2:
            if(scenario -> first_block -> color_code != Colors[2]) {
                scenario -> flood(scenario, Colors[2]);
                scenario -> current_move += 1;
            }
            break;

        case 3:
            if(scenario -> first_block -> color_code != 3) {
                scenario -> flood(scenario, Colors[3]);
                scenario -> current_move += 1;
            }
            break;

        case 4:
            if(scenario -> first_block -> color_code != Colors[4]) {
                scenario -> flood(scenario, Colors[4]);
                scenario -> current_move += 1;
            }
            break;

        case 5:
            if(scenario -> first_block -> color_code != Colors[5]) {
                scenario -> flood(scenario, Colors[5]);
                scenario -> current_move += 1;
            }
            break;

        case 6:
            if(scenario -> first_block -> color_code != Colors[6]) {
                scenario -> flood(scenario, Colors[6]);
                scenario -> current_move += 1;
            }
            break;

        case 7:
            if(scenario -> first_block -> color_code != Colors[7]) {
                scenario -> flood(scenario, Colors[7]);
                scenario -> current_move += 1;
            }
            break;

        }
    }

    return 0;
}
