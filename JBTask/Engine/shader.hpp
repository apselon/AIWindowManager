#pragma once

#include <cstdio>
#include <cassert>
#include <sys/stat.h>

GLuint load_shader(const char* vertex_fn, const char* fragment_fn) {
  FILE* vertex_f = fopen(vertex_fn, "r");
  assert(vertex_f != 0);
  FILE* fragment_f = fopen(fragment_fn, "r");
  assert(fragment_f != 0);

  struct stat st = {};
  fstat(fileno(vertex_f), &st);
  size_t vertex_len = (size_t)st.st_size;
  fstat(fileno(fragment_f), &st);
  size_t fragment_len = (size_t)st.st_size;

  char* vertex_buff = new char[vertex_len + fragment_len + 4]();
  char* fragment_buff = vertex_buff + vertex_len + 2;

  fread(vertex_buff, sizeof(char), vertex_len, vertex_f);
  fread(fragment_buff, sizeof(char), fragment_len, fragment_f);

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_buff, NULL);
  glCompileShader(vs);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_buff, NULL);
  glCompileShader(fs);

  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vs);
  glAttachShader(shader_program, fs);
  glLinkProgram(shader_program);

  delete[] vertex_buff;
  vertex_buff = nullptr;
  fclose(vertex_f);
  fclose(fragment_f);

  return shader_program;
};
