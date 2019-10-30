#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <DirectXMath.h>

#include "Mesh.h"

class GameObject
{
public:
	GameObject();
	~GameObject();		

protected:
	Mesh*		_mesh;		// Vertex info
	float		_scale;		// 1 = normal
	float		_angleX;
	float		_angleY;
	float		_angleZ;

	bool		isTransparent = false;
	bool		_alive;

	LPCWSTR	_texture_name;

	struct pos{
		float X;
		float Y;
		float Z;
	} _position;

public:
	Mesh* GetMesh()			const	{ return _mesh; }
	void SetMesh(Mesh* m)			{ _mesh = m; }

	float GetScale()		const	{ return _scale; }
	void SetScale(float v)			{ _scale = v; }

	LPCWSTR GetTexture()	const	{ return _texture_name; }
	void SetTexture(LPCWSTR	t)		{ _texture_name = t; }

public:

	bool GetTransparency()		const	{ return isTransparent; }
	void SetTransparency(bool t)			{ isTransparent = t; }

	float GetAngleX()		const	{ return _angleX; }
	void SetAngleX(float x)			{ _angleX = x; }
	float GetAngleY()		const	{ return _angleY; }
	void SetAngleY(float y)			{ _angleY = y; }
	float GetAngleZ()		const	{ return _angleZ; }
	void SetAngleZ(float z)			{ _angleZ = z; }

	float GetPosX()					    const	{ return _position.X; }
	float GetPosY()						const	{ return _position.Y; }
	float GetPosZ()						const	{ return _position.Z; }

	bool IsAlive()						const	{ return _alive; }
	void SetAlive(bool v)						{ _alive = v; }
	
	bool CollideWith(const GameObject* other);
};

