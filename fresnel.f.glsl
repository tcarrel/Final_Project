#version 450 core

in vec3 Normal;
in vec3 Position;

out vec4 color;

uniform vec3 cam_pos;
uniform samplerCube sky;

//   It is possible to have materials where different colors reflect/refract
// different amounts.  A future improvement may be to use reflection and
// refraction maps from these values.
uniform float refractive_index = 1.52;

void main()
{
  vec3 I = normalize( Position - cam_pos );
  vec3 L = reflect( I, normalize(Normal) );
  vec3 R = refract( I, normalize(Normal), 1.0 / refractive_index );

  vec4 reflect_color = texture( sky, L );
  vec4 refract_color = texture( sky, R );

  //Compute fresnel reflectivity
  float F =
    pow(1.0 - clamp( dot( I , normalize( Normal ) ), 0.0, 1.0 ), 4.0);

  vec4 fresnel = vec4( F, F, F, F );

  color = vec4( vec3( mix( refract_color, reflect_color, fresnel ) ), 1.0 );
}
