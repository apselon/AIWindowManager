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
