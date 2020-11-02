#include "Scroll.hpp"

AbstractScrollPadding::AbstractScrollPadding(AbstractScrollBar* parent_bar)
    :parent_bar(parent_bar){}

bool AbstractScrollPadding::on_mouse_click(const Vector2d& click) {
    auto slider = parent_bar->get_slider();

    if (slider->clicked_lower(click)) {
        parent_bar->handle_scroll(-1);    
        return true;
    }

    else if (slider->clicked_higher(click)) {
        parent_bar->handle_scroll(1);
        return true;
    }

    return false;
}

//================================================================================


//================================================================================

AbstractScrollBar::AbstractScrollBar(AbstractScrollContainer* container)
    :container(container) {};

bool AbstractScrollBar::handle_scroll(long scrol_quant){
    return container->on_scroll(scrol_quant);
}

AbstractScrollSlider* AbstractScrollBar::get_slider() {
    return slider;
}

AbstractScrollPadding* AbstractScrollBar::get_padding() {
    return padding;
}

//================================================================================

AbstractScrollContainer::AbstractScrollContainer(AbstractScrollBar* scroll_bar)
    :scroll_bar(scroll_bar)
{
    add_subwindow(scroll_bar);
}

AbstractScrollBar* AbstractScrollContainer::get_scroll_bar() {
    return scroll_bar;
}
