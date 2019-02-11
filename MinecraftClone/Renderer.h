#pragma once
#include "Header.h"
#include "Entity.h"
#include "Camera.h"
#include "Matrix.h"
#include "Config.h"
#include "Quad.h"
#include "Vertex.h"

class Camera;
struct Entity;
struct Quad;

class Renderer

{
public:
	

	Renderer(unsigned int sp, Camera& camera, Config& conf);
	void setUniforms(Entity& entity);
	void setShader(unsigned int sp);

	template<typename Drawable> void makeBuffers(Drawable& drawable)

	{
		glGenVertexArrays(1, &drawable.entity.VAO);
		glGenBuffers(1, &drawable.entity.VBO);
		glGenBuffers(1, &drawable.entity.EBO);
	}

	template<typename Drawable> void updateBuffers(Drawable& drawable)

	{
		glBindVertexArray(drawable.entity.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, drawable.entity.VBO);
		glBufferData(GL_ARRAY_BUFFER, drawable.vertices.size() * sizeof(Vertex), &drawable.vertices[0], GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable.entity.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawable.indices.size() * sizeof(unsigned int), &drawable.indices[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)offsetof(Vertex, textureCoords));
		glEnableVertexAttribArray(1);
	}

	template<typename Drawable> void draw(Drawable& drawable, Texture& texture)

	{
		texture.bind();
		glUseProgram(shaderProgram);
		glBindVertexArray(drawable.entity.VAO);
		glDrawElements(GL_TRIANGLES, drawable.indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		texture.unbind();
	}

private:
	unsigned int shaderProgram;
	Camera& camRef;
	Config config;
};