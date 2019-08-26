#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "../Window.h"
#include "../../Defines.h"
#include "Framebuffer.h"
#include "../../resources/resourcemanager/ResourceManager.h"
#include "../../resources/resourcetypes/Program.h"
#include "../../resources/resourcetypes/Texture.h"
#include "../../entitysystem/entitymanager/EntityManager.h"
#include "../../entitysystem/defaultcomponents/Graphics.h"
#include "../../entitysystem/defaultcomponents/Spatial.h"
#include "../../scenes/Scene.h"
#include "../VertexAttributeLocations.h"

namespace abyssengine {
	namespace graphics {
		void renderQuad()
		{
			static GLuint VAO = 0;
			static GLuint VBO = 0;
			static bool initialized = false;

			static struct VertexData
			{
				math::vec3f vertex;
				math::vec2f uv;
			} vertexData[]
			{
				{math::vec3f{-1.0f, -1.0f, 0.0f}, math::vec2f{ 0.0f, 0.0f } },
				{math::vec3f{-1.0f,  1.0f, 0.0f}, math::vec2f{ 0.0f, 1.0f } },
				{math::vec3f{ 1.0f,  1.0f, 0.0f}, math::vec2f{ 1.0f, 1.0f } },
				{math::vec3f{ 1.0f, -1.0f, 0.0f}, math::vec2f{ 1.0f, 0.0f } }
			};

			if (!initialized)
			{
				initialized = true;
				glGenVertexArrays(1, &VAO);
				glGenBuffers(1, &VBO);

				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);

				// Vertex
				glEnableVertexAttribArray(InVertexAttributePositions::in_position);
				glVertexAttribPointer(InVertexAttributePositions::in_position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, VertexData::vertex)));
				// Texture coordinate
				glEnableVertexAttribArray(InVertexAttributePositions::in_uv);
				glVertexAttribPointer(InVertexAttributePositions::in_uv, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, VertexData::uv)));

				glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData[0], GL_STATIC_DRAW);
			}
			glBindVertexArray(VAO);

			glDrawArrays(GL_QUADS, 0, 4);

			glBindVertexArray(0);
		}

		class RenderManager
		{
		private:
			Window* window = nullptr;
			Framebuffer* framebuffer = nullptr;
		public:
			RenderManager()
			{
				int width = (int)(SCREEN_WIDTH / (1.5f));
				int height = (int)(SCREEN_HEIGHT / (1.5f));

				if (!glfwInit())
					std::cout << "Failed to initialize GLFW!" << std::endl;

				window = new Window(WINDOW_NAME, width, height);

				framebuffer = new Framebuffer(width, height);

				glEnable(GL_DEPTH_TEST);
				//glEnable(GL_BLEND);
				//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glFrontFace(GL_CW);
				glClearColor(1.0f, 0.7f, 0.3f, 1.0f);
			};

			~RenderManager() { delete window; };

			bool getWindowClosed() { return window->closed(); }

			void render(const std::vector<Scene*> & scenes)
			{
				// 1. geometry pass: render all geometric/color data to g-buffer 

				framebuffer->bind();
				window->clear();
				
				resources::Program& geometryProgram = *resources::ResourceManager::getInstance()->getResource<resources::Program>("GeometryPass.prog");
				geometryProgram.enable();
				
				// Set projection and view matrix
				entitysystem::EntityManager* entitymanager = scenes.at(0)->getEntityManager();
				entitysystem::Camera_Component& camera = entitymanager->getUnitVector<entitysystem::Camera_Component>()->at(0);

				geometryProgram.setUniformMat4("projection", math::mat4f::perspective(FOV, ASPECT_RATIO, NEAR, FAR));
				geometryProgram.setUniformMat4("view", camera.view);
				

				/// Render objects

				geometryProgram.setUniformMat4("model", math::mat4f::scale(math::vec3f(1.0f, 1.0f, 1.0f)));
				
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, resources::ResourceManager::getInstance()->getResource<resources::Texture>("DefaultTexture1.png")->getTextureID());
				GLuint texLoc = glGetUniformLocation(geometryProgram.getID(), "texture_diffuse");
				glUniform1i(texLoc, 0);
				renderQuad();

				/// Render objects
				
				framebuffer->unBind();
				
				// 2. lighting pass: use g-buffer to calculate the scene's lighting.
				window->clear();
				resources::Program& lightingProgram = *resources::ResourceManager::getInstance()->getResource<resources::Program>("LightingPass.prog");
				lightingProgram.enable();
				lightingProgram.setUniform3f("viewPos", camera.position);
				lightingProgram.setUniform1i("fboPosition", 0);
				lightingProgram.setUniform1i("fboNormal", 1);
				lightingProgram.setUniform1i("fboAlbedoSpecular", 2);
				
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, framebuffer->position->getID());
				
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, framebuffer->normal->getID());
				
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, framebuffer->albedoSpecular->getID());
				
				lightingProgram.setUniform3f("lights[0].Position", math::vec3f(0.0f, 0.0f, 0.1f));
				lightingProgram.setUniform3f("lights[0].Color", math::vec3f(0.5f, 0.5f, 0.5f));
				float constant = 1.0f;
				float linear = 1.0f;
				float quadratic = 1.0f;
				lightingProgram.setUniform1f("lights[0].Constant", constant);
				lightingProgram.setUniform1f("lights[0].Linear", linear);
				lightingProgram.setUniform1f("lights[0].Quadratic", quadratic);

				//window->clear();
				//resources::Program& simpleTextureProgram = *resources::ResourceManager::getInstance()->getResource<resources::Program>("SimpleTexture.prog");
				//simpleTextureProgram.enable();
				//
				////simpleTextureProgram.setUniformMat4("projection", math::mat4f::orthographic(-0.5, 0.5, -0.5, 0.5f, -10.0f, 20.0f));
				//simpleTextureProgram.setUniformMat4("projection", math::mat4f::perspective(FOV, ASPECT_RATIO, NEAR, FAR));
				//simpleTextureProgram.setUniformMat4("view", math::mat4f::viewMatrix(math::vec3f(0.0f, 0.0f, 10.0f), math::vec3f(0.0f, 0.0f, 0.0f), math::vec3f(0.0f, 1.0f, 0.0f)));
				//simpleTextureProgram.setUniformMat4("model", math::mat4f::scale(math::vec3f(2.0f, 2.0f, 2.0f)));
				//
				//glActiveTexture(GL_TEXTURE0);
				//glBindTexture(GL_TEXTURE_2D, resources::ResourceManager::getInstance()->getResource<resources::Texture>("DefaultTexture1.png")->getTextureID());
				//GLuint texLoc = glGetUniformLocation(simpleTextureProgram.getID(), "tex");
				//glUniform1i(texLoc, 0);
				////glBindTexture(GL_TEXTURE_2D, framebuffer->depth->getID());

				renderQuad();

				lightingProgram.disable();
				window->update();
			}
		};
	}
}