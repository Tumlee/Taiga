#include "TaigaRender.h"

//==========================================
//Member functions for the TaigaLayer class.
//==========================================
void TaigaLayer::add_entry(TaigaDrawer* entry)
{
	if(entry)
		entries.push_back(entry);
}

void TaigaLayer::draw()
{
	for(auto entry : entries)
		entry->draw();
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
	resize(4);
}

void TaigaLayerList::add_entry(TaigaDrawer* entry, int layernum)
{
	//-1 has a special meaning, it means the last available layer.
	if(layernum == -1)
		layernum = layers.size() - 1;

	if((size_t)layernum >= layers.size())
		return;

	layers[layernum].add_entry(entry);
}

void TaigaLayerList::draw()
{
	for(auto layer : layers)
		layer.draw();
}

void TaigaLayerList::clear()
{
	for(auto& layer : layers)
		layer.clear();
}

void TaigaLayerList::resize(size_t count)
{
	clear();
	layers.clear();

	for(size_t i = 0; i < count; i++)
		layers.emplace_back(TaigaLayer());
}

int image_width(ALLEGRO_BITMAP* image)
{
	return image ? al_get_bitmap_width(image) : 0;
}

int image_height(ALLEGRO_BITMAP* image)
{
	return image ? al_get_bitmap_height(image) : 0;
}
