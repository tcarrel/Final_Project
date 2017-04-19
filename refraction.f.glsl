#version 450 core

in vec3 Normal;
in vec3 Position;

out vec3 color;

uniform vec3 cam_pos;
uniform samplerCube sky;

uniform float refractive_index = 1.52;

void main()
{
  vec3 I = normalize( Position - cam_pos );
  vec3 R = refract( I, normalize(Normal), 1.0 / refractive_index );
  color  = texture( sky, R );
}
