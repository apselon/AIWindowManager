#include "../Window/Window.hpp"

class InterfaceScrollable {

public:
    virtual bool handle_scroll(double quant) = 0;
};


enum class Orientation {
    VERTICAL,
    HORIZONTAL,
    DIAGONAL,
    OR_LENGTH
};

class Slider: public DraggableRectWindow {
protected:
    Vector2d dir = {};
    Vector2d limits = {};
    Orientation orientation = Orientation::VERTICAL;
    InterfaceScrollable* parent = nullptr;

public:
    Slider(const Vector2d& pos, const Vector2d& size, const Vector2d& limits,
           InterfaceScrollable* parent = nullptr,
           const Orientation orientation = Orientation::VERTICAL);

    void drag_to(const Vector2d& click) override;
};

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
