#pragma once
#include <vector>
#include <gl/glew.h>
#include "../../entities/components/gComponent/GLComponent.h"
#include "../shaders/Program.h"
#include "../../entities/Entity.h"

#define LR_PROGRAM						Program::type::LINE

#define LINE_WIDTH						3.0f

#define LR_RENDERER_MAX_LINES			1000
#define LR_RENDERER_VERTEX_SIZE			sizeof(GLComponent::VertexData)
#define LR_RENDERER_LINE_SIZE			LR_RENDERER_VERTEX_SIZE * 2
#define LR_RENDERER_BUFFER_SIZE			LR_RENDERER_LINE_SIZE * LR_RENDERER_MAX_LINES
#define LR_RENDERER_INDICES_SIZE		LR_RENDERER_MAX_LINES * 2


#define LR_SHADER_VERTEX_INDEX			0
#define LR_SHADER_COLOR_INDEX			1

struct mat4;
class Program;

class LineRenderer
{
private:
	static LineRenderer* instance;
	LineRenderer();
public:
	static LineRenderer* getInstance();
	~LineRenderer();
private:
	Program* program;

	GLuint VAO, VBO, IBO;
	GLuint projectionMatrixLocation, viewMatrixLocation, texLoc;
	GLComponent::VertexData* VERTEX_DATA = new GLComponent::VertexData[LR_RENDERER_BUFFER_SIZE];

	GLuint* IBO_DATA = new GLuint[LR_RENDERER_INDICES_SIZE];		// RENDERER_INDICES_SIZE is max size of IBO_DATA
	GLsizei IBO_COUNT = 0;
public:
	void render(const std::vector<GLComponent*>& components, const mat4& pr_matrix, const mat4& vw_matrix);
};