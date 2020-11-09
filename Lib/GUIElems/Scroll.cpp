#include "Scroll.hpp"
#include "../Engine/SFMLGraphics.hpp"

Slider::Slider(const Vector2d& pos, const Vector2d& size, const Vector2d& limits,
               const Orientation orientation)
    :DraggableRectWindow(pos, size), limits(limits), orientation(orientation)
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
}
