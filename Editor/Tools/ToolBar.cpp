#include "ToolBar.hpp"

ToolButton::ToolButton(const Vector2d& pos, const Vector2d& size, 
                       const char* icon, Tool* tool)
    :AbstractRectButton(pos, size, icon), tool(tool) {}

bool ToolButton::on_mouse_click(const Vector2d& pos)
{
    ToolManager::set_active(tool);
    return true;
}

bool ToolButton::on_mouse_move(const Vector2d& pos) {return false;}
bool ToolButton::on_mouse_release(const Vector2d& pos) {return false;}

//================================================================================

ThicknessSlider::ThicknessSlider(const Vector2d& pos, const Vector2d& size,
                                 const Vector2d& limits, const char* icon = nullptr)
    :Slider(pos, size, limits, nullptr, icon) {}

void ThicknessSlider::drag_to(const Vector2d& click)
{
    auto pos = shape.get_pos();

    auto new_pos = pos + (dir * ((click - pos /*- drag_rel_pos*/) ^ dir));

    switch (orientation){
        case Orientation::VERTICAL:
            if (new_pos.y <= limits.x) new_pos.y = limits.x;
            if (new_pos.y >= limits.y) new_pos.y = limits.y;
            break;
            
        default:
            break;
    }

    shape.set_pos(new_pos);
    ToolManager::set_thickness(static_cast<double>(new_pos.y - limits.x) / 100.0 * 20);
}
