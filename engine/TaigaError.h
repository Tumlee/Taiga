#ifndef TAIGA_ERROR
#define TAIGA_ERROR

#include <string>

//=============================================================
//If there is something wrong with the execution of your
//game that cannot be recovered (for example, failing to load
//important resources), call this function. It will immediately
//terminate your game and display the given error message.
//=============================================================
void fatal_error(std::string message);

#endif
