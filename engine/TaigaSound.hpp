#ifndef TAIGA_SOUND
#define TAIGA_SOUND

#include "TaigaCommon.hpp"

//Plays the given sample as a music, looping it by default. Passing nullptr as the 'music' argument
//will stop the current music.
void TaigaPlayMusic(ALLEGRO_SAMPLE* music, float volume = 1.0, ALLEGRO_PLAYMODE loopmode = ALLEGRO_PLAYMODE_LOOP);

//Plays the given sound at the specified volume, panning, and speed.
void TaigaPlaySound(ALLEGRO_SAMPLE* sound, float volume = 1.0, float pan = 0.0, float speed = 1.0);

//Stops the current music, equivalent to TaigaPlayMusic(nullptr)
void TaigaStopMusic();

//Sets the sound and music volume, respectively. Starts at 1.0
void TaigaSetMusicVolume(float volume);
void TaigaSetSoundVolume(float volume);

#endif
