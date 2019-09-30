#pragma once
#include "Mesh.h"
#include <vector>
#include <map>
#include "../../resources/resourcemanager/ResourceManager.h"
#include "../../resources/resourcetypes/Mesh.h"

namespace abyssengine {
	namespace math {
		namespace Icosahedron
		{
			std::map<unsigned __int64, size_t> middlePointCache;

			// Creates new vertex and returns index of new point between p1 and p2. (Indices index)
			int getMiddlePoint(Mesh* mesh, const size_t& p1, const size_t& p2)
			{
				bool firstIsSmaller = p1 < p2;
				unsigned __int64 smallerIndex = firstIsSmaller ? p1 : p2;
				unsigned __int64 biggerIndex = firstIsSmaller ? p2 : p1;
				unsigned __int64 key = (smallerIndex << 32) + biggerIndex;
				
				std::map<unsigned __int64, size_t>::iterator it;
				if ((it = middlePointCache.find(key)) != middlePointCache.end())
				{
					return it->second;
				}

				Mesh::VertexData vp1 = mesh->vertices[p1];
				Mesh::VertexData vp2 = mesh->vertices[p2];

				Mesh::VertexData midpoint = Mesh::VertexData(math::vec3f( 
					(vp1.position.x + vp2.position.x) / 2.0f, 
					(vp1.position.y + vp2.position.y) / 2.0f, 
					(vp1.position.z + vp2.position.z) / 2.0f).normalize());

				mesh->vertices.push_back(midpoint);
				middlePointCache[key] = mesh->vertices.size() - 1;

				return mesh->vertices.size() - 1;
			}

			std::vector<Mesh*> meshes;

			Mesh* generateFirst()
			{
				if (meshes.size() == 0)
				{
					Mesh* mesh = new Mesh();

					// Vertices
					float t = (1.0f + sqrt(5.0f)) / 2.0f;

					//float s = sqrt((5.0f - sqrt(5.0f)) / 10.0f);
					//float t = sqrt((5.0f + sqrt(5.0f)) / 10.0f);

					mesh->vertices.reserve(12);

					mesh->vertices.push_back(math::vec3f(-1.0f, t, 0.0f).normalize());
					mesh->vertices.push_back(math::vec3f(1.0f, t, 0.0f).normalize());
					mesh->vertices.push_back(math::vec3f(-1.0f, -t, 0.0f).normalize());
					mesh->vertices.push_back(math::vec3f(1.0f, -t, 0.0f).normalize());

					mesh->vertices.push_back(math::vec3f(0.0f, -1.0f, t).normalize());
					mesh->vertices.push_back(math::vec3f(0.0f, 1.0f, t).normalize());
					mesh->vertices.push_back(math::vec3f(0.0f, -1.0f, -t).normalize());
					mesh->vertices.push_back(math::vec3f(0.0f, 1.0f, -t).normalize());

					mesh->vertices.push_back(math::vec3f(t, 0.0f, -1.0f).normalize());
					mesh->vertices.push_back(math::vec3f(t, 0.0f, 1.0f).normalize());
					mesh->vertices.push_back(math::vec3f(-t, 0.0f, -1.0f).normalize());
					mesh->vertices.push_back(math::vec3f(-t, 0.0f, 1.0f).normalize());

					// Indices
					mesh->indices.reserve(60);

					mesh->indices.push_back(0); mesh->indices.push_back(11); mesh->indices.push_back(5);
					mesh->indices.push_back(0); mesh->indices.push_back(5); mesh->indices.push_back(1);
					mesh->indices.push_back(0); mesh->indices.push_back(1); mesh->indices.push_back(7);
					mesh->indices.push_back(0); mesh->indices.push_back(7); mesh->indices.push_back(10);
					mesh->indices.push_back(0); mesh->indices.push_back(10); mesh->indices.push_back(11);

					mesh->indices.push_back(1); mesh->indices.push_back(5); mesh->indices.push_back(9);
					mesh->indices.push_back(5); mesh->indices.push_back(11); mesh->indices.push_back(4);
					mesh->indices.push_back(11); mesh->indices.push_back(10); mesh->indices.push_back(2);
					mesh->indices.push_back(10); mesh->indices.push_back(7); mesh->indices.push_back(6);
					mesh->indices.push_back(7); mesh->indices.push_back(1); mesh->indices.push_back(8);

					mesh->indices.push_back(3); mesh->indices.push_back(9); mesh->indices.push_back(4);
					mesh->indices.push_back(3); mesh->indices.push_back(4); mesh->indices.push_back(2);
					mesh->indices.push_back(3); mesh->indices.push_back(2); mesh->indices.push_back(6);
					mesh->indices.push_back(3); mesh->indices.push_back(6); mesh->indices.push_back(8);
					mesh->indices.push_back(3); mesh->indices.push_back(8); mesh->indices.push_back(9);

					mesh->indices.push_back(4); mesh->indices.push_back(9); mesh->indices.push_back(5);
					mesh->indices.push_back(2); mesh->indices.push_back(4); mesh->indices.push_back(11);
					mesh->indices.push_back(6); mesh->indices.push_back(2); mesh->indices.push_back(10);
					mesh->indices.push_back(8); mesh->indices.push_back(6); mesh->indices.push_back(7);
					mesh->indices.push_back(9); mesh->indices.push_back(8); mesh->indices.push_back(1);

					resources::ResourceManager::getInstance()->submitGeneratedResource(new resources::MeshResource(std::string("generated/icosahedron:0"), *mesh));
					meshes.push_back(mesh);
				}

				return meshes.at(0);
			}

			Mesh* generate(const size_t& subdivision)
			{
				if (subdivision == 0) 
					return generateFirst();
				else if (meshes.size() > subdivision)
					return meshes.at(subdivision);

				middlePointCache.clear();

				// For every recursion level
					// Create a new empty vector of indices
					// For every face (3 indices) in original list of indices
						// Find 3 points that define new faces (getMiddlePoint)
						// Add faces into the new vector
					// Swap the two vectors of indices

				Mesh* oldMesh = generate(subdivision - 1);
				Mesh* newMesh = new Mesh();
				newMesh->vertices = oldMesh->vertices;

				for (size_t i = 0; i < subdivision; i++)
				{
					std::vector<size_t> newIndices;
					for (size_t j = 0; j < oldMesh->indices.size() / 3; j++) // For every face
					{
						// Add 3 new vertices
						size_t a = getMiddlePoint(newMesh, oldMesh->indices[j * 3 + 0], oldMesh->indices[j * 3 + 1]);
						size_t b = getMiddlePoint(newMesh, oldMesh->indices[j * 3 + 1], oldMesh->indices[j * 3 + 2]);
						size_t c = getMiddlePoint(newMesh, oldMesh->indices[j * 3 + 2], oldMesh->indices[j * 3 + 0]);

						// Add 12 new indices
						newIndices.push_back(oldMesh->indices[j * 3 + 0]); 	newIndices.push_back(a); newIndices.push_back(c);
						newIndices.push_back(oldMesh->indices[j * 3 + 1]); 	newIndices.push_back(b); newIndices.push_back(a);
						newIndices.push_back(oldMesh->indices[j * 3 + 2]); 	newIndices.push_back(c); newIndices.push_back(b);
						newIndices.push_back(a); newIndices.push_back(b); newIndices.push_back(c);
					}
					newMesh->indices = newIndices;
				}

				//for (size_t i = 0; i < oldMesh->indices.size() / 3; i++)
				//{
				//	newMesh->indices.push_back(oldMesh->indices[i * 3 + 0]);
				//	newMesh->indices.push_back(oldMesh->indices[i * 3 + 1]);
				//	newMesh->indices.push_back(oldMesh->indices[i * 3 + 2]);
				//}

				meshes.push_back(newMesh);

				resources::ResourceManager::getInstance()->submitGeneratedResource(new resources::MeshResource(std::string("generated/icosahedron:") + std::to_string(subdivision), *newMesh));

				return newMesh;
			}
		};
	}
}