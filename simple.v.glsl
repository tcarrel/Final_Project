//Very basic vertex shader for early development.
#version 450 core

layout (location = 0) in vec4 position;

out vec4 color;

void main()
{
  gl_position = position;
}

