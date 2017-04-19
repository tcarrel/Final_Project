#version 450 core

layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec3 vert_normal;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	Normal      = mat3( transpose( inverse( model ) ) ) * normal;
	Position    = vec3( model * vec4( position, 1.0f ) );
}
