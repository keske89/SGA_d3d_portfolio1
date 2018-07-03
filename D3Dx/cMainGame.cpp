#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
<<<<<<< HEAD

#include "cTestScene3.h"
=======
#include "cTestScene0.h"
>>>>>>> 32e50b91153d5dfd75d33d1dc06af75a5d4cc272


cMainGame::cMainGame()
	: m_pCamera(NULL)

{
}


cMainGame::~cMainGame()
{
	delete m_pCamera;

	TIMEMANAGER->Destroy();
	SCENEMANAGER->Destroy();
	g_pFontManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	SetLight();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

<<<<<<< HEAD
	SCENEMANAGER->AddScene("TestScene3", new cTestScene3);

	SCENEMANAGER->ChangeScene("TestScene3");
=======
	SCENEMANAGER->AddScene("TestScene0", new cTestScene0);
	SCENEMANAGER->ChangeScene("TestScene0");
>>>>>>> 32e50b91153d5dfd75d33d1dc06af75a5d4cc272


	m_pCamera = new cCamera;
	m_pCamera->Setup();


}

void cMainGame::Update()
{
	m_pCamera->Update();
	SCENEMANAGER->Update();

}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	TIMEMANAGER->Render();
	SCENEMANAGER->Render();

	SCENEMANAGER->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	
}

void cMainGame::SetLight()
{
	D3DLIGHT9	stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);

	g_pD3DDevice->LightEnable(0, true);
}


