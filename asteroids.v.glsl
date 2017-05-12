#version 450 core
layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 vert_color;
layout (location = 2) in vec2 tex_coords;
layout (location = 3) in mat4 instance_matrix;

out vec2 Tex_coords;

//out vec3 Color;

uniform mat4 projection;
uniform mat4 view;

void main()
{
  gl_Position  = projection * view * instance_matrix * vec4(position, 1.0f);
  Tex_coords   = tex_coords;
//  Color = vert_color;
}
