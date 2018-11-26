#include "SpriteRenderer.h"
#include "../shaders/Program.h"
#include "../TextureAtlas.h"

GLuint SpriteRenderer::VAO;
GLuint SpriteRenderer::IBO;
GLuint SpriteRenderer::VBO;
GSSComponent::VertexData* SpriteRenderer::VERTEX_DATA = new GSSComponent::VertexData[RENDERER_BUFFER_SIZE];
GLuint* SpriteRenderer::IBO_DATA = new GLuint[RENDERER_INDICES_SIZE];
GLsizei SpriteRenderer::IBO_COUNT = 0;

void SpriteRenderer::render(std::vector<GSSComponent*>* components, const mat4& viewMatrix, Program* program)
{
	for (size_t i = 0; i < components->size(); i++) 
	{
		vec3 position = components->at(i)->position;
		vec3 scale = components->at(i)->scale;
		vec4* color = components->at(i)->color;
		std::vector<vec2> uv = components->at(i)->uv;

		VERTEX_DATA[  i * 4  ].vertex.x = position.x;
		VERTEX_DATA[  i * 4  ].vertex.y = position.y;
		VERTEX_DATA[  i * 4  ].vertex.z = position.z;
		VERTEX_DATA[  i * 4  ].color = color[0];
		VERTEX_DATA[  i * 4  ].uv = uv.at(0);
		//std::cout << uv.at(0) << std::endl;

		VERTEX_DATA[i * 4 + 1].vertex.x = position.x;
		VERTEX_DATA[i * 4 + 1].vertex.y = position.y + scale.y;
		VERTEX_DATA[i * 4 + 1].vertex.z = position.z;
		VERTEX_DATA[i * 4 + 1].color = color[1];
		VERTEX_DATA[i * 4 + 1].uv = uv.at(1);
		//std::cout << uv.at(1) << std::endl;

		VERTEX_DATA[i * 4 + 2].vertex.x = position.x + scale.x;
		VERTEX_DATA[i * 4 + 2].vertex.y = position.y + scale.y;
		VERTEX_DATA[i * 4 + 2].vertex.z = position.z;
		VERTEX_DATA[i * 4 + 2].color = color[2];
		VERTEX_DATA[i * 4 + 2].uv = uv.at(2);
		//std::cout << uv.at(2) << std::endl;

		VERTEX_DATA[i * 4 + 3].vertex.x = position.x + scale.x;
		VERTEX_DATA[i * 4 + 3].vertex.y = position.y;
		VERTEX_DATA[i * 4 + 3].vertex.z = position.z;
		VERTEX_DATA[i * 4 + 3].color = color[3];
		VERTEX_DATA[i * 4 + 3].uv = uv.at(3);
		//std::cout << uv.at(3) << std::endl;
	}

	IBO_COUNT = components->size() * 6;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_SPRITE_SIZE * components->size(), VERTEX_DATA, GL_STATIC_DRAW);
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

void SpriteRenderer::init()
{
	//	Populate indices
	int indicesPattern[]
	{
		0, 1, 2, 0, 2, 3
	};

	for (size_t i = 0; i < RENDERER_INDICES_SIZE; i += 6) 
	{
		int offset = (i / 6) * 4;
		IBO_DATA[  i  ] = indicesPattern[0] + offset;
		IBO_DATA[i + 1] = indicesPattern[1] + offset;
		IBO_DATA[i + 2] = indicesPattern[2] + offset;
		IBO_DATA[i + 3] = indicesPattern[3] + offset;
		IBO_DATA[i + 4] = indicesPattern[4] + offset;
		IBO_DATA[i + 5] = indicesPattern[5] + offset;
	}

	// Create buffers
		// VBO and IBO
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