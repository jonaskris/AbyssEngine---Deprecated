#pragma once
#include "../components/Component.h"
#include "../../resources/resourcemanager/ResourceManager.h"
#include "../../math/linalg.h"
#include "../../math/Semantics.h"
#include "../../resources/resourcetypes/TextureAtlas.h"
#include "../../math/geometry/Mesh.h"

namespace abyssengine {
	namespace entitysystem {
		struct Point_Component : public Component<Point_Component>
		{
			struct VertexData
			{
				math::vec3f vertex;
				math::vec4f color;

				VertexData(const math::vec3f& vertex, const math::vec4f& color) : vertex(vertex), color(color) {};
				VertexData() : vertex(math::vec3f{ 0.0f, 0.0f, 0.0f }), color(math::vec4f(1.0f, 1.0f, 1.0f, 1.0f)) {};
			} vertex;

			Point_Component() {};
			Point_Component(const math::vec3f& vertex, const math::vec4f& color) : vertex(vertex, color) {};
		};

		struct Line_Component : public Component<Line_Component>
		{
			struct VertexData
			{
				math::vec3f vertex;
				math::vec4f color;

				VertexData(const math::vec3f& vertex, const math::vec4f& color) : vertex(vertex), color(color) {};
				VertexData() : vertex(math::vec3f{ 0.0f, 0.0f, 0.0f }), color(math::vec4f(1.0f, 1.0f, 1.0f, 1.0f)) {};
			} vertex[2];

			Line_Component() {};
			Line_Component(const math::vec3f& vertex0, const math::vec3f& vertex1, const math::vec4f& color0, const math::vec4f& color1) : vertex{ {vertex0, color0}, {vertex1, color1 } } {};
			Line_Component(const math::vec3f& vertex0, const math::vec3f& vertex1, const math::vec4f& color) : vertex{ {vertex0, color}, {vertex1, color } } {};
		};

		struct Sprite_Component : public Component<Sprite_Component>
		{
			size_t textureId;
			struct VertexData
			{
				math::vec3f vertex;
				math::vec3f normal;
				math::vec2f uv;

				VertexData(const math::vec3f& vertex, const math::vec3f& normal, const math::vec2f& uv) : vertex(vertex), normal(normal), uv(uv) {};
				VertexData() : vertex(math::vec3f{ 0.0f, 0.0f, 0.0f }), normal(math::vec3f{ 0.0f, 0.0f, 1.0f }), uv(math::vec2f{ 0.0f, 0.0f }) {};
			} vertex[4];

			Sprite_Component(const size_t& textureId, const float& scale) : textureId(textureId),
				vertex{
					{ math::vec3f{-scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec3f{ 0.0f, 0.0f, 1.0f }, math::vec2f{ 0.0f, 0.0f } },	// Bottom left
					{ math::vec3f{-scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec3f{ 0.0f, 0.0f, 1.0f }, math::vec2f{ 0.0f, 1.0f } },	// Top left
					{ math::vec3f{ scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec3f{ 0.0f, 0.0f, 1.0f }, math::vec2f{ 1.0f, 1.0f } },	// Top right
					{ math::vec3f{ scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec3f{ 0.0f, 0.0f, 1.0f }, math::vec2f{ 1.0f, 0.0f } }		// Bottom right
			}
			{};

			Sprite_Component(const size_t& textureId, const std::vector<math::vec2f>& uv, const float& scale) : textureId(textureId),
				vertex{
					{ math::vec3f{-scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec3f{ 0.0f, 0.0f, 1.0f }, uv.at(0) },	// Bottom left
					{ math::vec3f{-scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec3f{ 0.0f, 0.0f, 1.0f }, uv.at(3) },	// Top left
					{ math::vec3f{ scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec3f{ 0.0f, 0.0f, 1.0f }, uv.at(2) },	// Top right
					{ math::vec3f{ scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec3f{ 0.0f, 0.0f, 1.0f }, uv.at(1) }	// Bottom right
			}
			{};

			Sprite_Component(const resources::TextureAtlas* textureAtlas, const size_t& index, const float& scale) : Sprite_Component(textureAtlas->getTextureID(), textureAtlas->getUV(index), scale) {};
		};

		//struct Transform_Component : public Component<Transform_Component>
		//{
		//	math::mat4f transform = math::mat4f::identity();
		//
		//	template <typename Transform>
		//	void unpackRenderableOptions(const Transform& transform)
		//	{
		//		static_assert(std::is_base_of <math::Transform, Transform>::value, "Transform must be of type math::transform!");
		//		math::mat4f test = transform.toMatrix();
		//		this->transform = test * this->transform;
		//	}
		//
		//	template <typename Transform, typename... Transforms>
		//	void unpackRenderableOptions(const Transform& transform, const Transforms& ... transforms)
		//	{
		//		static_assert(std::is_base_of <math::Transform, Transform>::value, "Transform must be of type math::transform!");
		//		math::mat4f test = transform.toMatrix();
		//		this->transform = test * this->transform;
		//		unpackRenderableOptions(transforms...);
		//	}
		//
		//	template <typename... Transforms>
		//	Transform_Component(Transforms... transforms)
		//	{
		//		if constexpr (sizeof...(Transforms) > 0)
		//			unpackRenderableOptions(transforms...);
		//	};
		//};

		struct Camera_Component : public Component<Camera_Component>
		{
			math::vec3f position = math::vec3f(0.0f, 0.0f, 3.0f);

			float pitch = 0.0f, yaw = 90.0f, roll = 0.0f;
			math::vec3f front;
			math::vec3f up = math::vec3f(0.0f, 0.0f, 1.0f);

			math::mat4f view;

			Camera_Component() { update(); };

			void update()
			{
				front.x = cos(math::toRadians(pitch)) * cos(math::toRadians(yaw));
				front.y = cos(math::toRadians(pitch)) * sin(math::toRadians(yaw));
				front.z = sin(math::toRadians(pitch));

				view = math::mat4f::viewMatrix(position, position + front, up);
			}
		};

		struct Mesh_Component : public Component<Mesh_Component>
		{
			std::string meshPath; // Path to resource which contains the mesh itself
			GLuint textureID;
			math::vec3f position;
			math::vec3f scale; 
			math::vec4f rotation;
			bool flipNormals;

			Mesh_Component(
				const std::string& meshPath, 
				const GLuint& textureID, 
				const math::vec3f& position, 
				const math::vec3f& scale, 
				const bool& flipNormals = false, 
				const math::vec4f& rotation = math::vec4f(0.0f, 0.0f, 0.0f, 0.0f)) 
				: meshPath(meshPath), textureID(textureID), position(position), scale(scale), flipNormals(flipNormals), rotation(rotation) {};
		};
	}
}

/*
	Når mesher lastes, blir de gitt en id (Kanskje også en type streng/navn).
	Mesh componenter lagrer denne id'en, og en transform.
	Når mesher skal tegnes, bruk instancing for hvert mesh, og sett ett uniform array med X transforms. 
	Instancing skal da bruke transform uniformen i arrayet instanceid % (Antall tegnede mesh per instance drawcall).
	Så kan man sette antall tegnede mesh per instance drawcall ut ifra hva som er raskest.
*/