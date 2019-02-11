#pragma once
#include "Entity.h"
#include "Vertex.h"
#include "Cube.h"
#include "GeneralMaths.h"
#include "VertexData.h"
#include "TextureAtlas.h"
#include "Renderer.h"


#define BACK 0
#define FRONT 1
#define LEFT 2
#define RIGHT 3
#define TOP 4
#define BOTTOM 5

class Chunk

{
public:

	Chunk();
	Chunk operator=(const Chunk& ref);
	Chunk(const Chunk& ref);
	Chunk(std::vector<float>* cubeHeight, Cube* cubeRef, TextureAtlas* texAtlas, Entity ent, std::vector<Chunk>* chunksRef);
	~Chunk();
	void buildMesh();
	void addVertices(int i, int j, int k, int face, int index);
	void translateCubeMesh(int i, int j, int k, int index, int face, VertexData& data);
	void deleteBuffers();
	int setAdjacentChunks();
	unsigned char getBlock(int i, int j, int k);
	void setBlock(int i, int j, int k, unsigned char type);
	int adjacent(int face, int i, int j, int k);
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<unsigned char> cubes;
	Entity entity;
	//CubeData cubeData;
	Cube* cube;

	
	std::vector<Chunk>* chunks;
	int deleteBuf;
	int leftChunk;
	int rightChunk;
	int frontChunk;
	int backChunk;


	TextureAtlas* textureAtlas;
	//float vertices[20];
	//unsigned int indices[6];
private:
	int indexIndices;
};