#include "Engine/GLGraphics.hpp"
#include "Shape/Triangle.hpp"

int main() {
  GLGraphicSystem::start();  
  GLGraphicSystem::create_window({1024, 768});
  GLGraphicSystem::attach_context();

  Triangle t {{10, 10}, 10, "Shape/vertex.glsl", "Shape/fragment.glsl"};

  XEvent ev = {};
  while (true) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    t.move_by({100, 1});
    t.draw();
    GLGraphicSystem::swap_buffers();

    GLGraphicSystem::next_event(ev);
    switch(ev.type) {
      case ButtonPress:
        if (ev.xbutton.button == 1) {
          printf("!\n");
        }
        break;

      default:
        continue;
    }
  }
}
