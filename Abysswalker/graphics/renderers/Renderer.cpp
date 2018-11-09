#include <iostream>
#include "Renderer.h"
#include "../Window.h"
#include "../shaders/Program.h"
#include "../../entities/components/gComponent/GSSComponent.h"
#include <chrono>
#include <vector>
#include "../TextureAtlas.h"
#include "SpriteRenderer.h"


Renderer::Renderer()	// The renderer must be created before any shader is created, as the renderer initializes glfw, which is used by Shader.h
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