#version 330 core

out vec4 FragColor;

in vec3 vert_locCoords;

void main() {
  if(length(vert_locCoords.xy) > 1.){ // Make round.
    discard;
  }

  FragColor = vec4(0.8f, 0.7f, 0.7f, 1.0f);
}


