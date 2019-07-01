#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color; 
layout (location = 2) in vec2 uv;

uniform mat4 vw_matrix;
uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec4 color;
	vec2 uv;
} vs_out;



void main()
{
	//gl_Position = vw_matrix * ml_matrix * position;
	gl_Position = vw_matrix * position;
	vs_out.position = position;
	vs_out.color = color;
	vs_out.uv = uv;
}