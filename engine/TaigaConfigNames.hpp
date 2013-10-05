#ifndef TAIGA_CONFIG_NAMES
#define TAIGA_CONFIG_NAMES

//This header only really needs to be included by TaigaConfig, as it
//contains utilities to help translate certain data types to/from
//strings in order to read and write configuration files.
#include <string>
#include "TaigaCommon.hpp"

TaigaKeybind translate_keybind(std::string name);
std::string to_string(TaigaKeybind keybind);

bool translate_bool(std::string name);
std::string to_string(bool value);

#endif
