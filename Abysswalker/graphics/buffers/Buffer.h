#pragma once
#include <GL/glew.h>

class Buffer
{
private:
	GLuint bufferID;
	GLuint componentCount;
public:
	Buffer(GLfloat* data, GLsizei count, GLsizei componentCount);

	void bind() const;
	void unbind() const;

	GLuint getComponentCount() const;
};