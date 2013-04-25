#ifndef TAIGA_STATE
#define TAIGA_STATE

#include <list>

#include "Taiga.h"
#include "TaigaRender.h"

class TaigaActor;

//Note: In future versions of this engine, the framerate may be
//separate from the actual tic rate.
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

		std::list<TaigaActor*> actors;
		std::list<TaigaActor*>::iterator actorit;

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

	//Spawns a new actor. The actor needs to be allocated
	//by the user via 'new'. Deletion will be handled
	//by the TaigaState from there.
		void spawn(TaigaActor* actor);

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

	//====================================================================================
	//The TaigaState::first_actor() function is used to find the first actor of the given
	//type that is contained in the TaigaState's actor list. It will return nullptr if
	//there are no actors of the given type.
	//
	//Each call to TaigaState::next_actor() after that will get the next actor of the
	//given type, and when there are no more actors of that type, it will return nullptr.
	//
	//For example, if you wanted to operate on all spawned actors of the type "Ball", your
	//loop would be the following:
	//
	//for(Ball* ball = state->first_actor<Ball>(); ball; ball = state->next_actor<Ball>())
	//====================================================================================
		template <class T> T* first_actor()
		{
			for(actorit = actors.begin(); actorit != actors.end(); actorit++)
			{
				if(dynamic_cast<T*>(*actorit) != nullptr)
					return dynamic_cast<T*>(*actorit);
			}

			return nullptr;
		}

		template <class T> T* next_actor()
		{
			if(actorit == actors.end())
				return nullptr;

			for(actorit++; actorit != actors.end(); actorit++)
			{
				if(dynamic_cast<T*>(*actorit) != nullptr)
					return dynamic_cast<T*>(*actorit);
			}

			return nullptr;
		}
};

#endif
