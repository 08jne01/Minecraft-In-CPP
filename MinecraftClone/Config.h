#pragma once
#include "Header.h"

struct Config

{
	
	Config() : width(300), height(300), isFullscreen(0), renderDistance(16), fov(90)

	{

	}

	Config(int w, int h, int f, int d, int v) : width(w), height(h), isFullscreen(f), renderDistance(d), fov(v)

	{

	}

	int width, height, isFullscreen, renderDistance, fov;
};