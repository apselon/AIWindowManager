#pragma once
#include "../Aux/Auxiliary.hpp"

namespace Events {
enum Type {
    UNDEFIED = -1,
    MouseClickType,
    MouseMoveType,
    KeyPressType,
    KeyReleaseType
};

struct MouseClick {
    double pos_x;
    double pos_y;
};

struct MouseMove {
    double pos_x;
    double pos_y;
};

struct KeyPressed {
    int key_code;
};
};

struct Event {
    Events::Type type = Events::UNDEFIED;

	union {
	    Events::MouseClick mouse_click;
	    Events::MouseMove mouse_move; 
	    Events::KeyPressed key_pressed;
	};

    Event(Events::Type type): type(type) {};
};

