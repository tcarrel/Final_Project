
#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coord;

out vec2 Tex_coord;
out vec3 Frag_pos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 world_pos  = model * vec4( position, 1.0f );
	Frag_pos        = world_pos.xyz;
	gl_Position     = projection * view * world_pos;
	Tex_coord	= tex_coord;

	mat3 n_mat	= transpose( inverse( mat3( model ) ) );
	Normal		= n_mat * normal;
}

