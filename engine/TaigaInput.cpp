#include "TaigaInput.hpp"

//=======================================================
//Functions for the semantics behind checking the logical
//keystate of a key or button.
//=======================================================
static bool isdown(keystate state)
{
	return state == keystate::down || state == keystate::fresh;
}

static bool isfresh(keystate state)
{
	return state == keystate::fresh;
}

static bool isup(keystate state)
{
	return state == keystate::up || state == keystate::freshup;
}

static bool isfreshup(keystate state)
{
	return state == keystate::freshup;
}

//=============================================
//Member functions for the TaigaKeyboard class.
//=============================================
TaigaKeyboard::TaigaKeyboard()
{
	for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
		keys[i] = keystate::up;

	event_queue = nullptr;
}

void TaigaKeyboard::init()
{
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void TaigaKeyboard::update()
{
	if(event_queue == nullptr)
		fatal_error("Attempted to update an unitialized TaigaKeyboard.");

	for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
	{
		if(keys[i] == keystate::fresh)
			keys[i] = keystate::down;

		if(keys[i] == keystate::freshup)
			keys[i] = keystate::up;
	}

	ALLEGRO_EVENT ev;

	while(al_get_next_event(event_queue, &ev))
	{
		int key = ev.keyboard.keycode;

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN && up(key))
			keys[key] = keystate::fresh;

		if(ev.type == ALLEGRO_EVENT_KEY_UP && down(key))
			keys[key] = keystate::freshup;
	}
}

void TaigaKeyboard::clear()
{
	for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
	{
		if(isdown(keys[i]))
			keys[i] = keystate::freshup;
	}
}

bool TaigaKeyboard::fresh(int key)
{
	if(key <= 0 || key >= ALLEGRO_KEY_MAX)
		return false;

	return isfresh(keys[key]);
}

bool TaigaKeyboard::down(int key)
{
	if(key <= 0 || key >= ALLEGRO_KEY_MAX)
		return false;

	return isdown(keys[key]);
}

bool TaigaKeyboard::up(int key)
{
	if(key <= 0 || key >= ALLEGRO_KEY_MAX)
		return false;

	return isup(keys[key]);
}

bool TaigaKeyboard::freshup(int key)
{
	if(key <= 0 || key >= ALLEGRO_KEY_MAX)
		return false;

	return isfreshup(keys[key]);
}

//==========================================
//Member functions for the TaigaMouse class.
//==========================================
void TaigaMouse::init()
{
	buttons.clear();
	axis.clear();

	for(size_t i = 0; i < al_get_mouse_num_axes(); i++)
	{
		axis.push_back(0);
		delta.push_back(0);
	}

	for(size_t i = 0; i < al_get_mouse_num_buttons(); i++)
		buttons.push_back(keystate::up);

	return;
}

//====================================================
//A note here, I really wish there was a way to have
//explicitly scoped enums without removing the ability
//to implicitly typecast to int...
//====================================================
bool TaigaMouse::fresh(int button)
{
	if(button < 0 || (size_t)button >= buttons.size())
		return false;

	return isfresh(buttons[button]);
}

bool TaigaMouse::down(int button)
{
	if(button < 0 || (size_t)button >= buttons.size())
		return false;

	return isdown(buttons[button]);
}

bool TaigaMouse::up(int button)
{
	if(button < 0 || (size_t)button >= buttons.size())
		return false;

	return isup(buttons[button]);
}

bool TaigaMouse::freshup(int button)
{
	if(button < 0 || (size_t)button >= buttons.size())
		return false;

	return isfreshup(buttons[button]);
}

bool TaigaMouse::fresh(mousebut button)
{
	return fresh((int)button);
}

bool TaigaMouse::down(mousebut button)
{
	return down((int)button);
}

bool TaigaMouse::up(mousebut button)
{
	return up((int)button);
}

bool TaigaMouse::freshup(mousebut button)
{
	return freshup((int)button);
}

void TaigaMouse::update()
{
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);

	for(auto& button : buttons)
	{
		if(button == keystate::fresh)
			button = keystate::down;

		if(button == keystate::freshup)
			button = keystate::up;
	}

	//To calculate deltas, first we stuff the old values into delta.
	for(size_t i = 0; i < axis.size(); i++)
		delta[i] = axis[i];

	//Remember that the first mouse button is actually 1
	//when dealing with the al_mouse_button_down() function.
	for(size_t i = 0; i < buttons.size(); i++)
	{
		bool butdown = al_mouse_button_down(&state, i + 1);

		if(butdown && up(i))
			buttons[i] = keystate::fresh;

		if(!butdown && down(i))
			buttons[i] = keystate::freshup;
	}

	for(size_t i = 0; i < axis.size(); i++)
	{
		axis[i] = al_get_mouse_state_axis(&state, i);
		delta[i] = axis[i] - delta[i];	//Calculate deltas.
	}

	return;
}

void TaigaMouse::clear()
{
	for(auto& button : buttons)
	{
		if(isdown(button))
			button = keystate::freshup;
	}
}

int TaigaMouse::getaxis(int axisnum)
{
	if(axisnum < 0 || (size_t)axisnum >= axis.size())
		return 0;

	return axis[axisnum];
}

int TaigaMouse::axisdelta(int axisnum)
{
	if(axisnum < 0 || (size_t)axisnum >= axis.size())
		return 0;

	return delta[axisnum];
}

int TaigaMouse::getaxis(mouseaxis axisnum)
{
	return getaxis((int)axisnum);
}

int TaigaMouse::axisdelta(mouseaxis axisnum)
{
	return axisdelta((int)axisnum);
}

int TaigaMouse::x()
{
	return getaxis(mouseaxis::x);
}

int TaigaMouse::y()
{
	return getaxis(mouseaxis::y);
}

int TaigaMouse::scrolldelta()
{
	return axisdelta(mouseaxis::z);
}

//============================================
//Member functions for the TaigaKeybind class.
//============================================
extern TaigaKeyboard key;	//TaigaKeybinds utilize these objects exclusively.
extern TaigaMouse mouse;

TaigaKeybind::TaigaKeybind()
{
	type = TaigaKeybindType::none;
	enumeration = 0;
}

TaigaKeybind::TaigaKeybind(TaigaKeybindType t, int e)
{
	type = t;
	enumeration = e;
}

TaigaKeybind::TaigaKeybind(mousebut mb)
{
	type = TaigaKeybindType::mbutton;
	enumeration = (int)mb;
}

bool TaigaKeybind::down()
{
	switch(type)
	{
		case TaigaKeybindType::kbutton:
			return key.down(enumeration);

		case TaigaKeybindType::mbutton:
			return mouse.down(enumeration);

		case TaigaKeybindType::none:
			return false;

		default:
			fatal_error("Polled a malformed TaigaKeybind.");
	}
}

bool TaigaKeybind::fresh()
{
	switch(type)
	{
		case TaigaKeybindType::kbutton:
			return key.fresh(enumeration);

		case TaigaKeybindType::mbutton:
			return mouse.fresh(enumeration);

		case TaigaKeybindType::none:
			return false;

		default:
			fatal_error("Polled a malformed TaigaKeybind.");
	}
}

bool TaigaKeybind::up()
{
	switch(type)
	{
		case TaigaKeybindType::kbutton:
			return key.up(enumeration);

		case TaigaKeybindType::mbutton:
			return mouse.up(enumeration);

		case TaigaKeybindType::none:
			return true;

		default:
			fatal_error("Polled a malformed TaigaKeybind.");
	}
}

bool TaigaKeybind::freshup()
{
	switch(type)
	{
		case TaigaKeybindType::kbutton:
			return key.freshup(enumeration);

		case TaigaKeybindType::mbutton:
			return mouse.freshup(enumeration);

		case TaigaKeybindType::none:
			return false;

		default:
			fatal_error("Polled a malformed TaigaKeybind.");
	}
}
