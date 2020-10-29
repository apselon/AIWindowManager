#include "Application.hpp"
#include "../GUIElems/Button.hpp"
#include <SFML/Graphics/Color.hpp>

AbstractWindow* AIWM::Application::root_window = nullptr;

void AIWM::Application::start(){
    Application::root_window = new HelloWorldButton(100, 100, 100, 100);
    GraphicSystem::start();
    EventSystem::start();

}

void AIWM::Application::stop(){
    //delete Application::root_window;
    GraphicSystem::stop();
    EventSystem::start();
}

void AIWM::Application::run(){
    while (GraphicSystem::desktop()->isOpen()){
        auto cur_event = Event();

        GraphicSystem::desktop()->clear(sf::Color::White);

        if (EventSystem::parse_event(cur_event)){
            switch(cur_event.type){
                case Events::MouseClickType:
                    printf("Application got click\n");
                    root_window->handle_mouse_click({cur_event.mouse_click.pos_x, 
                                                     cur_event.mouse_click.pos_y});
                    break;
                default:
                    break;
            }
        } else {
            root_window->handle_idle();
        }

        GraphicSystem::display_desktop();
    }
}
