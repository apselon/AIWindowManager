#include "Lib/Engine/Application.hpp"
#include "Lib/GUIElems/Scroll.hpp"
#include "Lib/GUIElems/Button.hpp"

int main(void){
    AIWM::Application::start();
    AIWM::Application::open_window(new Slider({100 + 100, 100}, {10, 10}, {100, 100 + 100}, nullptr));
    AIWM::Application::open_window(new Slider({100 + 200, 100}, {10, 10}, {100, 100 + 100}, nullptr));
    AIWM::Application::run();
    AIWM::Application::stop();
};
