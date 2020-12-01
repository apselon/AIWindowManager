#include "SFMLEvents.hpp"
#include <SFML/Window/Event.hpp>

void SFMLEventSystem::start() {
}

void SFMLEventSystem::stop() {
}

const Event* SFMLEventSystem::parse_event(){
    auto sf_event = sf::Event();
    
    Vector2d pos = {};
    while (SFMLGraphicSystem::desktop()->pollEvent(sf_event)){
        switch (sf_event.type){
            case sf::Event::MouseButtonPressed:
                
                pos = Vector2d(sf_event.mouseButton.x, 
                               sf_event.mouseButton.y);

                return new MouseEvent(pos, EventType::MouseClick);
                break;

            case sf::Event::MouseButtonReleased:
                pos = Vector2d(sf_event.mouseButton.x, 
                               sf_event.mouseButton.y);

                return new MouseEvent(pos, EventType::MouseRelease);
                break;
            
            case sf::Event::MouseMoved:
                pos = Vector2d(sf_event.mouseButton.x, 
                               sf_event.mouseButton.y);

                return new MouseEvent(pos, EventType::MouseMove);
                break;

            default:
                return nullptr;
        }
    }

    return nullptr; 
}

const Event* SFMLEventSystem::poll_event() {
    return SFMLEventSystem::parse_event();
}

void SFMLEventSystem::append_event(const Event& event){
    /*
    SFMLEventSystem::events_queue->push(event);
    */
}

Event SFMLEventSystem::pop_event(){
    /*
    auto event = SFMLEventSystem::events_queue->front();
    SFMLEventSystem::events_queue->pop();

    return event;
    */
    return {};
}
