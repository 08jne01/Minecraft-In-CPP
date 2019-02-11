#include "Chunk.h"

Chunk::Chunk()
{

}

Chunk Chunk::operator=(const Chunk& ref)

{
	Chunk local_chunk(ref);
	return local_chunk;
}

Chunk::Chunk(const Chunk& ref)

{
	vertices = ref.vertices;
	indices = ref.indices;
	cubes = ref.cubes;
	entity = ref.entity;
	cube = ref.cube;
	chunks = ref.chunks;
	deleteBuf = ref.deleteBuf;
	leftChunk = ref.leftChunk;
	rightChunk = ref.rightChunk;
	frontChunk = ref.frontChunk;
	backChunk = ref.backChunk;
	textureAtlas = ref.textureAtlas;
	indexIndices = ref.indexIndices;
}

Chunk::Chunk(std::vector<float>* cubeHeight, Cube* cubeRef, TextureAtlas* texAtlas, Entity ent, std::vector<Chunk>* chunksRef):
	indexIndices(0), textureAtlas(texAtlas), entity(ent), cube(cubeRef), chunks(chunksRef), leftChunk(-1), rightChunk(-1), frontChunk(-1), backChunk(-1)

{
	cubes.resize(16 * 256 * 16);

	for (int i = 0; i < 16; i++)

	{
		for (int j = 0; j < 256; j++)

		{
			for (int k = 0; k < 16; k++)

			{
				if (j < (*cubeHeight)[i + k * 16] - 2)

				{
					cubes[i + j * 256 + 16 * k] = 3;
				}

				else if (j < (*cubeHeight)[i + k * 16] - 1)

				{
					cubes[i + j * 256 + 16 * k] = 2;
				}

				else if (j < (*cubeHeight)[i + k * 16])

				{
					cubes[i + j * 256 + 16 * k] = 1;
				}

				else

				{
					cubes[i + j * 256 + 16 * k] = 0;
				}
				
			}
		}
	}

	for (int i = 0; i < 16; i++)

	{
		for (int j = 0; j < 85; j++)

		{
			for (int k = 0; k < 16; k++)

			{
				if (cubes[i + j * 256 + 16 * k] == 0)

				{
					cubes[i + j * 256 + 16 * k] = 5;
				}
			}
		}
	}

	for (int i = 0; i < 16; i++)

	{
		for (int j = 0; j < 85; j++)

		{
			for (int k = 0; k < 16; k++)

			{
				if (cubes[i + j * 256 + 16 * k] == 5)

				{
					//if (adjacent(BACK, i, j, k) == 1) setBlock(i, j, k - 1, 4);
					//if (adjacent(FRONT, i, j, k) == 1) setBlock(i, j, k + 1, 4);
					//if (adjacent(LEFT, i, j, k) == 1) setBlock(i - 1, j, k, 4);
					//if (adjacent(RIGHT, i, j, k) == 1) setBlock(i + 1, j, k, 4);
					if (adjacent(BOTTOM, i, j, k) == 1) setBlock(i, j - 1, k, 4);
				}
			}
		}
	}
}

Chunk::~Chunk()

{
	if (deleteBuf == 1)

	{
		glDeleteBuffers(1, &entity.VAO);
		glDeleteBuffers(1, &entity.EBO);
		glDeleteBuffers(1, &entity.VBO);
	}
	vertices.clear();
	indices.clear();
	cubes.clear();
}

void Chunk::deleteBuffers()

{
	glDeleteBuffers(1, &entity.VAO);
	glDeleteBuffers(1, &entity.EBO);
	glDeleteBuffers(1, &entity.VBO);
}

unsigned char Chunk::getBlock(int i, int j, int k)

{
	return cubes[i + 256 * j + k * 16];
}

void Chunk::setBlock(int i, int j, int k, unsigned char type)

{
	if (i < 0 || i > 15 || j < 0 || j > 255 || k < 0 || k > 15)

	{
		return;
	}

	else

	{
		cubes[i + 256 * j + k * 16] = type;
	}
}

int Chunk::setAdjacentChunks()

{
	if (leftChunk == -1 || rightChunk == -1 || backChunk == -1 || frontChunk == -1)

	{
		int localLeft = leftChunk;
		int localRight = rightChunk;
		int localFront = frontChunk;
		int localBack = backChunk;

		int posx = entity.position.x;
		int posz = entity.position.z;

		for (int i = 0; i < chunks->size(); i++)

		{
			if (!((int)(*chunks)[i].entity.position.x == posx && (int)(*chunks)[i].entity.position.z == posz))

			{
				if ((int)(*chunks)[i].entity.position.x == posx + 16 && (int)(*chunks)[i].entity.position.z == posz) rightChunk = i; //f
				if ((int)(*chunks)[i].entity.position.x == posx - 16 && (int)(*chunks)[i].entity.position.z == posz) leftChunk = i; //b
				if ((int)(*chunks)[i].entity.position.z == posz + 16 && (int)(*chunks)[i].entity.position.x == posx) frontChunk = i; //r
				if ((int)(*chunks)[i].entity.position.z == posz - 16 && (int)(*chunks)[i].entity.position.x == posx) backChunk = i; //l
			}
		}

		if (localLeft != leftChunk || localRight != rightChunk || localFront != frontChunk || localBack != backChunk)

		{
			return 1;
		}
	}

	return 0;
}


void Chunk::translateCubeMesh(int i, int j, int k, int index, int face, VertexData& data)

{
	for (int n = 0; n < data.vertices.size(); n++)

	{
		Vertex v = data.vertices[n];
		glm::vec2 tex = textureAtlas->fetchCoords(getBlock(i, j, k), face);
		glm::vec2 def = data.vertices[n].textureCoords;
		float x, y;
		x = def.x / 16.0 + ((float)tex.x / 16.0) / 16.0;
		y = def.y / 16.0 + ((float)tex.y / 16.0) / 16.0;
		//std::cout << x << " " << y << std::endl;
		//std::cout << def.x / 256.0 + tex.x / 256.0 << std::endl;
		data.vertices[n] = Vertex({ v.position.x + i, v.position.y + j, v.position.z + k }, {x, y});
	}

	data.indices = offVec<unsigned int>(data.indices, index);
}

int Chunk::adjacent(int face, int i, int j, int k)

{
	switch (face)

	{
		case LEFT:

		{
			if (i - 1 < 0 && leftChunk == -1) return 0;
			else if (i - 1 < 0) return (int)(*chunks)[leftChunk].getBlock(15, j, k);
			return (int)getBlock(i - 1, j, k);
		}

		case RIGHT:

		{
			if (i + 1 > 15 && rightChunk == -1) return 0;
			else if (i + 1 > 15) return (int)(*chunks)[rightChunk].getBlock(0, j, k);
			return (int)getBlock(i + 1, j, k);
		}

		case BACK:

		{
			if (k - 1 < 0 && backChunk == -1) return 0;
			else if (k - 1 < 0) return (int)(*chunks)[backChunk].getBlock(i, j, 15);
			return (int)getBlock(i, j, k - 1);
		}

		case FRONT:

		{
			//if (frontChunk != nullptr) std::cout << frontChunk << std::endl;
			if (k + 1 > 15 && frontChunk == -1) return 0;
			else if (k + 1 > 15) return (int)(*chunks)[frontChunk].getBlock(i, j, 0);
			return (int)getBlock(i, j, k + 1);
		}

		case TOP:

		{
			if (j + 1 > 255) return 0;
			return (int)getBlock(i, j + 1, k);
		}

		case BOTTOM:

		{
			if (j - 1 < 0) return 0;
			return (int)getBlock(i, j - 1, k);
		}
	}
}

void Chunk::addVertices(int i, int j, int k, int face, int index)

{
	VertexData data(cube->verticesFaces[face], cube->indicesFaces[face]);
	translateCubeMesh(i, j, k, index, face, data);

	for (int n = 0; n < data.vertices.size(); n++)

	{
		vertices.push_back(data.vertices[n]);
	}

	for (int n = 0; n < data.indices.size(); n++)

	{
		indices.push_back(data.indices[n]);
	}
	indexIndices+=4;
}

void Chunk::buildMesh()

{
	vertices.clear();
	indices.clear();
	indexIndices = 0;

	for (int i = 0; i < 16; i++)

	{
		for (int j = 0; j < 256; j++)

		{
			for (int k = 0; k < 16; k++)

			{
				if (cubes[i + 256 * j + 16 * k] != 0)

				{
					if (adjacent(BACK, i, j, k) == 0) addVertices(i, j, k, BACK, indexIndices);
					if (adjacent(FRONT, i, j, k) == 0) addVertices(i, j, k, FRONT, indexIndices);
					if (adjacent(LEFT, i, j, k) == 0) addVertices(i, j, k, LEFT, indexIndices);
					if (adjacent(RIGHT, i, j, k) == 0) addVertices(i, j, k, RIGHT, indexIndices);
					if (adjacent(TOP, i, j, k) == 0) addVertices(i, j, k, TOP, indexIndices);
					if (adjacent(BOTTOM, i, j, k) == 0) addVertices(i, j, k, BOTTOM, indexIndices);

					if (adjacent(BACK, i, j, k) == 5 && getBlock(i, j, k) != 5) addVertices(i, j, k, BACK, indexIndices);
					if (adjacent(FRONT, i, j, k) == 5 && getBlock(i, j, k) != 5) addVertices(i, j, k, FRONT, indexIndices);
					if (adjacent(LEFT, i, j, k) == 5 && getBlock(i, j, k) != 5) addVertices(i, j, k, LEFT, indexIndices);
					if (adjacent(RIGHT, i, j, k) == 5 && getBlock(i, j, k) != 5) addVertices(i, j, k, RIGHT, indexIndices);
					if (adjacent(TOP, i, j, k) == 5 && getBlock(i, j, k) != 5) addVertices(i, j, k, TOP, indexIndices);
					if (adjacent(BOTTOM, i, j, k) == 5 && getBlock(i, j, k) != 5) addVertices(i, j, k, BOTTOM, indexIndices);

				}
			}
		}
	}
}