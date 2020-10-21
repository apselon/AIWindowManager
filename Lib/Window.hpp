#include <ctime>
#include <cstdint>

class AbstractWindow {
private:

protected:
    virtual void handle_mouse_move(double x, double y)  = 0;
    virtual void handle_mouse_click(double x, double y)  = 0;
    virtual void handle_timer(time_t timer)  = 0;
    //virtual void handle_resize(size_t new_w, size_t new_h)  = 0;
    //TODO virtual void handle_key_pressed(???) ;

public:
    virtual void draw()  = 0;
};

