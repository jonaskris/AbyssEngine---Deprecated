#pragma once
#include <GL/glew.h>

namespace abyssengine {
	class IndexBuffer
	{
	private:
		GLuint bufferID;
		GLuint count;
	public:
		IndexBuffer(GLuint* data, GLsizei count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		GLuint getCount() const;
	};
}