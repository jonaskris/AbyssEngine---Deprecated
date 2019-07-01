#include <iostream>
#include <string>
#include <vector>
#include "Shader.h"
#include "../../utils/FileUtils.h"

namespace abyssengine {
	Shader* Shader::shaders[shaderPathsSize] = {};
	bool Shader::initialized = false;
	const char* Shader::shaderPaths[Shader::shaderPathsSize] =
	{
		"src/graphics/shaders/sprite.vert", "src/graphics/shaders/sprite.frag",
		"src/graphics/shaders/line.vert", "src/graphics/shaders/line.frag",
		"src/graphics/shaders/text.vert", "src/graphics/shaders/text.frag"
	};

	Shader::Shader(const char* path, Shader::Type type)
	{
		this->path = path;
		this->type = type;
		this->shaderId = load();
	}

	Shader::~Shader()
	{
		glDeleteShader(shaderId);
	}

	GLuint Shader::getShaderID()
	{
		return shaderId;
	}

	GLuint Shader::load()
	{
		GLuint shaderId = 0;
		switch (type) {
		case Shader::Type::VERTEX:
			shaderId = glCreateShader(GL_VERTEX_SHADER);
			break;
		case Shader::Type::FRAGMENT:
			shaderId = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}

		std::string sourceString = FileUtils::read_file(path);
		if (sourceString == "") {
			std::cout << "Failed to read shader, perhaps the path is wrong?" << std::endl;
			return shaderId;
		}
		const char* source = sourceString.c_str();

		glShaderSource(shaderId, 1, &source, NULL);
		glCompileShader(shaderId);

		GLint result;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(shaderId, length, &length, &error[0]);
			std::cout << "Failed to compile shader : " << path << "!" << std::endl << &error[0] << std::endl;
			glDeleteShader(shaderId);
			return shaderId;
		}
		return shaderId;
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
			}
			else if (shaderPathExtension == "frag") {
				shaderType = Shader::Type::FRAGMENT;
			}
			else if (shaderPathExtension == "geom") {
				shaderType = Shader::Type::GEOMETRY;
				std::cout << "The engine doesen't support geometry shaders!";
				continue;
			}
			else if (shaderPathExtension == "tesc") {
				shaderType = Shader::Type::TESSELATION_CONTROL;
				std::cout << "The engine doesen't support tesselation control shaders!";
				continue;
			}
			else if (shaderPathExtension == "tese") {
				shaderType = Shader::Type::TESSELATION_EVALUATION;
				std::cout << "The engine doesen't support tesselation evaluation shaders!";
				continue;
			}
			else if (shaderPathExtension == "comp") {
				shaderType = Shader::Type::COMPUTE;
				std::cout << "The engine doesen't support compute shaders!";
				continue;
			}
			else {
				std::cout << "Failed to interpret shader type of shader '" << shaderPath << "'. Interpreted extension: '" << shaderPathExtension << "'." << std::endl;
				continue;
			}

			shaders[i] = new Shader(shaderPaths[i], shaderType);
		}
		initialized = true;
	}
}