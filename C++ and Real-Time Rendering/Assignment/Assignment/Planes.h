#pragma once

#include <fstream>

#include "Window.h"
#include "Vertex.h"
#include "Renderer.h"

#include "Mesh.h"
#include "Plane.h"
#include "Cube.h"
#include "Particle.h"
#include "Path.h"

enum State{

	Running,
	Paused,
	Resetting,
	Quit
};

class Renderer;
class Window;

class Planes
{
public:
	Planes();
	~Planes();

private:

	Window*					_window;
	Renderer*				_renderer;

	Cube*					_smallCube;
	Cube*					_bigCube;

	Path*					_pathOne;
	Path*					_pathTwo;
	Path*					_pathThree;
	Path*					_pathFour;

	std::vector<Plane*>		_planes;
	std::vector<Particle*>	_particles;
	std::vector<Cube*>		_stations;

	// Meshes
	Mesh					_meshCube;
	Mesh					_meshCubeBig;
	Mesh					_meshPlane;
	Mesh					_meshParticle;
	Mesh					_meshStation;
	Mesh					_meshPathOne;
	Mesh					_meshPathTwo;
	Mesh					_meshPathThree;
	Mesh					_meshPathFour;

	State					_currentState;

	bool					_cameraDisabled;	// if True disable arrow movements
	bool					_cameraPlane;
	bool					_keyStates[256];
	bool					_showPath;
	//bool					flag;				

	double					_lastFrameTime;		// Time of last frame
	double					_deltaTime;			// Time since last frame
	double					temp_time;
	double					resurrectionTime;
	double					_wait;
	double					timeModifier;
	double					_deltaTimeModified;

	float					amt;
	float					fps;

	int						counter;
	int						MAX_PLANES;
	int						MAX_PARTICLES;
	int						RESURRECTION_CD;
	int						configLines[9];

public:
	void Initialize(Window* w);
	void Run(void);     
	void Draw();
	void OnKeyboard(int key, bool down);
	void Reset();
	void ReadConfig();

	State GetPState()			const	{ return _currentState; }
};

