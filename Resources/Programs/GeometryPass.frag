#version 330 core
layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;
layout (location = 2) out vec4 out_albedo;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

void main()
{    
    // store the fragment position vector in the first gbuffer texture
    out_position = FragPos;
    // also store the per-fragment normals into the gbuffer
    out_normal = normalize(Normal);
    // and the diffuse per-fragment color
    out_albedo.rgb = texture(texture_diffuse, TexCoords).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    out_albedo.a = texture(texture_specular, TexCoords).r;
}