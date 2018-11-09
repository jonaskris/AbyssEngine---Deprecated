#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include "../../utils/FileUtils.h"
#include "../../math/vec2.h"
#include "../../math/vec3.h"
#include "../../math/vec4.h"
#include "../../math/mat4.h"
#include <vector>


class Program
{
public:
	enum Type { SPRITE, MAX };
	~Program();

	void setUniform1f(const GLchar* name, float value);
	void setUniform1i(const GLchar* name, int value);
	void setUniform2f(const GLchar* name, const vec2& vector);
	void setUniform3f(const GLchar* name, const vec3& vector);
	void setUniform4f(const GLchar* name, const vec4& vector);
	void setUniformMat4(const GLchar* name, const mat4& matrix);

	void enable() const;
	void disable() const;

	GLuint getProgramID();
private:
	Program(Type type);
	GLuint programID;
private:
	GLint getUniformLocation(const GLchar* name);
	static bool initialized;
public:
	static const unsigned short programsTypes[Type::MAX * 2];
	static Program* programs[Type::MAX];
	static void loadPrograms();
	static Program* getProgram(Type type);
};
