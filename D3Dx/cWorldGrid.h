#pragma once
#include "IDisplayObject.h"

class cWorldMapObj;
class cWMBorder;
class cWorldMapCar; //CAR ADDRESSLINK

class cWorldGrid : public IDisplayObject
{

	typedef ST_WM_PC_VERTEX VERTEX_TYPE_PC;
	typedef ST_WM_PNT_VERTEX VERTEX_TYPE_PNT;

private:

	LPDIRECT3DTEXTURE9 m_Texture; //TEXTURE FOR BOTTOM MESH
	
	vector<VERTEX_TYPE_PC> m_vertices; //GRID
	vector<VERTEX_TYPE_PNT> m_verticesPlane; //BOTTOM

	cWMBorder* m_Border; //BORDER

	cWorldMapCar* m_car; //ADDRESS LINK

public:
	cWorldGrid();
	virtual ~cWorldGrid();

	// IDisplayObject
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void setCar(cWorldMapCar* car) { m_car = car; }

	cWMBorder* getBorder() { return m_Border; }

};

