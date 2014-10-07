#include <allegro5/allegro.h>
#include "allegro-shell/Display.h"
#include "allegro-shell/EventQueue.h"
#include "core/Scenario.h"
#include "core/utils.h"


//recursos que necessitam de inicialização e desconstrução
Display* display;
EventQueue* queue;

#include "init.h"
#include "destroy.h"

int main(void) {
    config_init();

    display = new_Display(800, 600);
    queue = new_EventQueue(display);
    Scenario* scenario = new_Scenario(15,15,3,25);

    while(true) {
        queue -> wait_for_event(queue);

        scenario -> draw_to_display(scenario, display);
        al_flip_display();

        if(queue -> current_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }

    free_resources();

    return 0;
}

