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
#define SR_PROGRAM						Program::type::SPRITE

// Vertices
#define SR_VERTEX_SIZE					sizeof(Sprite_Component::VertexData)

// Sprites
#define SR_SPRITE_SIZE					SR_VERTEX_SIZE * 4
#define SR_MAX_SPRITES					500

// Indices
#define SR_INDICES_LENGTH				SR_MAX_SPRITES * 6

// Buffers
#define SR_BUFFER_SIZE					SR_SPRITE_SIZE * SR_MAX_SPRITES
#define SR_INDICES_SIZE					SR_INDICES_LENGTH * sizeof(GLuint)

// Shader indices
#define SR_SHADER_VERTEX_INDEX			0
#define SR_SHADER_COLOR_INDEX			1
#define SR_SHADER_UV_INDEX				2

namespace abyssengine {
	struct mat4;
	class Program;
	class Camera;

	class SpriteRenderer : public Renderer, public entitysystem::EachCallable<Sprite_Component, Position_Component>
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();
	private:
		Program* program = NULL;

		GLuint VAO, VBO, IBO;
		GLuint viewMatrixLocation, texLoc, textureId;
		Sprite_Component::VertexData* VERTEX_DATA = new Sprite_Component::VertexData[SR_INDICES_SIZE];
		
		GLuint* IBO_DATA = new GLuint[SR_INDICES_SIZE];
		GLsizei SPRITES_COUNT = 0;
	public:
		void begin(const math::mat4f& perspectiveViewMatrix) override;

		void submitUnits(entitysystem::EntityManager* entitymanager) override { entitymanager->each(this); }

		void eachCall(entitysystem::UnitGroup& unitgroup) override { submit(unitgroup); };

		void submit(entitysystem::UnitGroup& unitGroup) override;

		/*
			Called during submit if buffer is full, and when calling end() if there are sprites to draw.
		*/
		void render();

		void end() override;
	};
}