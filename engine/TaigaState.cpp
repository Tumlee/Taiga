#include "Taiga.h"
#include "TaigaState.h"
#include "TaigaInput.h"
#include "TaigaActor.h"

#include "physfs.h"

using std::string;

void game_start(TaigaState* state);
void game_posttick(TaigaState* state);
void game_pretick(TaigaState* state);

TaigaState::TaigaState()
{
	quitting = false;
	display = nullptr;
	event_queue = nullptr;
	ticktimer = nullptr;
	frametimer = nullptr;
}

TaigaState::~TaigaState()
{
	if(ticktimer)
		al_destroy_timer(ticktimer);

	if(frametimer)
		al_destroy_timer(frametimer);

	if(display)
		al_destroy_display(display);

	if(event_queue)
		al_destroy_event_queue(event_queue);
}

void init_subsystem(bool result, string description)
{
	if(result == false)
		fatal_error("Failed to " + description);
}

void TaigaState::init(TaigaInitSettings settings)
{
	//If any of these are non-null, we've already started.
	if(ticktimer || frametimer || event_queue || display)
		fatal_error("Attempted to reinitialize an already-running TaigaState.");

	//Initialize Allegro and all needed addons.
	init_subsystem(al_init(), "initialize Allegro.");
	init_subsystem(al_init_image_addon(), "initialize Allegro image addon.");
	init_subsystem(al_init_font_addon(), "initialize Allegro font addon.");
	init_subsystem(al_init_ttf_addon(), "initialize Allegro TTF addon.");
	init_subsystem(al_install_audio(), "initialize Allegro audio.");
	init_subsystem(al_init_acodec_addon(), "initialize Allegro audio codec addon.");

	//Set up the event queue and start up graphics, audio, and input.
    init_subsystem((event_queue = al_create_event_queue()), "create an event queue.");
	init_subsystem((display = al_create_display(settings.width, settings.height)), "create a display.");
	init_subsystem(al_install_keyboard(), "install keyboard for Allegro.");
	init_subsystem(al_install_mouse(), "install mouse for Allegro.");
	init_subsystem(al_reserve_samples(16), "reserve samples for Allegro audio.");

	mouse.init();
	key.init();

	//Set up the tick timer.
	init_subsystem((ticktimer = al_create_timer(1 / settings.tickrate)), "create the ticktimer.");
	al_register_event_source(event_queue, al_get_timer_event_source(ticktimer));

	if(settings.framerate != 0)
	{
		init_subsystem((frametimer = al_create_timer(1 / settings.framerate)), "create the frametimer.");
		al_register_event_source(event_queue, al_get_timer_event_source(frametimer));
	}

	//Set up physfs and use the your .trp as a "resources" folder.
	PHYSFS_init(global_argv[0]);
	PHYSFS_mount((settings.gametitle + ".trp").data(), "resources", 0);
	PHYSFS_mount("resources", "resources", 0);
	al_set_physfs_file_interface();

	//Clear the display and register it as an event source.
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    game_start(this);
	al_start_timer(ticktimer);

	if(frametimer)
		al_start_timer(frametimer);

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
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == ticktimer)
        {
			layerlist.clear();
        	tick();
            redraw = true;
        }

        if(quitting)
			break;

        if(ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == frametimer)
			frameokay = true;

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if(redraw && al_is_event_queue_empty(event_queue) && frameokay)
        {
            redraw = false;
			retarget_display();	//Make sure our draws actually end up on the display.
            layerlist.draw();
            al_flip_display();

            if(frametimer)
				frameokay = false;
        }
    }
}

void TaigaState::tick()
{
	key.update();
	mouse.update();

	game_pretick(this);

	for(auto& actor : actors)
	{
		if(actor->tick() == false)
		{
			delete actor;
			actor = nullptr;
		}
	}

	actors.remove(nullptr);

	game_posttick(this);

	return;
}

void TaigaState::spawn(TaigaActor* actor)
{
	if(actor == nullptr)
		fatal_error("Tried to spawn a null actor.");

	actors.push_back(actor);
	actor->state = this;

	return;
}

void TaigaState::quit()
{
	quitting = true;
}

void TaigaState::draw(TaigaDrawer* drawer, int layer)
{
	layerlist.add_entry(drawer, layer);
}

void TaigaState::resize_layers(size_t count)
{
	layerlist.resize(count);
}

void TaigaState::retarget_display()
{
	al_set_target_bitmap(al_get_backbuffer(display));
}

ALLEGRO_DISPLAY* TaigaState::get_display()
{
	return display;
}

void TaigaState::set_cursor(ALLEGRO_BITMAP* image, int x, int y)
{
	static ALLEGRO_MOUSE_CURSOR* cur_cursor = nullptr;

	if(cur_cursor)
		al_destroy_mouse_cursor(cur_cursor);

	cur_cursor = al_create_mouse_cursor(image, x, y);

	al_set_mouse_cursor(get_display(), cur_cursor);
}


