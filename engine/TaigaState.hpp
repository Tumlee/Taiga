#ifndef TAIGA_STATE
#define TAIGA_STATE

#include <vector>

#include "TaigaCommon.hpp"
#include "TaigaActorList.hpp"

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

	//Sets the target bitmap back to being the display backbuffer.
	//This needs to be called before the next render after targeting
	//a different bitmap.
		void retarget_display();

	//Returns a pointer to the display. This is needed because so many
	//Allegro functions demand a display as an argument.
		ALLEGRO_DISPLAY* get_display();

	//Forces the game to end immediately after game_posttick() returns.
		void quit();
};

#endif
