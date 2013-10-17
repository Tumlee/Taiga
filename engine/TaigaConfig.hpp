#ifndef TAIGA_CONFIG
#define TAIGA_CONFIG

#include "TaigaCommon.hpp"
#include "TaigaInput.hpp"
#include <string>
#include <vector>

//The base class for a configuration setting. None of the
//classes that derive from TaigaConfigSetting need to be
//created nor interacted with by the user --- it is all
//handled transparently through TaigaConfig.
class TaigaConfigSetting
{
	public:
		std::string sectionname;
		std::string keyname;

		virtual void load(ALLEGRO_CONFIG* config) = 0;
		virtual void save(ALLEGRO_CONFIG* config) = 0;

		virtual ~TaigaConfigSetting();
};

class TaigaConfigBool : public TaigaConfigSetting
{
	public:
		bool* setting;
		virtual void load(ALLEGRO_CONFIG* config);
		virtual void save(ALLEGRO_CONFIG* config);
};

class TaigaConfigInt : public TaigaConfigSetting
{
	public:
		int* setting;
		virtual void load(ALLEGRO_CONFIG* config);
		virtual void save(ALLEGRO_CONFIG* config);
};

class TaigaConfigFloat : public TaigaConfigSetting
{
	public:
		float* setting;
		virtual void load(ALLEGRO_CONFIG* config);
		virtual void save(ALLEGRO_CONFIG* config);
};

class TaigaConfigKeybind : public TaigaConfigSetting
{
	public:
		TaigaKeybind* setting;
		virtual void load(ALLEGRO_CONFIG* config);
		virtual void save(ALLEGRO_CONFIG* config);
};

//==========================================================================
//A class for handling the loading and saving of configuration files
//and tying the keys within them to actual variables in your game.
//
//In order to bind a variable to a configuration key, pass a pointer
//to it as an argument to TaigaConfig::add_setting() (documented below).
//
//Currently supported types are bool, int, float, and TaigaKeybind.
//An instance of this class must be created explicitly by the user,
//and the same goes with calling TaigaConfig::load() and TaigaConfig::save()
//==========================================================================
class TaigaConfig
{
	std::vector<TaigaConfigSetting*> settings;

	public:
		//Loads configuration settings from a file and stores them
		//into the variables supplied by calls to add_setting().
		//Returns false upon failure.
		bool load(std::string filename);

		//Saves configured settings to a file.
		//Returns false upon failure.
		bool save(std::string filename);

		//Clears all configuration bindings from this TaigaConfig.
		void clear();
		~TaigaConfig();

		//Binds an in-game variable to an INI key. See information on Allegro's
		//configuration handling for more details.
		void add_setting(bool* setting, std::string section, std::string key);
		void add_setting(int* setting, std::string section, std::string key);
		void add_setting(float* setting, std::string section, std::string key);
		void add_setting(TaigaKeybind* setting, std::string section, std::string key);
};

#endif
