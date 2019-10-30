#include "Mesh.h"

Mesh::Mesh()
	: _locked(false),
	  _vbo(NULL)
{
	
}

Mesh::~Mesh()
{
	delete _vbo;
	_vbo = NULL;
}

VBO* Mesh::CreateCube(Renderer* renderer)
{
	// create a triangle using the VERTEX struct
	VERTEX CubeVertices[] =
	{
		{ -1.0f, -1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.0f, 0.0f },    // side 1
		{ 1.0f, -1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 1.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 1.0f, 1.0f },

		{ -1.0f, -1.0f, -1.0f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.0f, 0.0f },    // side 2
		{ -1.0f, 1.0f, -1.0f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.0f, 1.0f },
		{ 1.0f, -1.0f, -1.0f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 1.0f, 0.0f },
		{ 1.0f, 1.0f, -1.0f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f },

		{ -1.0f, 1.0f, -1.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f },    // side 3
		{ -1.0f, 1.0f, 1.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.0f, 1.0f },
		{ 1.0f, 1.0f, -1.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 1.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 1.0f, 1.0f },

		{ -1.0f, -1.0f, -1.0f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0.0f, 0.0f },    // side 4
		{ 1.0f, -1.0f, -1.0f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 1.0f, 0.0f },
		{ -1.0f, -1.0f, 1.0f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0.0f, 1.0f },
		{ 1.0f, -1.0f, 1.0f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 1.0f, 1.0f },

		{ 1.0f, -1.0f, -1.0f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f },    // side 5
		{ 1.0f, 1.0f, -1.0f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.0f, 1.0f },
		{ 1.0f, -1.0f, 1.0f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 1.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 1.0f, 1.0f },

		{ -1.0f, -1.0f, -1.0f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 1.0f, 1.0f },    // side 6
		{ -1.0f, -1.0f, 1.0f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0.0f, 1.0f },
		{ -1.0f, 1.0f, -1.0f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 1.0f, 0.0f },
		{ -1.0f, 1.0f, 1.0f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0.0f, 0.0f },
	};

	// create the index buffer out of DWORDs
	DWORD CubeIndices[] =
	{
		0, 1, 2,       // side 1
		2, 1, 3,
		4, 5, 6,	   // side 2
		6, 5, 7,
		8, 9, 10,	   // side 3
		10, 9, 11,
		12, 13, 14,    // side 4
		14, 13, 15,
		16, 17, 18,    // side 5
		18, 17, 19,
		20, 21, 22,    // side 6
		22, 21, 23,
	};

	_vbo = new VBO();
	_vbo->Create(renderer, CubeVertices, CubeIndices, 24, 36);
	return _vbo;
}

/* Different Texture mapping*/
VBO* Mesh::CreateCubeBig(Renderer* renderer)
{
	// create a triangle using the VERTEX struct
	VERTEX CubeVertices[] =
	{
		{ -1.0f, -1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.0f, 1.0f },    // side 1
		{ 1.0f, -1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.5f, 1.0f },
		{ -1.0f, 1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.5f, 0.0f },

		{ -1.0f, -1.0f, -1.0f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.0f, 1.0f },    // side 2
		{ -1.0f, 1.0f, -1.0f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.0f, 0.0f },
		{ 1.0f, -1.0f, -1.0f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.5f, 1.0f },
		{ 1.0f, 1.0f, -1.0f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.5f, 0.0f },

		{ -1.0f, 1.0f, -1.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.0f, 1.0f },    // side 3
		{ -1.0f, 1.0f, 1.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f },
		{ 1.0f, 1.0f, -1.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.5f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.5f, 0.0f },

		{ -1.0f, -1.0f, -1.0f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0.0f, 1.0f },    // side 4
		{ 1.0f, -1.0f, -1.0f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0.0f, 0.0f },
		{ -1.0f, -1.0f, 1.0f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0.5f, 1.0f },
		{ 1.0f, -1.0f, 1.0f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0.5f, 0.0f },

		{ 1.0f, -1.0f, -1.0f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.5f, 1.0f },    // side 5
		{ 1.0f, 1.0f, -1.0f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.5f, 0.0f },
		{ 1.0f, -1.0f, 1.0f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f },

		{ -1.0f, -1.0f, -1.0f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0.0f, 1.0f },    // side 6
		{ -1.0f, -1.0f, 1.0f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0.5f, 1.0f },
		{ -1.0f, 1.0f, -1.0f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0.0f, 0.0f },
		{ -1.0f, 1.0f, 1.0f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0.5f, 0.0f },
	};

	// create the index buffer out of DWORDs
	DWORD CubeIndices[] =
	{
		0, 1, 2,       // side 1
		2, 1, 3,
		4, 5, 6,	   // side 2
		6, 5, 7,
		8, 9, 10,	   // side 3
		10, 9, 11,
		12, 13, 14,    // side 4
		14, 13, 15,
		16, 17, 18,    // side 5
		18, 17, 19,
		20, 21, 22,    // side 6
		22, 21, 23,
	};

	_vbo = new VBO();
	_vbo->Create(renderer, CubeVertices, CubeIndices, 24, 36);
	return _vbo;
}

VBO* Mesh::CreatePlane(Renderer* renderer)
{
	VERTEX PlaneVertices[] =
	{
		// fuselage
		{ 0.0f, 0.0f, 0.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f }, //0
		{ 0.0f, 0.0f, 1.5f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.0f, 0.0f }, //1
		{ 0.5f, 0.5f, 0.5f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.5f, 1.0f }, //2
		{ 0.5f, 0.5f, 0.0f, D3DXVECTOR3(0.0f, 1.0f, 1.0f), 0.5f, 1.0f }, //3
		//Wing DX
		{ 0.8f, 0.5f, 0.0f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 1.0f, 1.0f }, //4
		{ 0.8f, 0.5f, 0.5f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 1.0f, 1.0f }, //5

		{ -0.5f, 0.5f, 0.5f, D3DXVECTOR3(0.0f, 1.0f, 1.0f), 0.5f, 1.0f }, //6
		{ -0.5f, 0.5f, 0.0f, D3DXVECTOR3(0.0f, 1.0f, 1.0f), 0.5f, 1.0f }, //7

		{ -0.8f, 0.5f, 0.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 1.0f, 1.0f }, //8
		{ -0.8f, 0.5f, 0.5f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 1.0f, 1.0f }, //9
	};

	// create the index buffer out of DWORDs
	DWORD PlaneIndices[] =
	{
		0, 1, 2,    // fuselage
		2, 1, 3,
		3, 1, 0,
		0, 2, 3,
		3, 2, 5,    // wing DX
		5, 4, 3,
		3, 0, 1,
		1, 0, 6,
		6, 0, 7,
		7, 8, 6,
		6, 8, 9,
	}; 

	_vbo = new VBO();
	_vbo->Create(renderer, PlaneVertices, PlaneIndices, 10, 36);
	return _vbo;

}

VBO* Mesh::CreateParticle(Renderer* renderer)
{
	// create a triangle using the VERTEX struct
	VERTEX ParticleVertices[] =
	{
		{ -1.0f, -1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.04, 0.4f },    // side 1
		{ 1.0f, -1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.4f, 0.4f },
		{ 0.0f, 1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.4f, 0.4f },
	//	{ 1.0f, 1.0f, 1.0f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 1.0f, 1.0f },
	};

	// create the index buffer out of DWORDs
	DWORD ParticleIndices[] =
	{
		0, 1, 2,       // side 1
	};

	_vbo = new VBO();
	_vbo->Create(renderer, ParticleVertices, ParticleIndices, 3, 3);
	return _vbo;
}

VBO* Mesh::CreateStation(Renderer* renderer)
{
	// create a triangle using the VERTEX struct
	VERTEX StationVertices[] =
	{
		{ -0.5f, -0.5f, 1.5f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.0f, 0.0f },    // side 1
		{ 0.5f, -0.5f, 1.5f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.0f, 1.0f },
		{ -0.5f, 0.5f, 1.5f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 1.0f, 0.0f },
		{ 0.5f, 0.5f, 1.5f, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 1.0f, 1.0f },

		{ -0.5f, -0.5f, -1.5f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.0f, 0.0f },    // side 2
		{ -0.5f, 0.5f, -1.5f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0.0f, 1.0f },
		{ 0.5f, -0.5f, -1.5f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 1.0f, 0.0f },
		{ 0.5f, 0.5f, -1.5f, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f },

		{ -0.5f, 0.5f, -1.5f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f },    // side 3
		{ -0.5f, 0.5f, 1.5f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.0f, 1.0f },
		{ 0.5f, 0.5f, -1.5f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 1.0f, 0.0f },
		{ 0.5f, 0.5f, 1.5f, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 1.0f, 1.0f },

		{ -0.5f, -0.5f, -1.5f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0.0f, 0.0f },    // side 4
		{ 0.5f, -0.5f, -1.5f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 1.0f, 0.0f },
		{ -0.5f, -0.5f, 1.5f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0.0f, 1.0f },
		{ 0.5f, -0.5f, 1.5f, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 1.0f, 1.0f },

		{ 0.5f, -0.5f, -1.5f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f },    // side 5
		{ 0.5f, 0.5f, -1.5f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.0f, 1.0f },
		{ 0.5f, -0.5f, 1.5f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 1.0f, 0.0f },
		{ 0.5f, 0.5f, 1.5f, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 1.0f, 1.0f },

		{ -0.5f, -0.5f, -1.5f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 1.0f, 1.0f },    // side 6
		{ -0.5f, -0.5f, 1.5f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0.0f, 1.0f },
		{ -0.5f, 0.5f, -1.5f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 1.0f, 0.0f },
		{ -0.5f, 0.5f, 1.5f, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0.0f, 0.0f },
	};

	// create the index buffer out of DWORDs
	DWORD StationIndices[] =
	{
		0, 1, 2,       // side 1
		2, 1, 3,
		4, 5, 6,	   // side 2
		6, 5, 7,
		8, 9, 10,	   // side 3
		10, 9, 11,
		12, 13, 14,    // side 4
		14, 13, 15,
		16, 17, 18,    // side 5
		18, 17, 19,
		20, 21, 22,    // side 6
		22, 21, 23,
	};

	_vbo = new VBO();
	_vbo->Create(renderer, StationVertices, StationIndices, 24, 36);
	return _vbo;
}

/* Alternate texture mapping
// fuselage
		{ 0.0f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 0.0f, 0.0f }, //0
		{ 0.0f, 0.0f, 1.5f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 0.0f, 1.0f }, //1
		{ 0.5f, 0.5f, 0.5f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0.0f }, //2
		{ 0.5f, 0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 1.0f, 1.0f }, //3
		//Wing DX
		{ 0.8f, 0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 0.0f, 0.0f }, //4
		{ 0.8f, 0.5f, 0.5f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 1.0f, 1.0f }, //5

		{ -0.5f, 0.5f, 0.5f, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f, 0.0f }, //6
		{ -0.5f, 0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 1.0f, 1.0f }, //7

		{ -0.8f, 0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 0.0f, 0.0f }, //8
		{ -0.8f, 0.5f, 0.5f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 1.0f, 1.0f }, //9*/

bool Mesh::AddVertex(VERTEX v)
{
	if (!_locked)
	{
		_vertices.push_back(v);
		return true;
	}
	else
	{
		return false;
	}
}

VBO* Mesh::CreateVBO(Renderer* renderer)
{
	_locked = true;

	_vbo = new VBO();

	_vbo->Create(renderer, _vertices.data(), NumVertices());

	return _vbo;
}