//Very basic vertex shader for early development.
#version 450 core

layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec4 vert_color;
layout (location = 2) in vec3 vert_normal;

//Model-View matrix.
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 Color;

void main()
{
// Cast to vec4 and add w-coordinate.
  gl_Position = projection * view * model * vec4( vert_position, 1.0 );
  Color = vert_color;
}

