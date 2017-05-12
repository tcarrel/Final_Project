
in vec2 Tex_coords;
//in vec3 Color;
out vec4 color;

uniform sampler2D texture1;

void main()
{
  color  = texture( texture1, Tex_coords );
//  color = vec4( Color, 1.0f );
}
