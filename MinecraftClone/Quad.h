#pragma once
#include "Header.h"
#include "Texture.h"
#include "Entity.h"
#include "Vertex.h"

struct Quad

{
public:

	Quad(float width, float height, float x, float y, float z);
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	//float vertices[20];
	//unsigned int indices[6];
	Entity entity;
	Texture texture;
};