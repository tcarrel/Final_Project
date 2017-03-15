//Very basic fragment shader for use early in development.
#version 450 core

in  vec4  Color;
out vec4  frag_color;

void main()
{
  frag_color = Color;
}

