#include "Application.hpp"
#include "../Window/Window.hpp"
#include "../GUIElems/Scroll.hpp"

AbstractWindow* AIWM::Application::root_window = nullptr;

void AIWM::Application::start()
{
    Application::root_window = new DesktopWindow();
    GraphicSystem::start();
    EventSystem::start();

}

void AIWM::Application::open_window(AbstractWindow* new_window)
{
    root_window->add_subwindow(new_window);
}

void AIWM::Application::stop()
{
    delete root_window;

    GraphicSystem::stop();
    EventSystem::stop();
}

void AIWM::Application::run()
{
    auto redraw = RedrawEvent();
    while (GraphicSystem::is_running()){
        root_window->handle_event(EventSystem::poll_event());
        root_window->handle_event(&redraw);

        GraphicSystem::display_desktop();
    }
}
