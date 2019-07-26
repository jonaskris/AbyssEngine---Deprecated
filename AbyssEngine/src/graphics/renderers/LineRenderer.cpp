#include <utility>
#include "LineRenderer.h"
#include "../shaders/Program.h"
#include "../../resources/Texture.h"
#include "../../entitysystem/units/UnitManager.h"
#include "../../entitysystem/defaultcomponents/Graphics.h"
#include "../../entitysystem/defaultcomponents/Spatial.h"
#include "../../math/linalg.h"
#include "../Camera.h"

namespace abyssengine {
	LineRenderer::LineRenderer()
	{
		glLineWidth(LINE_WIDTH);

		this->program = Program::getProgram(LR_PROGRAM);

		// Create buffers
		glGenBuffers(1, &VBO);

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

		viewMatrixLocation = glGetUniformLocation(program->getProgramID(), "vw_matrix");
	}
	
	LineRenderer::~LineRenderer()
	{
		delete[] VERTEX_DATA;
	}

	void LineRenderer::begin(const math::mat4f& perspectiveViewMatrix)
	{
		glUseProgram(program->getProgramID());
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &(perspectiveViewMatrix).elements[0]);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}

	void LineRenderer::submit(entitysystem::UnitGroup& unitGroup)
	{
		std::pair<Line_Component*, size_t> lineComponents = unitGroup.get<Line_Component>();
		std::pair<Position_Component*, size_t> positionComponents = unitGroup.get<Position_Component>();

		if (positionComponents.second > 0)
			for (size_t i = 0; i < lineComponents.second; i++)
			{
				if (LINES_COUNT == LR_MAX_LINES)
					render();

				VERTEX_DATA[LINES_COUNT * 2 + 0].vertex = lineComponents.first[i].vertex[0].vertex + positionComponents.first[0];
				VERTEX_DATA[LINES_COUNT * 2 + 0].color = lineComponents.first[i].vertex[0].color;
				VERTEX_DATA[LINES_COUNT * 2 + 1].vertex = lineComponents.first[i].vertex[1].vertex + positionComponents.first[0];
				VERTEX_DATA[LINES_COUNT * 2 + 1].color = lineComponents.first[i].vertex[1].color;
				LINES_COUNT++;
			}
		else
			for (size_t i = 0; i < lineComponents.second; i++)
			{
				if (LINES_COUNT == LR_MAX_LINES)
					render();

				VERTEX_DATA[LINES_COUNT * 2 + 0] = lineComponents.first[i].vertex[0];
				VERTEX_DATA[LINES_COUNT * 2 + 1] = lineComponents.first[i].vertex[1];
				LINES_COUNT++;
			}
	}

	/*
		Called during submit if buffer is full, and when calling end() if there are lines to draw.
	*/
	void LineRenderer::render()
	{
		glBufferData(GL_ARRAY_BUFFER, LR_BUFFER_SIZE, VERTEX_DATA, GL_STATIC_DRAW);
		glDrawArrays(GL_LINES, 0, LINES_COUNT * 2);
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