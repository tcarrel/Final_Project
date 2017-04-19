#version 450 core
layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform uint wireframe;

out vec3 tex_coords;
out uint wf;

void main()
{
//	gl_Position = vec4( 0.0, 0.0, 0.0, 0.0 );
	vec4 pos    = projection * view * vec4(position, 1.0);
	gl_Position = pos.xyww;
	tex_coords  = position;
	wf          = wireframe;
}
