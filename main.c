#include <setjmp.h>
#include <allegro5/allegro.h>
#include "allegro-shell/Display.h"
#include "allegro-shell/EventQueue.h"
#include "core/constants.h"
#include "core/Scenario.h"
#include "core/Menu.h"
#include "shell/utils.h"
#include "init.h"

jmp_buf global_buffer;

int main(void) {
    Display* display = NULL;
    EventQueue* queue = NULL;
    /*Scenario* scenario;*/
    Menu* menu = NULL;
    int exception_code;

    init();

    if(!(exception_code = setjmp(global_buffer))) {

        display = new_Display(800, 600);
        queue = new_EventQueue(display);

        /*scenario = new_Scenario(18,10,3,25, display);*/
        menu = new_Menu(display, "New game", "Load game", "Highest scores", "Exit", NULL);

        while(true) {
            queue -> wait_for_event(queue);

            menu -> draw_to_display(menu);
            al_flip_display();

            if(queue -> current_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                break;
            }
        }
    }

    /* if any exception happened */
    if(exception_code) {
        print_error(exception_code);
    }

    /* cleanup */
    if(display != NULL) {
        display -> destroy(display);
    }
    if(queue != NULL) {
        queue -> destroy(queue);
    }
    /*scenario        -> destroy(scenario);*/

    return exception_code;
}

