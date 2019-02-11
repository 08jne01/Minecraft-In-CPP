#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#define BACK 0
#define FRONT 1
#define LEFT 2
#define RIGHT 3
#define TOP 4
#define BOTTOM 5

class TextureAtlas

{
public:

	TextureAtlas();
	void readData(const std::string& filename);

	struct BlockData

	{
		glm::vec2 texCoordsTop;
		glm::vec2 texCoordsSide;
		glm::vec2 texCoordsBottom;
		unsigned char ID;
	};

	BlockData fetchData(unsigned char id);
	glm::vec2 fetchCoords(unsigned char id, int face);

	void printData();

private:
	std::vector<BlockData> blockData;
};