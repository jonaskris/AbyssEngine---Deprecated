#include <utility>
#include "PointRenderer.h"
#include "../shaders/Program.h"
#include "../../resources/Texture.h"
#include "../../entitysystem/units/UnitManager.h"
#include "../../entitysystem/defaultcomponents/Graphics.h"
#include "../../math/linalg.h"
#include "../Camera.h"

namespace abyssengine {
	PointRenderer::PointRenderer()
	{
		glPointSize(POINT_SIZE);

		this->program = Program::getProgram(PR_PROGRAM);

		// Create buffers
		glGenBuffers(1, &VBO);

		// Create Vertex array
		glGenVertexArrays(1, &VAO);

		// Describe Vertex Array
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glEnableVertexAttribArray(PR_SHADER_VERTEX_INDEX);
		glVertexAttribPointer(PR_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Point_Component::VertexData), (const GLvoid*)(offsetof(Point_Component::VertexData, Point_Component::VertexData::vertex)));

		glEnableVertexAttribArray(PR_SHADER_COLOR_INDEX);
		glVertexAttribPointer(PR_SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_TRUE, sizeof(Point_Component::VertexData), (const GLvoid*)(offsetof(Point_Component::VertexData, Point_Component::VertexData::color)));

		glBindVertexArray(0);

		viewMatrixLocation = glGetUniformLocation(program->getProgramID(), "vw_matrix");
	}
	
	PointRenderer::~PointRenderer()
	{
		delete[] VERTEX_DATA;
	}

	void PointRenderer::begin(const math::mat4f& perspectiveViewMatrix)
	{
		glUseProgram(program->getProgramID());
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &(perspectiveViewMatrix).elements[0]);
		
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}

	void PointRenderer::submit(entitysystem::UnitGroup& unitGroup)
	{
		std::pair<Point_Component*, size_t> pointComponents = unitGroup.get<Point_Component>();
		std::pair<Position_Component*, size_t> positionComponents = unitGroup.get<Position_Component>();

		if (positionComponents.second > 0){
			for (size_t i = 0; i < pointComponents.second; i++)
			{
				if (POINTS_COUNT == PR_MAX_POINTS)
					render();

				VERTEX_DATA[POINTS_COUNT].vertex = pointComponents.first[i].vertex.vertex + positionComponents.first[0];
				VERTEX_DATA[POINTS_COUNT].color = pointComponents.first[i].vertex.color;
				POINTS_COUNT++;
			}
		} else {
			for (size_t i = 0; i < pointComponents.second; i++)
			{
				if (POINTS_COUNT == PR_MAX_POINTS)
					render();

				VERTEX_DATA[POINTS_COUNT] = pointComponents.first[i].vertex;
				POINTS_COUNT++;
			}
		}
	}

	/*
		Called during submit if buffer is full, and when calling end() if there are points to draw.
	*/
	void PointRenderer::render()
	{
		glBufferData(GL_ARRAY_BUFFER, PR_BUFFER_SIZE, VERTEX_DATA, GL_STATIC_DRAW);
		
		glDrawArrays(GL_POINTS, 0, POINTS_COUNT);
		POINTS_COUNT = 0;
	}

	void PointRenderer::end()
	{
		if (POINTS_COUNT > 0)
			render();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}