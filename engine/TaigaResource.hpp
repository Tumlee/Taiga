#ifndef TAIGA_RESOURCE
#define TAIGA_RESOURCE

#include "TaigaCommon.hpp"

#include <string>

//==========================================================================
//Functions for loading resources. These will ALL load resources either from
//a folder called "resources" in the working directory, or from a .trp file
//named after your game. (For example, if you name your game "pong", the
//package will be called "pong.trp")
//
//A .trp (Taiga Resource Package) can be any archive format that is
//supported by the physfs library. For example, you can take a .7z and
//rename the extension to .trp so it can be found.
//=========================================================================

//Loads a resource as an ALLEGRO_FILE, doing so in binary mode by default,
//rather than text mode. You will still have to understand how to read
//from an ALLEGRO_FILE in order for this to be useful.
ALLEGRO_FILE* load_resource(std::string resname, bool binary = true);

//Loads an image, which must be contained in the "images" folder of
//either your resources folder or your .trp. It supports any image
//format that Allegro supports.
ALLEGRO_BITMAP* load_image(std::string resname);

//Loads an audio sample, which must be contained in the "audio"
//folder of either your resources folder or your .trp. It supports
//any audio format that Allegro supports.
ALLEGRO_SAMPLE* load_sample(std::string resname);

//Loads a TTF font, which must be contained in the "fonts" folder of
//either your resources folder our your .trp. For more information on
//the 'size' and 'flags' parameters, see al_load_ttf_font()
ALLEGRO_FONT* load_font(std::string resname, int size, int flags = 0);

#endif
