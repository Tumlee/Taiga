#include "TaigaActor.h"
#include "TaigaState.h"

void TaigaActor::draw(TaigaDrawer* drawer, int layer)
{
	container->draw(drawer, layer);
}

void TaigaActor::spawn(TaigaActor* actor)
{
	container->spawn(actor);
}
