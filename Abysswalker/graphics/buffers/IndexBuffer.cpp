#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
{
	this->count = count;

	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint IndexBuffer::getCount() const
{
	return count;
}