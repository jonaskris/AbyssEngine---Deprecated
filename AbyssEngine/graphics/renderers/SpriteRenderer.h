#pragma once
#include <vector>
#include <gl/glew.h>
#include "../../entities/components/gComponent/GSSComponent.h"
#include "../shaders/Program.h"
#include "../../entities/Entity.h"

#define SR_PROGRAM						Program::type::SPRITE

#define SR_RENDERER_MAX_SPRITES			10000
#define SR_RENDERER_VERTEX_SIZE			sizeof(GSSComponent::VertexData)
#define SR_RENDERER_SPRITE_SIZE			SR_RENDERER_VERTEX_SIZE * 4
#define SR_RENDERER_BUFFER_SIZE			SR_RENDERER_SPRITE_SIZE * SR_RENDERER_MAX_SPRITES
#define SR_RENDERER_INDICES_LENGTH		SR_RENDERER_MAX_SPRITES * 6
#define SR_RENDERER_INDICES_SIZE		SR_RENDERER_INDICES_LENGTH * sizeof(GLuint)

#define SR_SHADER_VERTEX_INDEX			0
#define SR_SHADER_COLOR_INDEX			1
#define SR_SHADER_UV_INDEX				2

struct mat4;
class Program;

class SpriteRenderer
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
	GLuint projectionMatrixLocation, viewMatrixLocation, texLoc;
 	GSSComponent::VertexData* VERTEX_DATA = new GSSComponent::VertexData[SR_RENDERER_BUFFER_SIZE];
	GLuint* IBO_DATA = new GLuint[SR_RENDERER_INDICES_SIZE];	// RENDERER_INDICES_SIZE is max size of IBO_DATA
	GLsizei IBO_COUNT = 0;										// IBO_COUNT is how much data is actually in IBO_DATA, used when drawing
public:
	void render(const std::vector<GSSComponent*>& components, const mat4& pr_matrix, const mat4& vw_matrix);
};