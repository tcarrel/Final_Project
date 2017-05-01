#version 450 core

in vec3 Normal;
in vec3 Position;

out vec4 color;

uniform vec3 cam_pos;
uniform samplerCube sky;




void main()
{
  vec3 I = normalize( Position - cam_pos );
  vec3 R = reflect( I, normalize(Normal) );
  color  = texture( sky, R );
}
