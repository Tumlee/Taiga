#include "TaigaActor.hpp"
#include "TaigaState.hpp"

void TaigaActor::draw(TaigaDrawer* drawer, int layer)
{
	state->draw(drawer, layer);
}

void TaigaActor::spawn(TaigaActor* actor)
{
	container->spawn(actor);
}
