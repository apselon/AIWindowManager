#pragma once
#include "../Aux/Auxiliary.hpp"

enum class EventType {
    UNDEF = -1,
    Idle,
    MouseClick,
    MouseRelease,
    MouseMove,
    KeyPress,
    KeyRelease,
    Redraw
};

class Event {
private:
    EventType type = EventType::UNDEF;

public:
    Event() = default;
    Event(EventType type);
    EventType get_type();
};

class MouseEvent: public Event {
private:
    Vector2d pos = Vector2d();

public:
    MouseEvent() = default;
    MouseEvent(const Vector2d& pos, EventType type);
};

class KeyEvent: public Event {
private:
    int key = 0;

public:
    KeyEvent() = default;
    KeyEvent(int key, EventType type);
};

class RedrawEvent: public Event {
public:
    RedrawEvent();
};
