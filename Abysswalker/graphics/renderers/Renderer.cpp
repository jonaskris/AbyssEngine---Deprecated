#include <vector>
#include "Renderer.h"
#include <GL/glew.h>
#include "../Window.h"
#include "../shaders/Program.h"
#include "SpriteRenderer.h"
#include "../../math/mat4.h"

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
	SpriteRenderer::init();
}

Renderer::~Renderer()
{
	delete window;
}

bool Renderer::windowClosed() {
	return window->closed();
}

void Renderer::render(std::vector<GSSComponent*>* gssComponents)
{
	window->clear();
	SpriteRenderer::render(gssComponents, mat4::identity(), Program::getProgram(Program::SPRITE));
	window->update();
}

void Renderer::clear() { // Temporary
	window->clear();
}

void Renderer::update() { // Temporary
	window->update();
}