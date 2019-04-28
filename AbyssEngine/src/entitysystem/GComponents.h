#pragma once
#include "entities/components/Component.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/vec4.h"

namespace abyssengine {
	template <typename GraphicsComponentType>
	struct Graphics_Component : public Component<GraphicsComponentType>
	{

	};

	struct Point_Component : public Graphics_Component<Point_Component>
	{
		struct VertexData
		{
			math::vec3 vertex;
			math::vec4 color;

			VertexData(const math::vec3& vertex, const math::vec4& color) : vertex(vertex), color(color) {};
			VertexData() : vertex(math::vec3{ 0.0f, 0.0f, 0.0f }), color(math::vec4( 1.0f, 1.0f, 1.0f, 1.0f )) {};
		} vertex;

		Point_Component() {};
		Point_Component(const math::vec3& vertex, const math::vec4& color) : vertex(vertex, color) {};
	};

	struct Line_Component : public Graphics_Component<Line_Component>
	{
		struct VertexData
		{
			math::vec3 vertex;
			math::vec4 color;

			VertexData(const math::vec3& vertex, const math::vec4& color) : vertex(vertex), color(color) {};
			VertexData() : vertex(math::vec3{ 0.0f, 0.0f, 0.0f }), color(math::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {};
		} vertex[2];

		Line_Component() {};
		Line_Component(const math::vec3& vertex0, const math::vec3& vertex1, const math::vec4& color0, const math::vec4& color1) : vertex{ {vertex0, color0}, {vertex1, color1 } } {};
		Line_Component(const math::vec3& vertex0, const math::vec3& vertex1, const math::vec4& color) : vertex{ {vertex0, color}, {vertex1, color } } {};
	};

	struct Sprite_Component : public Graphics_Component<Sprite_Component>
	{
		unsigned short textureId;
		struct VertexData 
		{
			math::vec3 vertex;
			math::vec4 color;
			math::vec2 uv;
	
			VertexData(const math::vec3& vertex, const math::vec4& color, const math::vec2& uv) : vertex(vertex), color(color), uv(uv) {};
			VertexData() : vertex(math::vec3{ 0.0f, 0.0f, 0.0f }), color(math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }), uv(math::vec2{ 0.0f, 0.0f }) {};
		} vertex[4];
	
		Sprite_Component(const unsigned short& textureId, const float& scale) : 
			textureId(textureId), 
			vertex{
				{ math::vec3{-scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, math::vec2{ 0.0f, 0.0f } },	// Bottom left
				{ math::vec3{ scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, math::vec2{ 1.0f, 0.0f } },	// Bottom right
				{ math::vec3{ scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, math::vec2{ 1.0f, 1.0f } },	// Top right
				{ math::vec3{-scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, math::vec2{ 0.0f, 1.0f } }	// Top left
			}
		{};
	};

	struct SpriteSheet_Component : public Graphics_Component<SpriteSheet_Component>
	{
		unsigned short atlasId;
		unsigned short textureIndex;
		struct VertexData
		{
			math::vec3 vertex;
			math::vec4 color;
			math::vec2 uv;

			VertexData(const math::vec3& vertex, const math::vec4& color, const math::vec2& uv) : vertex(vertex), color(color), uv(uv) {};
			VertexData() : vertex(math::vec3{ 0.0f, 0.0f, 0.0f }), color(math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }), uv(math::vec2{ 0.0f, 0.0f }) {};
		} vertex[4];

		SpriteSheet_Component(const unsigned short& atlasId, const float& scale, const std::vector<math::vec2>& uv) :
			atlasId(atlasId),
			textureIndex(textureIndex),
			vertex{
				{ math::vec3{-scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, uv[0] },	// Bottom left
				{ math::vec3{ scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, uv[1] },	// Bottom right
				{ math::vec3{ scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, uv[2] },	// Top right
				{ math::vec3{-scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, uv[3] }		// Top left
		}
		{};
	};
}