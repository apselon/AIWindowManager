#include "../Window/Window.hpp"

class AbstractScrollContainer;
class AbstractScrollBar;
class AbstractScrollSlider;
class AbstractScrollPadding;

class AbstractScrollPadding: public AbstractRenderWindow {
private:
    AbstractScrollBar*    parent_bar = nullptr;
    AbstractScrollSlider* slider     = nullptr;

protected:
    AbstractScrollPadding(AbstractScrollBar* parent_bar);

public:
    bool on_mouse_click(const Vector2d& click) override;
};

//================================================================================

class AbstractScrollSlider: public AbstractRenderWindow {
    friend AbstractScrollPadding;

protected:
    bool on_mouse_click(const Vector2d&) override;
    bool on_mouse_release(const Vector2d&) override;
    bool on_mouse_move(const Vector2d& click) override;

public:
    virtual bool positioned_before(const Vector2d& click) = 0;
    virtual bool positioned_after (const Vector2d& click) = 0;
};

//================================================================================

class AbstractScrollBar: public AbstractRenderWindow {
    friend AbstractScrollPadding;
    friend AbstractScrollSlider;
    friend AbstractScrollContainer;

private:
    AbstractScrollSlider*  slider  = nullptr;
    AbstractScrollPadding* padding = nullptr;

protected:
    AbstractScrollSlider* get_slider();
    virtual bool handle_scroll(long scrol_quant);

    AbstractScrollBar(AbstractScrollSlider* slider, AbstractScrollPadding* padding);

public:
    virtual bool on_scroll() = 0;
};

//================================================================================

class BasicSlider: public AbstractScrollSlider, public IRect {

protected:
    void on_redraw() override;
    bool contains(const Vector2d& dot) override;

    BasicSlider(const Vector2d& pos, const Vector2sz& size);

public:
    bool positioned_before(const Vector2d& click) override;
    bool positioned_after (const Vector2d& click) override;
};

//================================================================================

class BasicPadding: public AbstractScrollPadding, public IRect {

protected:
    void on_redraw() override; 
    bool on_mouse_move(const Vector2d& click) override;
    bool contains(const Vector2d& dot) override;

    BasicPadding(const Vector2d& pos, const Vector2sz& size, AbstractScrollBar* bar);
};

class BasicScrollBar: public AbstractScrollBar, public IRect {

protected:
    void on_redraw() override;
    bool on_mouse_move(const Vector2d& click) override;
    bool on_mouse_click(const Vector2d& click) override;
    bool on_mouse_release(const Vector2d& click) override;
    bool contains(const Vector2d& dot) override;

    BasicScrollBar(const Vector2d& pos, const Vector2sz& size, 
                   AbstractScrollSlider* slider, 
                   AbstractScrollPadding* padding);

public:
    BasicScrollBar(const Vector2d& pos, const Vector2sz& size);
    
};
