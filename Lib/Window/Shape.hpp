#pragma once
#include "../Aux/Auxiliary.hpp"

class AbstractShape {
public:
    virtual bool draw() = 0;
    virtual bool contains(const Vector2d& point) = 0;
    virtual ~AbstractShape() = default;
};

//================================================================================

class RectShape: public AbstractShape {
protected:
    Vector2d pos = {}; 
    Vector2d size = {};

public:
    RectShape() = default;
    RectShape(const Vector2d& pos, const Vector2d& size);
    bool draw() override;
    bool contains(const Vector2d& point) override;
    Vector2d get_pos() const;
    void set_pos(const Vector2d& new_pos);
    void move_by(const Vector2d& delta);
};
