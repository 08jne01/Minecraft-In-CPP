#pragma once
#include "Header.h"
struct Entity

{
	Entity(): position(glm::vec3(0.0)), rotation(glm::vec3(0.0)), velocity(glm::vec3(0.0))

	{

	}

	Entity(const glm::vec3 pos, const glm::vec3 rot) : position(pos), rotation(rot), velocity(glm::vec3(0.0))

	{

	}

	Entity(const glm::vec3 pos, const glm::vec3 rot, const glm::vec3 vel) : position(pos), rotation(rot), velocity(vel)

	{

	}

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 velocity;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

};