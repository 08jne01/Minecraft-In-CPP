#include "Cube.h"

Cube::Cube(float width, float height, float depth, float x, float y, float z):
	texture("Resources/Textures/Blocks.png", GL_TEXTURE_2D)

{
	entity.position.x = x;
	entity.position.y = y;
	entity.position.z = z;
	//CCW
	//BACk
	verticesFaces.push_back({
		Vertex({-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}), //0 1 2, 2 1 3
		Vertex({0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}),
		Vertex({-0.5f,0.5f,-0.5f}, {1.0f, 0.0f}),
		Vertex({0.5f, 0.5f, -0.5f}, {0.0f, 0.0f}), });
	//Front
	verticesFaces.push_back({
		Vertex({-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f}), //0 1 2, 2 1 3 //Reverse
		Vertex({0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}),
		Vertex({-0.5f,0.5f,0.5f}, {1.0f, 0.0f}),
		Vertex({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}), });
	//Left
	verticesFaces.push_back({
		Vertex({-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}), //0 1 3, 3 1 2
		Vertex({-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}),
		Vertex({-0.5f,0.5f,-0.5f}, {1.0f, 0.0f}),
		Vertex({-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}), });
	//Right
	verticesFaces.push_back({
		Vertex({0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}), //0 1 2, 2 1 3
		Vertex({0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}),
		Vertex({0.5f, 0.5f,-0.5f}, {1.0f, 0.0f}),
		Vertex({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}), });
	//Top
	verticesFaces.push_back({
		Vertex({-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}), //0 1 2, 2 1 3
		Vertex({0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}),
		Vertex({-0.5f,0.5f, 0.5f}, {1.0f, 0.0f}),
		Vertex({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}), });
	//Bottom
	verticesFaces.push_back({
		Vertex({-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}), //0 3 2, 2 3 1
		Vertex({0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}),
		Vertex({-0.5f,-0.5f,0.5f}, {1.0f, 0.0f}),
		Vertex({0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}), });

	std::vector<unsigned int> vec1 = {
		0, 1, 2,
		2, 1, 3,
	};

	std::vector<unsigned int> vec2 = {
		0, 3, 2,
		2, 3, 1
	};

	std::vector<unsigned int> vec3 = {
		3, 1, 2,
		2, 1, 0,
	};

	std::vector<unsigned int> vec4 = {
		1, 3, 2,
		2, 3, 0
	};

	std::vector<unsigned int> vec5 = {

		3, 2, 1,
		1, 2, 0
	};

	indicesFaces.push_back(offVec<unsigned int>(vec3, 0)); //0

	indicesFaces.push_back(offVec<unsigned int>(vec1, 0)); //4 //1

	indicesFaces.push_back(offVec<unsigned int>(vec5, 0)); //... //5

	indicesFaces.push_back(offVec<unsigned int>(vec3, 0));

	indicesFaces.push_back(offVec<unsigned int>(vec3, 0));

	indicesFaces.push_back(offVec<unsigned int>(vec5, 0)); //20 //5

	for (int i = 0; i < verticesFaces.size(); i++)

	{
		for (int j = 0; j < verticesFaces[i].size(); j++)

		{
			vertices.push_back(verticesFaces[i][j]);
		}

		for (int j = 0; j < indicesFaces[i].size(); j++)

		{
			indices.push_back(indicesFaces[i][j]);
		}
	}

}