
#version 450 core

layout  (location  =  0)  out  vec3  g_position;
layout  (location  =  1)  out  vec3  g_normal;
layout  (location  =  2)  out  vec4  g_albedo_spec;

in  vec2  Tex_coord;
in  vec3  Frag_pos;
in  vec3  Normal;

uniform  sampler2D  diffuse_texture1;
uniform  sampler2D  specular_texture1;

void main()
{
  // Store the fragment position vector.
  g_position  =  Frag_pos;
  // Store the per-fragment normals.
  g_normal  =  normalize( Normal );
  // Store the per-fragment color.
  g_albedo_spec.rgb  =  texture( diffuse_texture1, Tex_coord ).rgb;
  // Store the specular intensity.
  g_albedo_spec.a    =  texture( specular_texture1, Tex_coord ).r;
}
