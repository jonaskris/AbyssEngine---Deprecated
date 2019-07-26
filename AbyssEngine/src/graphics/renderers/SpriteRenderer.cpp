#include "SpriteRenderer.h"
#include "../shaders/Program.h"
#include "../../resources/Texture.h"
#include "../../entitysystem/units/UnitManager.h"
#include "../../entitysystem/defaultcomponents/Graphics.h"
#include "../../entitysystem/defaultcomponents/Spatial.h"
#include "../../math/linalg.h"
#include "../Camera.h"
#include "../../resources/ResourceManager.h"
#include "../../resources/TextureAtlas.h"


namespace abyssengine {
	SpriteRenderer::SpriteRenderer() {

		this->program = Program::getProgram(SR_PROGRAM);

		//	Populate indices
		int indicesPattern[]
		{
			0, 1, 2, 0, 2, 3
		};

		for (size_t i = 0; i < SR_INDICES_SIZE; i += 6)
		{
			int offset = (i / 6) * 4;
			IBO_DATA[i] = indicesPattern[0] + offset;
			IBO_DATA[i + 1] = indicesPattern[1] + offset;
			IBO_DATA[i + 2] = indicesPattern[2] + offset;
			IBO_DATA[i + 3] = indicesPattern[3] + offset;
			IBO_DATA[i + 4] = indicesPattern[4] + offset;
			IBO_DATA[i + 5] = indicesPattern[5] + offset;
		}

		// Create buffers
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);

		// Create Vertex array
		glGenVertexArrays(1, &VAO);

		// Describe Vertex Array
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glEnableVertexAttribArray(SR_SHADER_VERTEX_INDEX);
		glVertexAttribPointer(SR_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Sprite_Component::VertexData), (const GLvoid*)(offsetof(Sprite_Component::VertexData, Sprite_Component::VertexData::vertex)));

		glEnableVertexAttribArray(SR_SHADER_COLOR_INDEX);
		glVertexAttribPointer(SR_SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_TRUE, sizeof(Sprite_Component::VertexData), (const GLvoid*)(offsetof(Sprite_Component::VertexData, Sprite_Component::VertexData::color)));

		glEnableVertexAttribArray(SR_SHADER_UV_INDEX);
		glVertexAttribPointer(SR_SHADER_UV_INDEX, 2, GL_FLOAT, GL_TRUE, sizeof(Sprite_Component::VertexData), (const GLvoid*)(offsetof(Sprite_Component::VertexData, Sprite_Component::VertexData::uv)));

		glBindVertexArray(0);

		// Describe IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, SR_INDICES_SIZE, IBO_DATA, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		texLoc = glGetUniformLocation(program->getProgramID(), "tex");
		viewMatrixLocation = glGetUniformLocation(program->getProgramID(), "vw_matrix");
	}
	
	SpriteRenderer::~SpriteRenderer()
	{
		delete[] VERTEX_DATA;
		delete[] IBO_DATA;
	}

	void SpriteRenderer::begin(const math::mat4f& perspectiveViewMatrix)
	{
		glUseProgram(program->getProgramID());
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &(perspectiveViewMatrix).elements[0]);
		
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(texLoc, 0);
		
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}

	void SpriteRenderer::submit(entitysystem::UnitGroup& unitGroup)
	{
		std::pair<Sprite_Component*, size_t> spriteComponents = unitGroup.get<Sprite_Component>();
		std::pair<Position_Component*, size_t> positionComponents = unitGroup.get<Position_Component>();

		size_t sid = (spriteComponents.second > 0)?(spriteComponents.first[0].getEntityId()):(0);
		size_t pid = (positionComponents.second > 0)?(positionComponents.first[0].getEntityId()):(0);

		if (positionComponents.second > 0){
			for (size_t i = 0; i < spriteComponents.second; i++)
			{
				if (spriteComponents.first[i].textureId != textureId || SPRITES_COUNT == SR_MAX_SPRITES)
					render();

				textureId = spriteComponents.first[i].textureId;

				VERTEX_DATA[SPRITES_COUNT * 4 + 0] = spriteComponents.first[i].vertex[0];
				VERTEX_DATA[SPRITES_COUNT * 4 + 0].vertex = spriteComponents.first[i].vertex[0].vertex + positionComponents.first[0];
				VERTEX_DATA[SPRITES_COUNT * 4 + 1] = spriteComponents.first[i].vertex[1];
				VERTEX_DATA[SPRITES_COUNT * 4 + 1].vertex = spriteComponents.first[i].vertex[1].vertex + positionComponents.first[0];
				VERTEX_DATA[SPRITES_COUNT * 4 + 2] = spriteComponents.first[i].vertex[2];
				VERTEX_DATA[SPRITES_COUNT * 4 + 2].vertex = spriteComponents.first[i].vertex[2].vertex + positionComponents.first[0];
				VERTEX_DATA[SPRITES_COUNT * 4 + 3] = spriteComponents.first[i].vertex[3];
				VERTEX_DATA[SPRITES_COUNT * 4 + 3].vertex = spriteComponents.first[i].vertex[3].vertex + positionComponents.first[0];

				SPRITES_COUNT++;
			}
		} else {
			for (size_t i = 0; i < spriteComponents.second; i++)
			{
				if (spriteComponents.first[i].textureId != textureId || SPRITES_COUNT == SR_MAX_SPRITES)
					render();

				textureId = spriteComponents.first[i].textureId;

				VERTEX_DATA[SPRITES_COUNT * 4 + 0] = spriteComponents.first[i].vertex[0];
				VERTEX_DATA[SPRITES_COUNT * 4 + 1] = spriteComponents.first[i].vertex[1];
				VERTEX_DATA[SPRITES_COUNT * 4 + 2] = spriteComponents.first[i].vertex[2];
				VERTEX_DATA[SPRITES_COUNT * 4 + 3] = spriteComponents.first[i].vertex[3];
				SPRITES_COUNT++;
			}
		}
	}

	/*
		Called during submit if buffer is full, and when calling end() if there are sprites to draw.
	*/
	void SpriteRenderer::render()
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
		glBufferData(GL_ARRAY_BUFFER, SR_BUFFER_SIZE, VERTEX_DATA, GL_STATIC_DRAW);
		glDrawElements(GL_TRIANGLES, SPRITES_COUNT * 6, GL_UNSIGNED_INT, NULL);

		SPRITES_COUNT = 0;
	}

	void SpriteRenderer::end()
	{
		if (SPRITES_COUNT > 0)
			render();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}