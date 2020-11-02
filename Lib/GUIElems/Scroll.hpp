#include "../Window/Window.hpp"

class AbstractScrollContainer;
class AbstractScrollBar;
class AbstractScrollSlider;
class AbstractScrollPadding;

class AbstractScrollPadding: public AbstractRenderWindow {
private:
    AbstractScrollBar* parent_bar = nullptr;

protected:
    AbstractScrollPadding(AbstractScrollBar* parent_bar);

public:
    bool on_mouse_click(const Vector2d& click) override;
};

//================================================================================

class AbstractScrollSlider: public AbstractRenderWindow {
    friend AbstractScrollPadding;

public:
    virtual bool clicked_higher(const Vector2d& click) = 0;
    virtual bool clicked_lower (const Vector2d& click) = 0;
    AbstractScrollSlider();
};

//================================================================================

class AbstractScrollBar: public AbstractContainerWindow {
    friend AbstractScrollPadding;
    friend AbstractScrollSlider;
    friend AbstractScrollContainer;

private:
    AbstractScrollContainer* container = nullptr;
    AbstractScrollSlider* slider       = nullptr;
    AbstractScrollPadding* padding     = nullptr;

protected:
    AbstractScrollBar(AbstractScrollContainer* container, 
                      AbstractScrollSlider* slider, 
                      AbstractScrollPadding* padding);

    AbstractScrollSlider* get_slider();
    AbstractScrollPadding* get_padding();

public:
    bool handle_scroll(long scrol_quant);
};

//================================================================================

class AbstractScrollContainer: public AbstractContainerWindow {
private:
    AbstractScrollBar* scroll_bar = nullptr;

public:
    AbstractScrollContainer(AbstractScrollBar* scroll_bar);
    AbstractScrollBar* get_scroll_bar();

    virtual bool on_scroll(long scroll_quant) = 0;
};

class BasicRectSlider: public AbstractScrollSlider {
private:
    Vector2d pos  = Vector2d();
    Vector2d size = Vector2d();
public:
    bool clicked_lower (const Vector2d& click) override; 
    bool clicked_higher(const Vector2d& click) override; 
};
