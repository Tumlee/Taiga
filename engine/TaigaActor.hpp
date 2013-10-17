#ifndef TAIGA_ACTOR
#define TAIGA_ACTOR

#include "TaigaActorList.hpp"
#include "TaigaRender.hpp"

//The base class for any actor in Taiga.
//It is an abstract class --- no attempt should
//be made to create an instance of it in a game.
class TaigaActor
{
	public:
	//The list the actor was spawned in.
		TaigaActorList* container;

	//Every spawnable actor must have a tick() function defined.
	//You should return false if you want the actor to be deleted
	//by the engine, and true otherwise.
		virtual bool tick() = 0;

	//The following functions only exist so we don't have to call
	//the container's member functions directly (saving keystrokes).
		void spawn(TaigaActor* actor);					//See TaigaActorList::spawn()

	//Destructor for the TaigaActor class. It doesn't do anything, but
	//is required in order to ensure user-created actor's destructors
	//work properly.
		virtual ~TaigaActor();

	//========================================================================
	//See the note on TaigaActorList::first() and TaigaActorList::next().
	//Because of these member functions, the example loop when inside a member
	//function of a TaigaActor derivative could be shortened to the following:
	//
	//for(Ball* ball = first<Ball>(); ball; ball = next<Ball>())
	//========================================================================
		template <class T = TaigaActor> T* first()
		{
			return container->first<T>();
		}

		template <class T = TaigaActor> T* next()
		{
			return container->next<T>();
		}
};

#endif
