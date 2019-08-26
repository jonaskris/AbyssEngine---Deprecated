#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>
#include "../file/File.h"
#include "../filetypes/Json.h"
#include "../filetypes/Shader.h"
#include "../Resource/Resource.h"
#include "../Resource/ResourceException.h"
#include "../resourcemanager/ResourceManager.h"
#include "../../math/Linalg.h"

namespace abyssengine {
	namespace resources {

		/*
			A program is a collection of shaders.

			The Json should be in the format of an array of paths to shaders.
			The Json should have .prog extension.
			Example:
			[
				"Shadername.vert",
				"Shadername.frag"
			]
		*/
		class Program : public Resource<Program>
		{
			friend class ResourceBase;
		private:
			GLuint programID;

			Program(const Json& json) : Resource(json.getPath())
			{
				const nlohmann::json jsonObj = json.getJsonObject();

				std::vector<Shader*> shaders;

				for (auto it = jsonObj.begin(); it != jsonObj.end(); it++)
					if (it.value().is_string()) {
						Shader* shader = ResourceManager::getInstance()->getFile<Shader>(it.value());
						if (shader)
							shaders.push_back(shader);
						else
							throw ResourceCreationException(std::string("Couldent find shader: ") + std::string(it.value()) + std::string(" for program!"));
					}
					else {
						throw ResourceCreationException("Couldent parse .prog file to initialize program. The file should contain a JSON formatted array of strings!");
					}

				programID = glCreateProgram();

				for (auto it = shaders.begin(); it != shaders.end(); it++)
					glAttachShader(programID, (*it)->shaderID);

				glLinkProgram(programID);

				GLint linkResult;
				glGetProgramiv(programID, GL_VALIDATE_STATUS, &linkResult);
				if (linkResult == GL_FALSE)
				{
					GLint maxLength = 0;
					glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

					std::vector<GLchar> error(maxLength);
					glGetProgramInfoLog(programID, maxLength, &maxLength, &error[0]);

					glDeleteProgram(programID);

					std::string errorString = std::string(error.begin(), error.end()); // Convert char vector to string
					errorString.erase(std::remove(errorString.begin(), errorString.end(), '\n'), errorString.end()); // Remove newlines

					throw FileCreationException(std::string("OpenGL failed to link program! Error: ") + errorString);
				}

				glValidateProgram(programID);

				GLint validateResult;
				glGetProgramiv(programID, GL_VALIDATE_STATUS, &validateResult);
				if (validateResult == GL_FALSE)
				{
					GLint maxLength = 0;
					glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

					std::vector<GLchar> error(maxLength);
					glGetProgramInfoLog(programID, maxLength, &maxLength, &error[0]);

					glDeleteProgram(programID);

					std::string errorString = std::string(error.begin(), error.end()); // Convert char vector to string
					errorString.erase(std::remove(errorString.begin(), errorString.end(), '\n'), errorString.end()); // Remove newlines

					throw FileCreationException(std::string("OpenGL failed to validate program! Error: ") + errorString);
				}
			}
		public:
			~Program() { glDeleteProgram(programID); }

			void enable() const { glUseProgram(programID); }
			void disable() const { glUseProgram(0); }
			GLuint getID() const { return programID; }

			GLint getUniformLocation(const GLchar * name)
			{
				return glGetUniformLocation(programID, name);
			}

			void setUniform1f(const GLchar * name, float value)
			{
				glUniform1f(getUniformLocation(name), value);
			}

			void setUniform1i(const GLchar * name, int value)
			{
				glUniform1i(getUniformLocation(name), value);
			}

			void setUniform2f(const GLchar * name, const math::vec2f & vector)
			{
				glUniform2f(getUniformLocation(name), vector.x, vector.y);
			}

			void setUniform3f(const GLchar * name, const math::vec3f & vector)
			{
				glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
			}

			void setUniform4f(const GLchar * name, const math::vec4f & vector)
			{
				glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
			}

			void setUniformMat4(const GLchar * name, const math::mat4f & matrix)
			{
				glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
			}
		};
	}
}