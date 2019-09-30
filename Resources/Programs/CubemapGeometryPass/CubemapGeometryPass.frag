#version 330 core
layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;
layout (location = 2) out vec4 out_albedo;

in vec3 FragPos;   
in vec4 FragColor;
in vec2 FragUV;
in vec3 FragNormal;

//uniform sampler2D texture_diffuse;
//uniform sampler2D texture_specular;
uniform samplerCube texture_cubemap;

void main()
{    
    // Store position of fragment in framebuffer
    out_position = FragPos;

    // Store normal of fragment in framebuffer
    out_normal = normalize(FragNormal);

    // Store diffuse color of fragment in framebuffer
	out_albedo = vec4(texture(texture_cubemap, FragNormal).rgb, 0.5);

    // Store specular intensity in framebuffer
	//out_albedo.a = texture(texture_specular, FragUV).r;
}