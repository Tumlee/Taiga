#ifndef TAIGA_ACTOR
#define TAIGA_ACTOR

#include "TaigaState.hpp"
#include "TaigaRender.hpp"

//The base class for any actor in Taiga.
//It is an abstract class --- no attempt should
//be made to create an instance of it in a game.
class TaigaActor
{
	public:
	//The list the actor was spawned in.
		TaigaActorList* container;
		TaigaState* state;

	//Every spawnable actor must have a tick() function defined.
	//You should return false if you want the actor to be deleted
	//by the engine, and true otherwise.
		virtual bool tick() = 0;

	//The following functions only exist so we don't have to call
	//the container's member functions directly (saving keystrokes).
		void draw(TaigaDrawer* drawer, int layer = -1);	//See TaigaState::draw()
		void spawn(TaigaActor* actor);					//See TaigaActorList::spawn()

	//========================================================================
	//See the note on TaigaActorList::first() and TaigaActorList::next().
	//Because of these member functions, the example loop when inside a member
	//function of a TaigaActor derivative could be shortened to the following:
	//
	//for(Ball* ball = first_actor<Ball>(); ball; ball = next_actor<Ball>())
	//========================================================================
		template <class T> T* first_actor()
		{
			return container->first<T>();
		}

		template <class T> T* next_actor()
		{
			return container->next<T>();
		}
};

#endif
