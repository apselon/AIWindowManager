#include "../../Lib/Aux/Auxiliary.hpp"
#include "ToolManager.hpp"

void Pencil::init(Image& canvas, const Vector2d& pos)
{
    printf("Pencil INIT\n");
}

void Pencil::finalize(Image& canvas, const Vector2d& pos)
{
    printf("Pencil FINALIZE\n");
}

void Pencil::apply(Image& canvas, const Vector2d& pos)
{
    for (auto x = pos.x - thickness; x < pos.x + thickness; ++x) {
        for (auto y = pos.y - thickness; y < pos.y + thickness; ++y) {
            canvas.set_color(x, y, color);
        }
    }
}

//================================================================================

list<Tool*> ToolManager::tools = list<Tool*>();
Tool* ToolManager::active_tool = nullptr;
bool ToolManager::is_applying = false;

void ToolManager::set_active(Tool* tool)
{
    active_tool = tool;
}

Tool* ToolManager::get_active()
{
    return active_tool;
}

void ToolManager::add_tool(Tool* new_tool)
{
    tools.push_back(new_tool);
}

bool ToolManager::is_active()
{
    return is_applying;
}

void ToolManager::start_applying(Image& canvas, const Vector2d& pos)
{
    is_applying = true;
    active_tool->init(canvas, pos);
}

void ToolManager::apply(Image& canvas, const Vector2d& pos)
{
    if (is_applying) active_tool->apply(canvas, pos);
}

void ToolManager::stop_applying(Image& canvas, const Vector2d& pos)
{
    is_applying = false;
    active_tool->finalize(canvas, pos);
}
