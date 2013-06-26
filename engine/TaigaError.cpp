#include "TaigaCommon.hpp"

#include <iostream>
#include <cstdlib>
#include <string>

using std::string;
using std::cerr;
using std::endl;

void fatal_error(string message)
{
	al_show_native_message_box(al_get_current_display(), "Taiga Fatal Error",
								"Fatal Error", message.data(), nullptr, ALLEGRO_MESSAGEBOX_ERROR);

	cerr << message << endl;
	exit(EXIT_FAILURE);
}
