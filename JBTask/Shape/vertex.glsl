#version 400

in vec3 position
uniform vec2 offset

void main() {
  gl_Position = vec4(position, 1.0) + vec4(offset, 0, 0);
}
