#include "Quad.h"

Quad::Quad(float width, float height, float x, float y, float z):

	vertices{
		Vertex({-width * 0.5f, -height * 0.5f, 0.0f}, {0.0f, 0.0f}), //BottomLeft
		Vertex({width*0.5f, -height * 0.5f, 0.0f}, {1.0f, 0.0f}),  //Bottom Right
		Vertex({-width * 0.5f,height*0.5f, 0.0f}, {0.0f, 1.0f}), //Top Left
		Vertex({width*0.5f, height*0.5f, 0.0f}, {1.0f, 1.0f}) //Top Right
	}, 

	indices{
		0, 1, 2,
		2, 3, 1
	}, entity(), texture("Resources/Textures/Heart.png", GL_TEXTURE_2D)
{
	entity.position.x = x;
	entity.position.y = y;
	entity.position.z = z;
}
