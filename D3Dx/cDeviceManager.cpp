#include "stdafx.h"
#include "cDeviceManager.h"


cDeviceManager::cDeviceManager()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;


	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 stCaps;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);

	int nVertexProcessing;
	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = true;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = true;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		nVertexProcessing,
		&stD3DPP,
		&m_pD3DDevice);
}


cDeviceManager::~cDeviceManager()
{
}

LPDIRECT3DDEVICE9 cDeviceManager::GetDevice()
{
	return m_pD3DDevice;
}

void cDeviceManager::Destroy()
{
	m_pD3D->Release();
	ULONG ul = m_pD3DDevice->Release();
	assert(ul == 0 && "디바이스를 이용해 생성한 객체 중 해제되지 않은 객체가 있다!!");
}
