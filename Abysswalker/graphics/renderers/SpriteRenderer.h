#pragma once
#include <vector>
#include "../../entities/components/gComponent/GSSComponent.h"
#include "../../math/mat4.h"
#include "../shaders/Program.h"
#include "../buffers/Buffer.h"
#include "../buffers/IndexBuffer.h"

#define RENDERER_MAX_SPRITES	10000
#define RENDERER_VERTEX_SIZE	sizeof(GSSComponent::VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_LENGTH	RENDERER_MAX_SPRITES * 6
#define RENDERER_INDICES_SIZE	RENDERER_INDICES_LENGTH * sizeof(GLuint)

#define SHADER_VERTEX_INDEX				0
#define SHADER_COLOR_INDEX				1
#define SHADER_UV_INDEX					2

class SpriteRenderer // todo: make into singleton
{
private:
	static GLuint VAO, VBO, IBO;

	static GSSComponent::VertexData* VERTEX_DATA;
	static GLuint* IBO_DATA;						// RENDERER_INDICES_SIZE is max size of IBO_DATA
	static GLsizei IBO_COUNT;						// IBO_COUNT is how much data is actually in IBO_DATA, used when drawing


public:
	static void init();
	static void render(std::vector<GSSComponent*>* components, const mat4& viewMatrix, Program* program);
};