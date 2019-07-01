#pragma once
#include <GL/glew.h>

namespace abyssengine {
	class Shader
	{
	public:
		enum Type { VERTEX, FRAGMENT, GEOMETRY, TESSELATION_CONTROL, TESSELATION_EVALUATION, COMPUTE };
		GLuint getShaderID();
		~Shader();
	private:
		GLuint shaderId;
		const char* path;
		Type type;
		Shader(const char* path, Type type);
		GLuint load();
	private:
		static const int shaderPathsSize = 6; // Remember to update this when adding new shaderPaths.
		static Shader* shaders[shaderPathsSize];
		static const char* shaderPaths[shaderPathsSize];
		static bool initialized;
	public:
		static Shader* getShader(unsigned short index);
		static void initShaders();
	};
}