#pragma once
#include "Chunk.h"
#include "Renderer.h"
#include "Cube.h"
#include "PerlinNoise.h"
#include "Camera.h"
#include <algorithm>

class World

{
public:
	World(int nChunks, int seed, const Camera& cam, Renderer& render);
	~World();

	void getChunkHeightMap(std::vector<float>& chunkHeight, float x, float z);
	void loadChunk(float x, float z);
	void updateChunks();
	void genChunks();
	void cullChunks();
	void getChunksShouldLoad();
	void getChunksShouldUnload();

	void renderChunks();
	std::vector<Chunk> chunks;
private:
	int numChunks;
	int indexDel;
	int numDel;
	std::vector<Chunk> *ptrChunks;
	std::vector<glm::vec3> chunksShouldBeLoaded;
	std::vector<int> chunksShouldBeUnloaded;
	const Camera& camera;
	Cube cube;
	Renderer& renderer;
	Texture texture;
	PerlinNoise perlinNoise;
	TextureAtlas textureAtlas;
	std::vector<Chunk>::iterator iter;
	TextureAtlas* ptrTex;
	Cube* ptrCube;

};