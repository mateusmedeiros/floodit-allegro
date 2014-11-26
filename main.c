#include <setjmp.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "allegro-shell/Display.h"
#include "allegro-shell/EventQueue.h"
#include "allegro-shell/FileDialog.h"
#include "shell/io_utils.h"
#include "core/constants.h"
#include "core/Scenario.h"
#include "core/Menu.h"
#include "shell/utils.h"
#include "init.h"

Display* display = NULL;
Configuration configuration;

int process_main_menu_keypresses(Menu*, EventQueue*, Scenario**);
int process_scenario_keypresses(Scenario**, EventQueue*, Menu**);

int main(void) {
    EventQueue* queue = NULL;
    Scenario* scenario = NULL;
    Exception exception;
    Menu* main_menu = NULL;

    try(exception) {
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
                    if(process_scenario_keypresses(&scenario, queue, &main_menu)) { break; }
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
        display -> destroy(&display);
    }
    if(main_menu != NULL) {
        main_menu -> destroy(&main_menu);
    }
    if(queue != NULL) {
        queue -> destroy(&queue);
    }
    if(scenario != NULL) {
        scenario -> destroy(&scenario);
    }

    return exception;
}

int process_main_menu_keypresses(Menu* menu, EventQueue* queue, Scenario** scenario_to_be_created) {
    FileDialog* fd;
    char* file_to_load;
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

        case 1:
            /**scenario_to_be_created = new_Scenario(configuration.columns,configuration.rows,
                                                  configuration.colors, configuration.moves, display);*/
            fd = new_FileDialog("Carregar jogo salvo", "*.*;*.sav", ALLEGRO_FILECHOOSER_FILE_MUST_EXIST | ALLEGRO_FILECHOOSER_SHOW_HIDDEN);
            file_to_load = (char*) fd -> get_file(fd);
            if(strcmp(file_to_load, "")) {
                *scenario_to_be_created = read_scenario_from_file(file_to_load);
                display -> set_drawing_routine(display, (*scenario_to_be_created) -> draw_to_display, *scenario_to_be_created);
                display -> current_state = SCENARIO;
            }

            break;

        /* exit */
        case 3:
            return 1;
        }
        break;
    }

    return 0;
}
/*
define flood_color(color) \
if((*scenario) -> first_block -> color_code != Colors[color]) {\
    (*scenario) -> current_move += 1;\
    (*scenario) -> flood((*scenario), Colors[color]);\
    if((*scenario) -> state == STATE_WON || (*scenario) -> state == STATE_LOST) {\
        (*scenario) -> destroy(scenario);\
        display -> set_drawing_routine(display, (*main_menu) -> draw_to_display, *main_menu);\
        display -> current_state = MAIN_MENU;\
    }\
}
*/

#define flood_color(color) \
if((*scenario) -> first_block -> color_code != Colors[color]) {\
    (*scenario) -> current_move += 1;\
    (*scenario) -> flood((*scenario), Colors[color]);\
    \
    if((*scenario) -> state == STATE_WON || (*scenario) -> state == STATE_LOST) {\
        display -> draw(display);\
    \
        if((*scenario) -> state == STATE_WON) {\
            al_show_native_message_box(display -> inner_display, "", "You won!",\
                                   "Congratulations!",\
                                   NULL, ALLEGRO_MESSAGEBOX_QUESTION);\
        } else {\
            al_show_native_message_box(display -> inner_display, "", "You lost.",\
                                   "Sorry. Better luck next time.",\
                                   NULL, ALLEGRO_MESSAGEBOX_QUESTION);\
        }\
    \
        (*scenario) -> destroy(scenario);\
        display -> set_drawing_routine(display, (*main_menu) -> draw_to_display, *main_menu);\
        display -> current_state = MAIN_MENU;\
    }\
}

int process_scenario_keypresses(Scenario** scenario, EventQueue* queue, Menu** main_menu) {
    switch(queue -> current_event.keyboard.keycode) {
    FileDialog* fd;
    char* file_to_load;

    case ALLEGRO_KEY_ESCAPE:
        fd = new_FileDialog("Salvar jogo", "*.*;*.sav", ALLEGRO_FILECHOOSER_SAVE | ALLEGRO_FILECHOOSER_SHOW_HIDDEN);
        file_to_load = (char*) fd -> get_file(fd);
        if(strcmp(file_to_load, "")) {
            write_scenario_to_file(file_to_load, *scenario);
            (*scenario) -> destroy(scenario);
            display -> set_drawing_routine(display, (*main_menu) -> draw_to_display, *main_menu);
            display -> current_state = MAIN_MENU;
        }

        break;

    case ALLEGRO_KEY_UP:
        if((*scenario) -> selected_color > 0) {
            (*scenario) -> selected_color -= 1;
        }
        break;

    case ALLEGRO_KEY_DOWN:
        if((*scenario) -> selected_color < (*scenario) -> number_of_colors - 1) {
            (*scenario) -> selected_color += 1;
        }
        break;

    case ALLEGRO_KEY_ENTER:
        switch((*scenario) -> selected_color) {
        case 0:
            flood_color(0);
            break;

        case 1:
            flood_color(1);
            break;

        case 2:
            flood_color(2);
            break;

        case 3:
            flood_color(3);
            break;

        case 4:
            flood_color(4);
            break;

        case 5:
            flood_color(5);
            break;

        case 6:
            flood_color(6);
            break;

        case 7:
            flood_color(7);
            break;

        }
    }

    return 0;
}
