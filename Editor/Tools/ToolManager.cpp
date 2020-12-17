#include "ToolManager.hpp"
#include <algorithm>

Tool::~Tool() {}

//Pencil::Pencil(const Color& color, int64_t thickness)

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

    auto thickness = ToolManager::get_thickness();

    auto x_start = std::max(pos.x - thickness, 1L);
    auto x_end   = std::min(pos.x + thickness, canvas.get_size().x - 1);

    auto y_start = std::max(pos.y - thickness, 1L);
    auto y_end   = std::min(pos.y + thickness, canvas.get_size().y - 1);

    /*
    if (prev_pos.x != -1 && prev_pos.y != -1) {
        x_start = std::min(pos.x, prev_pos.x) - thickness;
        x_end   = std::max(pos.x, pos.x) + thickness;;

        y_start = std::min(pos.y, prev_pos.y) - thickness;
        y_end   = std::max(pos.y, pos.y) + thickness;;
    }
    */

    auto color = ToolManager::get_color();

    for (auto x = x_start; x < x_end; ++x) {
        for (auto y = y_start; y < y_end; ++y) {
            canvas.set_color(x, y, color);
        }
    }

    prev_pos = pos;
}

//================================================================================

void Eraser::init(Image& canvas, const Vector2d& pos)
{
    saved_color = ToolManager::get_color();
    ToolManager::set_color({255, 255, 255, 255});
}

void Eraser::finalize(Image& canvas, const Vector2d& pos)
{
    ToolManager::set_color(saved_color);
}

//================================================================================

list<Tool*> ToolManager::tools = list<Tool*>();
Tool* ToolManager::active_tool = nullptr;
bool ToolManager::is_applying = false;
Color ToolManager::color = {0, 0, 0, 255};
int64_t ToolManager::thickness = 3;

void ToolManager::set_active(Tool* tool)
{
    active_tool = tool;
}

Tool* ToolManager::get_active()
{
    return active_tool;
}

void ToolManager::set_color(const Color& new_color)
{
    color = new_color;
}

Color ToolManager::get_color()
{
    return color;
}

void ToolManager::set_thickness(int64_t new_thickness)
{
    thickness = new_thickness;
}

int64_t ToolManager::get_thickness()
{
    return thickness;
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
