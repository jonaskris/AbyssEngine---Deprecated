#pragma once
#include <vector>
#include <gl/glew.h>
#include "../../entitysystem/entities/components/ComponentManager.h"
#include "../../entitysystem/DefaultGComponents.h"
#include "../shaders/Program.h"
#include "../../entitysystem/DefaultComponents.h"

#define LR_PROGRAM						Program::type::LINE

#define LINE_WIDTH						3.0f

#define LR_MAX_LINES					5000
#define LR_VERTEX_SIZE					sizeof(Line_Component::VertexData)
#define LR_LINE_SIZE					LR_VERTEX_SIZE * 2
#define LR_BUFFER_SIZE					LR_LINE_SIZE * LR_MAX_LINES
#define LR_INDICES_SIZE					LR_MAX_LINES * 2

#define LR_SHADER_VERTEX_INDEX			0
#define LR_SHADER_COLOR_INDEX			1

namespace abyssengine {
	struct mat4;
	class Program;
	class Camera;

	class LineRenderer
	{
	private:
		static LineRenderer* instance;
		LineRenderer();
	public:
		static LineRenderer* getInstance();
		~LineRenderer();
	private:
		Program* program = NULL;

		GLuint VAO, VBO, IBO;
		GLuint viewMatrixLocation;
		Line_Component::VertexData* VERTEX_DATA = new Line_Component::VertexData[LR_INDICES_SIZE];

		GLuint* IBO_DATA = new GLuint[LR_INDICES_SIZE];		// RENDERER_INDICES_SIZE is max size of IBO_DATA
		GLsizei IBO_COUNT = 0;
	public:
		void render(const std::vector<Line_Component>* components, const math::mat4& perspectiveViewMatrix);
	};
}