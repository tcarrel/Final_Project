//Very basic vertex shader for early development.
#version 450 core

layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec4 vert_color;

//Model-View matrix.
uniform mat4 vp = 
  mat4( 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0 );

const mat4 scale =
  mat4( 0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.0, 0.0, 0.0, 1.0 );

out vec4 Color;

void main()
{
  Color = vert_color;

// Cast to vec4 and add w-coordinate.
  gl_Position = vp * scale * vec4(vert_position, 1.0);
}

