#include "Scroll.hpp"
#include "../Engine/SFMLGraphics.hpp"

Slider::Slider(const Vector2d& pos, const Vector2d& size, const Vector2d& limits,
               Scrollable* parent,
               const Orientation orientation)
    :RectWindow({pos, size}), limits(limits), 
    orientation(orientation), parent(parent)
{
    dir = {0, 1};
}

bool Slider::handle_event(const Event* event) {
    if (event == nullptr) return true;

    Vector2d pos = {};
    auto type = event->get_type();

    if (type == EventType::Redraw) {
        draw();
        return false;
    }

    switch (type) {
        case EventType::MouseMove:
            pos = dynamic_cast<const MouseEvent*>(event)->get_pos();
            if (shape.contains(pos) || is_pressed) {
                on_mouse_move(pos);
                delete event;
                return true;
            }
            break;

        case EventType::MouseClick:
            pos = dynamic_cast<const MouseEvent*>(event)->get_pos();
            if (shape.contains(pos)) {
                on_mouse_click(pos);
                delete event;
                return true;
            }
            break;

        case EventType::MouseRelease:
            pos = dynamic_cast<const MouseEvent*>(event)->get_pos();
            if (shape.contains(pos) || is_pressed) {
                on_mouse_release(pos);
                delete event;
                return true;
            }

            break;

        default:
            return false;
    }

    return false;
}

void Slider::drag_to(const Vector2d& click) {
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

    if (parent != nullptr) {
        parent->handle_scroll({0, (new_pos.y - limits.x) / 100.0});
    }
}

//================================================================================

ScrollView::ScrollView(const Vector2d& pos, const Vector2d& size)
    :RectWindow({pos, size}) {}

bool ScrollView::handle_scroll(const Vector2<double>& quant)
{
    offset = {static_cast<int64_t>(quant.x * shape.get_size().x),
              static_cast<int64_t>(quant.y * shape.get_size().y)};

    return true;
}

bool ScrollView::handle_event(const Event* event)
{
    if (event == nullptr) return true;

    Vector2d pos = {};
    auto type = event->get_type();

    if (type == EventType::Redraw) {
        draw();
        GraphicSystem::push_target(shape.get_size(), offset);
        dispatch_event(event);
        GraphicSystem::pop_target_to_display(shape.get_pos());
        return false;
    }

    return dispatch_event(event);
}

void ScrollView::draw()
{
    shape.draw();
}
