#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector3.h"
#include "Rectangle.h"
#include "Colours.h"

class GameObject
{
public:

	GameObject();
	~GameObject();

	void Translate(Vector3);
	void Rotate(Vector3);
	void Scale(Vector3);

	void SetPosition(Vector3);
	void SetRotation(Vector3);
	void SetScale(Vector3);

	Vector3 GetTranslation();
	Vector3 GetRotation();
	Vector3 GetScale();

	Vector3 GetColour();
	void SetColour(Vector3);

	void SetVelocity(float);
	void SetDirection(Vector3);

	float GetVelocity();
	Vector3 GetDirection();

	Rect GetRect();
	bool CollidesWith(GameObject);

	void Update(float);

protected:

	Vector3 position;
	Vector3 scale;
	Vector3 rotation;

	float velocity;
	Vector3 direction;
	
	Vector3 colour;

	Rect collisionRect;
};

#endif