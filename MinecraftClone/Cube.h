#pragma once
#include "Vertex.h"
#include "Texture.h"
#include "Entity.h"
#include "GeneralMaths.h"

struct Cube

{
public:
	Cube(float width, float height, float depth, float x, float y, float z);
	std::vector<Vertex> vertices;
	std::vector<std::vector<Vertex>> verticesFaces;
	std::vector<std::vector<unsigned int>> indicesFaces;
	float ofx, ofy, ofz;
	std::vector<unsigned int> indices;
	//float vertices[20];
	//unsigned int indices[6];
	Entity entity;
	Texture texture;
};