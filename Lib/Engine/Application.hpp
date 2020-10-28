#include "SFMLGraphics.hpp"
#include "SFMLEvents.hpp"

using EventSystem   = SFMLEventSystem;
using GraphicSystem = SFMLGraphicSystem;

class Application {
private:
    Application() = default;

public:
    static void start();
    static void stop();
    static void run();
};
