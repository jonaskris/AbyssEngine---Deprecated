#include "LineRenderer.h"
#include "../shaders/Program.h"
#include "../TextureAtlas.h"
#include "../../entities/components/gComponent/GComponent.h"
#include "../../entities/components/PComponent.h"
#include "../../math/mat4.h"

LineRenderer* LineRenderer::instance;

LineRenderer::LineRenderer() 
{
	glLineWidth(LINE_WIDTH);

	this->program = Program::getProgram(LR_PROGRAM);


	for (size_t i = 0; i < LR_RENDERER_INDICES_SIZE; i += 1)
	{
		IBO_DATA[i] = i;
	}

	// Create buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	// Create Vertex array
	glGenVertexArrays(1, &VAO);

	// Describe Vertex Array
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(LR_SHADER_VERTEX_INDEX);
	glVertexAttribPointer(LR_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(GLComponent::VertexData), (const GLvoid*)(offsetof(GLComponent::VertexData, GLComponent::VertexData::vertex)));

	glEnableVertexAttribArray(LR_SHADER_COLOR_INDEX);
	glVertexAttribPointer(LR_SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_TRUE, sizeof(GLComponent::VertexData), (const GLvoid*)(offsetof(GLComponent::VertexData, GLComponent::VertexData::color)));

	glBindVertexArray(0);

	// Describe IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, LR_RENDERER_INDICES_SIZE, IBO_DATA, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	projectionMatrixLocation = glGetUniformLocation(program->getProgramID(), "pr_matrix");
	viewMatrixLocation = glGetUniformLocation(program->getProgramID(), "vw_matrix");
}

void LineRenderer::render(const std::vector<GLComponent*>& components, const mat4& pr_matrix, const mat4& vw_matrix)
{
	glUseProgram(program->getProgramID());
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &pr_matrix.elements[0]);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &vw_matrix.elements[0]);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	unsigned int toRender = components.size();
	unsigned int progress = 0;

	while (toRender > 0) {
		unsigned int renderFrom = progress;
		unsigned int renderTo;
		if (toRender >= LR_RENDERER_MAX_LINES) {
			renderTo = renderFrom + LR_RENDERER_MAX_LINES;
		}
		else {
			renderTo = renderFrom + toRender;
		}

		for (size_t i = renderFrom; i < renderTo; i++)
		{
			VERTEX_DATA[i * 2].vertex = components.at(i)->vertices[0] + components.at(i)->getPositionComponent()->position;
			VERTEX_DATA[i * 2].color = components.at(i)->colors[0];
			VERTEX_DATA[i * 2 + 1].vertex = components.at(i)->vertices[1] + components.at(i)->getPositionComponent()->position;
			VERTEX_DATA[i * 2 + 1].color = components.at(i)->colors[1];
		}

		glBufferData(GL_ARRAY_BUFFER, LR_RENDERER_LINE_SIZE * (renderTo - renderFrom), VERTEX_DATA, GL_STATIC_DRAW);

		IBO_COUNT = (renderTo - renderFrom) * 2;

		glDrawElements(GL_LINES, IBO_COUNT, GL_UNSIGNED_INT, NULL);

		toRender -= (renderTo - renderFrom);
		progress += (renderTo - renderFrom);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

LineRenderer::~LineRenderer()
{
	delete[] VERTEX_DATA;
}

LineRenderer* LineRenderer::getInstance()
{
	if (!instance)
	{
		std::cout << "Initialized LineRenderer singleton!" << std::endl;
		instance = new LineRenderer();
		return instance;
	}
	return instance;
}