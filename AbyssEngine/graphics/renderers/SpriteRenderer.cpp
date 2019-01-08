#include "SpriteRenderer.h"
#include "../shaders/Program.h"
#include "../TextureAtlas.h"
#include "../../entities/components/gComponent/GComponent.h"
#include "../../entities/components/PComponent.h"
#include "../../math/mat4.h"
#include "../Camera.h"

SpriteRenderer* SpriteRenderer::instance;

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
	glVertexAttribPointer(SR_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(GSSComponent::VertexData), (const GLvoid*)(offsetof(GSSComponent::VertexData, GSSComponent::VertexData::vertex)));

	glEnableVertexAttribArray(SR_SHADER_COLOR_INDEX);
	glVertexAttribPointer(SR_SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_TRUE, sizeof(GSSComponent::VertexData), (const GLvoid*)(offsetof(GSSComponent::VertexData, GSSComponent::VertexData::color)));

	glEnableVertexAttribArray(SR_SHADER_UV_INDEX);
	glVertexAttribPointer(SR_SHADER_UV_INDEX, 2, GL_FLOAT, GL_TRUE, sizeof(GSSComponent::VertexData), (const GLvoid*)(offsetof(GSSComponent::VertexData, GSSComponent::VertexData::uv)));

	glBindVertexArray(0);

	// Describe IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SR_INDICES_SIZE, IBO_DATA, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	texLoc = glGetUniformLocation(program->getProgramID(), "tex");
	viewMatrixLocation = glGetUniformLocation(program->getProgramID(), "vw_matrix");
}

void SpriteRenderer::render(const std::vector<GSSComponent*>& components, Camera* camera)
{
	glUseProgram(program->getProgramID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureAtlas::getAtlas(TextureAtlas::Atlas::TESTSHEET)->getTextureID());
	glUniform1i(texLoc, 0);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &(*camera->getViewMat()).elements[0]);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	unsigned int toRender = components.size();
	unsigned int progress = 0;

	while (toRender > 0) {
		unsigned int renderFrom = progress;
		unsigned int renderTo;
		if (toRender >= SR_MAX_SPRITES) {
			renderTo = renderFrom + SR_MAX_SPRITES;
		} else {
			renderTo = renderFrom + toRender;
		}

		for (size_t i = renderFrom; i < renderTo; i++)
		{
			vec3 gPosition = components.at(i)->getPosition();
			vec3 pPosition = components.at(i)->getPositionComponent()->position;
			vec3 scale = components.at(i)->getScale();
			vec4* color = components.at(i)->getColors();
			std::vector<vec2> uv = components.at(i)->uv;

			size_t index = i - renderFrom;

			VERTEX_DATA[index * 4 + 0].vertex.x = gPosition.x + pPosition.x - (scale.x / 2);
			VERTEX_DATA[index * 4 + 0].vertex.y = gPosition.y + pPosition.y - (scale.y / 2);
			VERTEX_DATA[index * 4 + 0].vertex.z = gPosition.z + pPosition.z - (scale.z / 2);
			VERTEX_DATA[index * 4 + 0].color = color[0];
			VERTEX_DATA[index * 4 + 0].uv = uv.at(0);

			VERTEX_DATA[index * 4 + 1].vertex.x = gPosition.x + pPosition.x - (scale.x / 2);
			VERTEX_DATA[index * 4 + 1].vertex.y = gPosition.y + pPosition.y + (scale.y / 2);
			VERTEX_DATA[index * 4 + 1].vertex.z = gPosition.z + pPosition.z - (scale.z / 2);
			VERTEX_DATA[index * 4 + 1].color = color[1];
			VERTEX_DATA[index * 4 + 1].uv = uv.at(1);
						
			VERTEX_DATA[index * 4 + 2].vertex.x = gPosition.x + pPosition.x + (scale.x / 2);
			VERTEX_DATA[index * 4 + 2].vertex.y = gPosition.y + pPosition.y + (scale.y / 2);
			VERTEX_DATA[index * 4 + 2].vertex.z = gPosition.z + pPosition.z - (scale.z / 2);
			VERTEX_DATA[index * 4 + 2].color = color[2];
			VERTEX_DATA[index * 4 + 2].uv = uv.at(2);
						
			VERTEX_DATA[index * 4 + 3].vertex.x = gPosition.x + pPosition.x + (scale.x / 2);
			VERTEX_DATA[index * 4 + 3].vertex.y = gPosition.y + pPosition.y - (scale.y / 2);
			VERTEX_DATA[index * 4 + 3].vertex.z = gPosition.z + pPosition.z - (scale.z / 2);
			VERTEX_DATA[index * 4 + 3].color = color[3];
			VERTEX_DATA[index * 4 + 3].uv = uv.at(3);
		}

		glBufferData(GL_ARRAY_BUFFER, SR_BUFFER_SIZE, VERTEX_DATA, GL_STATIC_DRAW);

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