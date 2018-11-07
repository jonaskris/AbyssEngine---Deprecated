#include "WorldScene.h"
#include "../entities/Entity.h"
#include "../math/mat4.h"
#include "../graphics/shaders/Shader.h"
#include <iostream>

WorldScene::WorldScene()
{

	std::cout << "BOI" << std::endl;
	mat4 ortho = mat4::orthographic(-8.0f, 8.0f, 4.5f, -4.5f, -1.0f, 1.0f);

	Shader* shader = new Shader("../graphics/shaders/basic.vert", "../graphics/shaders/basic.frag");
	shader->enable();
	shader->setUniformMat4("pr_matrix", ortho);
	shader->disable();

	setShader(shader);

	std::cout << "Shader: " << getShader() << std::endl;
}

WorldScene::~WorldScene()
{

}
