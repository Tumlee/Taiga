#ifndef TAIGA_RENDER
#define TAIGA_RENDER

#include "Taiga.h"

#include <vector>
#include <cstdlib>

class TaigaDrawer
{
	public:
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
		int x, y, flipflags;

		TaigaSprite()
		{
			sprite = nullptr;
			x = y = 0;
			flipflags = 0;
		}

		TaigaSprite(ALLEGRO_BITMAP* spr, int xx, int yy, int flags = 0)
		{
			sprite = spr;
			x = xx;
			y = yy;
			flipflags = flags;
		}

		virtual void draw()
		{
			if(sprite)
				al_draw_bitmap(sprite, x, y, flipflags);
		}
};

class TaigaSpriteEx : public TaigaDrawer
{
	public:
		ALLEGRO_BITMAP* sprite;
		int x, y, flipflags;
		float angle;
		float centerx, centery;
		float scalex, scaley;

		TaigaSpriteEx()
		{
			sprite = nullptr;
			x = y = 0;
			angle = 0;
			flipflags = 0;
			centerx = centery = 0;
			scalex = scaley = 0;
		}

		TaigaSpriteEx(ALLEGRO_BITMAP* spr, int xx, int yy, int flags = 0)
		{
			sprite = spr;
			x = xx;
			y = yy;
			flipflags = flags;
			angle = 0;
			centerx = centery = 0;
			scalex = scaley = 0;
		}

		virtual void draw()
		{
			if(sprite)
			{
				al_draw_scaled_rotated_bitmap(sprite, centerx, centery,
												x, y, scalex, scaley, angle, flipflags);
			}
		}
};

class TaigaClear : public TaigaDrawer
{
	public:
		int r, g, b;

		TaigaClear(int rr, int gg, int bb)
		{
			r = rr;
			g = gg;
			b = bb;
		}

		virtual void draw()
		{
			al_clear_to_color(al_map_rgb(r,g,b));
		}
};

class TaigaText : public TaigaDrawer
{
	public:
		ALLEGRO_FONT* font;
		std::string text;
		int x, y;
		int flags;
		ALLEGRO_COLOR color;

		TaigaText(std::string txt, ALLEGRO_FONT* fnt, int xx, int yy, ALLEGRO_COLOR clr, int flgs)
		{
			text = txt;
			font = fnt;
			x = xx;
			y = yy;
			flags = flgs;
			color = clr;
		}

		virtual void draw()
		{
			if(font)
				al_draw_text(font, color, x, y, flags, text.data());
		}
};

int image_height(ALLEGRO_BITMAP* image);
int image_width(ALLEGRO_BITMAP* image);

#endif
