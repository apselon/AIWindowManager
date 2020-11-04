#include "Scroll.hpp"
#include "../Engine/SFMLGraphics.hpp"

AbstractScrollPadding::AbstractScrollPadding(AbstractScrollBar* parent_bar)
    :parent_bar(parent_bar), slider(parent_bar->get_slider()) {}

bool AbstractScrollPadding::on_mouse_click(const Vector2d& click) {

    if (!contains(click)) return false;

    if (slider->positioned_after(click)) {
        parent_bar->handle_scroll(-1);    
        return true;
    }

    if (slider->positioned_before(click)) {
        parent_bar->handle_scroll(1);
        return true;
    }

    return false;
}

//================================================================================

AbstractScrollBar::AbstractScrollBar(AbstractScrollSlider* slider, 
                                     AbstractScrollPadding* padding)
    :slider(slider), padding(padding)
{
    add_subwindow(slider);
    add_subwindow(padding);
}

AbstractScrollSlider* AbstractScrollBar::get_slider() {
    return slider;    
}

bool AbstractScrollBar::handle_scroll(long) {
    //slider->move();
    return on_scroll();
}

//================================================================================

BasicSlider::BasicSlider(const Vector2d& pos, const Vector2sz& size)
    :IRect(pos, size) {}

bool BasicSlider::positioned_before(const Vector2d& click) {
    return (click.y <= pos.y);
}

bool BasicSlider::positioned_after(const Vector2d& click) {
    return (click.y >= pos.y + size.y);
}

void BasicSlider::on_redraw() {
    GraphicSystem::draw_rect(pos, size);
}

//================================================================================

BasicPadding::BasicPadding(const Vector2d& pos, const Vector2sz& size, AbstractScrollBar* bar)
    :AbstractScrollPadding(bar), IRect(pos, size) {}

void BasicPadding::on_redraw() {
    GraphicSystem::draw_rect(pos, size);
}

//================================================================================

BasicScrollBar::BasicScrollBar(const Vector2d& pos, const Vector2sz& size,
                               AbstractScrollSlider* slider, 
                               AbstractScrollPadding* padding)
    :AbstractScrollBar(slider, padding), IRect(pos, size) {}

BasicScrollBar::BasicScrollBar(const Vector2d& pos, const Vector2sz& size)
    :BasicScrollBar(pos, size, new BasicSlider(), new BasicPadding()) {}

