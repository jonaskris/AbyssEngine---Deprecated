#pragma once
#include <vector>
#include <gl/glew.h>
#include "Renderer.h"
#include "../../entitysystem/units/UnitManager.h"
#include "../../entitysystem/units/UnitGroup.h"
#include "../shaders/Program.h"

#define LR_PROGRAM						Program::type::LINE

#define LINE_WIDTH						3.0f

#define LR_VERTEX_SIZE					sizeof(Line_Component::VertexData)
#define LR_LINE_SIZE					LR_VERTEX_SIZE * 2

#define LR_MAX_LINES					100
#define LR_MAX_INDICES					LR_MAX_LINES * 2
#define LR_BUFFER_SIZE					LR_LINE_SIZE * LR_MAX_LINES

#define LR_SHADER_VERTEX_INDEX			0
#define LR_SHADER_COLOR_INDEX			1

namespace abyssengine {
	struct mat4;
	class Program;
	class Camera;

	class LineRenderer : Renderer
	{
	public:
		LineRenderer();
		~LineRenderer();
	private:
		Program* program = NULL;

		GLuint VAO, VBO, IBO;
		GLuint viewMatrixLocation;
		Line_Component::VertexData* VERTEX_DATA = new Line_Component::VertexData[LR_INDICES_SIZE];

		GLuint* IBO_DATA = new GLuint[LR_INDICES_SIZE];		// RENDERER_INDICES_SIZE is max size of IBO_DATA
		GLsizei LINES_COUNT = 0;

	public:
		void begin(const math::mat4& perspectiveViewMatrix) override;

		void submit(UnitGroup& unitGroup) override;

		/*
			Called during submit if buffer is full, and when calling end() if there are lines to draw.
		*/
		void render();

		void end() override;
	};
}