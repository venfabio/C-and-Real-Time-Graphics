#pragma once

#include "GameObject.h"

class Cube:
	public GameObject
{
public:
	Cube();
	~Cube();

public:
	void SetStationOne();
	void SetStationTwo();
	void SetStationThree();
	void SetStationFour();
	void SetStationFive();
};

