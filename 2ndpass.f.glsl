
#version 450 core

out  vec4  Frag_color;
in   vec2  Tex_coords;

uniform  sampler2D  g_position;
uniform  sampler2D  g_normal;
uniform  sampler2D  g_albedo_spec;

struct  Light{
  vec3  position;
  vec3  color;
  float linear;
  float quadratic;
}

const    int   LIGHT_QTY  =  32;
uniform  Light lights[LIGHT_QTY];
uniform  vec3  view_pos;

void main()
{
  // Load data from gbuffer.
  vec3  frag_pos  = texture( g_position, Tex_coords ).rgb;
  vec3  normal    = texture( g_normal,   Tex_coords ).rgb;
  vec4  light_nfo = texture( g_albedo_spec, Tex_coords );

  // Calculate lighting bassed on Blinn-Phong.
  vec3 lighting  =  light_nfo.rgb * 0.1;
  vec3 view_dir  =  normalize( view_pos - frag_pos );
  for( int i = 0; i < LIGHT_QTY; ++i )
  {
    //Diffuse
    vec3 light_dir  = normalize( lights[i].position - frag_pos );
    vec3 diffuse    = max( dot( normal, light_dir ), 0.0 )
      * light_nfo.rgb * lights[i].color;

    //Specular
    vec3  halfway  = normalize( view_dir + light_dir );
    float spec     = pow( max( dot( normal, halfway), 0.0), 16.0 );
    vec3  specular = lights[i].color * spec * light_nfo.a;

    //Attenuation
    float dist        = length( lights[i].position - frag_pos );
    float attenuation = 1.0 /
      (1.0 + lights[i].linear * dist + lights[i].quadratic * dist * dist );
    diffuse  *= attenuation;
    spec     *= attenuation;
    lighting += diffuse + specular;
  }

  Frag_color = vec4( lighting, 1.0 );
}
