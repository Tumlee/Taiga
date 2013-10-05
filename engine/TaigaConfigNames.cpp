#include <string>
#include <vector>
#include "TaigaInput.hpp"

using std::string;
using std::to_string;
using std::vector;

//A TaigaKeybind/string pair for identifying a control by name.
class TaigaNamedBind
{
	public:
		TaigaKeybind keybind;
		string name;
};

vector<TaigaNamedBind> keybindnames;

//Adds a new keyboard key to the list of keybind names.
static void add_keyname(int key, string name)
{
	TaigaNamedBind newcon;
	newcon.keybind = TaigaKeybind(TaigaKeybindType::kbutton, key);
	newcon.name = name;

	keybindnames.push_back(newcon);
}

//Adds a new mouse button to the list of keybind names.
static void add_mousename(int butnum, string name)
{
	TaigaNamedBind newcon;
	newcon.keybind = TaigaKeybind(TaigaKeybindType::mbutton, butnum);
	newcon.name = name;

	keybindnames.push_back(newcon);
}

//Generate a list of strings through which a keybinding
//can be referred to. This is required in order to load
//keybindings from an INI file.
static void generate_keybindnames()
{
	//Letter keys.
	for(int k = ALLEGRO_KEY_A; k <= ALLEGRO_KEY_Z; k++)
		add_keyname(k, string(1, 'a' + (k - ALLEGRO_KEY_A)));

	//Number keys.
	for(int k = ALLEGRO_KEY_0; k <= ALLEGRO_KEY_9; k++)
		add_keyname(k, string(1, '0' + (k - ALLEGRO_KEY_0)));

	//Function keys.
	for(int k = ALLEGRO_KEY_F1; k <= ALLEGRO_KEY_F12; k++)
		add_keyname(k, "f" + to_string(k + 1 - ALLEGRO_KEY_F1));

	//Keypad number keys.
	for(int k = ALLEGRO_KEY_PAD_0; k <= ALLEGRO_KEY_PAD_9; k++)
		add_keyname(k, "kp" + to_string(k - ALLEGRO_KEY_PAD_0));

	add_keyname(ALLEGRO_KEY_ESCAPE, "esc");
	add_keyname(ALLEGRO_KEY_TILDE, "`");
	add_keyname(ALLEGRO_KEY_MINUS, "-");
	add_keyname(ALLEGRO_KEY_EQUALS, "=");
	add_keyname(ALLEGRO_KEY_BACKSPACE, "backspace");
	add_keyname(ALLEGRO_KEY_TAB, "tab");
	add_keyname(ALLEGRO_KEY_OPENBRACE, "[");
	add_keyname(ALLEGRO_KEY_CLOSEBRACE, "]");
	add_keyname(ALLEGRO_KEY_ENTER, "enter");
	add_keyname(ALLEGRO_KEY_SEMICOLON, ";");
	add_keyname(ALLEGRO_KEY_QUOTE, "\'");
	add_keyname(ALLEGRO_KEY_BACKSLASH, "\\");
	add_keyname(ALLEGRO_KEY_BACKSLASH2, "kp\\");
	add_keyname(ALLEGRO_KEY_COMMA, ",");
	add_keyname(ALLEGRO_KEY_FULLSTOP, ".");
	add_keyname(ALLEGRO_KEY_SLASH, "/");
	add_keyname(ALLEGRO_KEY_SPACE, "space");

	add_keyname(ALLEGRO_KEY_INSERT, "insert");
	add_keyname(ALLEGRO_KEY_DELETE, "delete");
	add_keyname(ALLEGRO_KEY_HOME, "home");
	add_keyname(ALLEGRO_KEY_END, "end");
	add_keyname(ALLEGRO_KEY_PGUP, "pgup");
	add_keyname(ALLEGRO_KEY_PGDN, "pgdn");

	add_keyname(ALLEGRO_KEY_UP, "up");
	add_keyname(ALLEGRO_KEY_DOWN, "down");
	add_keyname(ALLEGRO_KEY_LEFT, "left");
	add_keyname(ALLEGRO_KEY_RIGHT, "right");

	add_keyname(ALLEGRO_KEY_PAD_SLASH, "kp/");
	add_keyname(ALLEGRO_KEY_PAD_ASTERISK, "*");
	add_keyname(ALLEGRO_KEY_PAD_MINUS, "kp-");
	add_keyname(ALLEGRO_KEY_PAD_PLUS, "+");
	add_keyname(ALLEGRO_KEY_PAD_DELETE, "kp_delete");
	add_keyname(ALLEGRO_KEY_PAD_ENTER, "kp_enter");
	add_keyname(ALLEGRO_KEY_PAUSE, "pause");

	add_keyname(ALLEGRO_KEY_LSHIFT, "lshift");
	add_keyname(ALLEGRO_KEY_RSHIFT, "rshift");
	add_keyname(ALLEGRO_KEY_RCTRL, "lctrl");
	add_keyname(ALLEGRO_KEY_LCTRL, "rctrl");
	add_keyname(ALLEGRO_KEY_ALT, "lalt");
	add_keyname(ALLEGRO_KEY_ALTGR, "ralt");
	add_keyname(ALLEGRO_KEY_PAD_EQUALS, "kp=");

	//All the mouse buttons are referred to by number.
	//Sixteen mouse buttons ought to be enough for anybody.
	for(int mb = 0; mb < 16; mb++)
		add_mousename(mb, "mouse" + to_string(mb + 1));
}

//Takes the name of a TaigaKeybind and returns
//the correct keybind, if there is one.
TaigaKeybind translate_keybind(string name)
{
	//Generate the list of keybind names if it
	//hasn't already been done.
	if(keybindnames.empty())
		generate_keybindnames();

	for(auto kn : keybindnames)
	{
		if(kn.name == name)
			return kn.keybind;
	}

	//Otherwise, return an empty keybind.
	return TaigaKeybind();
}

//Takes a keybind and attempts to return
//the name for it.
string to_string(TaigaKeybind keybind)
{
	if(keybindnames.empty())
		generate_keybindnames();

	for(auto kn : keybindnames)
	{
		if(kn.keybind == keybind)
			return kn.name;
	}

	return "(none)";
}

//Utilities for translating boolean values
//to and from strings.
bool translate_bool(string name)
{
	return name == "true";
}

string to_string(bool value)
{
	return value ? "true" : "false";
}

