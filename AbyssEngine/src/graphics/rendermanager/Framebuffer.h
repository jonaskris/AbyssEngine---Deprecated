#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Buffer.h"
#include "../VertexAttributeLocations.h"

namespace abyssengine {
	namespace graphics {
		class Framebuffer
		{
		public:
			size_t id;
			Buffer* position;
			Buffer* normal;
			Buffer* albedoSpecular;
			Buffer* depth;
		public:
			Framebuffer(const size_t& width, const size_t& height)
			{
				glGenFramebuffers(1, &id);
				glBindFramebuffer(GL_FRAMEBUFFER, id);

				// Color attachments
				position = new Buffer(width, height, Buffer::Type::POSITION);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, position->getID(), 0);
				normal = new Buffer(width, height, Buffer::Type::NORMAL);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normal->getID(), 0);
				albedoSpecular = new Buffer(width, height, Buffer::Type::ALBEDOSPECULAR);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, albedoSpecular->getID(), 0);

				unsigned int attachments[3] = {
					GL_COLOR_ATTACHMENT0,
					GL_COLOR_ATTACHMENT1,
					GL_COLOR_ATTACHMENT2 };

				glDrawBuffers(3, attachments);

				// Depth attachment
				depth = new Buffer(width, height, Buffer::Type::DEPTH);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth->getID());

				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
					std::cout << "Framebuffer is not complete!" << std::endl; /// Todo: log

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			~Framebuffer()
			{
				glDeleteFramebuffers(1, &id);
			}

			void bind() { glBindFramebuffer(GL_FRAMEBUFFER, id); };
			void unBind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); };
			size_t getID() const { return id; }
		};
	}
}