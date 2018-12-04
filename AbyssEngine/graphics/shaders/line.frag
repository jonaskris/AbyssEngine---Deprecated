#version 330 core

layout (location = 0) out vec4 out_Color;

in DATA
{
	vec4 color;
} fs_in;

void main()
{
	out_Color = fs_in.color;
}