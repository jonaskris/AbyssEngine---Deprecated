#include <iostream>
#include <string>
#include <vector>
#include "Shader.h"
#include "../../utils/FileUtils.h"

Shader* Shader::shaders[shaderPathsSize] = {};

bool Shader::initialized = false;
const char* Shader::shaderPaths[Shader::shaderPathsSize] = 
{
	"graphics/shaders/sprite.vert", "graphics/shaders/sprite.frag",
	"graphics/shaders/line.vert", "graphics/shaders/line.frag"
};

Shader::Shader(const char* path, Shader::Type type)
{
	this->path = path;
	this->type = type;
	load();
}

Shader::~Shader()
{
	glDeleteShader(shaderID);
}

GLuint Shader::getShaderID()
{
	return shaderID;
}

void Shader::load()
{
	switch (type) {
	case Shader::Type::VERTEX:
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case Shader::Type::FRAGMENT:
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	std::string sourceString = read_file(path);
	if (sourceString == "") {
		std::cout << "Failed to read shader, perhaps the path is wrong?" << std::endl;
		return;
	}
	const char* source = sourceString.c_str();

	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	GLint result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(shaderID, length, &length, &error[0]);
		std::cout << "Failed to compile shader : " << path << "!" << std::endl << &error[0] << std::endl;
		glDeleteShader(shaderID);
		return;
	}
}

Shader* Shader::getShader(unsigned short index)
{
	if (index >= shaderPathsSize) {
		std::cout << "Shader " << index << " does not exist! Only programs from 0 to " << shaderPathsSize / 2 << " are defined." << std::endl;
	}

	return shaders[index];
}

void Shader::initShaders()
{
	
	if (initialized) {
		return;
	}
	for (int i = 0; i < shaderPathsSize; i++) {
		std::string shaderPath = shaderPaths[i];
		std::string shaderPathExtension = shaderPath.substr(shaderPath.find(".") + 1);
		
		Type shaderType;
		if (shaderPathExtension == "vert") {
			shaderType = Shader::Type::VERTEX;
		} else if (shaderPathExtension == "frag") {
			shaderType = Shader::Type::FRAGMENT;
		} else if (shaderPathExtension == "geom") {
			shaderType = Shader::Type::GEOMETRY;
			std::cout << "The engine doesen't support geometry shaders!";
			continue;
		} else if (shaderPathExtension == "tesc") {
			shaderType = Shader::Type::TESSELATION_CONTROL;
			std::cout << "The engine doesen't support tesselation control shaders!";
				continue;
		} else if (shaderPathExtension == "tese") {
			shaderType = Shader::Type::TESSELATION_EVALUATION;
			std::cout << "The engine doesen't support tesselation evaluation shaders!";
				continue;
		} else if (shaderPathExtension == "comp") {
			shaderType = Shader::Type::COMPUTE;
			std::cout << "The engine doesen't support compute shaders!";
				continue;
		} else {
			std::cout << "Failed to interpret shader type of shader '" << shaderPath << "'. Interpreted extension: '" << shaderPathExtension << "'." << std::endl;
			continue;
		}

		shaders[i] = new Shader(shaderPaths[i], shaderType);
	}
	initialized = true;
}