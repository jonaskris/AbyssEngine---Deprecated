#pragma once
#include <vector>
#include <gl/glew.h>
#include "../../entitysystem/entities/components/ComponentManager.h"
#include "../../entitysystem/DefaultGComponents.h"
#include "../shaders/Program.h"
#include "../../entitysystem/DefaultComponents.h"

#define PR_PROGRAM						Program::type::LINE

#define POINT_SIZE						2.0f

#define PR_MAX_POINTS					1000
#define PR_POINT_SIZE					sizeof(Point_Component::VertexData)
#define PR_BUFFER_SIZE					PR_POINT_SIZE * PR_MAX_POINTS

#define PR_SHADER_VERTEX_INDEX			0
#define PR_SHADER_COLOR_INDEX			1

namespace abyssengine {
	struct mat4;
	class Program;
	class Camera;

	class PointRenderer
	{
	private:
		static PointRenderer* instance;
		PointRenderer();
	public:
		static PointRenderer* getInstance();
		~PointRenderer();
	private:
		Program* program = NULL;

		GLuint VAO, VBO, IBO;
		GLuint viewMatrixLocation;
		Point_Component::VertexData* VERTEX_DATA = new Point_Component::VertexData[PR_MAX_POINTS];

		GLuint* IBO_DATA = new GLuint[PR_MAX_POINTS];		// RENDERER_INDICES_SIZE is max size of IBO_DATA
		GLsizei IBO_COUNT = 0;
	public:
		void render(const std::vector<Point_Component>* components, const math::mat4& perspectiveViewMatrix);
	};
}