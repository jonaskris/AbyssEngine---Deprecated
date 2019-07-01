#include "SpriteRenderer.h"
#include "../shaders/Program.h"
#include "../../resources/Texture.h"
#include "../../entitysystem/entities/components/ComponentManager.h"
#include "../../entitysystem/DefaultGComponents.h"
#include "../../entitysystem/DefaultComponents.h"
#include "../../math/mat4.h"
#include "../Camera.h"
#include "../../resources/ResourceManager.h"
#include "../../resources/TextureAtlas.h"


namespace abyssengine {
	SpriteRenderer* SpriteRenderer::instance = NULL;
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

	void SpriteRenderer::render(const std::vector<Sprite_Component>* components, const math::mat4& perspectiveViewMatrix)
	{
		glUseProgram(program->getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(texLoc, 0);
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &(perspectiveViewMatrix).elements[0]);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);



		unsigned int progress = 0;
		while (progress < components->size()) {
			size_t IBOCount = 0;
			size_t index = 0;
			size_t textureId = components->at(progress).textureId;

			//if (toRender >= SR_MAX_SPRITES) {
			//	renderTo = renderFrom + SR_MAX_SPRITES;
			//}
			//else {
			//	renderTo = renderFrom + toRender;
			//}
			//
			//for (size_t i = renderFrom; i < renderTo; i++)
			//{				
			//	size_t index = i - renderFrom;
			//	
			//	VERTEX_DATA[index * 4 + 0] = components->at(i).vertex[0];
			//	VERTEX_DATA[index * 4 + 1] = components->at(i).vertex[1];
			//	VERTEX_DATA[index * 4 + 2] = components->at(i).vertex[2];
			//	VERTEX_DATA[index * 4 + 3] = components->at(i).vertex[3];
			//}

			for (size_t i = progress; i < components->size(); i++)
			{
				if ((i - progress) >= SR_MAX_SPRITES)
					break;
				else if (components->at(i).textureId != textureId)
					break;
				

				VERTEX_DATA[index * 4 + 0] = components->at(i).vertex[0];
				VERTEX_DATA[index * 4 + 1] = components->at(i).vertex[1];
				VERTEX_DATA[index * 4 + 2] = components->at(i).vertex[2];
				VERTEX_DATA[index * 4 + 3] = components->at(i).vertex[3];

				IBOCount += 6;
				index += 4;
				progress++;
			}

			glBindTexture(GL_TEXTURE_2D, textureId);

			glBufferData(GL_ARRAY_BUFFER, SR_BUFFER_SIZE, VERTEX_DATA, GL_STATIC_DRAW);

			glDrawElements(GL_TRIANGLES, IBOCount, GL_UNSIGNED_INT, NULL);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	SpriteRenderer::~SpriteRenderer()
	{
		delete[] VERTEX_DATA;
		delete[] IBO_DATA;
	}

	SpriteRenderer* SpriteRenderer::getInstance()
	{
		if (!instance)
		{
			std::cout << "Initialized SpriteRenderer singleton!" << std::endl;
			instance = new SpriteRenderer();
			return instance;
		}
		return instance;
	}
}