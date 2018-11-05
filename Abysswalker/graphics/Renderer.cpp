#include <iostream>
#include "Renderer.h"
#include "Window.h"

Renderer::Renderer()
{
	width = 1920 / 2;
	height = 1080 / 2;
	window = new Window("Abysswalker", width, height);
}

Renderer::~Renderer()
{
	delete window;
}

bool Renderer::windowClosed() {
	return window->closed();
}

void Renderer::render() {
	window->clear();
	window->update();
}

void Renderer::clear() {
	window->clear();
}

void Renderer::update() {
	window->update();
}