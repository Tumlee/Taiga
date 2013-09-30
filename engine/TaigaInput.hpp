#ifndef TAIGA_INPUT
#define TAIGA_INPUT

#include "TaigaCommon.hpp"
#include <vector>

//An enum to keep track of the state of a key.
enum class keystate
{
	up,
	down,
	fresh,
	freshup
};

//An enum that represents the different axes of the mouse,
//in the exact order that Allegro sees them.
//Your actual mouse may have more axes than the ones listed here.
enum class mouseaxis
{
	x = 0,
	y = 1,
	z = 2,
	w = 3
};

//An enum that represents the different buttons on a mouse,
//in the exact order that Allegro sees them.
//Your actual mouse may have more buttons than the ones listed here.
enum class mousebut
{
	left = 0,
	right = 1,
	middle = 2
};

//An enum that represents the different control types
//that a TaigaControl can have.
enum class TaigaControlType
{
	mbutton,
	kbutton
};

//=======================================================================
//Class to keep track of the keyboard, an instance of this, called 'key',
//is automatically created by the engine and can be accessed globally.
//It is updated by the game loop, so don't expect it to work properly
//during game_bootup() nor game_startup().
//=======================================================================
class TaigaKeyboard
{
	keystate keys[ALLEGRO_KEY_MAX];
	ALLEGRO_EVENT_QUEUE* event_queue;

	public:
		TaigaKeyboard();

	//These functions really shouldn't be called by the user, as
	//it will likely cause issues with input not being detected correctly.
		void init();
		void update();
		void clear();	//Automatically releases all keys.

	//All of these functions take an ALLEGRO_KEY_* as their argument.
	//Do not expect passing ASCII characters to work properly.
		bool fresh(int key);	//Return true if they key was JUST pressed this tick.
		bool down(int key);		//Returns true if the key is down at all.
		bool up(int key);		//Returns true if they key is not being pressed.
		bool freshup(int key);	//Returns true if the key was JUST released this tick.
};

//==================================================================
//Class to keep track of a mouse's position, changes in position
//from tick to tick, and whatever buttons are being pressed.
//An instance of this class called 'mouse' is automatically created
//by the engine, and the same rules apply as the 'key' object above.
//==================================================================
class TaigaMouse
{
	std::vector<keystate> buttons;
	std::vector<int> axis;
	std::vector<int> delta;

	public:
		int x();	//Returns the x position of the mouse relative to window.
		int y();	//Returns the y position of the mouse relative to window.
		int scrolldelta();	//Returns how much the scroll wheel has changed this tick.

	//This function returns the current value of the given axis.
		int getaxis(int axisnum);
		int getaxis(mouseaxis axisnum);

	//This function returns the change in value of the given
	//axis over the last tick.
		int axisdelta(int axisnum);
		int axisdelta(mouseaxis axisnum);

	//Returns true if the given mouse button has JUST been pressed this tick.
		bool fresh(int button);
		bool fresh(mousebut button);

	//Returns true if the given mouse button is pressed at all.
		bool down(int button);
		bool down(mousebut button);

	//Returns true if the given mouse button is not being pressed.
		bool up(int button);
		bool up(mousebut button);

	//Returns true if the given mouse button has JUST been released this tick.
		bool freshup(int button);
		bool freshup(mousebut button);

	//These functions should not be called by the user and are
	//automatically called by the game loop.
		void init();
		void update();
		void clear();	//Automatically releases all mousebuttons.
};

class TaigaControl
{
	TaigaControlType type;
	int enumeration;

	public:
		TaigaControl(TaigaControlType t, int e);
		TaigaControl(mousebut mb);

		bool down();
		bool fresh();
		bool up();
		bool freshup();
};

extern TaigaKeyboard key;
extern TaigaMouse mouse;

#endif
