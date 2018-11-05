#pragma once
#include <GL/glew.h>
#include <vector>
#include "Buffer.h"

class VertexArray
{
private:
	GLuint arrayID;
	std::vector<Buffer*> buffers;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(Buffer* buffer, GLuint index);
	void bind() const;
	void unbind() const;
};

