#pragma once
#include "cWMDefinition.h"
#include "IDisplayObject.h"

class cWorldMapCar;

class cSphere : public IDisplayObject
{
private:
	LPD3DXMESH m_pMesh;
	BoundingSphere m_Bs;

	cWorldMapCar* m_pCar; //FOR ADDRESSLINK

public:
	cSphere();
	virtual ~cSphere();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	LPD3DXMESH CreateMesh();
	void collisionCheck();

	BoundingSphere getBS() { return m_Bs; }
	

	void SetCar(cWorldMapCar* car) { m_pCar = car; }
};

