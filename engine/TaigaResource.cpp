#include "TaigaCommon.hpp"
#include "TaigaResource.hpp"

using std::string;

bool resources_required = false;

void set_resources_required(bool setting)
{
	resources_required = setting;
}

ALLEGRO_FILE* load_resource(string resname, bool binary)
{
	auto result = al_fopen(("resources/" + resname).data(), binary ? "rb" : "r");

	if(result == nullptr && resources_required)
		fatal_error("Unable to load required resource \'" + resname + "\'");

	return result;
}

ALLEGRO_BITMAP* load_image(string resname)
{
	auto result = al_load_bitmap(("resources/images/" + resname).data());

	if(result == nullptr && resources_required)
		fatal_error("Unable to load required image \'" + resname + "\'");

	return result;
}

ALLEGRO_SAMPLE* load_sample(string resname)
{
	auto result = al_load_sample(("resources/audio/" + resname).data());

	if(result == nullptr && resources_required)
		fatal_error("Unable to load required audio sample \'" + resname + "\'");

	return result;
}

ALLEGRO_FONT* load_font(string resname, int size, int flags)
{
	auto result = al_load_ttf_font(("resources/fonts/" + resname).data(), size, flags);

	if(result == nullptr && resources_required)
		fatal_error("Unable to load required font \'" + resname + "\'");

	return result;
}

void TaigaDisablePhysfs()
{
	al_set_standard_file_interface();
}

void TaigaEnablePhysfs()
{
	al_set_physfs_file_interface();
}
