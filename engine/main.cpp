#include "Taiga.hpp"
#include "TaigaState.hpp"

TaigaInitSettings game_bootup();

int global_argc;
char** global_argv;

TaigaKeyboard key;
TaigaMouse mouse;
TaigaActorList actors;
TaigaLayerList canvas;

ALLEGRO_DISPLAY* taiga_display = nullptr;
ALLEGRO_EVENT_QUEUE* taiga_events = nullptr;
ALLEGRO_TIMER* taiga_ticktimer = nullptr;
ALLEGRO_TIMER* taiga_frametimer = nullptr;
bool taiga_quitting = false;

int main(int argc, char** argv)
{
	global_argc = argc;
	global_argv = argv;

	TaigaState state;
	state.init(game_bootup());

    return 0;
}
