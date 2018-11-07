#include <iostream>
#include "graphics/Renderer.h"
#include <vector>
#include "math/mat4.h"
#include "graphics/shaders/Shader.h"
#include "graphics/buffers/Buffer.h"
#include "graphics/buffers/IndexBuffer.h"
#include "graphics/buffers/VertexArray.h"
#include "entities/components/CComponent.h"
#include "scenes/WorldScene.h"

int main() {
	Renderer renderer; // The renderer must be created before any shader is created, as the renderer initializes glfw, which is used by Shader.h.
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	WorldScene* ws = new WorldScene();

	system("PAUSE");
	return 0;
}