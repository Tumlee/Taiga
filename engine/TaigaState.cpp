#include "TaigaCommon.hpp"
#include "TaigaState.hpp"
#include "TaigaInput.hpp"
#include "TaigaActorList.hpp"
#include "TaigaRender.hpp"

#include "physfs.h"

using std::string;

void game_start(TaigaState* state);
void game_posttick(TaigaState* state);
void game_pretick(TaigaState* state);
void game_handle_event(TaigaState* state, ALLEGRO_EVENT event);

void init_subsystem(bool result, string description)
{
	if(result == false)
		fatal_error("Failed to " + description);
}

void TaigaState::init(TaigaInitSettings settings)
{
	//If any of these are non-null, we've already started.
	if(taiga_ticktimer || taiga_frametimer || taiga_events || taiga_display)
		fatal_error("Attempted to reinitialize an already-running TaigaState.");

	//Initialize Allegro and all needed addons.
	init_subsystem(al_init(), "initialize Allegro.");
	init_subsystem(al_init_image_addon(), "initialize Allegro image addon.");
	init_subsystem(al_init_font_addon(), "initialize Allegro font addon.");
	init_subsystem(al_init_ttf_addon(), "initialize Allegro TTF addon.");
	init_subsystem(al_install_audio(), "initialize Allegro audio.");
	init_subsystem(al_init_acodec_addon(), "initialize Allegro audio codec addon.");
	init_subsystem(al_init_primitives_addon(), "initialize Allegro primitives addon.");

	//Set up the event queue and start up graphics, audio, and input.
    init_subsystem((taiga_events = al_create_event_queue()), "create an event queue.");
	init_subsystem((taiga_display = al_create_display(settings.width, settings.height)), "create a display.");
	init_subsystem(al_install_keyboard(), "install keyboard for Allegro.");
	init_subsystem(al_install_mouse(), "install mouse for Allegro.");
	init_subsystem(al_reserve_samples(16), "reserve samples for Allegro audio.");

	mouse.init();
	key.init();
	canvas.target = al_get_backbuffer(taiga_display);

	//Set up the tick timer.
	init_subsystem((taiga_ticktimer = al_create_timer(1 / settings.tickrate)), "create the ticktimer.");
	al_register_event_source(taiga_events, al_get_timer_event_source(taiga_ticktimer));

	if(settings.framerate != 0)
	{
		init_subsystem((taiga_frametimer = al_create_timer(1 / settings.framerate)), "create the frametimer.");
		al_register_event_source(taiga_events, al_get_timer_event_source(taiga_frametimer));
	}

	//Set up physfs and use the your .trp as a "resources" folder.
	PHYSFS_init(global_argv[0]);
	PHYSFS_mount((settings.gametitle + ".trp").data(), "resources", 0);
	PHYSFS_mount("resources", "resources", 0);
	al_set_physfs_file_interface();

	//Clear the display and register it as an event source.
	al_register_event_source(taiga_events, al_get_display_event_source(taiga_display));
	al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    game_start(this);
	al_start_timer(taiga_ticktimer);

	if(taiga_frametimer)
		al_start_timer(taiga_frametimer);

    run();

    return;
}

void TaigaState::run()
{
	bool redraw = true;
	bool frameokay = true;

	while(true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(taiga_events, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == taiga_ticktimer)
        {
			canvas.clear();
        	tick();
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == taiga_frametimer)
		{
			frameokay = true;
		}
		else
		{
			game_handle_event(this, ev);
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
}

void TaigaState::tick()
{
	key.update();
	mouse.update();

	game_pretick(this);
	actors.tick();
	game_posttick(this);

	return;
}
