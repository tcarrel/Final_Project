#version 450 core
in  vec3 tex_coords;

uniform samplerCube sky;

out vec4 Color;

void main()
{
  Color = texture(sky, tex_coords);
}

