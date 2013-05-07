#include "TaigaActor.hpp"
#include "TaigaActorList.hpp"

TaigaActorList actors;

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
	for(size_t i = 0; i < list.size(); i++)
	{
		if(list[i]->tick() == false)
		{
			list.erase(list.begin() + i);
			i--;
		}
	}
}
