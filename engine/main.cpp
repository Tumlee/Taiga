#include "TaigaState.h"

TaigaInitSettings game_bootup();

int global_argc;
char** global_argv;

int main(int argc, char** argv)
{
	global_argc = argc;
	global_argv = argv;

	TaigaState state;
	state.init(game_bootup());

    return 0;
}
