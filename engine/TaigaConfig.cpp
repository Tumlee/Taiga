#include "TaigaConfig.hpp"
#include "TaigaConfigNames.hpp"

using std::string;
using std::vector;
using std::stoi;
using std::stof;
using std::to_string;

bool TaigaConfig::load(string filename)
{
	ALLEGRO_CONFIG* config = al_load_config_file(filename.data());

	if(config == nullptr)	//Failed to load the config.
		return false;

	for(auto setting : settings)
		setting->load(config);

	al_destroy_config(config);
	return true;
}

bool TaigaConfig::save(string filename)
{
	ALLEGRO_CONFIG* config = al_create_config();

	if(config == nullptr)	//Failed to create the config.
		return false;

	for(auto setting : settings)
		setting->save(config);

	//Attempt to save the config file, storing the result
	//so it can be reported back to the caller of TaigaConfig::save()
	bool result = al_save_config_file(filename.data(), config);

	al_destroy_config(config);
	return result;
}

void TaigaConfig::clear()
{
	for(auto setting : settings)
	{
		if(setting != nullptr)
			delete setting;
	}

	settings.clear();
}

TaigaConfig::~TaigaConfig()
{
	clear();
}

void TaigaConfig::add_setting(bool* setting, string section, string key)
{
	//Validate the setting first.
	if(setting == nullptr || key.empty())
		return;

	auto newset = new TaigaConfigBool;
	newset->setting = setting;
	newset->sectionname = section;
	newset->keyname = key;

	settings.push_back(newset);
}

void TaigaConfig::add_setting(int* setting, string section, string key)
{
	//Validate the setting first.
	if(setting == nullptr || key.empty())
		return;

	auto newset = new TaigaConfigInt;
	newset->setting = setting;
	newset->sectionname = section;
	newset->keyname = key;

	settings.push_back(newset);
}


void TaigaConfig::add_setting(float* setting, string section, string key)
{
	//Validate the setting first.
	if(setting == nullptr || key.empty())
		return;

	auto newset = new TaigaConfigFloat;
	newset->setting = setting;
	newset->sectionname = section;
	newset->keyname = key;

	settings.push_back(newset);
}


void TaigaConfig::add_setting(TaigaKeybind* setting, string section, string key)
{
	//Validate the setting first.
	if(setting == nullptr || key.empty())
		return;

	auto newset = new TaigaConfigKeybind;
	newset->setting = setting;
	newset->sectionname = section;
	newset->keyname = key;

	settings.push_back(newset);
}

void TaigaConfigInt::load(ALLEGRO_CONFIG* config)
{
	const char* val = al_get_config_value(config, sectionname.data(), keyname.data());

	if(val)
		*setting = stoi(val);
}

void TaigaConfigInt::save(ALLEGRO_CONFIG* config)
{
	al_set_config_value(config, sectionname.data(), keyname.data(), to_string(*setting).data());
}

void TaigaConfigFloat::load(ALLEGRO_CONFIG* config)
{
	const char* val = al_get_config_value(config, sectionname.data(), keyname.data());

	if(val)
		*setting = stof(val);
}

void TaigaConfigFloat::save(ALLEGRO_CONFIG* config)
{
	al_set_config_value(config, sectionname.data(), keyname.data(), to_string(*setting).data());
}

void TaigaConfigBool::load(ALLEGRO_CONFIG* config)
{
	const char* val = al_get_config_value(config, sectionname.data(), keyname.data());

	if(val)
		*setting = translate_bool(val);
}

void TaigaConfigBool::save(ALLEGRO_CONFIG* config)
{
	al_set_config_value(config, sectionname.data(), keyname.data(), ::to_string(*setting).data());
}

void TaigaConfigKeybind::load(ALLEGRO_CONFIG* config)
{
	const char* val = al_get_config_value(config, sectionname.data(), keyname.data());

	if(val)
		*setting = translate_keybind(val);
}

void TaigaConfigKeybind::save(ALLEGRO_CONFIG* config)
{
	al_set_config_value(config, sectionname.data(), keyname.data(), ::to_string(*setting).data());
}

