#ifndef TAIGA_RENDER
#define TAIGA_RENDER

#include "Taiga.hpp"

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

//A camera that can be applied to a layer. It essentially
//adjusts the x and y positions of TaigaDrawers.
class TaigaLayerCam
{
	public:
		int x, y;

		TaigaLayerCam();
		TaigaLayerCam(int xx, int yy);
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
		void add(TaigaDrawer* entry);
		void draw_entries();
		void clear();

		TaigaLayerCam cam;
};

class TaigaLayerList
{
	private:
		std::vector<TaigaLayer> layers;

	public:
		ALLEGRO_BITMAP* target;

		TaigaLayerList();

		void add(TaigaDrawer* entry, int layernum = -1);
		void draw_entries();
		void clear();
		void set_layercount(size_t count);

		void set_layercam(TaigaLayerCam cam, int layernum);
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

//A TaigaDrawer to change the Allegro blending style.
class TaigaBlend : public TaigaDrawer
{
	public:
		int op;
		int src;
		int dest;

		TaigaBlend(int oper, int source, int dest);
		virtual void draw();
};

int image_height(ALLEGRO_BITMAP* image);
int image_width(ALLEGRO_BITMAP* image);
int display_width();
int display_height();

//Sets the given bitmap as your cursor, with hotspot x, y.
void set_cursor(ALLEGRO_BITMAP* image, int x = 0, int y = 0);

extern TaigaLayerList canvas;

#endif
