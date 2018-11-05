#pragma once
#include <GL/glew.h>

class IndexBuffer
{
private:
	GLuint bufferID;
	GLuint count;
public:
	IndexBuffer(GLushort* data, GLsizei count);

	void bind() const;
	void unbind() const;
	
	GLuint getCount() const;
};