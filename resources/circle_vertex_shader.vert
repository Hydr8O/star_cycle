#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 vert_locCoords;

void main() {
  vert_locCoords = aPos;
  gl_Position = proj * view * model * vec4(aPos, 1.0);
}