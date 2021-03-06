#include "Taiga.hpp"
#include "TaigaInit.hpp"
#include "TaigaResource.hpp"

//================================================================================
//The very first function called by main().
//The settings returned by this function will be used to initalize the TaigaState.
//Because Allegro isn't initialized, you should not load any resources or spawn
//any actors yet.
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
//Called right after Allegro has been initalized and just before the
//game begins actually running. Use this to load whatever resources you
//need, start playing music, spawn actors, initialize any additional
//Allegro subsystems you might need, etc.
//
//You can even put up a loading screen before beginning to load your
//resources.
//======================================================================
void game_start()
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
void game_pretick()
{
}

void game_posttick()
{
}

//=========================================================
//Most Allegro events caught by the main loop are passed to
//this function so you can handle certain events yourself.
//=========================================================
void game_handle_event(ALLEGRO_EVENT event)
{
	//By default, quit the game if the X button was clicked.
	if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		taiga_quitting = true;
}
