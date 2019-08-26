#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_uv;
layout (location = 3) in vec3 in_normal;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vec4 worldPos = model * vec4(in_position, 1.0);
    FragPos = worldPos.xyz; 
    TexCoords = in_uv;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalMatrix * in_normal;

    gl_Position = projection * view * worldPos;
}