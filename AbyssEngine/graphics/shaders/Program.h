#pragma once
#include <GL/glew.h>
#include <vector>

struct mat4;
struct vec4;
struct vec3;
struct vec2;

class Program
{
public:
	enum type { SPRITE, LINE, MAX };
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
	Program(type type);
	GLuint programID;
private:
	GLint getUniformLocation(const GLchar* name);
	static bool initialized;
public:
	static const unsigned short programsTypes[type::MAX * 2];
	static Program* programs[type::MAX];
	static void loadPrograms();
	static Program* getProgram(type type);
};
