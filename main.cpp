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

    app::open_window(new Image({0, 0}, {1000, 1000}));
    app::open_window(new ToolButton({0, 1100}, {64, 64}, "Misc/Images/PencilIcon.png", new Pencil()));
    app::open_window(new ToolButton({64, 1100}, {64, 64}, "Misc/Images/EraserIcon.png", new Eraser()));

    void* box_blur_handle = dlopen("Editor/editor_plugin_api/plugins/BoxBlur/BoxBlur.so", RTLD_NOW);

    PluginAPI::Plugin* (*get_plugin)() = 
                reinterpret_cast<PluginAPI::Plugin* (*)()>(dlsym(box_blur_handle, "get_plugin"));


    app::open_window(new ToolButton({128, 1100}, {64, 64}, 
                     "Editor/editor_plugin_api/plugins/BoxBlur/icon.png",
                     new PluginWrapper(get_plugin(), box_blur_handle)));

    app::open_window(new ThicknessSlider({256, 1100}, {32, 32}, {1100, 1200}, nullptr));

    app::run();
    app::stop();
};
