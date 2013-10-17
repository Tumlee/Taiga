#include "TaigaRender.hpp"

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
	target = nullptr;
	screenshot = nullptr;
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
	if(target == nullptr)
		return;

	//Save the old target bitmap so we're not messing with the user.
	ALLEGRO_BITMAP* old_target = al_get_target_bitmap();

	//Make sure we're drawing on our target.
	al_set_target_bitmap(target);

	for(size_t i = 0; i < layers.size(); i++)
	{
		layers[i].draw_entries();

		if(screenshot_request == i)
		{
			screenshot = al_clone_bitmap(target);
			screenshot_request = -2;
		}
	}

	//Reset the target bitmap to the old one.
	al_set_target_bitmap(old_target);
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

	//When the number of layers changes, the requested layer
	//to take a screenshot from is no longer logically relevant.
	//Set it to -2, which signifies that there is no requested screenshot.
	screenshot_request = -2;
}

void TaigaLayerList::set_layercam(TaigaLayerCam cam, int layernum)
{
	if((size_t)layernum >= layers.size())
		return;

	layers[layernum].cam = cam;
}

void TaigaLayerList::request_screenshot(int layer)
{
	//screenshot request for -1 means the last avaliable layer.
	if(layer == -1)
		layer = layers.size() - 1;

	//Invalid screenshot request?
	if(layer >= layers.size())
		return;

	screenshot_request = layer;
}

void TaigaLayerList::clear_screenshot()
{
	al_destroy_bitmap(screenshot);
	screenshot = nullptr;
}

//===========================================
//Member functions for the TaigaDrawer class.
//===========================================
TaigaDrawer::~TaigaDrawer()
{
	return;
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
	alpha = 1.0;
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
	alpha = 1.0;
}

void TaigaSpriteEx::draw()
{
	if(sprite)
	{
		al_draw_tinted_scaled_rotated_bitmap(sprite, al_map_rgba_f(alpha, alpha, alpha, alpha),
										centerx, centery, x, y, scalex, scaley,
										angle, flipflags);
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
//Member functions for the TaigaBlend class.
//==========================================
TaigaBlend::TaigaBlend(int oper, int source, int destination)
{
	op = oper;
	src = source;
	dest = destination;
}

void TaigaBlend::draw()
{
	al_set_blender(op, src, dest);
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

int display_width()
{
	return al_get_display_width(al_get_current_display());
}

int display_height()
{
	return al_get_display_height(al_get_current_display());
}

void set_cursor(ALLEGRO_BITMAP* image, int x, int y)
{
	static ALLEGRO_MOUSE_CURSOR* cur_cursor = nullptr;

	//Destroy the current cursor if there is one.
	if(cur_cursor)
		al_destroy_mouse_cursor(cur_cursor);

	cur_cursor = al_create_mouse_cursor(image, x, y);

	al_set_mouse_cursor(al_get_current_display(), cur_cursor);
}
