#pragma once
#include "Header.h"

struct Vertex

{
	Vertex(glm::vec3 pos, glm::vec2 tex)

	{
		position = pos;
		textureCoords = tex;
	}

	glm::vec3 position;
	glm::vec2 textureCoords;
};