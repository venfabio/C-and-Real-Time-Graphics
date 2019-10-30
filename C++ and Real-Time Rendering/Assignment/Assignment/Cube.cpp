#include "Cube.h"

Cube::Cube()
{
}


Cube::~Cube()
{
}

void Cube::SetStationOne()
{
	_position.X = 1.8f;
	_position.Y = 3.0f;
	_position.Z = 0.0f;
}

void Cube::SetStationTwo()
{
	_position.X = 3.0f;
	_position.Y = 0.0f;
	_position.Z = 1.8f;
	_angleX = 0.02655f;
}

void Cube::SetStationThree()
{
	_position.X = -3.0f;
	_position.Y = 0.0f;
	_position.Z = -1.8f;
	_angleX = 0.02655f;
}

void Cube::SetStationFour()
{
	_position.X = 1.8f;
	_position.Y = 0.0f;
	_position.Z = -3.5f;
	_angleX = 0.02655f;
}

void Cube::SetStationFive()
{
	_position.X = 1.8f;
	_position.Y = -3.0f;
	_position.Z = 0.0f;
}