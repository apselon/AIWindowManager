#pragma once
#include "../Event/Event.hpp"
#include "../Aux/Auxiliary.hpp"
#include "SFMLGraphics.hpp"

class SFMLEventSystem {
private:
    SFMLEventSystem() = default;
    static queue<Event>* events_queue; 

public:
    static void start();
    static void stop();
    static bool parse_event(Event& event);
    static void append_event(const Event& event);
    static Event pop_event();

};

