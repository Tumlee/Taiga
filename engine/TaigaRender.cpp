#include "TaigaRender.hpp"

TaigaLayerList canvas;

//=============================================
//Member functions for the TaigaLayerCam class.
//=============================================
TaigaLayerCam::TaigaLayerCam()
{
	x = 0;
	y = 0;
}

TaigaLayerCam::TaigaLayerCam(int xx, int yy)
{
	x = xx;
	y = yy;
}

//==========================================
//Member functions for the TaigaLayer class.
//==========================================
void TaigaLayer::add(TaigaDrawer* entry)
{
	if(entry)
		entries.push_back(entry);
}

void TaigaLayer::draw_entries()
{
	for(auto entry : entries)
	{
		entry->x -= cam.x;
		entry->y -= cam.y;
		entry->draw();
	}
}

void TaigaLayer::clear()
{
	for(auto entry : entries)
		delete entry;

	entries.clear();
}

//==============================================
//Member functions for the TaigaLayerList class.
//==============================================
TaigaLayerList::TaigaLayerList()
{
	//By default, we have four layers to work with.
	//In most cases, this should be plenty.
	set_layercount(4);
}

void TaigaLayerList::add(TaigaDrawer* entry, int layernum)
{
	//-1 has a special meaning, it means the last available layer.
	if(layernum == -1)
		layernum = layers.size() - 1;

	if((size_t)layernum >= layers.size())
		return;

	layers[layernum].add(entry);
}

void TaigaLayerList::draw_entries()
{
	for(auto layer : layers)
		layer.draw_entries();
}

void TaigaLayerList::clear()
{
	for(auto& layer : layers)
		layer.clear();
}

void TaigaLayerList::set_layercount(size_t count)
{
	clear();
	layers.clear();

	for(size_t i = 0; i < count; i++)
		layers.emplace_back(TaigaLayer());
}

void TaigaLayerList::set_layercam(TaigaLayerCam cam, int layernum)
{
	if((size_t)layernum >= layers.size())
		return;

	layers[layernum].cam = cam;
}

//===========================================
//Member functions for the TaigaSprite class.
//===========================================
TaigaSprite::TaigaSprite()
{
	sprite = nullptr;
	x = y = 0;
	flipflags = 0;
}

TaigaSprite::TaigaSprite(ALLEGRO_BITMAP* spr, int xx, int yy, int flags)
{
	sprite = spr;
	x = xx;
	y = yy;
	flipflags = flags;
}

void TaigaSprite::draw()
{
	if(sprite)
		al_draw_bitmap(sprite, x, y, flipflags);
}

//=============================================
//Member functions for the TaigaSpriteEx class.
//=============================================
TaigaSpriteEx::TaigaSpriteEx()
{
	sprite = nullptr;
	x = y = 0;
	angle = 0;
	flipflags = 0;
	centerx = centery = 0;
	scalex = scaley = 1;
}

TaigaSpriteEx::TaigaSpriteEx(ALLEGRO_BITMAP* spr, int xx, int yy, int flags)
{
	sprite = spr;
	x = xx;
	y = yy;
	flipflags = flags;
	angle = 0;
	centerx = centery = 0;
	scalex = scaley = 1;
}

void TaigaSpriteEx::draw()
{
	if(sprite)
	{
		al_draw_scaled_rotated_bitmap(sprite, centerx, centery, x, y,
										scalex, scaley, angle, flipflags);
	}
}

//==========================================
//Member functions for the TaigaClear class.
//==========================================
TaigaClear::TaigaClear(int rr, int gg, int bb)
{
	r = rr;
	g = gg;
	b = bb;
}

void TaigaClear::draw()
{
	al_clear_to_color(al_map_rgb(r,g,b));
}

//=========================================
//Member functions for the TaigaText class.
//=========================================
TaigaText::TaigaText(std::string txt, ALLEGRO_FONT* fnt, int xx, int yy, ALLEGRO_COLOR clr, int flgs)
{
	text = txt;
	font = fnt;
	x = xx;
	y = yy;
	flags = flgs;
	color = clr;
}

void TaigaText::draw()
{
	if(font)
		al_draw_text(font, color, x, y, flags, text.data());
}

//==========================================
//Miscellaneous rendering-related functions.
//==========================================
int image_width(ALLEGRO_BITMAP* image)
{
	return image ? al_get_bitmap_width(image) : 0;
}

int image_height(ALLEGRO_BITMAP* image)
{
	return image ? al_get_bitmap_height(image) : 0;
}
