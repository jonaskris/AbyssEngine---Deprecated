/*#include "TextRenderer.h"
#include <algorithm>
#include "../shaders/Program.h"
#include "../TextureAtlas.h"
#include "../../entities/components/gComponent/GComponent.h"
#include "../../entities/components/PComponent.h"
#include "../../math/mat4.h"
#include "../Camera.h"

namespace abyssengine {
	TextRenderer* TextRenderer::instance = NULL;
	TextRenderer::TextRenderer() {

		this->program = Program::getProgram(TR_PROGRAM);

		//	Populate indices
		int indicesPattern[]
		{
			0, 1, 2, 0, 2, 3
		};

		for (size_t i = 0; i < TR_INDICES_SIZE; i += 6)
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

		glEnableVertexAttribArray(TR_SHADER_VERTEX_INDEX);
		glVertexAttribPointer(TR_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(GTComponent::VertexData), (const GLvoid*)(offsetof(GTComponent::VertexData, GTComponent::VertexData::vertex)));

		glEnableVertexAttribArray(TR_SHADER_COLOR_INDEX);
		glVertexAttribPointer(TR_SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_TRUE, sizeof(GTComponent::VertexData), (const GLvoid*)(offsetof(GTComponent::VertexData, GTComponent::VertexData::color)));

		glEnableVertexAttribArray(TR_SHADER_UV_INDEX);
		glVertexAttribPointer(TR_SHADER_UV_INDEX, 2, GL_FLOAT, GL_TRUE, sizeof(GTComponent::VertexData), (const GLvoid*)(offsetof(GTComponent::VertexData, GTComponent::VertexData::uv)));

		glBindVertexArray(0);

		// Describe IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, TR_INDICES_SIZE, IBO_DATA, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		texLoc = glGetUniformLocation(program->getProgramID(), "tex");
		viewMatrixLocation = glGetUniformLocation(program->getProgramID(), "vw_matrix");
	}

	void TextRenderer::render(const std::vector<GTComponent*>& components, Camera* camera)
	{
		glUseProgram(program->getProgramID());
		
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &(*camera->getViewMat()).elements[0]);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		/* Sort components by fontId, so that strings that use the same font are drawn together*/
		std::sort(components.begin(), components.end());

		unsigned int stringsToRender = components.size();

		unsigned int charsToRender = 0;
		for (size_t i = 0; i < components.size(); i++)
			charsToRender += components.at(i)->getCharCount();

		unsigned int stringsProgress = 0;

		while (stringsToRender > 0) {

			unsigned int renderFrom = stringsProgress;
			unsigned int renderTo = stringsProgress;
			unsigned int charsCount = 0;

			unsigned int fontId = components.at(stringsProgress)->getFontId();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, TextureAtlas::getAtlas(TextureAtlas::Atlas::TESTSHEET)->getTextureID());		/* Bind texture */
			glUniform1i(texLoc, 0);

			for (size_t i = 0; i < stringsToRender; i++)
			{
				if (components.at(stringsProgress + i)->getCharCount() + charsCount <= TR_MAX_CHARS && components.at(stringsProgress + i)->getFontId() == fontId)
				{
					renderTo++;
				} else {
					if (components.at(stringsProgress + i)->getCharCount() > TR_MAX_CHARS) {
						std::cout << "Failed to render string as it was longer than TR_MAX_CHARS, string ignored." << std::endl;
						stringsProgress++;
					}
					break;
				}
			}

			/* Get and bind textureatlas for fontId */

			/* Get and add vertices, colors, and texture coordinates for each char */




		

			glBufferData(GL_ARRAY_BUFFER, TR_BUFFER_SIZE, VERTEX_DATA, GL_STATIC_DRAW);

			IBO_COUNT = (renderTo - renderFrom) * 6;

			glDrawElements(GL_TRIANGLES, IBO_COUNT, GL_UNSIGNED_INT, NULL);

			toRender -= (renderTo - renderFrom);
			progress += (renderTo - renderFrom);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	TextRenderer::~TextRenderer()
	{
		delete[] VERTEX_DATA;
		delete[] IBO_DATA;
	}

	TextRenderer* TextRenderer::getInstance()
	{
		if (!instance)
		{
			std::cout << "Initialized TextRenderer singleton!" << std::endl;
			instance = new TextRenderer();
			return instance;
		}
		return instance;
	}
}*/