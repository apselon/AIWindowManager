#pragma once
#include "../Window/Window.hpp"

class Scrollable {
public:
    virtual bool handle_scroll(const Vector2<double>& quant) = 0;
    virtual ~Scrollable() = default;
};

enum class Orientation {
    VERTICAL,
    HORIZONTAL,
    DIAGONAL,
    OR_LENGTH
};

class Slider: public RectWindow,  public Draggable {
protected:
    Vector2d dir = {};
    Vector2d limits = {};
    Orientation orientation = Orientation::VERTICAL;
    Scrollable* parent = nullptr;

public:
    Slider(const Vector2d& pos, const Vector2d& size, const Vector2d& limits,
           Scrollable* parent = nullptr,
           const Orientation orientation = Orientation::VERTICAL);

    void drag_to(const Vector2d& click) override;
    bool handle_event(const Event* event) override;
};

//================================================================================

class ScrollView: public RectWindow, public Scrollable {
protected:
    Vector2d offset = {};

public:

    ScrollView(const Vector2d& pos, const Vector2d& size);
    bool handle_scroll(const Vector2<double>& quant) override;
    bool handle_event(const Event* event) override;
    void draw() override;
};

/*
class TextView: public AbstractRenderWindow, public InterfaceScrollable {
private:
    Vector2d pos = {};
    Vector2d size = {};
    const char* text = nullptr;
    double offset = 0;
    Slider* slider = nullptr;


protected:
    bool contains(const Vector2d& point) override;
    bool on_mouse_click(const Vector2d& click) override;
    bool on_mouse_move(const Vector2d& click) override;
    bool on_mouse_release(const Vector2d& click) override;
    void on_redraw() override;

    bool handle_scroll(double quant) override;

public:
    TextView(const Vector2d& pos, const Vector2d& size, const char* text = nullptr);
};
*/
