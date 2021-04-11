#include "GLGraphics.hpp"

Window GLGraphicSystem::window = {};
Display* GLGraphicSystem::display = nullptr;
int GLGraphicSystem::screen_id = -1;
GLXFBConfig GLGraphicSystem::fbconfig = {};
GLXContext GLGraphicSystem::glcontext = {};

void GLGraphicSystem::start() {
  //TODO Handle Error
  
  display = XOpenDisplay(nullptr);
  screen_id = DefaultScreen(display); 
}

void GLGraphicSystem::create_window(const Vector2d& res) {
  choose_fbconfig(); 
  auto* vi = glXGetVisualFromFBConfig(display, fbconfig);

  XSetWindowAttributes win_attribs = {
    .background_pixel = WhitePixel(display, screen_id),
    .border_pixel = BlackPixel(display, screen_id),
    .override_redirect = true,
    .colormap = XCreateColormap(display, root_window(), vi->visual,AllocNone)
  };

  window = XCreateWindow(display, root_window(), 0, 0, res.x, res.y, 1,
                         vi->depth, InputOutput, vi->visual,
                         CWBorderPixel | CWColormap | CWEventMask,
                         &win_attribs);

  auto event_mask = PointerMotionMask | ButtonPressMask | ButtonReleaseMask
                                      | EnterWindowMask | LeaveWindowMask;

  XSelectInput(display, window, event_mask);
  XClearWindow(display, window);
  XMapRaised(display, window);

}

void GLGraphicSystem::attach_context() {
  create_context();
  glXMakeCurrent(display, window, glcontext); 
  glewExperimental = GL_TRUE;
  glewInit();
}

void GLGraphicSystem::create_context() {
  /*
  glXCreateContextAttribsARB = reinterpret_cast<glXCreateContextAttribsARBProc>
        (glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB"));


  int context_attribs[] = {
    GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
    GLX_CONTEXT_MINOR_VERSION_ARB, 2,
    None
  };


  GLXContext ctx = glXCreateContextAttribsARB(display, fbc, NULL,
                                              true, context_attribs);
  */

  glcontext = glXCreateNewContext(display, fbconfig, GLX_RGBA_TYPE, NULL, True);
}

void GLGraphicSystem::choose_fbconfig() {

  int visual_attribs[] = {
    GLX_X_RENDERABLE,True,
    GLX_DRAWABLE_TYPE,GLX_WINDOW_BIT,
    GLX_RENDER_TYPE,GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE,GLX_TRUE_COLOR,
    GLX_RED_SIZE,8,
    GLX_GREEN_SIZE,8,
    GLX_BLUE_SIZE,8,
    GLX_ALPHA_SIZE,8,
    GLX_DEPTH_SIZE,24,
    GLX_STENCIL_SIZE,8,
    GLX_DOUBLEBUFFER,True,
    None
  };

  int fbc_list_len = 0;
  GLXFBConfig* fbc_list = glXChooseFBConfig(display, screen_id,
                                            visual_attribs, &fbc_list_len);
  /*
  int best_fbc_num = -1;
  int best_result = -1;

  for (int i = 0; i < fbc_list_len; ++i) {
    XVisualInfo* vi = glXGetVisualFromFBConfig(display, fbc_list[i]);

    if (vi) {
      int sampleBuffers;
      int samples;

      glXGetFBConfigAttrib(display, fbc_list[i], GLX_SAMPLE_BUFFERS, &sampleBuffers);
      glXGetFBConfigAttrib(display, fbc_list[i], GLX_SAMPLES, &samples);

      if (best_fbc_num < 0 || (sampleBuffers && samples > best_result) ) {
        best_fbc_num = i;
        best_result = samples;
      }

      XFree(vi);
    }
  }
  */

  fbconfig = fbc_list[0];
  XFree(fbc_list);
  fbc_list = nullptr;
};

void GLGraphicSystem::swap_buffers() {
  glXSwapBuffers(display, window);
}

Window GLGraphicSystem::root_window() {
  return RootWindow(display, screen_id);
}

void GLGraphicSystem::next_event(XEvent& ev) {
  XNextEvent(display, &ev);
}
