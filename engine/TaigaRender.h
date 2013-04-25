#ifndef TAIGA_RENDER
#define TAIGA_RENDER

#include "Taiga.h"

#include <vector>
#include <cstdlib>

//=====================================================================
//In order to facilitate layered drawing (a system of drawing where
//certain objects are drawn on top of others in a well-defined order),
//we can't simply draw something onto the screen the moment we know
//it needs to be drawn. Instead, we must send a message to the renderer
//to let it know to draw something when it can get around to it.
//
//This is what a TaigaDrawer is for, and its draw() function is
//basically the instructions on HOW to draw a particular concept.
//=====================================================================
class TaigaDrawer
{
	public:
		int x, y;
		virtual void draw() = 0;
};

//=======================================================================
//A TaigaLayer contains all of the TaigaDrawers registered on that layer.
//A TaigaLayerList is just a collection of enumerated layers, starting
//with 0. Things on layer 0 are drawn first (in the back), while things
//on the highest layer are drawn last (in front).
//=======================================================================
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

//And extended TaigaSprite which can be scaled and rotated.
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

//A TaigaDrawer which clears the screen to a given color.
class TaigaClear : public TaigaDrawer
{
	public:
		int r, g, b;

		TaigaClear(int rr, int gg, int bb);
		virtual void draw();
};

//This TaigaDrawer can be used to write text to the screen.
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
