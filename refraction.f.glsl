#version 450 core

in vec3 Normal;
in vec3 Position;

out vec4 color;

uniform vec3 cam_pos;
uniform samplerCube sky;

//Default to the value for glass to water.
uniform float refractive_ratio = 1.0 / 1.52;

void main()
{
  vec3 I = normalize( Position - cam_pos );
  vec3 R = refract( I, normalize(Normal), refractive_ratio );
  color  = texture( sky, R );
}
