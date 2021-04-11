#pragma once
#include "../Aux/Auxiliary.hpp"

#include <cstdio>
#include <GL/glew.h>
#include <GL/glx.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>


class GLGraphicSystem {
private:
  GLGraphicSystem() = default;
  static Display* display;
  static int screen_id;
  static Window window;
  static GLXFBConfig fbconfig;
  static GLXContext glcontext;


public:
  static void start();
  static void create_window(const Vector2d& res);
  static void attach_context(); 
  static void swap_buffers();
  static void next_event(XEvent& ev);
  /* static void stop(); */


private:
  static Window root_window();
  static void choose_fbconfig();
  static void create_context();
};
