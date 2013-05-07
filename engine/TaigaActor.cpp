#include "TaigaActor.hpp"
#include "TaigaState.hpp"

void TaigaActor::spawn(TaigaActor* actor)
{
	container->spawn(actor);
}
