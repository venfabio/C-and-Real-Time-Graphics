#include "VBO.h"
#include "Renderer.h"

VBO::VBO()
{
	_vbo = NULL;
	_vboi = NULL;
}


VBO::~VBO()
{
	if (_vbo)
		_vbo->Release();
	if (_vboi)
		_vboi->Release();
}

void VBO::Create(Renderer* renderer, VERTEX vertices[], DWORD indices[], int numVertices, int numIndexes)
{
	_numVertices = numVertices;
	_numIndexes = numIndexes;
	
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX) * numVertices;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	renderer->GetDevice()->CreateBuffer(&bd, NULL, &_vbo);								// Create Vertex Buffer

	// copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	renderer->GetContext()->Map(_vbo, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);		// map the buffer
	memcpy(ms.pData, vertices, sizeof(VERTEX)*numVertices);									// copy the data
	renderer->GetContext()->Unmap(_vbo, NULL);											// unmap the buffer

	// create the index buffer
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(DWORD) * numIndexes;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	renderer->GetDevice()->CreateBuffer(&bd, NULL, &_vboi);								// Create Index Buffer

	renderer->GetContext()->Map(_vboi, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);		// map the buffer
	memcpy(ms.pData, indices, sizeof(DWORD)*numIndexes);										// copy the data
	renderer->GetContext()->Unmap(_vboi, NULL);											// unmap the buffer

	
}

void VBO::Draw(Renderer* renderer, LPCWSTR tex)
{
	D3DX11CreateShaderResourceViewFromFile(renderer->GetDevice(),        // the Direct3D device
		tex,			// load the texture in the local folder based on its name
		NULL,           // no additional information
		NULL,           // no multithreading
		&pTexture,      // address of the shader-resource-view
		NULL);          // no multithreading

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	renderer->GetContext()->IASetVertexBuffers(0, 1, &_vbo, &stride, &offset);
	renderer->GetContext()->IASetIndexBuffer(_vboi, DXGI_FORMAT_R32_UINT, 0);

	// select which primtive type we are using
	renderer->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw the Object
	renderer->GetContext()->UpdateSubresource(renderer->GetConstantBuffer(), 0, 0, &renderer->Get_cBuffer(), 0, 0);
	renderer->GetContext()->PSSetShaderResources(0, 1, &pTexture);
	renderer->GetContext()->DrawIndexed(_numIndexes, 0, 0);
}

// Overloads
void VBO::Create(Renderer* renderer, VERTEX vertices[], int numVertices)
{
	_numVertices = numVertices;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX) * numVertices;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	renderer->GetDevice()->CreateBuffer(&bd, NULL, &_vbo);								// Create Vertex Buffer

	// copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	renderer->GetContext()->Map(_vbo, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);		// map the buffer
	memcpy(ms.pData, vertices, sizeof(VERTEX)*numVertices);									// copy the data
	renderer->GetContext()->Unmap(_vbo, NULL);											// unmap the buffer
}

void VBO::Draw(Renderer* renderer)
{
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	renderer->GetContext()->IASetVertexBuffers(0, 1, &_vbo, &stride, &offset);

	// select which primtive type we are using
	renderer->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	// draw the Object
	//renderer->GetContext()->UpdateSubresource(renderer->GetConstantBuffer(), 0, 0, &renderer->Get_cBuffer(), 0, 0);
	//renderer->GetContext()->PSSetShaderResources(0, 1, &pTexture);
	renderer->GetContext()->Draw(_numVertices, 0);
}