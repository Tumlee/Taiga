#ifndef TAIGA_MAINHEADER
#define TAIGA_MAINHEADER

#include "TaigaRender.hpp"
#include "TaigaActorList.hpp"
#include "TaigaInput.hpp"
#include "TaigaSound.hpp"
#include "TaigaConfig.hpp"

extern TaigaKeyboard key;
extern TaigaMouse mouse;
extern TaigaActorList actors;
extern TaigaLayerList canvas;

extern ALLEGRO_DISPLAY* taiga_display;
extern ALLEGRO_EVENT_QUEUE* taiga_events;
extern ALLEGRO_TIMER* taiga_ticktimer;
extern ALLEGRO_TIMER* taiga_frametimer;
extern bool taiga_quitting;

#endif
