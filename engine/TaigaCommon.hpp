#ifndef TAIGA_COMMON
#define TAIGA_COMMON

//Include all the Allegro 5 headers that we'll use.
//It doesn't slow compile THAT much --- honest!
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

//Pretty much all Taiga subsystems should have access
//to the fatal_error() function.
#include "TaigaError.hpp"

extern char** global_argv;
extern int global_argc;

#endif
