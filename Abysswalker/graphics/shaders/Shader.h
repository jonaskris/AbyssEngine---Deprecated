#pragma once
#include <GL/glew.h>
#include "../../utils/FileUtils.h"
#include "../../math/vec2.h"
#include "../../math/vec3.h"
#include "../../math/vec4.h"
#include "../../math/mat4.h"

class Shader
{
private:
	GLuint shaderID;
	const char* vertPath;
	const char* fragPath;
public:
	Shader(const char* vertPath, const char* fragPath); // shadersPath must be followed by '/'
	~Shader();


	void setUniform1f(const GLchar* name, float value);
	void setUniform1i(const GLchar* name, int value);
	void setUniform2f(const GLchar* name, const vec2& vector);
	void setUniform3f(const GLchar* name, const vec3& vector);
	void setUniform4f(const GLchar* name, const vec4& vector);
	void setUniformMat4(const GLchar* name, const mat4& matrix);

	void enable() const;
	void disable() const;
	
	GLuint getShaderID();
private:
	GLint getUniformLocation(const GLchar* name);
	GLuint load();
};