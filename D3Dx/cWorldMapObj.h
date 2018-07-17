#pragma once
#include "IDisplayObject.h"

class cObjLoader;

class cWorldMapObj : public IDisplayObject
{
	typedef ST_WM_PC_VERTEX VERTEX_TYPE;

private:

	LPDIRECT3DTEXTURE9	 m_Texture;
	LPD3DXMESH			 m_pMesh;

	CString			m_filePath;
	CString			m_fileName;
	CString			m_TextureName;

	
public:
	cWorldMapObj();
	virtual	~cWorldMapObj();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void SetFilename(LPCTSTR filepath, LPCTSTR filename, LPCTSTR texturename)
	{
		m_filePath = filepath; m_fileName = filename; m_TextureName = texturename;
	}
};

