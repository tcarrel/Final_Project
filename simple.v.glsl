//Very basic vertex shader for early development.
#version 450 core

layout (location = 0) in vec3 vert_position;

//Model-View matrix.
uniform vec4 mv;

//out vec4 color;

void main()
{

// Cast to vec4 and add w-coordinate.
  gl_Position = vec4(vert_position, 1.0);

}

