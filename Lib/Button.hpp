#include "Window.hpp"

class AbstractButton: public AbstractWindow {
protected:
    virtual void callback(void) = 0;
};

