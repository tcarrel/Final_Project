//Very basic vertex shader for early development.
#version 450 core

layout (location = 0) in vec3 position;

//out vec4 color;

void main()
{

// Cast to vec4 and add w-coordinate.
  gl_Position = vec4(position, 1.0);

}

