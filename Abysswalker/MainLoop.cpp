#include <iostream>
#include "graphics/Renderer.h"
#include <vector>
#include "math/mat4.h"
#include "graphics/shaders/Shader.h"
#include "graphics/buffers/Buffer.h"
#include "graphics/buffers/IndexBuffer.h"
#include "graphics/buffers/VertexArray.h"

int main() {
	Renderer renderer;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	/*GLfloat vertices[] =
	{
		4.0f,  4.5f / 2.0f, 0,
		4.0f, -4.5f / 2.0f, 0,
		-4.0f, -4.5f / 2.0f, 0,
		4.0f,  4.5f / 2.0f, 0,
		-4.0f, -4.5f / 2.0f, 0,
		-4.0f,  4.5f / 2.0f, 0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);*/

	GLfloat vertices[] =
	{
		4.0f,  4.5f / 2.0f, 0,		// Bottom right
		4.0f, -4.5f / 2.0f, 0,		// Top right
		-4.0f, -4.5f / 2.0f, 0,		// Top left
		-4.0f,  4.5f / 2.0f, 0		// Bottom left
	};

	GLushort indices[]
	{
		0, 1, 2, 0, 2, 3
	};

	VertexArray vao;
	Buffer* vbo = new Buffer(vertices, 4 * 3, 3);
	IndexBuffer ibo(indices, 6);

	vao.addBuffer(vbo, 0);

	mat4 ortho = mat4::orthographic(-8.0f, 8.0f, 4.5f, -4.5f, -1.0f, 1.0f);

	Shader shader("graphics/shaders/basic.vert", "graphics/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	//shader.setUniformMat4("ml_matrix", mat4::translation(vec3(-4.0f, -4.5/2.0f, 0.0f)));
	shader.setUniform4f("in_Color", vec4(1.0f, 0.0f, 1.0f, 1.0f));

	vec2 lightPos(-8.0f, 0.0f);
	vec2 lightAcceleration(0.1f, 0.1f);
	while (!renderer.windowClosed()) {
		//renderer.render();
		renderer.clear();
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		vao.bind();
		ibo.bind();

		if (lightPos.x > 8.0f) {
			lightAcceleration.x = -0.1f;
		}
		else if(lightPos.x < -8.0f) {
			lightAcceleration.x = 0.1f;
		}

		if (lightPos.y > 4.5f/2.0f) {
			lightAcceleration.y = -0.1f;
		}
		else if (lightPos.y < -4.5f/2.0f) {
			lightAcceleration.y = 0.1f;
		}

		lightPos.x += lightAcceleration.x;
		lightPos.y += lightAcceleration.y;


		shader.setUniform2f("light_position", lightPos);
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(-4.0f, 0.0f, 0.0f)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4.0f, 0.0f, 0.0f)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		vao.unbind();
		renderer.update();
	}

	return 0;
}