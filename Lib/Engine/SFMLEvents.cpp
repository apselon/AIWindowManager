#include "SFMLEvents.hpp"

queue<Event>* SFMLEventSystem::events_queue = nullptr;

void SFMLEventSystem::start() {
    SFMLEventSystem::events_queue = new queue<Event>();
}

void SFMLEventSystem::stop() {
    delete SFMLEventSystem::events_queue;
}

template <typename... Args_t>
void SFMLEventSystem::emplace_event(Events::Type type, Args_t... args){
    auto event = Event(type);

    switch (type) {
        case Events::MouseMoveType:
            event.mouse_move = Events::MouseMove{args...};
            break;
        case Events::MouseClickType:
            event.mouse_click = Events::MouseClick{args...};
        default:
            break;
    }

    SFMLEventSystem::events_queue->push(event);
}

bool SFMLEventSystem::poll_event(sf::RenderWindow* desktop){
    return desktop.pollEvent(event);
}

