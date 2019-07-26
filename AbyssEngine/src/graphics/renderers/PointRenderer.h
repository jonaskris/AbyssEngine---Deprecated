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
#define PR_PROGRAM						Program::type::LINE

// Points
#define POINT_SIZE						3.0f
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

	class PointRenderer : public Renderer, public entitysystem::EachCallable<Point_Component, Position_Component::optional>
	{
	public:
		PointRenderer();
		~PointRenderer();
	private:
		Program* program = NULL;

		GLuint VAO, VBO;//, IBO;
		GLuint viewMatrixLocation;
		Point_Component::VertexData* VERTEX_DATA = new Point_Component::VertexData[PR_MAX_POINTS];

		GLsizei POINTS_COUNT = 0;
	public:
		void begin(const math::mat4f& perspectiveViewMatrix) override;

		void submitUnits(entitysystem::EntityManager* entitymanager) override { entitymanager->each(this); }

		void eachCall(entitysystem::UnitGroup& unitgroup) override { submit(unitgroup); };

		void submit(entitysystem::UnitGroup& unitGroup) override;

		/*
			Called during submit if buffer is full, and when calling end() if there are points to draw.
		*/
		void render();

		void end() override;
	};
}