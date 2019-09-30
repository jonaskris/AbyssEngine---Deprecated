#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec4 in_color;
layout (location = 3) in vec3 in_normal;

out vec3 FragPos;   
out vec4 FragColor;
out vec2 FragUV;
flat out vec3 FragNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	// Position
    vec4 worldPos = model * vec4(in_position, 1.0);
    FragPos = worldPos.xyz; 

	// Color
	FragColor = in_color;

	// UV
    FragUV = in_uv;
    
	// Normal
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    FragNormal = normalMatrix * in_normal;

    gl_Position = projection * view * worldPos;
}