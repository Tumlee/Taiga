#include "TaigaActor.hpp"
#include "TaigaActorList.hpp"

TaigaActorList::TaigaActorList()
{
	paused = false;
}

void TaigaActorList::spawn(TaigaActor* actor)
{
	if(actor == nullptr)
		fatal_error("Tried to spawn a null actor.");

	list.push_back(actor);
	actor->container = this;

	return;
}

void TaigaActorList::tick()
{
	if(paused)
		return;

	for(size_t i = 0; i < list.size(); i++)
	{
		if(list[i]->tick() == false)
		{
			delete list[i];
			list.erase(list.begin() + i);
			i--;
		}
	}
}
