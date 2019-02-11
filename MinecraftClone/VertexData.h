#pragma once
#include "Vertex.h"

struct VertexData

{
	VertexData(std::vector<Vertex> verts, std::vector<unsigned int> inds): vertices(verts), indices(inds)

	{

	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};