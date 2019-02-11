#pragma once
#include "Header.h" 
#include "Entity.h"
#include "Camera.h"
class Camera;

class EventHandler

{
public:
	EventHandler(Camera& cam);
	void keyHandler(int action, int button);
	void mouseHandler(double x, double y);

private:

	Camera& camera;
};