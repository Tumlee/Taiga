#include "TaigaState.h"
#include "TaigaResource.h"
#include "TaigaSound.h"
#include "TaigaInput.h"

//================================================================================
//The very first function called by main().
//The settings returned by this function will be used to initalize the TaigaState.
//Because no TaigaState is up yet and Allegro isn't initialized, you should not
//load any resources or spawn any actors yet.
//
//Use this function to determine which screen dimensions you want to use, as well
//as your framerate, possibly loading these settings from an INI.
//================================================================================
TaigaInitSettings game_bootup(void)
{
	TaigaInitSettings settings;

	return settings;
}

//======================================================================
//Called right after the TaigaState has been initalized and just before
//the game begins actually running. Use this to load whatever resources
//you need, start playing music, spawn actors, initialize any additional
//Allegro subsystems you might need, etc.
//
//You can even put up a loading screen before beginning to load your
//resources.
//======================================================================
void game_start(TaigaState* state)
{
}

//=================================================================
//The game_pretick() and game_posttick() functions are for putting
//additional game logic in your game that is independent of any
//actors you may have spawned.
//
//A "tick" is a slice of time in your game. If you set the tickrate
//to 45, for example, the game will tick 45 times per second.
//
//At the beginning of each tick, game_pretick() is called. After
//that, each spawned actor has its tick() function called in the
//order that the actors were spawned. Finally, game_posttick()
//is called.
//=================================================================
void game_pretick(TaigaState* state)
{
}

void game_posttick(TaigaState* state)
{
}
