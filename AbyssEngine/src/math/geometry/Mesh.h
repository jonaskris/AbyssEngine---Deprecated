#pragma once
#include <vector>
#include "../Linalg.h"
#include "../../graphics/VertexAttributeLocations.h"

namespace abyssengine {
	namespace math {
		struct Mesh
		{
			struct VertexData
			{
				math::vec3f position;
				math::vec4f color;
				math::vec3f normal;

				VertexData(const math::vec3f& position) : position(position), color(1.0f, 1.0f, 1.0f, 1.0f), normal(position.normalize()) {};
			};
			std::vector<VertexData> vertices;
			std::vector<size_t> indices;

			Mesh() {};

			void draw()
			{
				static bool initialized = false;
				static GLuint VBO;
				static GLuint IBO;
				static GLuint VAO;

				if (!initialized)
				{
					initialized = true;

					/// VBO
						glGenBuffers(1, &VBO);
						glBindBuffer(GL_ARRAY_BUFFER, VBO);
						glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
						glBindBuffer(GL_ARRAY_BUFFER, 0);
					///~VBO

					/// IBO
						glGenBuffers(1, &IBO);
						glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
						glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(size_t) * indices.size(), &indices[0], GL_STATIC_DRAW);
						glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
					///~IBO

					/// VAO
						glGenVertexArrays(1, &VAO);
						glBindVertexArray(VAO);

						/// Bind buffers
							glBindBuffer(GL_ARRAY_BUFFER, VBO);
							glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
						///~Bind buffers

						/// Describe VertexData
							glEnableVertexAttribArray(graphics::InVertexAttributePositions::in_position);
							glVertexAttribPointer(graphics::InVertexAttributePositions::in_position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, VertexData::position)));
						
							glEnableVertexAttribArray(graphics::InVertexAttributePositions::in_color);
							glVertexAttribPointer(graphics::InVertexAttributePositions::in_color, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, VertexData::color)));
						
							glEnableVertexAttribArray(graphics::InVertexAttributePositions::in_normal);
							glVertexAttribPointer(graphics::InVertexAttributePositions::in_normal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, VertexData::normal)));
						///~Describe VertexData

						glBindVertexArray(0);
					///~VAO
				}

				/// Draw
				glBindVertexArray(VAO);				

				glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLvoid*)(0));

				glBindVertexArray(0);
				///~Draw
			}
		};
	}
}