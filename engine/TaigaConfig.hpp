#ifndef TAIGA_CONFIG
#define TAIGA_CONFIG

#include "TaigaCommon.hpp"
#include "TaigaInput.hpp"
#include <string>
#include <vector>

class TaigaConfigSetting
{
	public:
		std::string sectionname;
		std::string keyname;

		virtual void load(ALLEGRO_CONFIG* config) = 0;
		virtual void save(ALLEGRO_CONFIG* config) = 0;
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

class TaigaConfig
{
	std::vector<TaigaConfigSetting*> settings;

	public:
		bool load(std::string filename);
		bool save(std::string filename);

		void clear();
		~TaigaConfig();

		void add_setting(bool* setting, std::string section, std::string key);
		void add_setting(int* setting, std::string section, std::string key);
		void add_setting(float* setting, std::string section, std::string key);
		void add_setting(TaigaKeybind* setting, std::string section, std::string key);
};

#endif
