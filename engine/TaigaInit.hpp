#ifndef TAIGA_STATE
#define TAIGA_STATE

#include <vector>

#include "TaigaCommon.hpp"
#include "TaigaActorList.hpp"

class TaigaInitSettings
{
	public:
		std::string gametitle;
		int width;
		int height;
		int display_flags;
		float tickrate;
		float framerate;

		TaigaInitSettings() :
			gametitle("game"), width(640), height(480),
			display_flags(0), tickrate(60), framerate(0) {}
};
//This function is automatically called by main()
//and should not be called by the user.
void TaigaInit(TaigaInitSettings settings);

#endif
