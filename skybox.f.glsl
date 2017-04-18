#version 450 core
in  vec3 tex_coords;

out vec4 Color;

uniform samplerCube skybox;

void main()
{
  Color = texture(skybox, tex_coords);
}

