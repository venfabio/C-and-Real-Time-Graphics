#pragma once
#include <vector>
#include <string>
#include "VBO.h"
#include "Vertex.h"

using namespace std;

class Renderer;

class Mesh
{
	// Data
private:

	bool _locked;
	VBO*	_vbo;
	std::vector<VERTEX> _vertices;

public:
	Mesh();
	~Mesh();

	Mesh(const Mesh&) = delete;
	Mesh & operator=(const Mesh&) = delete;

public:
	VBO* CreateCube(Renderer* r);
	VBO* CreateCubeBig(Renderer* r);
	VBO* CreatePlane(Renderer* r);
	VBO* CreateParticle(Renderer* r);
	VBO* CreateStation(Renderer* r);
	VBO* CreateVBO(Renderer* r);
	bool AddVertex(VERTEX v);
	VBO* GetVBO()		const		{ return _vbo; }		// Exception to rule 9.1.3 from codingstandard.com
	int NumVertices()		const	{ return (int)_vertices.size(); }
};

