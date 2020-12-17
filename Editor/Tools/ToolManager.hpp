#pragma once

#include "../../Lib/Aux/Auxiliary.hpp"
#include "../Canvas/Canvas.hpp"
#include "PluginApi.hpp"

class Tool {
public:
    virtual void init(Image& canvas, const Vector2d& pos) = 0;
    virtual void apply(Image& canvas, const Vector2d& pos) = 0;
    virtual void finalize(Image& canvas, const Vector2d& pos) = 0;

    virtual ~Tool();
};

//================================================================================

class Pencil: public Tool {
protected:
    Vector2d prev_pos = {-1, -1};

public:
    Pencil() = default;
    //Pencil(const Color& color, int64_t thickness);

    void init(Image& canvas, const Vector2d& pos) override;
    void apply(Image& canvas, const Vector2d& pos) override;
    void finalize(Image& canvas, const Vector2d& pos) override;

};

//================================================================================

class Eraser: public Pencil {
protected:
    Color saved_color = {};

public:
    Eraser() = default;

    void init(Image& canvas, const Vector2d& pos) override;
    void finalize(Image& canvas, const Vector2d& pos) override;
};

//================================================================================

class PluginWrapper: public Tool {
protected:
    PluginAPI::Plugin* plugin = nullptr;
    void* handle = nullptr;
public:
    PluginWrapper(PluginAPI::Plugin* plugin, void* handle);

    void init(Image& canvas, const Vector2d& pos) override;
    void apply(Image& canvas, const Vector2d& pos) override;
    void finalize(Image& canvas, const Vector2d& pos) override;
};


class PluginManager {
protected:
    PluginAPI::Plugin* plugin = nullptr;
    void* hadle = nullptr;

public:
    PluginManager(const char* so_file);
};

//================================================================================
class ToolManager {
protected:
    static list<Tool*> tools;
    static Tool* active_tool;
    static bool is_applying;

    static Color color ;
    static int64_t thickness ;

    ToolManager() = default;

public:
    static void set_active(Tool* tool);
    static Tool* get_active(); 
    static void add_tool(Tool* new_tool);
    static bool is_active();
    static void set_color(const Color& color);
    static Color get_color();
    static void set_thickness(int64_t new_thickness);
    static int64_t get_thickness();

    static void start_applying(Image& canvas, const Vector2d& pos);
    static void apply(Image& canvas, const Vector2d& pos);
    static void stop_applying(Image& canvas, const Vector2d& pos);
};
