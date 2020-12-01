#include "Scroll.hpp"
#include "../Engine/SFMLGraphics.hpp"

/*
//================================================================================

Slider::Slider(const Vector2d& pos, const Vector2d& size, const Vector2d& limits,
               InterfaceScrollable* parent,
               const Orientation orientation)
    :DraggableRectWindow(pos, size), limits(limits), 
    orientation(orientation), parent(parent)
{
    dir = {0, 1};
}

void Slider::drag_to(const Vector2d& click) {
    auto new_pos = pos + (dir * ((click - pos - drag_rel_pos) ^ dir));

    switch (orientation){
        case Orientation::VERTICAL:
            if (new_pos.y <= limits.x) new_pos.y = limits.x;
            if (new_pos.y >= limits.y) new_pos.y = limits.y;
            break;
            
        default:
            break;
    }

    pos = new_pos;
    if (parent != nullptr) {
        parent->handle_scroll(-(new_pos.y - limits.x) / 100);
    }
}

//================================================================================

TextView::TextView(const Vector2d& pos, const Vector2d& size, const char* text)
    :pos(pos), size(size), text(text)
{
    slider = new Slider({pos.x + size.x, pos.y}, {10, 10}, {pos.y, pos.y + size.y}, this);
    add_subwindow(slider);
}

bool TextView::contains        (const Vector2d&) {return false;}
bool TextView::on_mouse_move   (const Vector2d&) {return false;}
bool TextView::on_mouse_click  (const Vector2d&) {return false;}
bool TextView::on_mouse_release(const Vector2d&) {return false;}

void TextView::on_redraw() {
    GraphicSystem::draw_scrollable_text(std::string(text), pos, size, offset);    
}

bool TextView::handle_scroll(double quant) {
    offset = quant * pos.y;

    //if (offset >= size.y) offset = size.y;
    //if (offset <= 0) offset = 0;

    printf("[%lg]\n", offset);
    return true;
}
*/
