#ifndef TAIGA_CONFIG_NAMES
#define TAIGA_CONFIG_NAMES

#include <string>
#include "TaigaCommon.hpp"

TaigaKeybind translate_keybind(std::string name);
std::string to_string(TaigaKeybind keybind);

bool translate_bool(std::string name);
std::string to_string(bool value);

#endif
