#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <string>
#include "Vertex.h"

using namespace std;

class Renderer;

class VBO
{
public:
	VBO();
	~VBO();

protected:
	ID3D11Buffer* _vbo;
	ID3D11Buffer* _vboi;
	int _numVertices;
	int _numIndexes;

	ID3D11Buffer *pCBuffer;                // the pointer to the constant buffer
	ID3D11ShaderResourceView *pTexture;    // the pointer to the texture

public:
	void Create(Renderer* renderer, VERTEX vertices[], DWORD indices[], int numVertices, int numIndexes);
	void Draw(Renderer* renderer, LPCWSTR tex);
	// overloads
	void Create(Renderer*, VERTEX vertices[], int numVertices);
	void Draw(Renderer* renderer);
};

