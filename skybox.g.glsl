#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices = 14) out;

uniform mat4 projection;
uniform mat4 view;

out vec3 tex_coords;

//Vertices:
// 1	( -1,  1,  1 )
// 2	( -1,  1, -1 )
// 3	(  1,  1,  1 )
// 4	(  1,  1, -1 )
// 5	( -1, -1,  1 )
// 6	( -1, -1, -1 )
// 7	(  1, -1, -1 )
// 8	(  1, -1,  1 )
//Winding order: 4,3,7,8,5,3,1,4,2,7,6,5,2,1

void main()
{
//	4 (1)
	gl_Position = vec4(projection * view * vec4(  1.0,  1.0, -1.0,  1.0 )).xyww;
	tex_coords = vec3(  1.0,  1.0, -1.0 );
	EmitVertex();

//	3 (2)	
	gl_Position = vec4(projection * view * vec4(  1.0,  1.0,  1.0,  1.0 )).xyww;
	tex_coords = vec3(  1.0,  1.0,  1.0 );
	EmitVertex();

//	7 (3)	
	gl_Position = vec4(projection * view * vec4(  1.0, -1.0, -1.0,  1.0 )).xyww;
	tex_coords = vec3(  1.0, -1.0, -1.0 );
	EmitVertex();

//	8 (4)	
	gl_Position = vec4(projection * view * vec4(  1.0, -1.0,  1.0,  1.0 )).xyww;
	tex_coords = vec3(  1.0, -1.0,  1.0 );
	EmitVertex();

//	5 (5)	
	gl_Position = vec4(projection * view * vec4( -1.0, -1.0,  1.0,  1.0 )).xyww;
	tex_coords = vec3( -1.0, -1.0,  1.0 );
	EmitVertex();

//	3 (6)
	gl_Position = vec4(projection * view * vec4(  1.0,  1.0,  1.0,  1.0 )).xyww;
	tex_coords = vec3(  1.0,  1.0,  1.0 );
	EmitVertex();

//	1 (7)
	gl_Position = vec4(projection * view * vec4( -1.0,  1.0,  1.0,  1.0 )).xyww;
	tex_coords = vec3( -1.0,  1.0,  1.0 );
	EmitVertex();

//	4 (8)
	gl_Position = vec4(projection * view * vec4(  1.0,  1.0, -1.0,  1.0 )).xyww;
	tex_coords = vec3(  1.0,  1.0, -1.0 );
	EmitVertex();

//	2 (9)
	gl_Position = vec4(projection * view * vec4( -1.0,  1.0, -1.0,  1.0 )).xyww;
	tex_coords = vec3( -1.0,  1.0, -1.0 );
	EmitVertex();

//	7 (10)
	gl_Position = vec4(projection * view * vec4(  1.0, -1.0, -1.0,  1.0 )).xyww;
	tex_coords = vec3(  1.0, -1.0, -1.0 );
	EmitVertex();

//	6 (11)
	gl_Position = vec4(projection * view * vec4( -1.0, -1.0, -1.0,  1.0 )).xyww;
	tex_coords = vec3( -1.0, -1.0, -1.0 );
	EmitVertex();

//	5 (12)
	gl_Position = vec4(projection * view * vec4( -1.0, -1.0,  1.0,  1.0 )).xyww;
	tex_coords = vec3( -1.0, -1.0,  1.0 );
	EmitVertex();

//	2 (13)
	gl_Position = vec4(projection * view * vec4( -1.0,  1.0, -1.0,  1.0 )).xyww;
	tex_coords = vec3( -1.0,  1.0, -1.0 );
	EmitVertex();

//	1 (14)
	gl_Position = vec4(projection * view * vec4( -1.0,  1.0,  1.0,  1.0 )).xyww;
	tex_coords = vec3( -1.0,  1.0,  1.0 );
	EmitVertex();

	EndPrimitive();
}

