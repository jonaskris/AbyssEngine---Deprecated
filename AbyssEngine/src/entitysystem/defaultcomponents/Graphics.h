#pragma once
#include "../components/Component.h"
#include "../../resources/ResourceManager.h"
#include "../../math/linalg.h"
#include "../../math/MathSemanticTypes.h"

namespace abyssengine {

	template <typename ComponentType>
	using Component = entitysystem::Component<ComponentType>;

	template <typename GraphicsComponentType>
	struct Graphics_Component : public Component<GraphicsComponentType>
	{

	};

	struct Point_Component : public Graphics_Component<Point_Component>
	{
		struct VertexData
		{
			math::vec3f vertex;
			math::vec4f color;

			VertexData(const math::vec3f& vertex, const math::vec4f& color) : vertex(vertex), color(color) {};
			VertexData() : vertex(math::vec3f{ 0.0f, 0.0f, 0.0f }), color(math::vec4f( 1.0f, 1.0f, 1.0f, 1.0f )) {};
		} vertex;

		Point_Component() {};
		Point_Component(const math::vec3f& vertex, const math::vec4f& color) : vertex(vertex, color) {};
	};

	struct Line_Component : public Graphics_Component<Line_Component>
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

	struct Sprite_Component : public Graphics_Component<Sprite_Component>
	{
		size_t textureId;
		struct VertexData 
		{
			math::vec3f vertex;
			math::vec4f color;
			math::vec2f uv;
	
			VertexData(const math::vec3f& vertex, const math::vec4f& color, const math::vec2f& uv) : vertex(vertex), color(color), uv(uv) {};
			VertexData() : vertex(math::vec3f{ 0.0f, 0.0f, 0.0f }), color(math::vec4f{ 1.0f, 1.0f, 1.0f, 1.0f }), uv(math::vec2f{ 0.0f, 0.0f }) {};
		} vertex[4];
		
		Sprite_Component(const size_t& textureId, const float& scale) : textureId(textureId), 
			vertex{
				{ math::vec3f{-scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec4f{ 1.0f, 1.0f, 1.0f, 1.0f }, math::vec2f{ 0.0f, 0.0f } },	// Bottom left
				{ math::vec3f{ scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec4f{ 1.0f, 1.0f, 1.0f, 1.0f }, math::vec2f{ 1.0f, 0.0f } },	// Bottom right
				{ math::vec3f{ scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec4f{ 1.0f, 1.0f, 1.0f, 1.0f }, math::vec2f{ 1.0f, 1.0f } },	// Top right
				{ math::vec3f{-scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec4f{ 1.0f, 1.0f, 1.0f, 1.0f }, math::vec2f{ 0.0f, 1.0f } }	// Top left
			}
		{};

		Sprite_Component(const size_t& textureId, const QuadVec<math::vec2f>& uv, const float& scale) : textureId(textureId),
			vertex{
				{ math::vec3f{-scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec4f{ 1.0f, 1.0f, 1.0f, 1.0f }, uv.vec0 },	// Bottom left
				{ math::vec3f{ scale / 2.0f, -scale / 2.0f, 0.0f}, math::vec4f{ 1.0f, 1.0f, 1.0f, 1.0f }, uv.vec1 },	// Bottom right
				{ math::vec3f{ scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec4f{ 1.0f, 1.0f, 1.0f, 1.0f }, uv.vec2 },	// Top right
				{ math::vec3f{-scale / 2.0f,  scale / 2.0f, 0.0f}, math::vec4f{ 1.0f, 1.0f, 1.0f, 1.0f }, uv.vec3 }	// Top left
		}
		{};

		Sprite_Component(const TextureAtlas* textureAtlas, const size_t& index, const float& scale) : Sprite_Component(textureAtlas->getTextureId(), textureAtlas->getUv(index), scale) {};

		Sprite_Component(const std::string& textureAtlas, const size_t& index, const float& scale) : Sprite_Component(ResourceManager::getInstance()->getResource<TextureAtlas>(textureAtlas), index, scale) {};
	};

	struct Camera_Component : public Component<Camera_Component>
	{
		math::vec3f lookAt;
		math::vec3f lookFrom;

		math::mat4f perspective;
		math::mat4f viewMatrix;

		float fov;
		float aspectRatio;
		float near;
		float far;

		Camera_Component(const float& fov, const float& aspectRatio, const float& near, const float& far) :
			lookAt(math::vec3f{ 0.0f, 0.0f, 0.0f }),
			lookFrom(math::vec3f{ 0.0f, 0.0f, 1.0f }),
			fov(fov),
			aspectRatio(aspectRatio),
			near(near),
			far(far),
			perspective(math::mat4f::perspective(fov, aspectRatio, near, far)),
			viewMatrix(math::mat4f::viewMatrix(lookFrom, lookAt, math::vec3f{ 0, 1, 0 })) {}
	};
}