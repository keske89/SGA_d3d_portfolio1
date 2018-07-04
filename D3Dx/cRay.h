#pragma once
class cRay
{
public:
	cRay();
	~cRay();

	D3DXVECTOR3 getPickRayDir();
	D3DXVECTOR3 getPickRayOrg();
};

