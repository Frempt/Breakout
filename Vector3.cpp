#include "vector3.h"

Vector3::Vector3()
{
	//create zero vector
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float nX, float nY, float nZ)
{
	//create vector with specified values
	x = nX;
	y = nY;
	z = nZ;
}

Vector3::~Vector3()
{
}

float Vector3::GetMagnitude() const
{
	float mag;

	//calculate the magnitude of the vector
	mag = sqrt(x*x+y*y+z*z);

	//return the magnitude of the vector
	return mag;
}

void Vector3::Normalize()
{
	//get magnitude of vector
	float mag = GetMagnitude();

	//if the magnitude is not 0 or 1, make the vector a unit vector
	if(mag != 0.0f && mag != 1.0f)
	{
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

//calculate vector product of two vectors
Vector3 Vector3::CrossProduct(const Vector3 & V2) const
{
    Vector3 prodvect;

	//calculate the cross product of two vectors
	prodvect.x = y*V2.z-z*V2.y;
	prodvect.y = -x*V2.z+z*V2.x;
	prodvect.z = x*V2.y-y*V2.x;

	return prodvect;
}