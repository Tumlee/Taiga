#ifndef TAIGA_ACTOR
#define TAIGA_ACTOR

#include "TaigaState.h"
#include "TaigaRender.h"

//The base class for any actor in Taiga.
//It is an abstract class --- no attempt should
//be made to create an instance of it in a game.
class TaigaActor
{
	public:
	//The TaigaState that the actor was spawned in. There is
	//no good reason to access this feild directly.
		TaigaState* container;

	//Every spawnable actor must have a tick() function defined.
	//You should return false if you want the actor to be deleted
	//by the engine, and true otherwise.
		virtual bool tick() = 0;

	//The following functions only exist so we don't have to call
	//the container's member functions directly (saving keystrokes).
		void draw(TaigaDrawer* drawer, int layer = -1);	//See TaigaState::draw()
		void spawn(TaigaActor* actor);					//See TaigaState::spawn()

	//========================================================================
	//See the note on TaigaState::first_actor() and TaigaState::next_actor().
	//Because of these member functions, the example loop when inside a member
	//function of a TaigaActor derivative could be shortened to the following:
	//
	//for(Ball* ball = first_actor<Ball>(); ball; ball = next_actor<Ball>())
	//========================================================================
		template <class T> T* first_actor()
		{
			return container->first_actor<T>();
		}

		template <class T> T* next_actor()
		{
			return container->next_actor<T>();
		}
};

#endif
