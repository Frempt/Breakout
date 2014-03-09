#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3
{
public:
	Vector3();
	Vector3(float nX, float nY, float nZ);

	~Vector3();

	float GetMagnitude() const;
	void Normalize();
	Vector3 CrossProduct(const Vector3 & V2) const;

	float x;
	float y;
	float z;
};

#endif