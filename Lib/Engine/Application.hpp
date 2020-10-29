#pragma once

#include "SFMLGraphics.hpp"
#include "SFMLEvents.hpp"
#include "../Window/Window.hpp"

namespace AIWM {

class Application {
private:
    Application() = default;
    static AbstractWindow* root_window;

public:
    static void start();
    static void stop();
    static void run();
};

} //AIWM
