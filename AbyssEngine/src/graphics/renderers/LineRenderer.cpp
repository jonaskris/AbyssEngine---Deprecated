#include <utility>
#include "LineRenderer.h"
#include "../shaders/Program.h"
#include "../../resources/Texture.h"
#include "../../entitysystem/units/UnitManager.h"
#include "../../entitysystem/DefaultGComponents.h"
#include "../../math/mat4.h"
#include "../Camera.h"

namespace abyssengine {
	LineRenderer::LineRenderer()
	{
		glLineWidth(LINE_WIDTH);

		this->program = Program::getProgram(LR_PROGRAM);


		for (size_t i = 0; i < LR_INDICES_SIZE; i++)
			IBO_DATA[i] = i;

		// Create buffers
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);

		// Create Vertex array
		glGenVertexArrays(1, &VAO);

		// Describe Vertex Array
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glEnableVertexAttribArray(LR_SHADER_VERTEX_INDEX);
		glVertexAttribPointer(LR_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Line_Component::VertexData), (const GLvoid*)(offsetof(Line_Component::VertexData, Line_Component::VertexData::vertex)));

		glEnableVertexAttribArray(LR_SHADER_COLOR_INDEX);
		glVertexAttribPointer(LR_SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_TRUE, sizeof(Line_Component::VertexData), (const GLvoid*)(offsetof(Line_Component::VertexData, Line_Component::VertexData::color)));

		glBindVertexArray(0);

		// Describe IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, LR_INDICES_SIZE, IBO_DATA, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		viewMatrixLocation = glGetUniformLocation(program->getProgramID(), "vw_matrix");
	}

	//void LineRenderer::render(const std::vector<Line_Component>* components, )
	//{
	//	glUseProgram(program->getProgramID());
	//	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &(perspectiveViewMatrix).elements[0]);
	//	glBindVertexArray(VAO);
	//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//
	//	unsigned int toRender = components->size();
	//	unsigned int progress = 0;
	//
	//	while (toRender > 0) {
	//		unsigned int renderFrom = progress;
	//		unsigned int renderTo;
	//		if (toRender >= LR_MAX_LINES)
	//			renderTo = renderFrom + LR_MAX_LINES;
	//		else
	//			renderTo = renderFrom + toRender;
	//
	//		for (size_t i = renderFrom; i < renderTo; i++)
	//		{
	//			size_t index = i - renderFrom;
	//			//if (components->at(i).getPositionComponent() != NULL)
	//			//{
	//			//	VERTEX_DATA[index * 2 + 0].vertex = components.at(i)->getVertex(0) + components.at(i)->getPositionComponent()->position;
	//			//	VERTEX_DATA[index * 2 + 0].color = components.at(i)->getColor(0);
	//			//	VERTEX_DATA[index * 2 + 1].vertex = components.at(i)->getVertex(1) + components.at(i)->getPositionComponent()->position;
	//			//	VERTEX_DATA[index * 2 + 1].color = components.at(i)->getColor(1);
	//			//}
	//			//else {
	//				VERTEX_DATA[index * 2 + 0].vertex = components->at(i).vertex[0].vertex;
	//				VERTEX_DATA[index * 2 + 0].color = components->at(i).vertex[0].color;
	//				VERTEX_DATA[index * 2 + 1].vertex = components->at(i).vertex[1].vertex;
	//				VERTEX_DATA[index * 2 + 1].color = components->at(i).vertex[1].color;
	//			//}
	//		}
	//
	//
	//		IBO_COUNT = (renderTo - renderFrom) * 2;
	//
	//		//glDrawElements(GL_LINES, IBO_COUNT, GL_UNSIGNED_INT, NULL);
	//		glBufferData(GL_ARRAY_BUFFER, LR_BUFFER_SIZE, VERTEX_DATA, GL_STATIC_DRAW);
	//		glDrawArrays(GL_LINES, 0, (renderTo - renderFrom) * 2);
	//
	//		toRender -= (renderTo - renderFrom);
	//		progress += (renderTo - renderFrom);
	//	}
	//
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//	glBindVertexArray(0);
	//	glUseProgram(0);
	//}

	LineRenderer::~LineRenderer()
	{
		delete[] VERTEX_DATA;
	}

	void LineRenderer::begin(const math::mat4& perspectiveViewMatrix)
	{
		glUseProgram(program->getProgramID());
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &(perspectiveViewMatrix).elements[0]);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		LINES_COUNT = 0;
	}

	void LineRenderer::submit(UnitGroup& unitGroup)
	{
		std::pair<Line_Component*, size_t> lineComponents = unitGroup.get<Line_Component>();

		for (size_t i = 0; i < lineComponents.second; i++)
		{
			VERTEX_DATA[LINES_COUNT * 2 + 0] = lineComponents.first[i].vertex[0];
			VERTEX_DATA[LINES_COUNT * 2 + 1] = lineComponents.first[i].vertex[1];
			LINES_COUNT++;

			if (LINES_COUNT == LR_MAX_LINES)
				render();
		}
	}

	/*
		Called during submit if buffer is full, and when calling end() if there are lines to draw.
	*/
	void LineRenderer::render()
	{
		glBufferData(GL_ARRAY_BUFFER, LR_BUFFER_SIZE, VERTEX_DATA, GL_STATIC_DRAW);
		glDrawArrays(GL_LINES, 0, LINES_COUNT);
		LINES_COUNT = 0;
	}

	void LineRenderer::end()
	{
		if (LINES_COUNT > 0)
		render();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}