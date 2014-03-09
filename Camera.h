#ifndef CAMERA_H
#define CAMERA_H

#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <cmath>
#include "vector3.h"

#define M_PI 3.1415926535

class Camera
{
	public:
	Camera();
	~Camera();

	void Update(float roll, float pitch, float yaw);

	Vector3 position;
	Vector3 forward;
	Vector3 up;
	Vector3 side;
	Vector3 lookat;
};

#endif