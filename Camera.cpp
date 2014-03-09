#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "camera.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.1415926535f
#endif


//constructor
Camera::Camera()
{
	position = Vector3(0.0f, 0.0f, -10.0f);
}

//destructor
Camera::~Camera()
{
}

void Camera::Update(float roll, float pitch, float yaw)
{
	float cosR, cosP, cosY;	
    float sinR, sinP, sinY;		

	//calculate the cosines and sines of the yaw, pitch and roll values
	cosY = cosf(yaw*M_PI/180.0f);
	cosP = cosf(pitch*M_PI/180.0f);
	cosR = cosf(roll*M_PI/180.0f);
	sinY = sinf(yaw*M_PI/180.0f);
	sinP = sinf(pitch*M_PI/180.0f);
	sinR = sinf(roll*M_PI/180.0f);

	//calculate the forward vector
	forward.x = sinY*cosP;
	forward.y = sinP;
    forward.z = cosP*-cosY;

	//calculate the up vector
	up.x = -cosY*sinR-sinY*sinP*cosR;
	up.y = cosP*cosR;
	up.z = -sinY*sinR-sinP*cosR*-cosY;

	//calculate the side vector
	side = forward.CrossProduct(up);

	//calculate the camera target (look at) vector 
	lookat.x = position.x + forward.x;
	lookat.y = position.y + forward.y;
	lookat.z = position.z + forward.z;
}