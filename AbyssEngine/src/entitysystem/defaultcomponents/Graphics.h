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

		struct Target_Camera : public Component<Target_Camera>
		{
			math::vec3f position;
			size_t entityIdTarget;
			math::vec3f up = math::vec3f(0.0f, 0.0f, 1.0f);

			math::mat4f view;

			Target_Camera(const math::vec3f& position, const size_t& entityIdTarget) : position(position), entityIdTarget(entityIdTarget) { };

		public:
			void update(const math::vec3f& lookat)
			{
				view = math::mat4f::viewMatrix(position, lookat, up);
			}

			void update(const math::vec4f& lookat) { update(math::toVec3f(lookat)); }
			size_t getEntityIdTarget() { return entityIdTarget; }
		};

		struct Mesh_Component : public Component<Mesh_Component>
		{
			std::string meshPath;
			bool flipNormals;

			Mesh_Component(const std::string& meshPath, const bool& flipNormals = false ) : meshPath(meshPath), flipNormals(flipNormals) {};
		};

		struct Texture_Component : public Component<Texture_Component>
		{
			size_t textureId;

			Texture_Component(const size_t& textureId) : textureId(textureId) {};

			size_t getTextureid() const { return textureId; }
		};
	}
}