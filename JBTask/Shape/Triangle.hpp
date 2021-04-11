#pragma once
#include "../Aux/Auxiliary.hpp"
#include "../Engine/GLGraphics.hpp"

class Triangle {
protected:
  Vector2d pos = {};
  size_t len = 0;
  GLuint shader_program  = 0;
  GLuint vertex_buff_id  = 0;
  GLuint vertex_array_id = 0;
  int offset_location = 0;

public:
  Triangle() = delete;
  Triangle(const Vector2d& pos, size_t len,
           const char* v_shader, const char* f_shader);
  bool draw();
  void set_pos(const Vector2d& new_pos);
  void move_by(const Vector2d& delta);
};
