#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace abyssengine {
	namespace graphics {
		class Buffer
		{
		public:
			const enum Type { POSITION, NORMAL, ALBEDOSPECULAR, DEPTH };
		private:
			const size_t width, height;
			size_t id = 0;
		public:
			Buffer(const size_t& width, const size_t& height, const Type& type) : width(width), height(height)
			{
				switch (type)
				{
				case POSITION:
					glGenTextures(1, &id);

					glBindTexture(GL_TEXTURE_2D, id);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					break;
				case NORMAL:
					glGenTextures(1, &id);

					glBindTexture(GL_TEXTURE_2D, id);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					break;
				case ALBEDOSPECULAR:
					glGenTextures(1, &id);

					glBindTexture(GL_TEXTURE_2D, id);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					break;
				case DEPTH:
					glGenRenderbuffers(1, &id);
					glBindRenderbuffer(GL_RENDERBUFFER, id);
					glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
					break;
				}

			}

			void bind() { glBindTexture(GL_TEXTURE_2D, id); };
			void unBind() { glBindTexture(GL_TEXTURE_2D, 0); };
			size_t getID() const { return id; }
		};
	}
}