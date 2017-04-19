#version 450 core

in vec3 Normal;
in vec3 Position;

out vec3 color;

uniform vec3 cam_pos;
uniform samplerCube sky;

//   It is possible to have materials where different colors reflect/refract
// different amounts.  A future improvement may be to use reflection and
// refraction maps from these values.
uniform vec4 refractive_index = vec4( 1.52, 1.52, 1.52, 1.52 );
uniform vec4 reflect_amt      = vec4(  0.5,  0.5,  0.5,  0.5 );

void main()
{
  vec3 I = normalize( Position - cam_pos );
  vec3 L = reflect( I, normalize(Normal) );
  vec3 R = refract( I, normalize(Normal), 1.0 / refractive_index );

  vec4 reflect_color = texture( sky, L );
  vec4 refract_color = texture( sky, R );

  color  = mix( refract_color, reflect_color, reflect_amt );
}
