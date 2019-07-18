#include <utility>
#include "PointRenderer.h"
#include "../shaders/Program.h"
#include "../../resources/Texture.h"
#include "../../entitysystem/units/UnitManager.h"
#include "../../entitysystem/DefaultGComponents.h"
#include "../../math/mat4.h"
#include "../Camera.h"

namespace abyssengine {
	PointRenderer::PointRenderer()
	{
		glPointSize(POINT_SIZE);

		this->program = Program::getProgram(PR_PROGRAM);


		for (size_t i = 0; i < PR_MAX_POINTS; i++)
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

		glEnableVertexAttribArray(PR_SHADER_VERTEX_INDEX);
		glVertexAttribPointer(PR_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Point_Component::VertexData), (const GLvoid*)(offsetof(Point_Component::VertexData, Point_Component::VertexData::vertex)));

		glEnableVertexAttribArray(PR_SHADER_COLOR_INDEX);
		glVertexAttribPointer(PR_SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_TRUE, sizeof(Point_Component::VertexData), (const GLvoid*)(offsetof(Point_Component::VertexData, Point_Component::VertexData::color)));

		glBindVertexArray(0);

		// Describe IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, PR_MAX_POINTS, IBO_DATA, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		viewMatrixLocation = glGetUniformLocation(program->getProgramID(), "vw_matrix");
	}

	//void PointRenderer::render(const std::vector<Point_Component>* components, const math::mat4& perspectiveViewMatrix)
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
	//		if (toRender >= PR_MAX_POINTS)
	//			renderTo = renderFrom + PR_MAX_POINTS;
	//		else
	//			renderTo = renderFrom + toRender;
	//
	//		for (size_t i = renderFrom; i < renderTo; i++)
	//		{
	//			size_t index = i - renderFrom;
	//			//if (components.at(i)->getPositionComponent() != NULL)
	//			//{
	//			//	VERTEX_DATA[index].vertex = components.at(i)->getVertex() + components.at(i)->getPositionComponent()->position;
	//			//	VERTEX_DATA[index].color = components.at(i)->getColor();
	//			//}
	//			//else {
	//				VERTEX_DATA[index].vertex = components->at(i).vertex.vertex;
	//				VERTEX_DATA[index].color = components->at(i).vertex.color;
	//			//}
	//		}
	//
	//		glBufferData(GL_ARRAY_BUFFER, PR_BUFFER_SIZE, VERTEX_DATA, GL_STATIC_DRAW);
	//
	//		IBO_COUNT = (renderTo - renderFrom);
	//
	//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	//		//glDrawElements(GL_LINES, IBO_COUNT, GL_UNSIGNED_INT, NULL);
	//		glDrawArrays(GL_POINTS, 0, (renderTo - renderFrom));
	//
	//		toRender -= (renderTo - renderFrom);
	//		progress += (renderTo - renderFrom);
	//	}
	//
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//	glBindVertexArray(0);
	//	glUseProgram(0);
	//}

	PointRenderer::~PointRenderer()
	{
		delete[] VERTEX_DATA;
	}

	void PointRenderer::begin(const math::mat4& perspectiveViewMatrix)
	{
		glUseProgram(program->getProgramID());
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &(perspectiveViewMatrix).elements[0]);
		
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		POINTS_COUNT = 0;
	}

	void PointRenderer::submit(UnitGroup& unitGroup)
	{
		std::pair<Point_Component*, size_t> pointComponents = unitGroup.get<Point_Component>();

		for (size_t i = 0; i < pointComponents.second; i++)
		{
			if (POINTS_COUNT == PR_MAX_POINTS - 1)
				render();

			VERTEX_DATA[POINTS_COUNT * 2 + 0] = pointComponents.first[i].vertex;
			VERTEX_DATA[POINTS_COUNT * 2 + 1] = pointComponents.first[i].vertex;
			POINTS_COUNT++;
		}
	}

	/*
		Called during submit if buffer is full, and when calling end() if there are points to draw.
	*/
	void PointRenderer::render()
	{
		glBufferData(GL_ARRAY_BUFFER, PR_BUFFER_SIZE, VERTEX_DATA, GL_STATIC_DRAW);
		glDrawArrays(GL_LINES, 0, POINTS_COUNT);
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