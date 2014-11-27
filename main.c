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

/* Global variables go here : */
Display* display = NULL; /* This is the only display that should be created in the entire life of the process */
Configuration configuration;

/* These forward declarations are just so that I can leave main as the first function. They are defined below main */
int process_main_menu_keypresses(Menu*, EventQueue*, Scenario**);
int process_scenario_keypresses(Scenario**, EventQueue*, Menu**);

int main(void) {
    /* EventQueue encapsulates an ALLEGRO_EVENT_QUEUE */
    EventQueue* queue = NULL;

    /* Scenario is an abstraction of a game */
    Scenario* scenario = NULL;

    /* This is actually just an int (it's an enum). */
    Exception exception;
    Menu* main_menu = NULL;

    /* This try is actually a macro for a setjmp. 
     * There's also a throw that is a macro for a longjmp. 
     * They both use a global special variable for the jmp_buf so I can abstract that */
    try(exception) {

        /* Initialization of allegro addons and seeding of the pseudo-random number generator and etc */
        init();

        display = new_Display(800, 600);
        queue = new_EventQueue(display);

        /* This shall end with a NULL to mark the end of the var args */
        main_menu = new_Menu(display, "New game", "Load game", "Highest scores", "Exit", NULL);
        display -> set_drawing_routine(display, main_menu -> draw_to_display, main_menu);

        while(true) {
            /* A timer that generates 60 events per second for the fps is already internally created in the new_EventQueue 
             * so there's no need to worry about that */
            queue -> wait_for_event(queue);

            /* If the last event generated was that of a key being pressed down */ 
            if(queue -> current_event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if(display -> current_state == MAIN_MENU) {
                    /* The "process_something_keypresses" functions have that break because if they need to break out of the loop
                     * (like the main menu when the player chooses "Exit") they just return true. */

                    /* This will manage the key presses on main menu and selection of options */
                    if(process_main_menu_keypresses(main_menu, queue, &scenario)) { break; }
                } else if(display -> current_state == SCENARIO) {
                    /* This will manage the key presses on Scenario and the selection of the color to flood */
                    if(process_scenario_keypresses(&scenario, queue, &main_menu)) { break; }
                }
            }

            /* If the player clicks on the X on the window */
            if(queue -> current_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                break;
            }

            /* Will draw whatever is set as the drawing routine of the display */
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
        /* If up and down, it will change the selected entry on the menu, but only if there's something there, to make sure no overflow will happen */
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

        /* Inside enter there's another test, for what part of the menu was selected */
    case ALLEGRO_KEY_ENTER:
        switch(menu -> selected_entry) {
        /* new game */
        case 0:
            *scenario_to_be_created = new_Scenario(configuration.columns,configuration.rows,
                                                  configuration.colors, configuration.moves, display);
            display -> set_drawing_routine(display, (*scenario_to_be_created) -> draw_to_display, *scenario_to_be_created);
            display -> current_state = SCENARIO;
            break;

        /* load game */
        case 1:
            fd = new_FileDialog("Carregar jogo salvo", "*.*;*.sav", ALLEGRO_FILECHOOSER_FILE_MUST_EXIST | ALLEGRO_FILECHOOSER_SHOW_HIDDEN);
            file_to_load = (char*) fd -> get_file(fd);

            /* the get_file() function will actually return an empty string if the user clicks cancel or anything similar */
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
            /* I don't like the macro, but it would be a big amount of repeating code if I just leaved it here, and there was enough arguments involved
             * to make it not worth making a true function */
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
