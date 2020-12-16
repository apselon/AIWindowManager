#include "Canvas.hpp"
#include "../Tools/ToolManager.hpp"

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    :r(r), g(g), b(b), a(a) {}

//================================================================================

Image::Image(const Vector2d& pos, const Vector2d& size)
    :ShapedWindow<RectShape>({pos, size}) {

        data.assign((size.x + 1) * (size.y + 1) * sizeof(Color), 0);
    }

void Image::set_color(int64_t x, int64_t y, const Color& color)
{
    int64_t i = (x + y * shape.get_size().x) * sizeof(Color);
    data[i    ] = color.r;
    data[i + 1] = color.g;
    data[i + 2] = color.b;
    data[i + 3] = color.a;

}

Color Image::get_color(int64_t x, int64_t y)
{
    int64_t i = (y * shape.get_size().x + x) * sizeof(Color);

    return *reinterpret_cast<Color*>(data.data() + i);
}

uint8_t* Image::get_data()
{
    return data.data();
}

void Image::draw()
{
    GraphicSystem::draw_bitmap(data, shape.get_pos(), shape.get_size());
}

bool Image::on_mouse_click(const Vector2d& pos) {
    ToolManager::start_applying(*this, pos);
    return true;
}

bool Image::on_mouse_move(const Vector2d& pos) {
    ToolManager::apply(*this, pos);
    return true;
}

bool Image::on_mouse_release(const Vector2d& pos) {
    ToolManager::stop_applying(*this, pos);
    return true;
}

bool Image::handle_event(const Event* event)
{
    if (event == nullptr) return true;

    Vector2d pos = {};
    auto type = event->get_type();

    if (type == EventType::Redraw) {
        draw();
        return false;
    }

    switch (type) {

        case (EventType::MouseClick):
            pos = dynamic_cast<const MouseEvent*>(event)->get_pos();
            if (shape.contains(pos)) {
                on_mouse_click(pos);
                delete event;
                return true;
            }

        case (EventType::MouseMove):
            pos = dynamic_cast<const MouseEvent*>(event)->get_pos();
            if (shape.contains(pos)) {
                on_mouse_move(pos);
                delete event;
                return true;
            }

        case (EventType::MouseRelease):
            pos = dynamic_cast<const MouseEvent*>(event)->get_pos();
            if (shape.contains(pos)) {
                on_mouse_release(pos);
                delete event;
                return true;
            }

        default:
            return false;
    }

    return false;
}
