#ifndef TAIGA_STATE
#define TAIGA_STATE

#include <vector>

#include "Taiga.hpp"
#include "TaigaActorList.hpp"
#include "TaigaRender.hpp"

class TaigaInitSettings
{
	public:
		std::string gametitle;
		int width;
		int height;
		float tickrate;
		float framerate;

		TaigaInitSettings() :
			gametitle("game"), width(640), height(480),
			tickrate(60), framerate(0) {}
};

class TaigaState
{
	private:
		ALLEGRO_DISPLAY* display;
		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_TIMER* ticktimer;
		ALLEGRO_TIMER* frametimer;

		TaigaLayerList layerlist;
		bool quitting;

		void tick();
		void run();

	public:
		TaigaState();
		~TaigaState();

	//This function is automatically called by main()
	//and should not be called by the user.
		void init(TaigaInitSettings settings);

	//Registers a new event source so their events can be passed
	//to the user in game_handle_event()
		void register_event_source(ALLEGRO_EVENT_SOURCE* source);

	//Registers a TaigaDrawer to be drawn on the next render,
	//on the given layer.
		void draw(TaigaDrawer* drawer, int layer = -1);

	//Resizes the layer list so there are the given number
	//of layers. This should only really be called during
	//game_startup()
		void resize_layers(size_t count);

	//Sets a camera position for the given layer.
		void set_layercam(TaigaLayerCam cam, int layernum);

	//Sets the target bitmap back to being the display backbuffer.
	//This needs to be called before the next render after targeting
	//a different bitmap.
		void retarget_display();

	//Returns a pointer to the display. This is needed because so many
	//Allegro functions demand a display as an argument.
		ALLEGRO_DISPLAY* get_display();

	//Forces the game to end immediately after game_posttick() returns.
		void quit();

	//Sets the given bitmap as your cursor, with hotspot x, y.
		void set_cursor(ALLEGRO_BITMAP* image, int x = 0, int y = 0);
};

#endif
