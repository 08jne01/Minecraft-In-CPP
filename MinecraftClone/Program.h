#pragma once
#include "Header.h"
#include "Camera.h"
#include "BasicShader.h"
#include "Renderer.h"
#include "Quad.h"
#include "EventHandler.h"
#include "Cube.h"
#include "Chunk.h"
#include "Clock.h"
#include "TextureAtlas.h"
#include "World.h"

class Camera;
class EventHandler;

class Program

{
public:

	Program(int width, int height, std::string s);
	int mainLoop();
	int seedToInt(std::string s);

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int button, int scancode, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

private:
	GLFWwindow* window;
	Camera camera;
	EventHandler eventHandler;
	std::string seed;
	int w, h;
};