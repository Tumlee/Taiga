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
		float tickrate;
		float framerate;

		TaigaInitSettings() :
			gametitle("game"), width(640), height(480),
			tickrate(60), framerate(0) {}
};
//This function is automatically called by main()
//and should not be called by the user.
void TaigaInit(TaigaInitSettings settings);

#endif
