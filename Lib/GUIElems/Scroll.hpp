#include "../Window/Window.hpp"

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

public:
    Slider(const Vector2d& pos, const Vector2d& size, const Vector2d& limits,
           const Orientation orientation = Orientation::VERTICAL); 

    void drag_to(const Vector2d& click) override;
};
