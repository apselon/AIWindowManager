#pragma once
#include "../Event/Event.hpp"
#include "../Aux/Auxiliary.hpp"

class SFMLEventSystem {
private:
    SFMLEventSystem() = default;
    static queue<Event>* events_queue; 

public:
    void start();
    void stop();
    template <typename... Args_t>
    void emplace_event(Events::Type type, Args_t... args);
    bool poll_event(sf::RenderWindow* desktop);

};

