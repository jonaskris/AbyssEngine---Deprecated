#pragma once
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>
#include <string>
#include "../Path.h"
#include "../File/File.h"
#include "../File/FileException.h"

namespace abyssengine {
	namespace resources {
		class Program;

		class Shader : public File<Shader>
		{
		public:
			friend class FileBase;
			friend class Program;

			const enum Type { VERTEX, FRAGMENT, GEOMETRY, TESSELLATION_EVALUATION, TESSELLATION_CONTROL, COMPUTE };
		private:
			size_t shaderID = 0;
			Type shaderType;

			Shader(const Path& path) : File(path)
			{
				if (path.extension == "vert") {
					shaderID = glCreateShader(GL_VERTEX_SHADER);
					shaderType = VERTEX;
				}
				else if (path.extension == "frag") {
					shaderID = glCreateShader(GL_FRAGMENT_SHADER);
					shaderType = FRAGMENT;
				}
				else if (path.extension == "geom") {
					shaderID = glCreateShader(GL_GEOMETRY_SHADER);
					shaderType = GEOMETRY;
				}
				else if (path.extension == "tese") {
					shaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
					shaderType = TESSELLATION_EVALUATION;
				}
				else if (path.extension == "tesc") {
					shaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
					shaderType = TESSELLATION_CONTROL;
				}
				else if (path.extension == "comp") {
					shaderID = glCreateShader(GL_COMPUTE_SHADER);
					shaderType = COMPUTE;
				}

				std::ifstream file(path.getFullPath());

				if (!file.is_open())
					throw FileCreationException(std::string("Couldent find file: ") + path.getFullPath());

				std::string file_contents;
				std::string string;
				while (std::getline(file, string))
				{
					file_contents += string + "\n";
				}
				file.close();

				const char* cstr = file_contents.c_str();

				glShaderSource(shaderID, 1, &cstr, NULL);
				glCompileShader(shaderID);

				GLint result;
				glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

				if (result == GL_FALSE)
				{
					GLint length;
					glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

					std::vector<char> error(length);
					glGetShaderInfoLog(shaderID, length, &length, &error[0]);

					glDeleteShader(shaderID);

					std::string errorString = std::string(error.begin(), error.end()); // Convert char vector to string
					errorString.erase(std::remove(errorString.begin(), errorString.end(), '\n'), errorString.end()); // Remove newlines

					throw FileCreationException(std::string("OpenGL failed to compile shader! Error: ") + errorString);
				}
			}
		public:
			~Shader() { glDeleteShader(shaderID); }

			bool suitableAsDefaultFor(const Path & originallyRequested) const override { return false; };
		};
	}
}