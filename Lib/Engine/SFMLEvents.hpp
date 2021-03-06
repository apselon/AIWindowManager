#pragma once

#include "../Event/Event.hpp"
#include "../Aux/Auxiliary.hpp"
#include "SFMLGraphics.hpp"

class SFMLEventSystem {
private:
    SFMLEventSystem() = default;

public:
    static void start();
    static void stop();
    static const Event* parse_event();
    static const Event* poll_event();
    static void append_event(const Event& event);
    static Event pop_event();

};

using EventSystem = SFMLEventSystem;
