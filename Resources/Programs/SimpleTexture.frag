#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
	FragColor.rgba = texture(tex, TexCoords).rgba;
	//FragColor.a = 1;
}