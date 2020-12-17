#include "ToolManager.hpp"
#include "PluginApi.hpp"
#include <algorithm>
#include <cmath>

Tool::~Tool() {}

//================================================================================

PluginWrapper::PluginWrapper(PluginAPI::Plugin* plugin, void* handle)
    :handle(handle), plugin(plugin)
{
    plugin->init();
}

void PluginWrapper::init(Image& canvas, const Vector2d& pos)
{
    PluginAPI::Position plug_pos = {pos.x, pos.y};
    size_t widht = canvas.get_size().x;
    size_t height = canvas.get_size().y;
    
    PluginAPI::Canvas plug_canvas = {canvas.get_data(), widht, height};
    for (auto& p: plugin->properties) {
        if (p.first == PluginAPI::TYPE::THICKNESS) {
            p.second.int_value = ToolManager::get_thickness();
        }
    }

    plugin->start_apply(plug_canvas, plug_pos);
}

void PluginWrapper::apply(Image& canvas, const Vector2d& pos)
{
    PluginAPI::Position plug_pos = {pos.x, pos.y};
    size_t widht = canvas.get_size().x;
    size_t height = canvas.get_size().y;
    PluginAPI::Canvas plug_canvas = {canvas.get_data(), widht, height};

    plugin->apply(plug_canvas, plug_pos);
};

void PluginWrapper::finalize(Image& canvas, const Vector2d& pos)
{
    PluginAPI::Position plug_pos = {pos.x, pos.y};
    size_t widht = canvas.get_size().x;
    size_t height = canvas.get_size().y;
    PluginAPI::Canvas plug_canvas = {canvas.get_data(), widht, height};

    plugin->stop_apply(plug_canvas, plug_pos);
}

//================================================================================

void Pencil::init(Image& canvas, const Vector2d& pos)
{
    prev_pos = {-1, -1};
}

void Pencil::finalize(Image& canvas, const Vector2d& pos)
{
}

void Pencil::apply(Image& canvas, const Vector2d& pos)
{

    auto thickness = ToolManager::get_thickness();
    auto size = canvas.get_size();

    if (-1 == prev_pos.x || -1 == prev_pos.y) {
        prev_pos = pos;
    }

	double x_start = std::min(pos.x, prev_pos.x);
    double y_start = (x_start == pos.x)?(pos.y):(prev_pos.y);
    double x_end = std::max(pos.x, prev_pos.x);
    double y_end = (x_end == prev_pos.x)?(prev_pos.y):(pos.y);

    double step = std::max(std::abs(x_end - x_start), std::abs(y_end - y_start)) + 1;

    double dx = (x_end - x_start) / step;
    double dy = (y_end - y_start) / step;

    for (int i = 0; i < step; ++i) {
        x_start += dx;
        y_start += dy;

        for (int x = x_start - thickness; x < x_start + thickness; ++x) {
            for (int y = y_start - thickness; y < y_start + thickness; ++y) {
                if (0 <= x && x < size.x && 0 <= y && y < size.y) {
                    canvas.set_color(x, y, ToolManager::get_color());
                }
            }
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
    if (is_applying) {
        is_applying = false;
        active_tool->finalize(canvas, pos);
    }
}
