#pragma once
#include <vector>
#include <gl/glew.h>
#include "Renderer.h"
#include "../../entitysystem/units/UnitManager.h"
#include "../../entitysystem/units/UnitGroup.h"
#include "../../entitysystem/entitymanager/EachCallable.h"
#include "../../entitysystem/entitymanager/EntityManager.h"
#include "../../entitysystem/defaultcomponents/Graphics.h"
#include "../../entitysystem/defaultcomponents/Spatial.h"
#include "../shaders/Program.h"

// Program
#define LR_PROGRAM						Program::type::LINE

// Lines
#define LINE_WIDTH						3.0f
#define LR_VERTEX_SIZE					sizeof(Line_Component::VertexData)
#define LR_LINE_SIZE					LR_VERTEX_SIZE * 2
#define LR_MAX_LINES					100

// Buffers
#define LR_BUFFER_SIZE					LR_LINE_SIZE * LR_MAX_LINES

// Shader indices
#define LR_SHADER_VERTEX_INDEX			0
#define LR_SHADER_COLOR_INDEX			1

namespace abyssengine {
	struct mat4;
	class Program;
	class Camera;

	class LineRenderer : public Renderer, public entitysystem::EachCallable<Line_Component, Position_Component::optional>
	{
	public:
		LineRenderer();
		~LineRenderer();
	private:
		Program* program = NULL;

		GLuint VAO, VBO;//, IBO;
		GLuint viewMatrixLocation;
		Line_Component::VertexData* VERTEX_DATA = new Line_Component::VertexData[LR_MAX_LINES * 2];

		GLsizei LINES_COUNT = 0;
	public:
		void begin(const math::mat4f& perspectiveViewMatrix) override;

		void submitUnits(entitysystem::EntityManager* entitymanager) override { entitymanager->each(this); }

		void eachCall(entitysystem::UnitGroup& unitgroup) override { submit(unitgroup); };

		void submit(entitysystem::UnitGroup& unitGroup) override;

		/*
			Called during submit if buffer is full, and when calling end() if there are lines to draw.
		*/
		void render();

		void end() override;
	};
}