#include "World.h"

World::World(int nChunk, int seed, const Camera& cam, Renderer& render) :
	texture("Resources/Textures/Blocks.png", GL_TEXTURE_2D), cube(1.0, 1.0, 1.0, 0.0, 0.0, 0.0), numChunks(nChunk),
	perlinNoise(100, 100, seed, 100.0, 0.5), camera(cam), renderer(render), numDel(0)

{
	ptrChunks = &this->chunks;
	textureAtlas.readData("Resources/Database/BlocksTextureMap.dat");
}

World::~World()

{

}

void World::getChunkHeightMap(std::vector<float>& chunkHeight, float x, float z)

{
	for (int i = 0; i < 16; i++)

	{
		for (int j = 0; j < 16; j++)

		{
			chunkHeight.push_back(100 + perlinNoise.fractalNoise(x + (float)i, z + (float)j, 20, 64.0));
		}
	}
}

void World::loadChunk(float x, float z)

{
	std::vector<float> heightMap;
	getChunkHeightMap(heightMap, z, x);
	chunks.push_back(Chunk(&heightMap, &this->cube, &this->textureAtlas, Entity({ x , -100, z }, { 0,0,0 }), ptrChunks));
	renderer.makeBuffers(chunks[chunks.size() - 1]);
	chunks[chunks.size() - 1].setAdjacentChunks();
	chunks[chunks.size() - 1].buildMesh();
	renderer.updateBuffers(chunks[chunks.size() - 1]);
}

void World::updateChunks()

{
	for (int i = 0; i < chunks.size(); i++)

	{
		if (chunks[i].setAdjacentChunks() == 1)

		{
			chunks[i].buildMesh();
			renderer.updateBuffers(chunks[i]);
		}
	}
}



void World::getChunksShouldLoad()

{
	int nearestChunkX, nearestChunkZ;
	nearestChunkX = -(int)camera.cameraEntity.position.x + (int)camera.cameraEntity.position.x % 16;
	nearestChunkZ = -(int)camera.cameraEntity.position.z + (int)camera.cameraEntity.position.z % 16;


	for (int i = 0; i < numChunks; i++)

	{
		for (int j = 0; j < numChunks; j++)

		{
			chunksShouldBeLoaded.push_back({ nearestChunkX + 16 * (i - numChunks / 2), nearestChunkZ + 16 * (j - numChunks / 2), 0.0 }); //X, Z, Loaded
		}
	}

	for (int i = 0; i < chunks.size(); i++)

	{
		for (int j = 0; j < chunksShouldBeLoaded.size(); j++)

		{
			if ((int)chunks[i].entity.position.x == (int)chunksShouldBeLoaded[j].x && (int)chunks[i].entity.position.z == (int)chunksShouldBeLoaded[j].y)

			{
				chunksShouldBeLoaded.erase(chunksShouldBeLoaded.begin() + j);
			}
		}
	}

	std::cout << chunksShouldBeLoaded.size() << std::endl;

}

void World::getChunksShouldUnload()

{
	chunksShouldBeUnloaded.clear();
	int nearestChunkX, nearestChunkZ;
	nearestChunkX = -(int)camera.cameraEntity.position.x + (int)camera.cameraEntity.position.x % 16;
	nearestChunkZ = -(int)camera.cameraEntity.position.z + (int)camera.cameraEntity.position.z % 16;
	//std::cout << nearestChunkX << " " << nearestChunkZ << std::endl;
	//std::cout << nearestChunkZ << " " << nearestChunkX << std::endl;
	indexDel = -1;

	//std::cout << sqrt((double)pow(nearestChunkX - (int)chunks[8 + 8*numChunks].entity.position.x, 2) + pow(nearestChunkZ - (int)chunks[8 + 8 * numChunks].entity.position.z, 2)) << std::endl;

	int dist = 0;
	for (int i = 0; i < chunks.size(); i++)

	{
		int posx, posz;

		posx = nearestChunkX - chunks[i].entity.position.x;
		posz = nearestChunkZ - chunks[i].entity.position.z;

		//std::cout << (int)chunks[i].entity.position.x << std::endl;

		//posz = 0;
		//std::cout << posx << std::endl;

		if (pow(posx,2) + pow(posz,2) > pow(numChunks,2))

		{
			if ((posx*posx + posz * posz) > dist)

			{
				//indexDel = i;
				//dist = (posx*posx + posz*posz);
			}

			indexDel = i;
			//std::cout << i << std::endl;
			//std::cout << sqrt(posx*posx + posz*posz) << " " << sqrt(8 * numChunks * 8 * numChunks) << std::endl;
			//int push = 1;
			//for (int j = 0; j < chunksShouldBeUnloaded.size(); j++)

			//{
				//if (chunksShouldBeUnloaded[j] == i)
				//{
					//push = 0;
					//std::cout << "Does this even happen?" << std::endl;
				//}
			//}
			//if (push == 1) chunksShouldBeUnloaded.push_back(i);
			//chunksShouldBeUnloaded.push_back(i);
		}

		if (indexDel != -1) break;

	}

	//std::cout << chunksShouldBeUnloaded.size() << std::endl;
}

void World::cullChunks()

{
	if (indexDel > -0.9)

	{
		//std::cout << chunksShouldBeUnloaded.size() << " ";
		//std::cout << chunksShouldBeUnloaded[indexDel] << std::endl;
		//std::cout << in
		//std::cout << indexDel << std::endl;
		//chunks[indexDel].deleteBuffers();
		//chunks[indexDel].entity.position = glm::vec3(0.0, 0.0, 0.0);
		//chunks[indexDel].vertices.clear();
		//chunks[indexDel].indices.clear();
		//chunks[indexDel].cubes.clear();
		//std::cout << chunks.size() << std::endl;
		//chunks[indexDel] = chunks.back();
		//chunks.pop_back();
		indexDel = -1;
		numDel++;
		//std::vector<Chunk>(chunks).swap(chunks);
		
		
		//chunksShouldBeUnloaded.erase(chunksShouldBeUnloaded.begin() + chunksShouldBeUnloaded.size() - 1);
		//std::cout << chunksShouldBeUnloaded.size() << std::endl;
		//chunks.shrink_to_fit();
		//chunksShouldBeUnloaded.shrink_to_fit();
	}
}

void World::genChunks()

{
	if (chunksShouldBeLoaded.size() > 0)

	{
		loadChunk(chunksShouldBeLoaded[0].x, chunksShouldBeLoaded[0].y);
		chunksShouldBeLoaded.erase(chunksShouldBeLoaded.begin());
		chunksShouldBeLoaded.shrink_to_fit();
	}
}

void World::renderChunks()

{
	for (int i = 0; i < chunks.size(); i++)

	{
		renderer.setUniforms(chunks[i].entity);
		renderer.draw(chunks[i], texture);
	}
}