#include "Shape.hpp"
#include "../../Lib/Engine/SFMLGraphics.hpp"

RectShape::RectShape(const Vector2d& pos, const Vector2d& size) 
    :pos(pos), size(size) {};

bool RectShape::draw()
{
    GraphicSystem::draw_rect(pos, size);
    return true;
};

bool RectShape::contains(const Vector2d& point)
{
    return (pos.x <= point.x && point.x <= pos.x + size.x) &&
           (pos.y <= point.y && point.y <= pos.y + size.y);
}

Vector2d RectShape::get_pos() const
{
    return pos;
}

void RectShape::set_pos(const Vector2d& new_pos)
{
    pos = new_pos;
}
