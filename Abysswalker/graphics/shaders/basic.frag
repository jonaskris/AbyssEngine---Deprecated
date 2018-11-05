#version 330 core

layout (location = 0) out vec4 out_Color;

uniform vec4 in_Color;
uniform vec2 light_position;

in vec4 pos;

void main()
{
	float intensity = 0.2 / length(pos.xy - light_position);
	out_Color = in_Color * intensity;
}