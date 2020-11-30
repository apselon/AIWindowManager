#include "Event.hpp"

Event::Event(EventType type)
    :type(type) {}

EventType Event::get_type() {
    return type;
}

//================================================================================
    
MouseEvent::MouseEvent(const Vector2d& pos, EventType type)
    :Event(type), pos(pos) {}

//================================================================================

KeyEvent::KeyEvent(int key, EventType type)
    :Event(type), key(key) {}

//================================================================================

RedrawEvent::RedrawEvent()
    :Event(EventType::Redraw) {}
