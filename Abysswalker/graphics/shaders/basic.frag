#version 330 core

layout (location = 0) out vec4 out_Color;

//uniform vec2 light_position;

in DATA
{
	vec4 position;
	vec4 color;
	vec2 uv;
} fs_in;

uniform sampler2D tex0;

void main()
{
	//float intensity = 1.0 / length(fs_in.position.xy - light_position);
	//out_Color = fs_in.color;
	out_Color = texture(tex0, fs_in.uv) * fs_in.color;
}