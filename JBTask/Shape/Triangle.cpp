#include "Triangle.hpp"
#include "../Engine/shader.hpp"

Triangle::Triangle(const Vector2d& pos, size_t len, 
                   const char* v_shader, const char* f_shader)
  :pos(pos), len(len) {
  
    shader_program = load_shader(v_shader, f_shader);

    glGenBuffers(1, &vertex_buff_id);
    glGenVertexArrays(1, &vertex_array_id);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buff_id);
    glBindVertexArray(vertex_array_id);

    float points[] = {
       0.0,  0.25, 0.0,
       0.25, -0.25, 0.0,
      -0.25, -0.25, 0.0
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    offset_location = glGetUniformLocation(shader_program, "offset");
  }

bool Triangle::draw() {
  glUseProgram(shader_program);
  glUniform2f(offset_location, 0.5, 0.5);
  //glBindBuffer(GL_ARRAY_BUFFER, vertex_buff_id);
  glBindVertexArray(vertex_array_id);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  return true;
};


void Triangle::set_pos(const Vector2d& new_pos)
{
      pos = new_pos;
}

void Triangle::move_by(const Vector2d& delta)
{
}


