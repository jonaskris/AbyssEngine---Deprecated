#include <vector>
#include "Renderer.h"
#include <GL/glew.h>
#include "../Window.h"
#include "../shaders/Program.h"
#include "SpriteRenderer.h"
#include "../../math/mat4.h"
#include "../../entities/Entity.h"

Renderer* Renderer::instance;

Renderer* Renderer::getInstance() 
{
	if (!instance)
	{
		std::cout << "Initialized Renderer singleton!" << std::endl;
		instance = new Renderer();
		return instance;
	}
	return instance;
}

Renderer::Renderer()
{
	width = 1920 / 2;
	height = 1080 / 2;
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
	}
	window = new Window("Abysswalker", width, height);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Program::loadPrograms();
	TextureAtlas::loadAtlases();
}

Renderer::~Renderer()
{
	delete window;
}

bool Renderer::windowClosed() {
	return window->closed();
}

void Renderer::render(std::vector<Entity*>& entities)
{
	window->clear();
	std::vector<GSSComponent*> components;
	for (size_t i = 0; i < entities.size(); i++) 
	{
		std::vector<GComponent*> GComponents = entities.at(i)->getGComponents();
		for (size_t j = 0; j < GComponents.size(); j++) 
		{
			components.push_back((GSSComponent*)GComponents.at(j));
		}
	}

	SpriteRenderer::getInstance()->render(components, mat4::identity());
	window->update();
}

void Renderer::clear() { // Temporary
	window->clear();
}

void Renderer::update() { // Temporary
	window->update();
}