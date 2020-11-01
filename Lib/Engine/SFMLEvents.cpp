#include "SFMLEvents.hpp"
#include <SFML/Window/Event.hpp>

queue<Event>* SFMLEventSystem::events_queue = nullptr;

void SFMLEventSystem::start() {
    SFMLEventSystem::events_queue = new queue<Event>();
}

void SFMLEventSystem::stop() {
    delete SFMLEventSystem::events_queue;
}

bool SFMLEventSystem::parse_event(Event& my_event){
    auto sf_event = sf::Event();

    while (SFMLGraphicSystem::desktop()->pollEvent(sf_event)){
        switch (sf_event.type){
            case sf::Event::MouseButtonPressed:
                my_event.type = Events::MouseClickType;
                my_event.mouse_click = Events::MouseClick {
                    static_cast<double>(sf_event.mouseButton.x),
                    static_cast<double>(sf_event.mouseButton.y)
                };
                break;
            
            case sf::Event::MouseMoved:
                my_event.type = Events::MouseMoveType;
                my_event.mouse_move = Events::MouseMove {
                    static_cast<double>(sf_event.mouseMove.x),
                    static_cast<double>(sf_event.mouseMove.y),
                };
                break;

            default:
                return false;
        }
    }

    return true;
}

bool SFMLEventSystem::poll_event(Event& event) {
    return SFMLEventSystem::parse_event(event);
}

void SFMLEventSystem::append_event(const Event& event){
    SFMLEventSystem::events_queue->push(event);
}

Event SFMLEventSystem::pop_event(){

    auto event = SFMLEventSystem::events_queue->front();
    SFMLEventSystem::events_queue->pop();

    return event;
}
