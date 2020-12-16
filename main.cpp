#include "Lib/Engine/Application.hpp"
#include "Lib/GUIElems/Scroll.hpp"
#include "Lib/GUIElems/Button.hpp"
#include "Lib/GUIElems/Label.hpp"
#include "Editor/Canvas/Canvas.hpp"
#include "Editor/Tools/ToolManager.hpp"

using app = AIWM::Application;

int main(void){
    app::start();

    app::open_window(new Image({0, 0}, {500, 500}));
    auto pencil = new Pencil();
    pencil->set_color({0, 0, 0, 255});
    ToolManager::set_active(pencil);

    app::run();
    app::stop();
};
