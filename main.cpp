#include <dlfcn.h>
#include "Lib/Engine/Application.hpp"
#include "Lib/GUIElems/Scroll.hpp"
#include "Lib/GUIElems/HWB.hpp"
#include "Lib/GUIElems/Label.hpp"
#include "Editor/Canvas/Canvas.hpp"
#include "Editor/Tools/ToolManager.hpp"
#include "Editor/Tools/ToolBar.hpp"

using app = AIWM::Application;

int main(void){
    app::start();

    auto pencil = new Pencil();
    auto eraser = new Eraser();

    void* handle = dlopen("Editor/editor_plugin_api/plugins/BoxBlur/BoxBlur.so", RTLD_NOW);

    PluginAPI::Plugin* (*get_plugin)() = 
                reinterpret_cast<PluginAPI::Plugin* (*)()>(dlsym(handle, "get_plugin"));

    auto box_blur = new PluginWrapper(get_plugin(), handle);

    app::open_window(new Image({0, 0}, {1000, 500}));
    app::open_window(new ToolButton({0, 600}, {64, 64}, "Misc/Images/PencilIcon.png", pencil));
    app::open_window(new ToolButton({64, 600}, {64, 64}, "Misc/Images/EraserIcon.png", eraser));
    app::open_window(new ToolButton({256, 600}, {32, 32}, "Editor/editor_plugin_api/plugins/BoxBlur/icon.png", box_blur));
    app::open_window(new ThicknessSlider({128, 600}, {32, 32}, {600, 700}, nullptr));

    app::run();
    app::stop();
};
