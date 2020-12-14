#include "Lib/Engine/Application.hpp"
#include "Lib/GUIElems/Scroll.hpp"
#include "Lib/GUIElems/Button.hpp"
#include "Lib/GUIElems/Label.hpp"

int main(void){
    AIWM::Application::start();

    auto scroll_view = new ScrollView({10, 10}, {200, 100});
    scroll_view->add_subwindow(new TextLabel({0, 0}, {20, 20}, "Hello World!", 40));
    //scroll_view->add_subwindow(new HelloWorldButton({0, 0}, {20, 20}));
    AIWM::Application::open_window(scroll_view);
    AIWM::Application::open_window(new Slider({100 + 200, 100}, {10, 10}, {100, 100 + 100}, scroll_view));

    AIWM::Application::open_window(new HelloWorldButton({400, 400}, {100, 100}, "Misc/Images/Floppa.jpg"));


    AIWM::Application::run();
    AIWM::Application::stop();
};
