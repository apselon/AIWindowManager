#pragma once

#include "../../Lib/GUIElems/Button.hpp"
#include "../../Lib/GUIElems/Scroll.hpp"
#include "ToolManager.hpp"

class ToolButton: public AbstractRectButton {
protected:
    Tool* tool = nullptr;

    bool on_mouse_move(const Vector2d& pos) override;
    bool on_mouse_click(const Vector2d& pos) override;
    bool on_mouse_release(const Vector2d& pos) override;

public:
    ToolButton(const Vector2d& pos, const Vector2d& size, 
               const char* icon = nullptr, Tool* tool = nullptr);

    void draw() override;
};

//================================================================================

class ThicknessSlider: public Slider {
protected:

public:
    ThicknessSlider(const Vector2d& pos, const Vector2d& size, 
                    const Vector2d& limits, const char* icon);

    void drag_to(const Vector2d& pos) override;
    void draw() override;
};
