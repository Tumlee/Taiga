#include "Taiga.hpp"
#include "TaigaInit.hpp"

TaigaInitSettings game_bootup();
void game_posttick();
void game_pretick();
void game_handle_event(ALLEGRO_EVENT event);

int global_argc;
char** global_argv;

TaigaKeyboard key;
TaigaMouse mouse;
TaigaActorList actors;
TaigaLayerList canvas;

ALLEGRO_DISPLAY* taiga_display = nullptr;
ALLEGRO_EVENT_QUEUE* taiga_events = nullptr;
ALLEGRO_TIMER* taiga_ticktimer = nullptr;
ALLEGRO_TIMER* taiga_frametimer = nullptr;
bool taiga_quitting = false;

int main(int argc, char** argv)
{
	global_argc = argc;
	global_argv = argv;

	TaigaInit(game_bootup());

	bool redraw = true;
	bool frameokay = true;

	while(true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(taiga_events, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == taiga_ticktimer)
        {
			canvas.clear();
        	key.update();
			mouse.update();

			game_pretick();
			actors.tick();
			game_posttick();
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == taiga_frametimer)
		{
			frameokay = true;
		}
		else
		{
			game_handle_event(ev);
		}

        if(taiga_quitting)
			break;

        if(redraw && al_is_event_queue_empty(taiga_events) && frameokay)
        {
            redraw = false;
            canvas.draw_entries();
            al_flip_display();

            if(taiga_frametimer)
				frameokay = false;
        }
    }

    return 0;
}
