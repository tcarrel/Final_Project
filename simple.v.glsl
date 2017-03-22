//Very basic vertex shader for early development.
#version 450 core

layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec4 vert_color;

//Model-View matrix.
uniform mat4 vp = mat4(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0 );

uniform float sf = 1.0;


out vec4 Color;

const float sqt = sqrt(3.0)/2.0;

void main()
{
  mat4 scale =
    mat4(
        sf, 0.0, 0.0, 0.0,
        0.0, sf, 0.0, 0.0,
        0.0, 0.0, sf, 0.0,
        0.0, 0.0, 0.0, 1.0 );
  /*
     mat4 rot =
     mat4(
     0.0, 0.0, 1.0, 0.0,
     1.0, 0.0, 0.0, 0.0,
     0.0, 1.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 1.0
     );
   */
// Color = normalize(rot * vert_color);

  Color = vert_color;
// Cast to vec4 and add w-coordinate.
  gl_Position = vp * scale * vec4( vert_position, 1.0 );
}

