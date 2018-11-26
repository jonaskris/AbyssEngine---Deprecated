#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#include "../math/vec2.h"


#define SPRITE_SIZE 32
#define TEXTURE_ATLAS_PATH std::string("../Resources/TextureAtlases/")

class TextureAtlas
{
public:
	enum Atlas { TESTSHEET, TESTSPRITE, MAX };
	static void loadAtlases();
	static void getTextureCoordinates(int index, Atlas type, std::vector<vec2>* textureCoordinates);
	static TextureAtlas* getAtlas(Atlas type);
	static TextureAtlas* atlases[Atlas::MAX];
private:
	std::string path;
	GLuint textureID;
	GLsizei width, height;
	unsigned int spriteSize;
private:
	float hpcX; // Half pixel correction to avoid bleeding between individual textures
	float hpcY;
	void calculateHPC();
public:
	TextureAtlas(const std::string& path, unsigned int spriteSize);

	void load();

	void getTextureCoordinates(int index, std::vector<vec2>* textureCoordinates);
	GLuint getTextureID();

	void bind() const;
	void unbind() const;

	inline unsigned int getWidth() const;
	inline unsigned int getHeight() const;
private:
	static bool initialized;
	static const std::string atlasPaths[Atlas::MAX];
};