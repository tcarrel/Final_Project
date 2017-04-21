#version 450 core

in vec3 Normal;
in vec3 Position;

out vec4 color;

uniform vec3 cam_pos;
uniform samplerCube sky;

uniform float refractive_index = 1.52;

void main()
{
  float enter = 1.0 / refractive_index;
  vec3 I = normalize( Position - cam_pos );
  vec3 R = refract( I, normalize(Normal), enter );
  color  = texture( sky, R );
}
