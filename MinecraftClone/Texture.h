#pragma once
#include "Header.h"
#include <stb/stb_image.h>

class Texture

{
public:

	Texture(const std::string& path, unsigned int typeTex);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

private:

	unsigned int renderID, type;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, bpp;

};