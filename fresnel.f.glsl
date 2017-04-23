#version 450 core

in vec3 Normal;
in vec3 Position;

out vec4 color;

uniform vec3 cam_pos;
uniform samplerCube sky;

//   It is possible to have materials where different colors reflect/refract
// (wavelengths) have different amounts.  A future improvement may be to use
// vec3 for these values, or even better, use per-color refraction maps from
// these values.
uniform float refraction_ratio = 1.0 / 1.52;
//  Reflection coefficient
uniform float r_0 = (1.0 - 1.52) / (1.52 + 1.0);

void main()
{
//Get color due to reflection.
  vec3 N = normalize( Normal );
  vec3 I = normalize( Position - cam_pos );
  vec3 L = reflect( I, N );

//Calculate R(theta)
  float r_theta = r_0 + ( 1 - r_0 ) * pow( clamp(dot( N, I ), 0.0, 1.0), 5 );
  vec4  fresnel = vec4( r_theta, r_theta, r_theta, 1 );

  vec3 R = refract( I, N, refraction_ratio );

  vec4 reflect_color = texture( sky, L );
  vec4 refract_color = texture( sky, R );

  color = vec4( vec3( mix( refract_color, reflect_color, fresnel ) ), 1.0 );
}
