#pragma once
#include <vector>
#include <gl/glew.h>
#include "../../entities/components/gComponent/GTComponent.h"
#include "../shaders/Program.h"
#include "../../entities/Entity.h"

#define TR_PROGRAM						Program::type::TEXT

#define TR_MAX_CHARS					500
#define TR_VERTEX_SIZE					sizeof(GTComponent::VertexData)
#define TR_CHAR_SIZE					TR_VERTEX_SIZE * 4
#define TR_BUFFER_SIZE					TR_CHAR_SIZE * TR_MAX_CHARS
#define TR_INDICES_LENGTH				TR_MAX_CHARS * 6
#define TR_INDICES_SIZE					TR_INDICES_LENGTH * sizeof(GLuint)

#define TR_SHADER_VERTEX_INDEX			0
#define TR_SHADER_COLOR_INDEX			1
#define TR_SHADER_UV_INDEX				2

namespace abyssengine {
	struct mat4;
	class Program;
	class Camera;

	class TextRenderer
	{
	private:
		static TextRenderer* instance;
		TextRenderer();
	public:
		static TextRenderer* getInstance();
		~TextRenderer();
	private:
		Program* program = NULL;

		GLuint VAO, VBO, IBO;
		GLuint viewMatrixLocation, texLoc;
		GTComponent::VertexData* VERTEX_DATA = new GTComponent::VertexData[TR_INDICES_SIZE];
		GLuint* IBO_DATA = new GLuint[TR_INDICES_SIZE];	// RENDERER_INDICES_SIZE is max size of IBO_DATA
		GLsizei IBO_COUNT = 0;							// IBO_COUNT is how much data is actually in IBO_DATA, used when drawing
	public:
		void render(const std::vector<GTComponent*>& components, Camera* camera);
	};
}