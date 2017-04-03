#version 450 core

layout (triangles, equal_spacing, cw) in;

in vec4 Color;
out vec4 C;

void main( void )
{
  gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +
                 gl_TessCoord.y * gl_in[1].gl_Position +
                 gl_TessCoord.z * gl_in[2].gl_Position );
  C = Color;
}
