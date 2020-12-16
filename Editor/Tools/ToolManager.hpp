#pragma once

#include "../../Lib/Aux/Auxiliary.hpp"
#include "../Canvas/Canvas.hpp"

class Tool {
public:
    virtual void init(Image& canvas, const Vector2d& pos);
    virtual void apply(Image& canvas, const Vector2d& pos);
    virtual void finalize(Image& canvas, const Vector2d& pos);

    virtual ~Tool();
};

//================================================================================

class Pencil: public Tool {
protected:
    Color color = {};
    int64_t thickness = 1;
    Vector2d prev_pos = {-1, -1};

public:
    Pencil() = default;

    void init(Image& canvas, const Vector2d& pos) override;
    void apply(Image& canvas, const Vector2d& pos) override;
    void finalize(Image& canvas, const Vector2d& pos) override;

    virtual void set_color(const Color& color);
    virtual Color get_color();
};

//================================================================================

class ToolManager {
protected:
    static list<Tool*> tools;
    static Tool* active_tool;
    static bool is_applying;

    ToolManager() = default;

public:
    static void set_active(Tool* tool);
    static Tool* get_active(); 
    static void add_tool(Tool* new_tool);
    static bool is_active();

    static void start_applying(Image& canvas, const Vector2d& pos);
    static void apply(Image& canvas, const Vector2d& pos);
    static void stop_applying(Image& canvas, const Vector2d& pos);
};
