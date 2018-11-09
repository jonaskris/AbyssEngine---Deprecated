#pragma once
#include <vector>
#include <GL/glew.h>

class Shader
{
public:
	enum Type { VERTEX, FRAGMENT, GEOMETRY, TESSELATION_CONTROL, TESSELATION_EVALUATION, COMPUTE};
	GLuint getShaderID();
	~Shader();
private:
	GLuint shaderID;
	const char* path;
	Type type;
	Shader(const char* path, Type type);
	void load();
private:
	static const int shaderPathsSize = 2; // Remember to update this when adding new shaderPaths.
	static Shader* shaders[shaderPathsSize];
	static const char* shaderPaths[shaderPathsSize];
	static bool initialized;
public:
	static Shader* getShader(unsigned short index);
	static void initShaders();
};
