#pragma once
#include <vector>
#include <gl/glew.h>
#include "../../entities/components/gComponent/GPComponent.h"
#include "../shaders/Program.h"
#include "../../entities/Entity.h"

#define PR_PROGRAM						Program::type::LINE

#define POINT_SIZE						5.0f

#define PR_MAX_POINTS					1000
#define PR_POINT_SIZE					sizeof(GPComponent::VertexData)
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
		GLuint viewMatrixLocation, texLoc;
		GPComponent::VertexData* VERTEX_DATA = new GPComponent::VertexData[PR_MAX_POINTS];

		GLuint* IBO_DATA = new GLuint[PR_MAX_POINTS];		// RENDERER_INDICES_SIZE is max size of IBO_DATA
		GLsizei IBO_COUNT = 0;
	public:
		void render(const std::vector<GPComponent*>& components, Camera* camera);
	};
}