#include <vector>
#include <iostream>
#include "Program.h"
#include "Shader.h"
#include "../../math/mat4.h"
#include "../../math/vec2.h"
#include "../../math/vec3.h"
#include "../../math/vec4.h"

Program* Program::programs[type::MAX] = {};
bool Program::initialized = false;

const unsigned short Program::programsTypes[] = 
{
	0, 1,
	2, 3 
};

Program::Program(Program::type type)
{
	programID = glCreateProgram();
	switch (type)
	{
	case type::SPRITE:
		glAttachShader(programID, (Shader::getShader(0)->getShaderID()));
		glAttachShader(programID, (Shader::getShader(1)->getShaderID()));
		break;
	case type::LINE:
		glAttachShader(programID, (Shader::getShader(2)->getShaderID()));
		glAttachShader(programID, (Shader::getShader(3)->getShaderID()));
		break;
	}
	glLinkProgram(programID);
	glValidateProgram(programID);

}

Program::~Program()
{
	glDeleteProgram(programID);
}

GLuint Program::getProgramID() {
	return programID;
}

void Program::enable() const
{
	glUseProgram(programID);
}

void Program::disable() const
{
	glUseProgram(0);
}

void Program::loadPrograms()
{
	if (initialized) {
		return;
	}
	Shader::initShaders();
	for (int i = 0; i < type::MAX; i++) {
		programs[i] = new Program(type(i));
	}
	initialized = true;
}

Program* Program::getProgram(type type)
{
	return programs[type];
}

GLint Program::getUniformLocation(const GLchar* name)
{
	return glGetUniformLocation(programID, name);
}

void Program::setUniform1f(const GLchar* name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Program::setUniform1i(const GLchar* name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Program::setUniform2f(const GLchar* name, const vec2& vector)
{
	glUniform2f(getUniformLocation(name), vector.x, vector.y);
}

void Program::setUniform3f(const GLchar* name, const vec3& vector)
{
	glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void Program::setUniform4f(const GLchar* name, const vec4& vector)
{
	glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Program::setUniformMat4(const GLchar* name, const mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
}