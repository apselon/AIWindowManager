#include "Application.hpp"

void Application::start(){
    GraphicSystem::start();
    EventSystem::start();
}

void Application::stop(){
    GraphicSystem::stop();
    EventSystem::start();
}

void Application::run(){
    auto cur_event = Event();
    while (EventSystem::parse_event(cur_event)){
        
    }
}
