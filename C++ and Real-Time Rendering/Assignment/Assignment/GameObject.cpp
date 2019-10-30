#include "GameObject.h"


GameObject::GameObject()
{
	_position.X = 0;
	_position.Y = 0;
	_position.Z = 0;
	_angleX = 0;
	_angleY = 0;
	_angleZ = 0;
	_scale = 1;
}

GameObject::~GameObject()
{
}

bool GameObject::CollideWith(const GameObject* other)
{
	float x, y, z;
	x = other->GetPosX();
	y = other->GetPosY();
	z = other->GetPosZ();

	x -= this->GetPosX();
	y -= this->GetPosY();
	z -= this->GetPosZ();
	
	double dist;

	dist = sqrt((x*x) + (y*y) + (z*z));

	double squaredRadi;

	squaredRadi = sqrt(0.2); // "suppose" each plane radius is 0.1, think about it as a Collision Mask.

	if (dist <= squaredRadi)
		return true;
	else
		return false;
}