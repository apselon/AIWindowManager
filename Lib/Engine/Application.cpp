#include "Application.hpp"
#include "../GUIElems/Label.hpp"
#include "../GUIElems/Button.hpp"
#include <SFML/Graphics/Color.hpp>

AbstractWindow* AIWM::Application::root_window = nullptr;

void AIWM::Application::start(){
    Application::root_window = new HelloWorldButton(100, 100, 100, 200);
    GraphicSystem::start();
    EventSystem::start();

}

void AIWM::Application::stop(){
    delete Application::root_window;
    GraphicSystem::stop();
    EventSystem::start();
}

void AIWM::Application::run(){
    while (GraphicSystem::is_running()){
        auto cur_event = Event();

        if (EventSystem::poll_event(cur_event)){
            switch(cur_event.type){
                case Events::MouseClickType:
                    root_window->handle_mouse_click({
                        cur_event.mouse_click.pos_x, 
                        cur_event.mouse_click.pos_y
                    });
                    break;
                
                case Events::MouseMoveType:
                    root_window->handle_mouse_move({
                            cur_event.mouse_move.pos_x,
                            cur_event.mouse_move.pos_y
                    });
                    break;

                default:
                    break;
            }
        }

        root_window->handle_redraw();
        GraphicSystem::display_desktop();
    }
}
