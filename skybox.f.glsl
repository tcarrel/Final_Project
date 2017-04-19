#version 450 core
in  vec3 tex_coords;
flat in  uint wf;

uniform samplerCube sky;

out vec4 Color;

void main()
{
  if( wf == 1 )
  {
    Color = vec4( 1, 1, 1, 1 );
  }
  else
  {
    Color = texture(sky, tex_coords);
  }
}

