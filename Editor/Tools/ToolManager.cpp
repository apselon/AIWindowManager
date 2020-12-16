#include "ToolManager.hpp"
#include <algorithm>

Tool::~Tool() {}

void Pencil::init(Image& canvas, const Vector2d& pos)
{
    printf("Pencil INIT at (%ld, %ld)\n", pos.x, pos.y);
    prev_pos = {-1, -1};
}

void Pencil::finalize(Image& canvas, const Vector2d& pos)
{
    printf("Pencil FINALIZE at (%ld, %ld)\n", pos.x, pos.y);
}

void Pencil::apply(Image& canvas, const Vector2d& pos)
{
    printf("Pencil Apply at (%ld, %ld)\n", pos.x, pos.y);

    auto x_start = std::max(pos.x - thickness, 1L);
    auto x_end   = std::min(pos.x + thickness, canvas.get_size().x - 1);

    auto y_start = std::max(pos.y - thickness, 1L);
    auto y_end   = std::min(pos.y + thickness, canvas.get_size().y - 1);

    if (prev_pos.x != -1 && prev_pos.y != -1) {
        x_start = std::min(pos.x, prev_pos.x) - thickness;
        x_end   = std::max(pos.x, pos.x) + thickness;;

        y_start = std::min(pos.y, prev_pos.y) - thickness;
        y_end   = std::max(pos.y, pos.y) + thickness;;
    }

    for (auto x = x_start; x < x_end; ++x) {
        for (auto y = y_start; y < y_end; ++y) {
            canvas.set_color(x, y, color);
        }
    }

    prev_pos = pos;
}

void Pencil::set_color(const Color& new_color)
{
    color = new_color;
}

Color Pencil::get_color()
{
    return color;
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
    if (active_tool != nullptr) {
        is_applying = true;
        active_tool->init(canvas, pos);
    }
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
