#pragma once
#include "../Aux/Auxiliary.hpp"

namespace Events {
enum class Type {
    UNDEFIED = -1,
    IdleType,
    MouseClick,
    MouseRelease,
    MouseMove,
    KeyPress,
    KeyRelease
};

struct MouseClick {
    double pos_x;
    double pos_y;
};

struct MouseMove {
    double pos_x;
    double pos_y;
};

struct MouseRelease {
    double pos_x;
    double pos_y;
};

struct KeyPressed {
    int key_code;
};
};

struct Event {
    Events::Type type = Events::Type::UNDEFIED;

	union {
	    Events::MouseClick mouse_click;
	    Events::MouseMove mouse_move; 
	    Events::KeyPressed key_pressed;
        Events::MouseRelease mouse_release;
	};

    Event(): type(Events::Type::UNDEFIED) {};
    Event(Events::Type type): type(type) {};
};

