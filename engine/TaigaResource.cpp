#include "TaigaCommon.hpp"
#include "TaigaResource.hpp"

using std::string;

ALLEGRO_FILE* load_resource(string resname, bool binary)
{
	return al_fopen(("resources/" + resname).data(), binary ? "rb" : "r");
}

ALLEGRO_BITMAP* load_image(string resname)
{
	return al_load_bitmap(("resources/images/" + resname).data());
}

ALLEGRO_SAMPLE* load_sample(string resname)
{
	return al_load_sample(("resources/audio/" + resname).data());
}

ALLEGRO_FONT* load_font(string resname, int size, int flags)
{
	return al_load_ttf_font(("resources/fonts/" + resname).data(), size, flags);
}
