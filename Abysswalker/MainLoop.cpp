#include <iostream>
#include "graphics/renderers/Renderer.h"
#include <vector>
#include "math/mat4.h"
#include "graphics/shaders/Shader.h"
#include "graphics/buffers/Buffer.h"
#include "graphics/buffers/IndexBuffer.h"
#include "graphics/buffers/VertexArray.h"
#include "entities/components/CComponent.h"
#include "scenes/WorldScene.h"
#include "graphics/shaders/Program.h"
#include "graphics/TextureAtlas.h"


int main() 
{


	Renderer renderer;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


	std::vector<GSSComponent*> components;



	float a = 0.0001f;
	int j = 0;
	while (true) {
		j++;
		components.clear();
		vec3 pos(-1.0f, 0.0f, 0.0f);
		vec3 offset(0.35f + a * j, 0.0f, 0.0f);
		for (int i = 0; i < 1; i++) {
			components.push_back(new GSSComponent(NULL, TextureAtlas::Atlas::TEST, i));
			components.back()->position = pos + offset * (float)i;
			components.back()->scale = vec3(0.3f, 0.3f, 0.3f);
			components.back()->color[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			components.back()->color[1] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			components.back()->color[2] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			components.back()->color[3] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		}

		renderer.render(&components);
		system("PAUSE");
		for (size_t i = 0; i < components.size(); i++) {
			delete components.at(i);
		}
	}

}
	/*struct vertex
	{
		vec3 vertex;
		vec4 color;
	};

	float vertexData[] = {
//			Vertices						Color
		0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, -0.5f, 0.0f, 	1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.0f, 0.0f, 	0.6f, 1.0f, 1.0f, 1.0f
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(vertex), (const GLvoid*)(offsetof(vertex, vertex::vertex)));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), (const GLvoid*)(offsetof(vertex, vertex::color)));

	glBindVertexArray(0);

	glUseProgram(Program::getProgram(Program::SPRITE)->getProgramID());
	glBindVertexArray(VAO);

	while (true) {
		renderer.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		renderer.update();
	}



	system("PAUSE");
	return 0;
}*/

/*
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	// Fill IBO_DATA with indicies and set IBO_COUNT here
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_INDICES_SIZE * sizeof(GLuint), IBO_DATA, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
*/

// Draw once triangle without VAO
/*GLuint vertexBuffer;
glGenBuffers(1, &vertexBuffer);
glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

while (true) {
renderer.clear();

glEnableVertexAttribArray(0);
glVertexAttribPointer(
	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	3,                  // size
	GL_FLOAT,           // type
	GL_FALSE,           // normalized?
	0,                  // stride
	(void*)0            // array buffer offset
);

// Draw the triangle !
glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
glDisableVertexAttribArray(0);

renderer.update();
}*/


// Draw two triangles with VAO
/*struct vertex
	{
		vec3 vertex;
		vec4 color;
	};

	float vertexData[] = {
//			Vertices						Color
		0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, -0.5f, 0.0f, 	1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.0f, 0.0f, 	0.6f, 1.0f, 1.0f, 1.0f
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(vertex), (const GLvoid*)(offsetof(vertex, vertex::vertex)));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), (const GLvoid*)(offsetof(vertex, vertex::color)));

	glBindVertexArray(0);


	renderer.clear();
	glUseProgram(Program::getProgram(Program::SPRITE)->getProgramID());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	renderer.update();*/