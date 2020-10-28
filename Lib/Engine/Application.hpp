#include "SFMLGraphics.hpp"
#include "SFMLEvents.hpp"
#include "../Window/Window.hpp"

using EventSystem   = SFMLEventSystem;
using GraphicSystem = SFMLGraphicSystem;

class Application {
private:
    Application() = default;
    static ContainerWindow* root_window;

public:
    static void start();
    static void stop();
    static void run();
};
