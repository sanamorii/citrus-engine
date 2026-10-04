#pragma once

#include <glad/glad.h>
#include <string>

namespace citrus::gfx {

struct TextureDescription {
	GLenum target = GL_TEXTURE_2D;
	//TODO ...
};

class Texture {
public:
	Texture(const std::string& path);
	//~Texture();
	void ApplyParameters();
	bool LoadTexture();
	unsigned int ID() const { return m_texture; }
private:
	GLuint m_texture;
	const char* m_texturePath;
	int m_width;
	int m_height;
	int m_nrChannels;
};

}