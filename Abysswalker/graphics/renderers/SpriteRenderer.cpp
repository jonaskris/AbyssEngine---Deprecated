#include "SpriteRenderer.h"
#include "../shaders/Program.h"
#include "../TextureAtlas.h"
#include "../../entities/components/gComponent/GComponent.h"
#include "../../entities/components/PComponent.h"

SpriteRenderer* SpriteRenderer::instance;

SpriteRenderer::SpriteRenderer() {

	this->program = Program::getProgram(PROGRAM);

	//	Populate indices
	int indicesPattern[]
	{
		0, 1, 2, 0, 2, 3
	};

	for (size_t i = 0; i < RENDERER_INDICES_SIZE; i += 6)
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

	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(GSSComponent::VertexData), (const GLvoid*)(offsetof(GSSComponent::VertexData, GSSComponent::VertexData::vertex)));

	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_TRUE, sizeof(GSSComponent::VertexData), (const GLvoid*)(offsetof(GSSComponent::VertexData, GSSComponent::VertexData::color)));

	glEnableVertexAttribArray(SHADER_UV_INDEX);
	glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_TRUE, sizeof(GSSComponent::VertexData), (const GLvoid*)(offsetof(GSSComponent::VertexData, GSSComponent::VertexData::uv)));

	glBindVertexArray(0);

	// Describe IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_INDICES_SIZE, IBO_DATA, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SpriteRenderer::render(std::vector<GSSComponent*>& components, const mat4& viewMatrix)
{
	for (size_t i = 0; i < components.size(); i++) 
	{
		vec3 gPosition = components.at(i)->position;
		vec3 pPosition = components.at(i)->getPositionComponent()->position;
		vec3 scale = components.at(i)->scale;
		vec4* color = components.at(i)->color;
		std::vector<vec2> uv = components.at(i)->uv;

		VERTEX_DATA[  i * 4  ].vertex.x = gPosition.x + pPosition.x;
		VERTEX_DATA[  i * 4  ].vertex.y = gPosition.y + pPosition.y;
		VERTEX_DATA[  i * 4  ].vertex.z = gPosition.z + pPosition.z;
		VERTEX_DATA[  i * 4  ].color = color[0];
		VERTEX_DATA[  i * 4  ].uv = uv.at(0);

		VERTEX_DATA[i * 4 + 1].vertex.x = gPosition.x + pPosition.x;
		VERTEX_DATA[i * 4 + 1].vertex.y = gPosition.y + pPosition.y + scale.y;
		VERTEX_DATA[i * 4 + 1].vertex.z = gPosition.z + pPosition.z;
		VERTEX_DATA[i * 4 + 1].color = color[1];
		VERTEX_DATA[i * 4 + 1].uv = uv.at(1);

		VERTEX_DATA[i * 4 + 2].vertex.x = gPosition.x + pPosition.x + scale.x;
		VERTEX_DATA[i * 4 + 2].vertex.y = gPosition.y + pPosition.y + scale.y;
		VERTEX_DATA[i * 4 + 2].vertex.z = gPosition.z + pPosition.z;
		VERTEX_DATA[i * 4 + 2].color = color[2];
		VERTEX_DATA[i * 4 + 2].uv = uv.at(2);

		VERTEX_DATA[i * 4 + 3].vertex.x = gPosition.x + pPosition.x + scale.x;
		VERTEX_DATA[i * 4 + 3].vertex.y = gPosition.y + pPosition.y;
		VERTEX_DATA[i * 4 + 3].vertex.z = gPosition.z + pPosition.z;
		VERTEX_DATA[i * 4 + 3].color = color[3];
		VERTEX_DATA[i * 4 + 3].uv = uv.at(3);
	}

	IBO_COUNT = components.size() * 6;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_SPRITE_SIZE * components.size(), VERTEX_DATA, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glUseProgram(program->getProgramID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureAtlas::getAtlas(TextureAtlas::Atlas::TESTSHEET)->getTextureID());
		GLuint texLoc = glGetUniformLocation(program->getProgramID(), "tex");
		glUniform1i(texLoc, 0);

		glBindVertexArray(VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

				glDrawElements(GL_TRIANGLES, IBO_COUNT, GL_UNSIGNED_INT, NULL);

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