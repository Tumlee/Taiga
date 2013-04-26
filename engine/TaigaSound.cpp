#include "TaigaSound.hpp"

void TaigaPlayMusic(ALLEGRO_SAMPLE* music, float volume, ALLEGRO_PLAYMODE loopmode)
{
	static ALLEGRO_SAMPLE_ID musicid;
	static bool musicvalid = false;

	if(musicvalid)	//We're already playing some music, stop it.
		al_stop_sample(&musicid);

	if(music)
	{
		al_play_sample(music, volume, 0.0, 1.0, loopmode, &musicid);
		musicvalid = true;
	}
	else
		musicvalid = false;
}

void TaigaPlaySound(ALLEGRO_SAMPLE* sound, float volume, float pan, float speed)
{
	if(sound)
		al_play_sample(sound, volume, pan, speed, ALLEGRO_PLAYMODE_ONCE, nullptr);
}

void TaigaStopMusic()
{
	TaigaPlayMusic(nullptr);
}
