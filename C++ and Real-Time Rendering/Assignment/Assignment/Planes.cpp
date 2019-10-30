#include "Planes.h"

Planes::Planes()
{
	//flag = true;
	counter = 0;
	timeModifier = 0;
	resurrectionTime = 0;
	_cameraDisabled = false;
	_cameraPlane = false;
	_wait = 0;
	_showPath = true;
}


Planes::~Planes()
{
}

void Planes::Initialize(Window* w)
{
	_window = w;
	_renderer = w->GetRenderer();

	// Read stuff from config file
	ReadConfig();

	// Cube creation
	_meshCube.CreateCube(_renderer);
	_smallCube = new Cube();
	_smallCube->SetMesh(&_meshCube);
	_smallCube->SetTexture(L"highway.png");

	_meshCubeBig.CreateCubeBig(_renderer);
	_bigCube = new Cube();
	_bigCube->SetMesh(&_meshCubeBig);
	_bigCube->SetScale(10);
	_bigCube->SetTexture(L"texture4.png");
	_bigCube->SetTransparency(true);

	// Plane creation
	for (int i = 0; i < MAX_PLANES; i++)
	{
		_meshPlane.CreatePlane(_renderer);
		Plane* p = new Plane();
		p->SetMesh(&_meshPlane);
		if (i < 2)
			p->SetTexture(L"texture2.jpg");
		else
			p->SetTexture(L"texture3.jpg");
		_planes.push_back(p);
	}

	// Particle creation
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		_meshParticle.CreateParticle(_renderer);
		Particle* p = new Particle();
		p->SetMesh(&_meshParticle);
		p->SetScale(0.3f);
		p->SetTexture(L"particle.png");
		_particles.push_back(p);
	}

	// Station creation
	_meshStation.CreateStation(_renderer);
	for (int i = 0; i <= 5; i++)
	{
		Cube* c = new Cube();
		c->SetMesh(&_meshStation);
		c->SetScale(0.4f);
		c->SetTexture(L"texture1.jpg");
		_stations.push_back(c);
	}

	_stations[0]->SetStationOne();
	_stations[1]->SetStationTwo();
	_stations[2]->SetStationThree();
	_stations[3]->SetStationFour();
	_stations[4]->SetStationFive();

	// Flight paths
	_meshPathOne.AddVertex({ 0.0f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathOne.AddVertex({ 0.0f, 0.22f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathOne.AddVertex({ 0.0f, 0.22f, 0.15f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathOne.AddVertex({ 0.0f, 0.0f, 0.45f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathOne.AddVertex({ 0.0f, -0.18f, 0.5f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathOne.AddVertex({ 0.0f, -0.18f, -0.3f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathOne.AddVertex({ 0.0f, 0.22f, -0.6f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathOne.AddVertex({ 0.0f, 0.22f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });

	_meshPathTwo.AddVertex({ 0.0f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathTwo.AddVertex({ 0.37f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathTwo.AddVertex({ 0.32f, 0.2f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathTwo.AddVertex({ -0.3f, 0.2f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathTwo.AddVertex({ -0.3f, -0.2f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathTwo.AddVertex({ 0.37f, -0.2f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathTwo.AddVertex({ 0.37f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });

	_meshPathThree.AddVertex({ 0.0f, -0.03f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathThree.AddVertex({ -0.37f, -0.03f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathThree.AddVertex({ -0.37f, -0.2f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathThree.AddVertex({ 0.3f, -0.2f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathThree.AddVertex({ 0.3f, 0.25f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathThree.AddVertex({ -0.3f, 0.25f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathThree.AddVertex({ -0.3f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathThree.AddVertex({ 0.0f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });

	_meshPathFour.AddVertex({ 0.0f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathFour.AddVertex({ 0.0f, -0.4f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathFour.AddVertex({ -0.2f, -0.4f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathFour.AddVertex({ -0.37f, -0.2f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathFour.AddVertex({ -0.37f, 0.35f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathFour.AddVertex({ -0.32f, 0.47f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathFour.AddVertex({ 0.24f, 0.47f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathFour.AddVertex({ 0.32f, 0.4f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathFour.AddVertex({ 0.32f, -0.4f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });
	_meshPathFour.AddVertex({ 0.0f, -0.4f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f });

	_meshPathOne.CreateVBO(_renderer);
	_meshPathTwo.CreateVBO(_renderer);
	_meshPathThree.CreateVBO(_renderer);
	_meshPathFour.CreateVBO(_renderer);

	_pathOne = new Path();
	_pathOne->SetMesh(&_meshPathOne);
	_pathTwo = new Path();
	_pathTwo->SetMesh(&_meshPathTwo);
	_pathThree = new Path();
	_pathThree->SetMesh(&_meshPathThree);
	_pathFour = new Path();
	_pathFour->SetMesh(&_meshPathFour);

	_currentState = Running;
}


// this is the function used to render a single frame
void Planes::Run(void)
{
	// Get delta time
	temp_time = clock();
	_deltaTime = (temp_time - _lastFrameTime) / CLOCKS_PER_SEC;
	_deltaTimeModified = _deltaTime + timeModifier;
	fps = 1.0f / _deltaTime;
	_lastFrameTime = temp_time;
	
	//OnKeyboard();
	
	if (_currentState == Running)
	{
		switch (MAX_PLANES) {
		case 1:
			_planes[configLines[3]]->PathOne(_deltaTimeModified);
			break;
		case 2:
			_planes[configLines[3]]->PathOne(_deltaTimeModified);
			_planes[configLines[4]]->PathThree(_deltaTimeModified);
			break;
		case 3:
			_planes[configLines[3]]->PathOne(_deltaTimeModified);
			_planes[configLines[4]]->PathThree(_deltaTimeModified);
			_planes[configLines[5]]->PathFour(_deltaTimeModified);
			break;
		case 4:
			_planes[configLines[3]]->PathOne(_deltaTimeModified);
			_planes[configLines[4]]->PathThree(_deltaTimeModified);
			_planes[configLines[5]]->PathFour(_deltaTimeModified);
			_planes[configLines[6]]->PathFive(_deltaTimeModified);
		}
		/*
		_planes[0]->PathOne(_deltaTime);
		_planes[1]->PathFive(_deltaTime);
		_planes[2]->PathThree(_deltaTime);
		_planes[3]->PathFour(_deltaTime);*/
		
		// Collision detection
		for (int i = 0; i < (int)_planes.size(); i++)
			for (int j = 1; j < (int)_planes.size(); j++)
			{
				if (_planes[i]->IsAlive() &&
					_planes[j]->IsAlive() &&
					_planes[i]->GetPlaneState() == Flying &&
					_planes[j]->GetPlaneState() == Flying &&
					i != j &&
					_planes[i]->CollideWith(_planes[j]))
				{
					
					_planes[i]->SetAlive(false);
					_planes[j]->SetAlive(false);
					// Make it sparkle.
					for (int k = 0; k < (int)_particles.size(); k++)
						if (_particles[k]->IsAlive() == false)
							_particles[k]->Create(_planes[i]->GetPosX(), _planes[i]->GetPosY(), _planes[i]->GetPosZ());
				}
			}
		// Update particles
		for (int i = 0; i < (int)_particles.size(); i++)
		{
			if (_particles[i]->IsAlive())
				_particles[i]->Update(_deltaTimeModified);
		}
	}

	// /cast Ancestral Spirit
	if (resurrectionTime > RESURRECTION_CD)
	{
		for (int i = 0; i < (int)_planes.size(); i++)
		{
			if (_planes[i]->IsAlive() == false)
				_planes[i]->Reset();
		}
		resurrectionTime = 0;			// All planes have been resurrected! Miracle!
	}
	else
		resurrectionTime += _deltaTimeModified;	// Cooldown.

	if (_cameraPlane)
	{
		if (_planes[counter]->IsAlive())
			_renderer->SetCameraPlane(_planes[counter]);
		else
		{
			if (counter < MAX_PLANES - 1)
				counter++;
			else if (counter == MAX_PLANES - 1)
				counter = 0;
		}
	}

	// Send statistics to Renderer so ATB can use them.
	_renderer->SetStatistics(fps, timeModifier);
	// Draw Everything
	Draw();
}

void Planes::Draw()
{
	_renderer->ClearScreen();
	_renderer->RenderFrame();

	_renderer->DrawGO(_smallCube);

	// Draw Planes
	for (int i = 0; i < (int)_planes.size(); i++)
	{
		if (_planes[i]->IsAlive())
			_renderer->DrawGO(_planes[i]);
	}

	// Draw Stations

	_renderer->DrawGO(_stations[0]);
	_renderer->DrawGO(_stations[1]);
	_renderer->DrawGO(_stations[2]);
	_renderer->DrawGO(_stations[3]);
	_renderer->DrawGO(_stations[4]);
	
	// Draw Particles
	for (int i = 0; i < (int)_particles.size(); i++)
	{
		if (_particles[i]->IsAlive())
			_renderer->DrawGO(_particles[i]);
	}
	
	_renderer->DrawGO(_bigCube);

	if (_showPath)
	{
		_renderer->DrawPath(_pathOne);
		_renderer->DrawPath(_pathTwo);
		_renderer->DrawPath(_pathThree);
		_renderer->DrawPath(_pathFour);
	}

	_renderer->SwapBuffer();
}

void Planes::ReadConfig()
{
	const string ConfigFile = "config.txt";

	ifstream f(ConfigFile);
	string line;
	int i = 0;

	while (!f.eof()) {
		getline(f, line);

		if (line[0] != '/')
		{
			configLines[i] = std::stoi(line);
			i++;
		}
	}

	MAX_PLANES = configLines[0];
	MAX_PARTICLES = configLines[1];
	RESURRECTION_CD = configLines[2];
}
/* Alternate input
void Planes::OnKeyboard(int key, bool down)
{
	if (GetKeyState(VK_F1) & 0x8000)
	{
		_cameraDisabled = false;
		_cameraPlane = false;
		_renderer->SetCameraOne();
	}
	if (GetKeyState(VK_F2) & 0x8000)
	{
		_cameraDisabled = false;
		_cameraPlane = false;
		_renderer->SetCameraTwo();
	}
	if (_cameraDisabled == false)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			amt = -2.75f * _deltaTime;
			_renderer->RotateCameraX(amt);
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			amt = 2.75f * _deltaTime;
			_renderer->RotateCameraX(amt);
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			amt = -2.75f * _deltaTime;
			_renderer->RotateCameraY(amt);
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			amt = 2.75f * _deltaTime;
			_renderer->RotateCameraY(amt);
		}
		if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_LEFT) & 0x8000))
		{
			amt = -2.75f * _deltaTime;
			_renderer->MoveCameraX(amt);
		}
		if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_RIGHT) & 0x8000))
		{
			amt = 2.75f * _deltaTime;
			_renderer->MoveCameraX(amt);
		}
		if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_DOWN) & 0x8000))
		{
			amt = -2.75f * _deltaTime;
			_renderer->MoveCameraZ(amt);
		}
		if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_UP) & 0x8000))
		{
			amt = 2.75f * _deltaTime;
			_renderer->MoveCameraZ(amt);
		}
		if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_PRIOR) & 0x8000))
		{
			amt = 2.75f * _deltaTime;
			_renderer->MoveCameraY(amt);
		}
		if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_NEXT) & 0x8000))
		{
			amt = -2.75f * _deltaTime;
			_renderer->MoveCameraY(amt);
		}
	}
	if (GetKeyState(VK_F3) & 0x8000)
	{
		_cameraDisabled = true;
		_cameraPlane = true;
		counter = 0;
	}
	if (GetKeyState(VK_F4) & 0x8000)	
	{
		if ((_planes[counter]->IsAlive()) && flag)
		{
			if (counter == MAX_PLANES-1)
				counter = 0;				// don't go out of range
			counter = counter + 1;
			flag = false;
		}
		_wait += _deltaTime;
		if (_wait > 3)						// can't switch to another plane before 3 secs
		{
			_wait = 0;
			flag = true;
		}
	}
	if (GetKeyState(VK_ESCAPE) & 0x8000)
	{
		exit(0);
	}
	if (GetKeyState(0x50) & 0x8000)
	{
		if (_currentState == Running)
			_currentState = Paused;
		else if (_currentState == Paused)
			_currentState = Running;
	}
	if (GetKeyState(0x52) & 0x8000)
	{
		_currentState = Resetting;
		Reset();
		_currentState = Running;
	}
	/*
	if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(0x54) & 0x8000))
	{
		timeModifier = timeModifier + 0.001f;
	}
	if (GetKeyState(0x54) & 0x8000)
	{
		timeModifier = timeModifier + 0.001f;
	}
}
*/

void Planes::OnKeyboard(int key, bool down)
{
	_keyStates[key] = down;

	// Function cases
	if (_keyStates[112])
	{
		_cameraDisabled = false;
		_cameraPlane = false;
		_renderer->SetCameraOne();
	}
	if (_keyStates[113])
	{
		_cameraDisabled = false;
		_cameraPlane = false;
		_renderer->SetCameraTwo();
	}
	if (_keyStates[114])
	{
		_cameraDisabled = true;
		_cameraPlane = true;
		counter = 0;
	}
	if (_keyStates[115])
	{
		if (_planes[counter]->IsAlive())
		{
			if (counter == MAX_PLANES - 1)
				counter = 0;				// don't go out of range
			else
				counter = counter + 1;
		}
	}
	// Arrow case
	if (_keyStates[17] && _keyStates[37])
	{
			if (_cameraDisabled == false)
			{
				amt = -2.75f * _deltaTime;
				_renderer->MoveCameraX(amt);
			}
	
	}
	else if (_keyStates[37])
	{
		if (_cameraDisabled == false)
		{
			amt = -2.75f * _deltaTime;
			_renderer->RotateCameraX(amt);
		}
	}
	if (_keyStates[17] && _keyStates[38])
	{
		if (_cameraDisabled == false)
		{
			amt = 2.75f * _deltaTime;
			_renderer->MoveCameraZ(amt);
		}

	}
	else if (_keyStates[38])
	{
		if (_cameraDisabled == false)
		{
			amt = 2.75f * _deltaTime;
			_renderer->RotateCameraY(amt);
		}
	}
	if (_keyStates[17] && _keyStates[39])
	{
		if (_cameraDisabled == false)
		{
			amt = 2.75f * _deltaTime;
			_renderer->MoveCameraX(amt);
		}

	}
	else if (_keyStates[39])
	{
		if (_cameraDisabled == false)
		{
			amt = 2.75f * _deltaTime;
			_renderer->RotateCameraX(amt);
		}
	}
	if (_keyStates[17] && _keyStates[40])
	{
		if (_cameraDisabled == false)
		{
			amt = -2.75f * _deltaTime;
			_renderer->MoveCameraZ(amt);
		}

	}
	else if (_keyStates[40])
	{
		if (_cameraDisabled == false)
		{
			amt = -2.75f * _deltaTime;
			_renderer->RotateCameraY(amt);
		}
	}
	if (_keyStates[17] && _keyStates[33])
	{
		if (_cameraDisabled == false)
		{
			amt = 2.75f * _deltaTime;
			_renderer->MoveCameraY(amt);
		}
	}
	if (_keyStates[17] && _keyStates[34])
	{
		if (_cameraDisabled == false)
		{
			amt = -2.75f * _deltaTime;
			_renderer->MoveCameraY(amt);
		}
	}
	// Misc
	if (_keyStates[27])
	{
		exit(0);
	}
	if (_keyStates[80])
	{
		if (_currentState == Running)
			_currentState = Paused;
		else if (_currentState == Paused)
			_currentState = Running;
	}
	if (_keyStates[82])
	{
		_currentState = Resetting;
		Reset();
		_currentState = Running;
	}
	if (_keyStates[16] && _keyStates[84])
	{
		timeModifier = timeModifier + 0.01f;
	}
	else if (_keyStates[84])
	{
		if (timeModifier > -0.03f)
			timeModifier = timeModifier - 0.01f;
	}
	if (_keyStates[70])
	{
		_showPath = !_showPath;
	}
}

void Planes::Reset()
{
	for (int i = 0; i < (int)_planes.size(); i++)
	{
		_planes[i]->SetAlive(false);
		_planes[i]->Reset();
		resurrectionTime = 0;
		timeModifier = 0;
		//_renderer->SetCameraOne();
	}

	for (int i = 0; i < (int)_particles.size(); i++)
	{
		_particles[i]->SetAlive(false);
	}
}