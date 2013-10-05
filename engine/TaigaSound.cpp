#include "TaigaSound.hpp"

//A global "sound volume" that can be set by the user.
//All sounds played by TaigaPlaySound() and TaigaPlayMusic()
//have their volumes multiplied by these values.
float taiga_music_volume = 1.0;
float taiga_sound_volume = 1.0;

void TaigaPlayMusic(ALLEGRO_SAMPLE* music, float volume, ALLEGRO_PLAYMODE loopmode)
{
	static ALLEGRO_SAMPLE_ID musicid;
	static bool musicvalid = false;

	if(musicvalid)	//We're already playing some music, stop it.
		al_stop_sample(&musicid);

	if(music)
	{
		al_play_sample(music, volume * taiga_music_volume, 0.0, 1.0, loopmode, &musicid);
		musicvalid = true;
	}
	else
		musicvalid = false;
}

void TaigaPlaySound(ALLEGRO_SAMPLE* sound, float volume, float pan, float speed)
{
	if(sound)
		al_play_sample(sound, volume * taiga_sound_volume, pan, speed, ALLEGRO_PLAYMODE_ONCE, nullptr);
}

void TaigaStopMusic()
{
	TaigaPlayMusic(nullptr);
}

void TaigaSetMusicVolume(float volume)
{
	taiga_music_volume = volume;
}

void TaigaSetSoundVolume(float volume)
{
	taiga_sound_volume = volume;
}
