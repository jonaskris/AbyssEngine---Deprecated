#pragma once
#include <vector>
#include <gl/glew.h>
#include "../../entities/components/gComponent/GSSComponent.h"
#include "../shaders/Program.h"
#include "../../entities/Entity.h"

#define PROGRAM						Program::Type::SPRITE

#define RENDERER_MAX_SPRITES		50000
#define RENDERER_VERTEX_SIZE		sizeof(GSSComponent::VertexData)
#define RENDERER_SPRITE_SIZE		RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_LENGTH		RENDERER_MAX_SPRITES * 6
#define RENDERER_INDICES_SIZE		RENDERER_INDICES_LENGTH * sizeof(GLuint)

#define SHADER_VERTEX_INDEX			0
#define SHADER_COLOR_INDEX			1
#define SHADER_UV_INDEX				2

struct mat4;
class Program;

class SpriteRenderer // todo: make into singleton
{
private:
	static SpriteRenderer* instance;
	SpriteRenderer();
public:
	static SpriteRenderer* getInstance();
	~SpriteRenderer();
private:
	Program* program;

	GLuint VAO, VBO, IBO;
	GSSComponent::VertexData* VERTEX_DATA = new GSSComponent::VertexData[RENDERER_BUFFER_SIZE];
	GLuint* IBO_DATA = new GLuint[RENDERER_INDICES_SIZE];	// RENDERER_INDICES_SIZE is max size of IBO_DATA
	GLsizei IBO_COUNT = 0;									// IBO_COUNT is how much data is actually in IBO_DATA, used when drawing
public:
	void render(std::vector<GSSComponent*>& components, const mat4& viewMatrix);
};