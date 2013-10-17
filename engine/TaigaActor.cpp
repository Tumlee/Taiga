#include "TaigaActor.hpp"

void TaigaActor::spawn(TaigaActor* actor)
{
	container->spawn(actor);
}

TaigaActor::~TaigaActor()
{
	return;
}
