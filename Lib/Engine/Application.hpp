#pragma once

#include "SFMLGraphics.hpp"
#include "SFMLEvents.hpp"
#include "../Window/Window.hpp"

namespace AIWM {

class Application {
private:
    Application() = default;
    static list<AbstractWindow*> root_windows;

public:
    static void start();
    static void stop();
    static void run();

    static void open_window(AbstractWindow* new_window);
};

} //AIWM
