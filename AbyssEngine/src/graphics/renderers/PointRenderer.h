#pragma once
#include <vector>
#include <gl/glew.h>
#include "Renderer.h"
#include "../../entitysystem/units/UnitManager.h"
#include "../../entitysystem/units/UnitGroup.h"
#include "../shaders/Program.h"
#include "../../entitysystem/DefaultGComponents.h"

// Program
#define PR_PROGRAM						Program::type::LINE

// Points
#define POINT_SIZE						2.0f
#define PR_POINT_SIZE					sizeof(Point_Component::VertexData)
#define PR_MAX_POINTS					1000

// Buffers
#define PR_BUFFER_SIZE					PR_POINT_SIZE * PR_MAX_POINTS

// Shader indices
#define PR_SHADER_VERTEX_INDEX			0
#define PR_SHADER_COLOR_INDEX			1

namespace abyssengine {
	struct mat4;
	class Program;
	class Camera;

	class PointRenderer : Renderer
	{
	public:
		PointRenderer();
		~PointRenderer();
	private:
		Program* program = NULL;

		GLuint VAO, VBO, IBO;
		GLuint viewMatrixLocation;
		Point_Component::VertexData* VERTEX_DATA = new Point_Component::VertexData[PR_MAX_POINTS];

		GLuint* IBO_DATA = new GLuint[PR_MAX_POINTS];
		GLsizei POINTS_COUNT = 0;
	public:
		void begin(const math::mat4& perspectiveViewMatrix) override;

		void submit(UnitGroup& unitGroup) override;

		/*
			Called during submit if buffer is full, and when calling end() if there are points to draw.
		*/
		void render();

		void end() override;
	};
}