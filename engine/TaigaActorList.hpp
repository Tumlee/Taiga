#ifndef TAIGA_ACTORLIST
#define TAIGA_ACTORLIST

class TaigaActor;

class TaigaActorList
{
	std::vector<TaigaActor*> list;
	std::vector<TaigaActor*>::iterator it;

	public:

	//Spawns a new actor. The actor needs to be allocated by the user via 'new'.
	//Deletion will be handled by the list from there.
		void spawn(TaigaActor* actor);

	//Calls the tick() function for all actors stored in the list.
	//Any actors returning false will be removed.
		void tick();

	//====================================================================================
	//The TaigaActorList::first() function is used to find the first actor of the given
	//type that is contained in the actor list. It will return nullptr if there are no
	//actors of the given type.
	//
	//Each call to TaigaState::next_actor() after that will get the next actor of the
	//given type, and when there are no more actors of that type, it will return nullptr.
	//
	//For example, if you wanted to operate on all spawned actors of the type "Ball", your
	//loop would be the following:
	//
	//for(Ball* ball = actors.first<Ball>(); ball; ball = actors.next<Ball>())
	//====================================================================================
		template <class T = TaigaActor> T* first()
		{
			for(it = list.begin(); it != list.end(); it++)
			{
				if(dynamic_cast<T*>(*it) != nullptr)
					return dynamic_cast<T*>(*it);
			}

			return nullptr;
		}

		template <class T = TaigaActor> T* next()
		{
			if(it == list.end())
				return nullptr;

			for(it++; it != list.end(); it++)
			{
				if(dynamic_cast<T*>(*it) != nullptr)
					return dynamic_cast<T*>(*it);
			}

			return nullptr;
		}
};

extern TaigaActorList actors;

#endif
