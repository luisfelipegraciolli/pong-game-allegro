// PADROES DO SISTEMA
#include <stdio.h>
#include <stdbool.h>
//BIBLIOTEAS
#include "headers/must_init.h"
#include "headers/player.h"
//ALEGREO
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

// CONSTANTES
#define FPS 30
#define SCREEN_W 640
#define SCREEN_H 480
#define OFFSET_PLAYABLE_AREA 40


int main()
{
    Player new_player = init_player("LFG\0");

    al_init();
    al_install_keyboard();
    al_init_image_addon();

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");
    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_W, SCREEN_H);
    must_init(disp, "display");
    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "display");
    ALLEGRO_BITMAP* apple = al_load_bitmap("images/apple.png");
    must_init(apple, "display");

    must_init(al_init_primitives_addon(), "primitives");


    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if((event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(42, 52, 64));
            al_draw_text(font, al_map_rgb(255,255,255), 320, 0, ALLEGRO_ALIGN_CENTRE,"Aperte ESC para sair || Aperte 's' para mostrar suas pontuações");
            al_draw_text(font, al_map_rgb(255,255,255), 320, 20, ALLEGRO_ALIGN_CENTRE,"Score: %d");

            al_draw_bitmap(apple, 320,240, ALLEGRO_ALIGN_CENTRE);
            
            
            al_draw_rounded_rectangle(OFFSET_PLAYABLE_AREA, OFFSET_PLAYABLE_AREA, SCREEN_W-OFFSET_PLAYABLE_AREA, SCREEN_H-OFFSET_PLAYABLE_AREA, 2, 2, al_map_rgb(255,255,255),1.2);


            al_flip_display();

            redraw = false;
        }
    }


    al_destroy_bitmap(apple);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
