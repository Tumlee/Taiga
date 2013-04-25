#ifndef TAIGA_RENDER
#define TAIGA_RENDER

#include "Taiga.h"

#include <vector>
#include <cstdlib>

class TaigaDrawer
{
	public:
		int x, y;
		virtual void draw() = 0;
};

class TaigaLayer
{
	private:
		std::vector<TaigaDrawer*> entries;

	public:
		void add_entry(TaigaDrawer* entry);
		void draw();
		void clear();
};

class TaigaLayerList
{
	private:
		std::vector<TaigaLayer> layers;

	public:
		TaigaLayerList();

		void add_entry(TaigaDrawer* entry, int layernum = -1);
		void draw();
		void clear();
		void resize(size_t count);
};

//A basic TaigaDrawer that draws a sprite, so users don't have to write
//their own TaigaDrawer just to draw one.
class TaigaSprite : public TaigaDrawer
{
	public:
		ALLEGRO_BITMAP* sprite;
		int flipflags;

		TaigaSprite();
		TaigaSprite(ALLEGRO_BITMAP* spr, int xx, int yy, int flags = 0);
		virtual void draw();
};

class TaigaSpriteEx : public TaigaDrawer
{
	public:
		ALLEGRO_BITMAP* sprite;
		int flipflags;
		float angle;
		float centerx, centery;
		float scalex, scaley;

		TaigaSpriteEx();
		TaigaSpriteEx(ALLEGRO_BITMAP* spr, int xx, int yy, int flags = 0);
		virtual void draw();
};

class TaigaClear : public TaigaDrawer
{
	public:
		int r, g, b;

		TaigaClear(int rr, int gg, int bb);
		virtual void draw();
};

class TaigaText : public TaigaDrawer
{
	public:
		ALLEGRO_FONT* font;
		std::string text;
		int flags;
		ALLEGRO_COLOR color;

		TaigaText(std::string txt, ALLEGRO_FONT* fnt, int xx, int yy, ALLEGRO_COLOR clr, int flgs);
		virtual void draw();
};

int image_height(ALLEGRO_BITMAP* image);
int image_width(ALLEGRO_BITMAP* image);

#endif
