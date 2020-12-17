#pragma once

#include "../Window/Window.hpp"
#include "../Aux/Auxiliary.hpp"
#include "../Engine/SFMLGraphics.hpp"

class AbstractRectButton: public RectWindow, public MouseReceptive {
public:
    AbstractRectButton();
    AbstractRectButton(const Vector2d& pos, const Vector2d& size,
                       const char* image = nullptr);
    bool handle_event(const Event* event) override;
};

//================================================================================

