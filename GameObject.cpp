#include "GameObject.h"

GameObject::GameObject()
{
	//give the vectors initial values
	position = Vector3(0.0f, 0.0f, 0.0f);
	scale = Vector3(1.0f, 1.0f, 1.0f);
	rotation = Vector3(0.0f, 0.0f, 0.0f);
	
	//set an initial colour
	colour = Colours::White();
}

GameObject::~GameObject()
{
}

Vector3 GameObject::GetTranslation()
{
	return position;
}

Vector3 GameObject::GetRotation()
{
	return rotation;
}

Vector3 GameObject::GetScale()
{
	return scale;
}

//move BY a specified amount
void GameObject::Translate(Vector3 trans)
{
	position.x += trans.x;
	position.y += trans.y;
	position.z += trans.z;
}

//rotate BY a specified amount
void GameObject::Rotate(Vector3 rot)
{
	rotation.x += rot.x;
	rotation.y += rot.y;
	rotation.z += rot.z;
}

//scale BY a specified amount
void GameObject::Scale(Vector3 scaleFactor)
{
	scale.x += scaleFactor.x;
	scale.y += scaleFactor.y;
	scale.z += scaleFactor.z;
}

//move TO a specified translation (from origin)
void GameObject::SetPosition(Vector3 trans)
{
	position.x = trans.x;
	position.y = trans.y;
	position.z = trans.z;
}

//rotate TO a specified rotation
void GameObject::SetRotation(Vector3 rot)
{
	rotation.x = rot.x;
	rotation.y = rot.y;
	rotation.z = rot.z;
}

//scale TO a specified factor (of original size)
void GameObject::SetScale(Vector3 scaleFactor)
{
	scale.x = scaleFactor.x;
	scale.y = scaleFactor.y;
	scale.z = scaleFactor.z;
}

Vector3 GameObject::GetColour()
{
	return colour;
}

void GameObject::SetColour(Vector3 nColour)
{
	colour = nColour;
}

float GameObject::GetVelocity()
{
	return velocity;
}

Vector3 GameObject::GetDirection()
{
	return direction;
}

void GameObject::SetVelocity(float newV)
{
	velocity = newV;
}

void GameObject::SetDirection(Vector3 newDir)
{
	direction = newDir;
	direction.Normalize();
}

Rect GameObject::GetRect()
{
	return collisionRect;
}

//2D collision detection between this gameobject and a second
bool GameObject::CollidesWith(GameObject other)
{
	//get the other object's collision rectangle
	Rect otherRect = other.GetRect();

	//if the objects collide
	if(collisionRect.GetLeft() < otherRect.GetRight() && collisionRect.GetRight() > otherRect.GetLeft() && collisionRect.GetTop() < otherRect.GetBottom() && collisionRect.GetBottom() > otherRect.GetTop())
	{
		//return true
		return true;
	}

	//return false
	return false;
}

void GameObject::Update(float frameTime)
{
	//calculate collision rectangle
	collisionRect = Rect(position.x - scale.x, position.y - scale.y, scale.x * 2, scale.y * 2);

	//move by direction * velocity * frametime
	Translate(Vector3(direction.x * velocity * frameTime, direction.y * velocity * frameTime, direction.z * velocity * frameTime));
}